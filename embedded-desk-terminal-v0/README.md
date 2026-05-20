# Embedded Desk Terminal v0

This is my first documented Raspberry Pi Pico project.

The goal of this project was to build a small embedded system using a Raspberry Pi Pico, an LCD1602 I2C display, a push button, an LED, and an SG90 micro servo.

This project is not meant to be a finished commercial product. It is a functional prototype built to understand the fundamentals of embedded systems through real wiring, firmware, debugging, and documentation.

## Overview

The Embedded Desk Terminal v0 is a small interactive device with four system states:

- IDLE
- FOCUS
- BREAK
- ALERT

Each state changes the behavior of the system:

- The LCD shows the current mode.
- The LED changes its behavior depending on the state.
- The servo moves to a different position.
- A push button is used to cycle through the states.

## Main Features

- GPIO output control for an LED
- GPIO input reading using an internal pull-up resistor
- I2C communication with an LCD1602 display
- PWM control for an SG90 servo
- Button debounce logic
- Finite state machine implemented in C
- Breadboard prototype before soldering

## Hardware Used

- Raspberry Pi Pico
- LCD1602 display with I2C module
- SG90 micro servo
- Push button
- LED
- Resistor for the LED
- Breadboard
- Jumper wires
- 22 AWG wires
- Multimeter

## Pinout

| Component | Pico Pin |
|---|---|
| LCD SDA | GP4 |
| LCD SCL | GP5 |
| LED | GP10 |
| Servo signal | GP15 |
| Push button | GP16 |
| LCD VCC | 3V3 |
| Servo VCC | VBUS |
| Common ground | GND |

## System States

| State | LCD Message | LED Behavior | Servo Position |
|---|---|---|---|
| IDLE | STATUS: IDLE | OFF | Center |
| FOCUS | MODE: FOCUS | ON | Left position |
| BREAK | MODE: BREAK | Slow blink | Right position |
| ALERT | MODE: ALERT | Fast blink | Alert position |

## Why did I use C in this project?

I used C because it is a powerful language for embedded systems.

C is more difficult than using a high-level environment, but that difficulty is useful. It forces me to understand what is really happening under the hood: GPIO configuration, timing, PWM signals, I2C communication, memory, compilation, and the relationship between software and hardware.

For this project, using C helped me understand the Raspberry Pi Pico as a real microcontroller, not just as a board running simple scripts.

## What I Learned

Through this project, I learned how to:

- Configure GPIO pins as inputs and outputs
- Use an internal pull-up resistor for a button
- Control an LED from firmware
- Generate PWM signals for a servo
- Communicate with an LCD using I2C
- Implement basic debounce logic
- Build a finite state machine
- Debug hardware and software together

## Project Status

Current status: functional prototype completed on breadboard.

Next steps:

- Design a cleaner perfboard layout
- Solder the circuit permanently
- Improve cable management
- Add photos and wiring diagrams
- Document problems and lessons learned
