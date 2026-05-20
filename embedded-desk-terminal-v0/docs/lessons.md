# Lessons Learned

## Overview

This document summarizes the main lessons learned while building the Embedded Desk Terminal v0.

This was my first documented Raspberry Pi Pico project. The goal was not only to make the circuit work, but to understand the relationship between firmware, hardware, wiring, debugging, and documentation.

---

## Lesson 1: Embedded Systems Are Hardware and Software Together

One of the most important lessons from this project is that embedded systems are not only about writing code.

The firmware can be correct, but the system will still fail if:

- A wire is connected to the wrong pin
- GND is missing
- The LED is reversed
- The button is wired incorrectly
- The LCD contrast is not adjusted
- The wrong `.uf2` file is uploaded

This project showed me that embedded development requires thinking about both software and physical electronics at the same time.

---

## Lesson 2: GPIO Output Needs a Complete Circuit

Controlling an LED from a GPIO pin is simple, but it still requires a correct electrical path.

The correct LED path was:

```text
GP10 -> resistor -> LED anode
LED cathode -> GND
```

The resistor is necessary because it limits current.

Without the resistor, the LED or the microcontroller pin could be damaged.

This helped me understand that a GPIO pin is not just an abstract software output. It is a real electrical connection.

---

## Lesson 3: GPIO Input Needs a Defined State

The push button was connected between GP16 and GND.

The Pico internal pull-up resistor was used:

```c
gpio_pull_up(BUTTON_PIN);
```

This means:

```text
Button not pressed -> GPIO reads HIGH
Button pressed     -> GPIO reads LOW
```

This is called active-low logic.

The important lesson is that input pins should not be left floating. They need a defined default state.

---

## Lesson 4: Four-Pin Buttons Can Be Confusing

A four-pin tactile button is not as obvious as it looks.

Two pins on the same side are usually already connected internally.

The correct method is to use opposite sides of the button:

```text
GP16 -> button -> GND
```

This helped me understand why physical component layout matters.

A circuit can look correct but still fail if the component is placed incorrectly on the breadboard.

---

## Lesson 5: I2C Reduces Wiring Complexity

The LCD1602 display used an I2C backpack module.

Instead of using many parallel data pins, the display only needed:

```text
SDA
SCL
VCC
GND
```

The Pico pins used were:

```text
SDA -> GP4
SCL -> GP5
```

This showed me why communication protocols are useful in embedded systems.

I2C allows multiple devices to communicate using only two signal lines, which makes wiring cleaner and saves GPIO pins.

---

## Lesson 6: LCD Problems Are Not Always Code Problems

At first, the LCD backlight worked, but the text was not visible.

The issue was solved by adjusting the contrast potentiometer on the I2C module.

This taught me an important debugging rule:

```text
A visible hardware symptom does not always mean the firmware is wrong.
```

Sometimes the problem is electrical, mechanical, or configuration-related.

---

## Lesson 7: PWM Controls Servo Position

The SG90 servo was controlled using PWM from GP15.

The firmware generated a 50 Hz PWM signal.

The pulse width determined the servo position:

```text
Around 1000 us -> one side
Around 1500 us -> center
Around 2000 us -> other side
```

This helped me understand that PWM is not just “analog output”. It is a timed digital signal used to control devices.

---

## Lesson 8: Motors and Servos Need Power Attention

The SG90 servo worked from VBUS during the prototype.

However, servos can draw more current than LEDs or logic components.

A servo can cause problems such as:

- Jitter
- Voltage drops
- Pico resets
- USB disconnection
- LCD flickering

The main lesson is that moving parts require more careful power planning.

For future projects, a separate 5V supply may be better for motors or servos, while keeping a common GND with the Pico.

---

## Lesson 9: Debounce Is Necessary for Mechanical Buttons

Mechanical buttons do not always produce one clean signal.

When pressed, the contacts can bounce electrically, causing the microcontroller to detect multiple presses.

The project used debounce logic:

```c
#define DEBOUNCE_MS 200
```

This made each physical press count as only one state transition.

This helped me understand that real-world inputs are imperfect and firmware must handle that.

---

## Lesson 10: A State Machine Makes Firmware Cleaner

The final firmware used a finite state machine with four states:

```text
IDLE
FOCUS
BREAK
ALERT
```

Each state controlled:

- LCD message
- LED behavior
- Servo position

This made the firmware easier to understand and extend.

Instead of writing disconnected conditions, the state machine gave the system a clear structure.

---

## Lesson 11: C Makes the Hardware Feel Real

Using C made the project harder than using a higher-level environment, but it also made the learning deeper.

With C, I had to think about:

- Pin initialization
- GPIO direction
- Pull-up resistors
- PWM configuration
- I2C communication
- Build system configuration
- Header files and source files
- Compilation and linking

This helped me understand what happens under the hood.

For embedded systems, C is powerful because it gives direct control over hardware while still being structured enough to build real firmware.

---

## Lesson 12: The Build System Is Part of the Project

CMake and the Pico SDK were part of the learning process.

I had to understand the role of:

```text
CMakeLists.txt
pico_sdk_import.cmake
build/
.uf2 output files
```

This taught me that embedded development is not only about writing C code.

The build system, file organization, and upload process are also part of the engineering workflow.

---

## Lesson 13: Documentation Makes the Project More Valuable

The same circuit becomes more valuable when it is documented properly.

This project includes:

- README
- Wiring notes
- System design
- State machine explanation
- Problems encountered
- Lessons learned
- Firmware source code
- Photos

Documentation turns a simple prototype into a learning artifact.

It shows not only the final result, but also the process used to build it.

---

## Final Reflection

This project was small, but it combined several important embedded systems concepts:

- GPIO output
- GPIO input
- Pull-up resistors
- I2C
- PWM
- Debounce
- State machines
- Hardware debugging
- C firmware
- GitHub documentation

The most important lesson is that even a small embedded system requires careful thinking.

A good project is not measured only by complexity. It is measured by how clearly it is designed, tested, debugged, and documented.
