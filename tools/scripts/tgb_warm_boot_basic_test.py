import serial
import time
import os
import subprocess
import sys
import threading

TOTAL_RUNS = 100
BOOT_TIMEOUT_S = 70
BASIC_TEST_TIMEOUT_S = 100
BASIC_CMD_DELAY_S = 2
BASIC_CMD_CHAR_DELAY_S = 0.05
BASIC_PASS_STR = "CL0:[PASS] / CL1:[PASS] / CL2:[PASS] / CL3:[PASS]"

# Instruction: Install the PCIe hot reset script and configure password-less sudo access.
# 1. Copy the script to /usr/local/bin and make it executable.
#   sudo cp ~/rebel_cds_collab_hw/tools/scripts/pcie_hot_reset.sh /usr/local/bin/
#   sudo chmod +x /usr/local/bin/pcie_hot_reset.sh
# 2. Add a sudoers rule to allow execution without a password.
#   echo "ALL ALL=(ALL) NOPASSWD: /usr/local/bin/pcie_hot_reset.sh" \
#     | sudo tee /etc/sudoers.d/pcie_reset > /dev/null
#   sudo chmod 0440 /etc/sudoers.d/pcie_reset
pcie_reset_path = "/usr/local/bin/pcie_hot_reset.sh"
UART_BAUD = 115200
UART_DEVICES = [0, 1, 2, 3] # CL0=ttyUSB0, UART2/3/4=ttyUSB1,2,3
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

class Tee:
    def __init__(self, *streams):
        self._streams = streams
    def write(self, data):
        for s in self._streams:
            s.write(data)
            s.flush()
    def flush(self):
        for s in self._streams:
            if hasattr(s, "flush"):
                s.flush()

def uart_reader_thread(dev, baud, log_path, stop_event):
    ser = None
    try:
        ser = serial.Serial(
            port=dev, baudrate=baud,
            bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE, timeout=0.5,
            xonxoff=False, rtscts=False, dsrdtr=False
        )
        with open(log_path, "wb") as f:
            while not stop_event.is_set():
                if ser.in_waiting > 0:
                    data = ser.read(ser.in_waiting)
                    f.write(data)
                    f.flush()
                else:
                    time.sleep(0.01)
    except Exception as e:
        print(f"\n[Thread Error] {dev}: {e}")
    finally:
        if ser and ser.is_open:
            ser.close()

def start_uart_loggers(iter_num, results_dir, uart_threads_list, stop_event):
    uart_dir = os.path.join(results_dir, f"uart_{iter_num}")
    os.makedirs(uart_dir, exist_ok=True)
    stop_event.clear()
    uart_threads_list.clear()
    for n in UART_DEVICES[1:]:
        dev = f"/dev/ttyUSB{n}"
        if not os.path.exists(dev): continue
        log_path = os.path.join(uart_dir, f"run_{iter_num}_ttyUSB{n}.log")
        t = threading.Thread(target=uart_reader_thread, args=(dev, UART_BAUD, log_path, stop_event), daemon=True)
        t.start()
        uart_threads_list.append(t)

def stop_uart_loggers(stop_event, uart_threads_list):
    stop_event.set()
    for t in uart_threads_list:
        t.join(timeout=1.0)
    uart_threads_list.clear()

def run_evb_uart_power_cycle():
    boot_test_success = 0
    basic_test_success = 0
    trial = 0
    failed_list = []
    results_dir = os.path.join(SCRIPT_DIR, f"tgb_result_{time.strftime('%Y-%m-%d_%H-%M-%S')}")
    os.makedirs(results_dir, exist_ok=True)

    uart_threads = []
    uart_stop_event = threading.Event()
    cl0_port = f"/dev/ttyUSB{UART_DEVICES[0]}"

    try:
        with serial.Serial(cl0_port, UART_BAUD, timeout=0.1, xonxoff=False) as tty_cl0:
            print(f"Test start! Target: {cl0_port}, Total Run: {TOTAL_RUNS}\n")

            while trial < TOTAL_RUNS:
                trial += 1
                print(f"\n🔄 Test #{trial} " + "-"*60)

                start_uart_loggers(trial, results_dir, uart_threads, uart_stop_event)

                run_log_path = os.path.join(results_dir, f"run_{trial}.log")
                uart_dir = os.path.join(results_dir, f"uart_{trial}")
                cl0_log_path = os.path.join(uart_dir, f"run_{trial}_ttyUSB{UART_DEVICES[0]}.log")
                os.makedirs(uart_dir, exist_ok=True)

                with open(run_log_path, "w", encoding="utf-8") as run_log, \
                     open(cl0_log_path, "wb") as cl0_log:

                    old_stdout = sys.stdout
                    sys.stdout = Tee(old_stdout, run_log)

                    try:
                        tty_cl0.reset_input_buffer()
                        print(f"[{time.strftime('%H:%M:%S')}] Executing PCIe hot reset...")
                        if os.path.exists(pcie_reset_path):
                            subprocess.run(["sudo", pcie_reset_path, "01:00.0"], capture_output=True, timeout=30)

                        boot_test_ok = False
                        basic_test_ok = False
                        basic_test_started = False
                        basic_buf = ""

                        start_time = time.time()
                        max_wait = BOOT_TIMEOUT_S + BASIC_TEST_TIMEOUT_S

                        while (time.time() - start_time) < max_wait:
                            if tty_cl0.in_waiting > 0:
                                raw = tty_cl0.read(tty_cl0.in_waiting)
                                cl0_log.write(raw)
                                cl0_log.flush()

                                chunk = raw.decode('utf-8', errors='replace')
                                for line in chunk.splitlines():
                                    if line.strip(): print(f"[CL0] {line.strip()}")

                                if not boot_test_ok and "Start FreeRTOS scheduler" in chunk:
                                    boot_test_ok = True
                                    boot_test_success += 1
                                    print(f">>> Boot Detected! Wait {BASIC_CMD_DELAY_S}s then send command...")
                                    time.sleep(BASIC_CMD_DELAY_S)

                                    cmd = b"basic_test_all_chiplet all 1\r\n"
                                    for b in cmd:
                                        tty_cl0.write(bytes([b]))
                                        time.sleep(BASIC_CMD_CHAR_DELAY_S)
                                    tty_cl0.flush()
                                    basic_test_started = True

                                if basic_test_started and not basic_test_ok:
                                    basic_buf += chunk
                                    if BASIC_PASS_STR in basic_buf:
                                        basic_test_ok = True
                                        basic_test_success += 1
                                        print(">>> Basic Test All Chiplet: PASS")
                                        break

                            time.sleep(0.01)

                        boot_res = "PASS" if boot_test_ok else "FAIL"
                        basic_res = "PASS" if basic_test_ok else ("SKIP" if not boot_test_ok else "FAIL")
                        if not (boot_test_ok and basic_test_ok):
                            failed_list.append(trial)

                        print(f"\n✅ Trial #{trial} Result Summary:")
                        print(f"   Boot Test:  [{boot_res}]")
                        print(f"   Basic Test: [{basic_res}]")

                    finally:
                        sys.stdout.flush()
                        sys.stdout = old_stdout
                        stop_uart_loggers(uart_stop_event, uart_threads)

                time.sleep(2)

    except KeyboardInterrupt:
        print("\n[!] Test interrupted by user.")
    except Exception as e:
        print(f"\n[!] Unexpected Error: {e}")
    finally:
        stop_uart_loggers(uart_stop_event, uart_threads)

    summary = [
        "\n" + "="*40,
        "🏁 FINAL TEST REPORT",
        "="*40,
        f"Total Iterations: {trial}",
        f"Boot Success:    {boot_test_success}/{trial}",
        f"Basic Success:   {basic_test_success}/{trial}",
        f"Failed Runs:     {', '.join(map(str, failed_list)) if failed_list else 'None'}",
        f"Results Dir:     {results_dir}",
        "="*40
    ]
    for line in summary: print(line)

    with open(os.path.join(results_dir, "summary.txt"), "w") as f:
        f.write("\n".join(summary))

if __name__ == "__main__":
    run_evb_uart_power_cycle()
