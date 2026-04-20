import os
import subprocess
import sys
import time
import serial

# Default iteration count (same as run_all_iter.sh)
ITERATIONS = 100
BOOT_TIMEOUT_S = 70
BASIC_TEST_TIMEOUT_S = 100
BASIC_CMD_DELAY_S = 2  # Wait for output after sending basic_test_all_chiplet
BASIC_CMD_CHAR_DELAY_S = 0.05
BASIC_PASS_STR = "CL0:[PASS] / CL1:[PASS] / CL2:[PASS] / CL3:[PASS]"

# UART capture: baudrate and device numbers (set per PC: 0 1 2 3 or e.g. 1 2 3 4).
UART_BAUD = 115200
UART_DEVICES = [13, 8, 4, 1]
# tty_cl0 = first UART device (/dev/ttyUSB{UART_DEVICES[0]}) for command tx/rx.

EVB_CTRL_TTY_PORT = "/dev/ttyACM0"
EVB_CTRL_TTY_BAUDRATE = 115200

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))


class Tee:
    """Write to multiple streams (e.g. stdout and run_N.log)."""

    def __init__(self, *streams):
        self._streams = streams

    def write(self, data):
        for s in self._streams:
            s.write(data)
            s.flush()

    def flush(self):
        for s in self._streams:
            s.flush()


def start_uart_loggers(iter_num, results_dir, uart_procs_list):
    """Start capturing UART logs from /dev/ttyUSB{n} for current iteration. Skip first device (tty_cl0)."""
    uart_dir = os.path.join(results_dir, f"uart_{iter_num}")
    os.makedirs(uart_dir, exist_ok=True)
    uart_procs_list.clear()
    for n in UART_DEVICES[1:]:
        dev = f"/dev/ttyUSB{n}"
        if not os.path.exists(dev):
            continue
        try:
            subprocess.run(
                ["stty", "-F", dev, str(UART_BAUD), "raw", "-echo"],
                capture_output=True,
                timeout=2,
            )
        except (FileNotFoundError, subprocess.TimeoutExpired, OSError):
            pass
        log_path = os.path.join(uart_dir, f"run_{iter_num}_ttyUSB{n}.log")
        log_file = None
        try:
            log_file = open(log_path, "wb")
            proc = subprocess.Popen(
                ["stdbuf", "-o0", "cat", dev],
                stdin=subprocess.DEVNULL,
                stdout=log_file,
                stderr=subprocess.DEVNULL,
            )
            uart_procs_list.append((proc, log_file))
        except (FileNotFoundError, OSError):
            if log_file is not None:
                log_file.close()


def stop_uart_loggers(uart_procs_list):
    """Stop UART logger processes (same as run_all_iter.sh)."""
    for proc, log_file in uart_procs_list:
        try:
            proc.terminate()
            proc.wait(timeout=2)
        except (OSError, subprocess.TimeoutExpired):
            try:
                proc.kill()
            except OSError:
                pass
        try:
            log_file.close()
        except OSError:
            pass
    uart_procs_list.clear()


def run_evb_uart_power_cycle():

    boot_test_success = 0
    basic_test_success = 0
    trial = 0
    failed_list = []
    results_dir = None
    uart_logger_procs = []

    try:
        # Same as run_all_iter.sh: create results dir run_results_<timestamp>
        results_dir = os.path.join(SCRIPT_DIR, f"evb_results_{time.strftime('%Y-%m-%d_%H-%M-%S')}")
        os.makedirs(results_dir, exist_ok=True)

        cl0_port = f"/dev/ttyUSB{UART_DEVICES[0]}"
        with serial.Serial(cl0_port, UART_BAUD, timeout=1) as tty_cl0, \
             serial.Serial(EVB_CTRL_TTY_PORT, EVB_CTRL_TTY_BAUDRATE, timeout=1) as tty_ctrl:

             print(f"\nTest start! Iterations = {ITERATIONS}\n")

             while trial < ITERATIONS:
                trial += 1
                print(f"\n🔄 Test #{trial}")
                print("-" * 80)

                # Start UART loggers for this iteration (skip first device = tty_cl0)
                start_uart_loggers(trial, results_dir, uart_logger_procs)

                # run_{trial}.log: tee stdout for this iteration (same as run_all_iter.sh run_${i}.log)
                run_log_path = os.path.join(results_dir, f"run_{trial}.log")
                run_log = open(run_log_path, "w", encoding="utf-8")
                old_stdout = sys.stdout
                sys.stdout = Tee(old_stdout, run_log)
                try:
                    # Log file for tty_cl0 (first UART device); others are captured by start_uart_loggers
                    uart_dir = os.path.join(results_dir, f"uart_{trial}")
                    cl0_log_path = os.path.join(uart_dir, f"run_{trial}_ttyUSB{UART_DEVICES[0]}.log")
                    cl0_log = open(cl0_log_path, "wb")
                    try:
                        tty_cl0.reset_input_buffer()

                        # PSU_OFF
                        cmd_psu_off = b"psu_off\n"
                        for b in cmd_psu_off:
                            tty_ctrl.write(bytes([b]))
                            time.sleep(BASIC_CMD_CHAR_DELAY_S)
                        tty_ctrl.flush()
                        time.sleep(3)
                        # PSU_ON
                        cmd_psu_on = b"psu_on\n"
                        for b in cmd_psu_on:
                            tty_ctrl.write(bytes([b]))
                            time.sleep(BASIC_CMD_CHAR_DELAY_S)
                        tty_ctrl.flush()

                        boot_test_ok = False
                        start_time = time.time()

                        while (time.time() - start_time) < BOOT_TIMEOUT_S:
                            if tty_cl0.in_waiting > 0:
                                raw = tty_cl0.readline()
                                cl0_log.write(raw)
                                cl0_log.flush()
                                line = raw.decode('utf-8', errors='replace').strip()
                                if line:
                                    print(f"[Log] {line}")

                                if "Start FreeRTOS scheduler" in line:
                                    boot_test_ok = True
                                    boot_test_success += 1
                                    break

                            time.sleep(0.05)

                        basic_test_ok = False
                        if boot_test_ok:
                            time.sleep(1)
                            cmd = b"basic_test_all_chiplet all 1\r\n"
                            for b in cmd:
                                tty_cl0.write(bytes([b]))
                                time.sleep(BASIC_CMD_CHAR_DELAY_S)
                            tty_cl0.flush()
                            time.sleep(BASIC_CMD_DELAY_S)  # Wait for command processing and output to start
                            basic_start = time.time()
                            basic_buf = ""
                            while (time.time() - basic_start) < BASIC_TEST_TIMEOUT_S:
                                if tty_cl0.in_waiting > 0:
                                    raw_chunk = tty_cl0.read(tty_cl0.in_waiting)
                                    cl0_log.write(raw_chunk)
                                    cl0_log.flush()
                                    chunk = raw_chunk.decode('utf-8', errors='replace')
                                    basic_buf += chunk
                                    while "\n" in basic_buf or "\r" in basic_buf:
                                        sep = "\n" if "\n" in basic_buf else "\r"
                                        idx = basic_buf.index(sep)
                                        line = basic_buf[:idx].strip()
                                        basic_buf = basic_buf[idx + 1 :].lstrip("\r\n")
                                        if line:
                                            print(f"[Log] {line}")
                                        if BASIC_PASS_STR in line:
                                            basic_test_ok = True
                                            basic_test_success += 1
                                            break
                                    if not basic_test_ok and BASIC_PASS_STR in basic_buf:
                                        basic_test_ok = True
                                        basic_test_success += 1
                                    if basic_test_ok:
                                        break
                                time.sleep(0.05)

                        boot_result = "PASS" if boot_test_ok else "FAIL"
                        basic_result = "PASS" if basic_test_ok else ("SKIP" if not boot_test_ok else "FAIL")
                        if not boot_test_ok or not basic_test_ok:
                            failed_list.append(trial)
                        print(f"\n✅ boot_test:  [{boot_result}]  ({boot_test_success}/{trial})")
                        print(f"✅ basic_all_test:  [{basic_result}]  ({basic_test_success}/{trial})")
                        print("-" * 80)
                        print("\n")

                    finally:
                        cl0_log.close()
                        # Stop UART loggers
                        stop_uart_loggers(uart_logger_procs)
                finally:
                    sys.stdout = old_stdout
                    run_log.close()

                time.sleep(1)
    except serial.SerialException as e:
        print(f"Serial Port Error {e}")
    except KeyboardInterrupt:
        print("Test interrupted by user")
    finally:
        stop_uart_loggers(uart_logger_procs)

    # Print summary in same order/format as run_all_iter.sh and save summary.txt
    summary_lines = [
        "",
        "🏁 Test Session Finished.",
        f"boot_test PASSED: {boot_test_success} / {trial}",
        f"basic_all_test PASSED: {basic_test_success} / {trial}",
        "",
        "==========================================",
        "All runs complete. Result summary",
        "==========================================",
    ]
    if not failed_list:
        summary_lines.append("Failed iterations: none")
    else:
        failed_str = ", ".join(map(str, failed_list))
        summary_lines.append(f"Failed iterations: {failed_str}")
        if results_dir:
            summary_lines.append(f"(Details: {results_dir}/uart_<N>/)")
    summary_lines.extend(["", "Result log directory: " + (results_dir or ""), "End."])

    for line in summary_lines:
        print(line)

    if results_dir:
        summary_file = os.path.join(results_dir, "summary.txt")
        with open(summary_file, "w", encoding="utf-8") as f:
            f.write("\n".join(summary_lines) + "\n")
        print("")
        print(f"Summary saved: {summary_file}")


if __name__ == "__main__":
    run_evb_uart_power_cycle()
