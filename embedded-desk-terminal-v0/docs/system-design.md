# System Design

## Overview

The Embedded Desk Terminal v0 is a small embedded system built around a Raspberry Pi Pico.

The system combines four main hardware functions:

- Digital output: LED
- Digital input: push button
- I2C communication: LCD1602 display
- PWM output: SG90 micro servo

The purpose of the project is to understand how a microcontroller can coordinate multiple hardware components through firmware written in C.

## System Architecture

The Raspberry Pi Pico acts as the central controller.

It reads the push button, updates the current system state, controls the LED behavior, writes messages to the LCD, and sends PWM signals to the servo.

```text
                +----------------------+
                |  Raspberry Pi Pico   |
                |                      |
Button -------> | GPIO Input GP16      |
LED <---------- | GPIO Output GP10     |
LCD <---------> | I2C GP4 / GP5        |
Servo <-------- | PWM GP15             |
                +----------------------+
```

## Hardware Modules
Raspberry Pi Pico

The Raspberry Pi Pico is the main controller of the system.

It is responsible for:

Reading the push button
Controlling the LED
Communicating with the LCD through I2C
Generating PWM signals for the servo
Running the finite state machine
LCD1602 I2C Display

The LCD is used to show the current state of the system.

It communicates with the Pico using the I2C protocol.

Connections:
| LCD Pin | Pico Pin |
| ------- | -------- |
| GND     | GND      |
| VCC     | 3V3      |
| SDA     | GP4      |
| SCL     | GP5      |

STATUS: IDLE
MODE: FOCUS
MODE: BREAK
MODE: ALERT

## Push Button

The push button is used as the main input device.

It is connected to GP16 and GND.

The Pico uses its internal pull-up resistor, so the button works with active-low logic:
Button not pressed -> GPIO reads 1
Button pressed     -> GPIO reads 0
This avoids the need for an external pull-up resistor.

## LED

The LED is used as a visual status indicator.

It is connected to GP10 through a current-limiting resistor.

The LED behavior depends on the current state:
| State | LED Behavior |
| ----- | ------------ |
| IDLE  | Off          |
| FOCUS | On           |
| BREAK | Slow blink   |
| ALERT | Fast blink   |

## SG90 Servo

The SG90 micro servo is controlled using PWM from GP15.

The servo moves to different positions depending on the current state.
| State | Servo Behavior  |
| ----- | --------------- |
| IDLE  | Center position |
| FOCUS | Left position   |
| BREAK | Right position  |
| ALERT | Alert position  |

## Firmware Structure

The firmware is written in C using the Raspberry Pi Pico SDK.

The main firmware responsibilities are:

Initialize GPIO pins.
Initialize I2C communication.
Initialize PWM for the servo.
Initialize the LCD.
Read the push button.
Apply debounce logic.
Update the finite state machine.
Update the LED, LCD, and servo according to the current state.
Main Concepts Used
GPIO Output

The LED is controlled using a GPIO output pin.

The firmware writes either HIGH or LOW to GP10 to turn the LED on or off.

## GPIO Input

The button is read using a GPIO input pin.

The internal pull-up resistor keeps the pin HIGH when the button is not pressed.

When the button is pressed, the pin is connected to GND and reads LOW.

## I2C Communication

The LCD1602 display uses I2C communication.
This reduces the number of required wires compared to a parallel LCD interface.

Only two signal lines are needed:
SDA -> data
SCL -> clock

## PWM Servo Control

The servo is controlled using a PWM signal.

The firmware generates a 50 Hz PWM signal, where the pulse width determines the servo position.

Typical pulse widths used:
1000 us -> one side
1500 us -> center
2000 us -> other side

## Finite State Machine

The system is controlled using a finite state machine.

The current state determines the behavior of the LCD, LED, and servo.

The states are:
IDLE -> FOCUS -> BREAK -> ALERT -> IDLE
Each button press advances the system to the next state.
## Design Reasoning

The project was designed to be simple enough to build on a breadboard, but complete enough to demonstrate real embedded systems concepts.

Instead of testing each component separately forever, the final firmware integrates all modules into one coherent system.

This makes the project useful as a learning prototype and as documentation for future embedded projects.



