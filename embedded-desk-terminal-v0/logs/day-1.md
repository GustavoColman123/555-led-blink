# Day 1 - First Functional Prototype

## Project

Embedded Desk Terminal v0

## Goal of the Day

The goal of this session was to build the first functional prototype of the Embedded Desk Terminal v0 using a Raspberry Pi Pico.

The prototype had to integrate:

- LED output
- Push button input
- LCD1602 I2C display
- SG90 servo
- Firmware written in C using the Raspberry Pi Pico SDK

The main objective was not only to make the components work individually, but to combine them into one small embedded system.

---

## Phase 1 - LED Test

### Goal

Verify that the Raspberry Pi Pico could control an external LED using GPIO output.

### Wiring

```text
GP10 -> resistor -> LED anode
LED cathode -> GND
```

### Result

The LED blinked successfully.

### What This Confirmed

- The Pico SDK toolchain worked.
- The `.uf2` file was generated correctly.
- The Pico could be programmed through BOOTSEL mode.
- GP10 worked as a digital output.
- The LED circuit was wired correctly.

### Notes

This was the first basic hardware test. Even though blinking an LED is simple, it confirmed that the development environment and physical wiring were working.

---

## Phase 2 - Servo PWM Test

### Goal

Control an SG90 micro servo using PWM from the Raspberry Pi Pico.

### Wiring

```text
Servo signal -> GP15
Servo VCC    -> VBUS
Servo GND    -> GND
```

### Result

The servo moved correctly between different positions.

### What This Confirmed

- PWM output worked on GP15.
- The SG90 servo responded correctly to pulse width changes.
- VBUS was sufficient for this basic prototype test.
- The Pico and servo shared a correct common ground.

### Notes

The servo moved successfully without resetting the Pico or disconnecting the USB connection.

---

## Phase 3 - LCD1602 I2C Test

### Goal

Display text on the LCD1602 using I2C communication.

### Wiring

```text
LCD GND -> GND
LCD VCC -> 3V3
LCD SDA -> GP4
LCD SCL -> GP5
```

### Test Message

```text
EMBEDDED TERM
LCD OK
```

### Result

The LCD successfully displayed the expected message.

### What This Confirmed

- I2C communication worked.
- GP4 worked as SDA.
- GP5 worked as SCL.
- The LCD I2C address `0x27` was correct.
- The LCD driver code worked.
- The contrast potentiometer was adjusted correctly.

### Notes

The LCD backlight turned on before the text was clearly visible. The contrast potentiometer had to be adjusted to make the characters readable.

---

## Phase 4 - Push Button Input Test

### Goal

Read a tactile push button using GPIO input and the Pico internal pull-up resistor.

### Wiring

```text
GP16 -> push button -> GND
```

### Logic

```text
Button not pressed -> GPIO reads HIGH
Button pressed     -> GPIO reads LOW
```

### Result

The button was successfully detected by the firmware.

### What This Confirmed

- GP16 worked as a digital input.
- The internal pull-up resistor worked.
- Active-low button logic worked.
- The tactile button was wired correctly after understanding its four-pin layout.

### Notes

The tactile push button had to be placed correctly across the breadboard center gap. Using the wrong pair of legs can make the button behave incorrectly.

---

## Phase 5 - LCD + Button + LED Integration

### Goal

Combine the LCD, button, and LED in one firmware test.

### Expected Behavior

```text
Button not pressed -> LCD shows READY, LED off
Button pressed     -> LCD shows PRESSED, LED on
```

### Result

The system worked correctly.

### What This Confirmed

- GPIO input and output could work together.
- The LCD could be updated based on button input.
- The firmware could react to physical input and update physical outputs.

### Notes

This was the first integration test. At this point, the project stopped being separate component tests and became a small interactive embedded system.

---

## Phase 6 - Full Integration with Servo

### Goal

Add the SG90 servo to the existing LCD + button + LED prototype.

### Expected Behavior

```text
READY   -> LCD shows READY, LED off, servo centered
PRESSED -> LCD shows PRESSED, LED on, servo moves
```

### Result

The system worked correctly.

When the button was pressed:

- The LCD changed message.
- The LED turned on.
- The servo moved.

When the button was released:

- The LCD returned to the ready state.
- The LED turned off.
- The servo returned to its original position.

### What This Confirmed

- GPIO input worked together with GPIO output.
- I2C LCD communication continued working with the other components connected.
- PWM servo control worked in the integrated system.
- The Pico could coordinate multiple hardware modules at the same time.

---

## Phase 7 - Finite State Machine

### Goal

Replace the simple pressed/released behavior with a real state machine.

### States

```text
IDLE
FOCUS
BREAK
ALERT
```

### Transition Order

```text
IDLE -> FOCUS -> BREAK -> ALERT -> IDLE
```

### Expected Behavior

Each button press advances the system to the next state.

The state controls:

- LCD message
- LED behavior
- Servo position

### Result

The state machine worked correctly.

### What This Confirmed

- The firmware could store and update system state.
- A single button could control multiple modes.
- The system no longer required the button to be held down.
- Edge detection and debounce logic worked.

---

## Phase 8 - Final Firmware Behavior

### Goal

Improve the firmware behavior and make the prototype more presentable.

### Final State Behavior

| State | LCD Message | LED Behavior | Servo Behavior |
|---|---|---|---|
| IDLE | STATUS: IDLE | Off | Center |
| FOCUS | MODE: FOCUS | On | Left position |
| BREAK | MODE: BREAK | Slow blink | Right position |
| ALERT | MODE: ALERT | Fast blink | Alert position |

### Result

The final firmware worked correctly.

### What This Confirmed

- The system had a clear user interaction model.
- The LED pattern changed depending on the current state.
- The servo position changed depending on the current state.
- The LCD displayed the correct state message.
- The button cycled through all modes reliably.

---

## Main Problems Encountered

The main problems during this session were:

- Confusion between the source folder and the `build/` folder.
- Missing `pico_sdk_import.cmake`.
- Confusion between `main.c`, `blink.c`, `main.uf2`, and `blink.uf2`.
- Linker error: `undefined reference to main`.
- Difficulty understanding the LED wiring path from GP10 to GND.
- Difficulty understanding the four-pin tactile button.
- LCD text visibility until contrast was adjusted.
- GitHub authentication problem when using `git push`.

These problems were solved one by one through testing, rewiring, code correction, and documentation.

---

## Final Result of the Day

By the end of the session, the project had a functional breadboard prototype.

The prototype successfully integrated:

- Raspberry Pi Pico
- LCD1602 I2C display
- Push button
- LED
- SG90 servo
- C firmware
- PWM
- I2C
- GPIO input/output
- Debounce
- Finite state machine

The project is now ready for documentation, photos, and later perfboard planning.

---

## Reflection

This was my first documented Raspberry Pi Pico project.

The most important lesson was that even a small embedded system requires careful thinking about code, wiring, timing, power, and debugging.

The project started with a simple LED test and evolved into a complete small embedded prototype with multiple states and hardware outputs.

This makes the project a useful foundation for future embedded systems work.
