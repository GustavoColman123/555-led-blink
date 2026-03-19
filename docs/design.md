# Design

## Overview

This circuit uses the NE555 timer in astable mode to generate a continuous oscillating signal.

The output signal is used to turn an LED on and off periodically.

## How It Works

The 555 timer operates by charging and discharging a capacitor.

1. The capacitor charges through R1 and R2
2. When the voltage reaches a threshold, the 555 switches state
3. The capacitor then discharges through pin 7
4. This cycle repeats continuously

This creates a square wave output at pin 3.

## Key Components

- R1 (1kΩ): Controls charge path
- R2 (100kΩ): Controls charge and discharge timing
- Capacitor (10µF): Determines oscillation frequency

## Signal Behavior

The output at pin 3 alternates between HIGH (≈5V) and LOW (≈0V), causing the LED to blink.

The frequency of blinking depends on:

- Resistance values (R1, R2)
- Capacitance (C)

## Notes

Understanding this behavior is essential before moving to more complex circuits such as counters (CD4017) or microcontroller-based systems.
