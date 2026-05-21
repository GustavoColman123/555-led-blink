# Firmware

This folder contains the firmware for the Embedded Desk Terminal v0.

The firmware is written in C using the Raspberry Pi Pico SDK.

## Files

| File | Purpose |
|---|---|
| `blink.c` | Main firmware logic |
| `lcd_i2c.c` | LCD1602 I2C driver implementation |
| `lcd_i2c.h` | LCD1602 I2C driver header |
| `CMakeLists.txt` | CMake build configuration |

## Firmware Features

The firmware implements:

- GPIO output for LED control
- GPIO input for push button reading
- Internal pull-up resistor for the button
- I2C communication with the LCD1602 display
- PWM signal generation for the SG90 servo
- Button debounce logic
- Finite state machine with four states

## System States

The firmware cycles through these states:

```text
IDLE -> FOCUS -> BREAK -> ALERT -> IDLE
```

Each button press advances to the next state.

## Pin Configuration

| Function | Raspberry Pi Pico Pin |
|---|---|
| LCD SDA | GP4 |
| LCD SCL | GP5 |
| LED | GP10 |
| Servo PWM signal | GP15 |
| Push button | GP16 |

## Build Requirements

To build this firmware, the Raspberry Pi Pico SDK must be installed.

The project also requires:

- CMake
- ARM GCC toolchain
- Raspberry Pi Pico SDK
- `pico_sdk_import.cmake`

## Important Note About `pico_sdk_import.cmake`

The file `pico_sdk_import.cmake` is required by `CMakeLists.txt`.

If it is not already inside this firmware folder, it can be copied from the Pico SDK:

```bash
cp /home/gustavo/embedded/pico-sdk/external/pico_sdk_import.cmake .
```

This command should be executed from inside the `firmware/` directory.

## Build Instructions

From this folder:

```bash
mkdir build
cd build
cmake ..
make
```

If the build is successful, CMake will generate a `.uf2` file.

Expected output file:

```text
blink.uf2
```

## Uploading to the Raspberry Pi Pico

1. Hold the `BOOTSEL` button on the Raspberry Pi Pico.
2. Connect the Pico to the computer through USB.
3. Release `BOOTSEL`.
4. The Pico should appear as a USB storage device named:

```text
RPI-RP2
```

5. Copy the `.uf2` file:

```bash
cp blink.uf2 /media/gustavo/RPI-RP2/
```

After copying, the Pico will reboot automatically and run the firmware.

## Expected Behavior

When powered on, the system starts in:

```text
STATUS: IDLE
```

Each button press changes the state:

```text
IDLE -> FOCUS -> BREAK -> ALERT -> IDLE
```

The LCD, LED, and servo change behavior depending on the current state.

## Notes

This firmware was developed as part of my first documented Raspberry Pi Pico project.

The goal was not only to make the system work, but to understand how GPIO, I2C, PWM, debounce logic, and state machines work together in an embedded system.
