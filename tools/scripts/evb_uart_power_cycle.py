import serial
import time
import os

TOTAL_RUNS = 100
BOOT_TIMEOUT_S = 70

CL0_TTY_PORT = "/dev/ttyUSB13"
CL0_TTY_BAUDRATE = 115200

EVB_CTRL_TTY_PORT = "/dev/ttyACM0"
EVB_CTRL_TTY_BAUDRATE = 460800

def run_evb_uart_power_cycle():

    success = 0
    try:
        with serial.Serial(CL0_TTY_PORT, CL0_TTY_BAUDRATE, timeout=1) as tty_cl0, \
             serial.Serial(EVB_CTRL_TTY_PORT, EVB_CTRL_TTY_BAUDRATE, timeout=1) as tty_ctrl:

             print(f"\nTest start! Total Run = {TOTAL_RUNS}\n")

             trial = 0
             while trial < TOTAL_RUNS:
                trial += 1
                print(f"\n🔄 Test #{trial}")
                print("-" * 80)
                tty_cl0.reset_input_buffer()

                # PSU_OFF
                tty_ctrl.write(b"p")
                time.sleep(0.05)
                tty_ctrl.write(b"s")
                time.sleep(0.05)
                tty_ctrl.write(b"u")
                time.sleep(0.05)
                tty_ctrl.write(b"_")
                time.sleep(0.05)
                tty_ctrl.write(b"o")
                time.sleep(0.05)
                tty_ctrl.write(b"f")
                time.sleep(0.05)
                tty_ctrl.write(b"f")
                time.sleep(0.05)
                tty_ctrl.write(b"\n")
                time.sleep(0.05)
                tty_ctrl.flush()
                time.sleep(1)
                # PSU_ON
                tty_ctrl.write(b"p")
                time.sleep(0.05)
                tty_ctrl.write(b"s")
                time.sleep(0.05)
                tty_ctrl.write(b"u")
                time.sleep(0.05)
                tty_ctrl.write(b"_")
                time.sleep(0.05)
                tty_ctrl.write(b"o")
                time.sleep(0.05)
                tty_ctrl.write(b"n")
                time.sleep(0.05)
                tty_ctrl.write(b"\n")
                time.sleep(0.05)
                tty_ctrl.flush()

                is_success = False
                start_time = time.time()

                while (time.time() - start_time) < BOOT_TIMEOUT_S:
                    if tty_cl0.in_waiting > 0:
                        line = tty_cl0.readline().decode('utf-8', errors='replace').strip()
                        if line:
                            print(f"[Log] {line}")

                        if "Start FreeRTOS scheduler" in line:
                            is_success = True
                            success += 1
                            break

                    time.sleep(0.05)

                if is_success:
                    print(f"\n✅ Success! {success}/{trial}")
                else:
                    print("\n❌ Fail!")
                print("-" * 80)
                print("\n")

                time.sleep(1)
    except serial.SerialException as e:
        print(f"Serial Port Error {e}")
    except KeyboardInterrupt:
        print(f"Test interrupted by user")

    print(f"🏁 Test Session Finished. Total Success {success}/{trial}")

if __name__ == "__main__":
    run_evb_uart_power_cycle()