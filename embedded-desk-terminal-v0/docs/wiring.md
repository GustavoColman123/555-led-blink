# Wiring

## Overview

This document describes the wiring used in the Embedded Desk Terminal v0 prototype.

The system uses a Raspberry Pi Pico connected to:

- LCD1602 I2C display
- SG90 micro servo
- Push button
- LED with current-limiting resistor

All components share a common ground.

## Pinout Summary

| Component | Component Pin | Raspberry Pi Pico Pin |
|---|---|---|
| LCD1602 I2C | GND | GND |
| LCD1602 I2C | VCC | 3V3 |
| LCD1602 I2C | SDA | GP4 |
| LCD1602 I2C | SCL | GP5 |
| LED | Anode (+) through resistor | GP10 |
| LED | Cathode (-) | GND |
| SG90 Servo | Signal wire | GP15 |
| SG90 Servo | VCC / Red wire | VBUS |
| SG90 Servo | GND / Brown wire | GND |
| Push Button | One side | GP16 |
| Push Button | Opposite side | GND |

## LCD1602 I2C Wiring

The LCD1602 display uses an I2C backpack module, which reduces the required wiring to four pins.

Connections:

| LCD Pin | Pico Pin |
|---|---|
| GND | GND |
| VCC | 3V3 |
| SDA | GP4 |
| SCL | GP5 |

The LCD was tested using the I2C address:

```text
0x27
```

The display showed the expected text after adjusting the contrast potentiometer on the I2C module.

## LED Wiring

The LED is connected to GP10 through a current-limiting resistor.

Connection path:

```text
GP10 -> resistor -> LED anode
LED cathode -> GND
```

The resistor is required to limit current and protect both the LED and the Pico GPIO pin.

Expected behavior:

| State | LED Behavior |
|---|---|
| IDLE | Off |
| FOCUS | On |
| BREAK | Slow blink |
| ALERT | Fast blink |

## Push Button Wiring

The push button is connected between GP16 and GND.

Connection path:

```text
GP16 -> push button -> GND
```

The firmware enables the Pico internal pull-up resistor on GP16.

Because of this, the button uses active-low logic:

```text
Button not pressed -> GPIO reads HIGH
Button pressed     -> GPIO reads LOW
```

No external resistor is required for the button.

## Four-Pin Tactile Button Placement

The tactile push button has four legs.

It must be placed across the center gap of the breadboard.

Correct placement:

```text
Top side pins
    |     |
----|-----|----
    center gap
----|-----|----
    |     |
Bottom side pins
```

The two pins on the same side are usually internally connected.

For the button to work correctly, one side must be connected to GP16 and the opposite side to GND.

Incorrect wiring can cause the button to appear as if it does nothing or as if it is always pressed.

## SG90 Servo Wiring

The SG90 micro servo has three wires:

| Servo Wire | Function | Pico Connection |
|---|---|---|
| Brown / Black | GND | GND |
| Red | VCC | VBUS |
| Orange / Yellow | PWM Signal | GP15 |

The servo is powered from VBUS during the prototype phase.

Important note:

The servo and the Pico must share a common GND. Without common ground, the PWM signal may not be interpreted correctly by the servo.

## Power Notes

The LCD is powered from 3V3.

The SG90 servo is powered from VBUS, which provides USB 5V.

This worked for the breadboard prototype, but a more robust version should consider a separate 5V power source for the servo if instability appears.

Possible symptoms of unstable servo power:

- Servo jitter
- Pico reset
- USB disconnecting
- LCD flickering
- Random behavior

## Breadboard Prototype

The first version was built on a breadboard before soldering.

This was important because each subsystem could be tested independently:

1. LED test
2. Servo PWM test
3. LCD I2C test
4. Button input test
5. LCD + button + LED integration
6. Full system integration with servo

Only after confirming that the circuit works correctly should the project move to perfboard soldering.

## Wiring Principle

The system follows one main rule:

```text
Every signal needs a reference ground.
```

That means all modules must share GND with the Raspberry Pi Pico.

The button, LCD, servo, and LED all depend on the Pico GND to work correctly.
