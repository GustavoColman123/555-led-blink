# State Machine

## Overview

The Embedded Desk Terminal v0 uses a finite state machine to control the behavior of the system.

A finite state machine is a programming structure where the system can only be in one defined state at a time.

In this project, the current state determines:

- What the LCD displays
- How the LED behaves
- Where the servo moves
- What happens after a button press

## System States

The system has four states:

```text
IDLE
FOCUS
BREAK
ALERT
```

The states cycle in this order:

```text
IDLE -> FOCUS -> BREAK -> ALERT -> IDLE
```

Each button press moves the system to the next state.

## State Behavior

| State | LCD Message | LED Behavior | Servo Behavior |
|---|---|---|---|
| IDLE | STATUS: IDLE | Off | Center position |
| FOCUS | MODE: FOCUS | On | Left position |
| BREAK | MODE: BREAK | Slow blink | Right position |
| ALERT | MODE: ALERT | Fast blink | Alert position |

## State Transition Logic

The push button is used to change states.

The button is connected to GP16 and uses the Pico internal pull-up resistor.

Because the button is active-low:

```text
Not pressed -> GPIO reads 1
Pressed     -> GPIO reads 0
```

The firmware detects a new button press by checking when the button changes from not pressed to pressed.

This is called an edge detection.

The firmware does not change state continuously while the button is held down. It only changes state once per press.

## State Transition Diagram

```text
        +------+
        | IDLE |
        +------+
           |
           | button press
           v
       +--------+
       | FOCUS  |
       +--------+
           |
           | button press
           v
       +--------+
       | BREAK  |
       +--------+
           |
           | button press
           v
       +--------+
       | ALERT  |
       +--------+
           |
           | button press
           v
        +------+
        | IDLE |
        +------+
```

## C Enum Representation

The states are represented in C using an enum:

```c
typedef enum {
    STATE_IDLE,
    STATE_FOCUS,
    STATE_BREAK,
    STATE_ALERT,
    STATE_COUNT
} system_state_t;
```

Using an enum makes the code easier to read than using raw numbers.

Instead of writing:

```c
if (state == 0)
```

the firmware can use:

```c
if (state == STATE_IDLE)
```

This improves clarity and reduces mistakes.

## Advancing to the Next State

The firmware advances to the next state using this expression:

```c
current_state = (current_state + 1) % STATE_COUNT;
```

This means:

- Add 1 to the current state.
- If the value reaches `STATE_COUNT`, return to 0.
- This creates a loop from ALERT back to IDLE.

Example:

```text
STATE_IDLE  + 1 -> STATE_FOCUS
STATE_FOCUS + 1 -> STATE_BREAK
STATE_BREAK + 1 -> STATE_ALERT
STATE_ALERT + 1 -> STATE_IDLE
```

## Debounce Logic

Mechanical buttons do not produce a perfectly clean signal.

When a button is pressed, the metal contacts inside the button can bounce electrically for a short time.

This can cause the microcontroller to detect multiple presses even though the user pressed the button only once.

To reduce this problem, the firmware uses debounce logic.

The debounce delay used in this project is:

```c
#define DEBOUNCE_MS 200
```

This means that after one valid press, the firmware ignores additional button transitions for 200 milliseconds.

## LED Patterns

The LED behavior is updated continuously inside the main loop.

Different states produce different LED patterns:

```text
IDLE  -> LED off
FOCUS -> LED constantly on
BREAK -> LED blinks slowly
ALERT -> LED blinks quickly
```

This makes the system state visible even without looking at the LCD.

## Servo Positions

The servo is moved using PWM pulse widths.

The firmware uses different pulse widths for different states:

```c
#define SERVO_IDLE_US 1500
#define SERVO_FOCUS_US 1000
#define SERVO_BREAK_US 2000
#define SERVO_ALERT_US 1200
```

These values are approximate and depend on the specific servo.

The servo should not be forced against its mechanical limits. If the servo buzzes loudly or struggles, the pulse values should be adjusted to safer limits.

## Why Use a State Machine?

A state machine makes the firmware easier to understand and extend.

Without a state machine, the code could become a collection of disconnected conditions.

With a state machine, each mode has a clear meaning:

- IDLE means the system is waiting.
- FOCUS means the system is in focus mode.
- BREAK means the system is in break mode.
- ALERT means the system is in alert mode.

This structure also makes it easier to add future states or change the behavior of existing states.

## Current Result

The final prototype successfully cycles through four states using one button.

Each state updates:

- The LCD message
- The LED pattern
- The servo position

This confirms that the project integrates input handling, output control, timing, PWM, I2C, and state-based firmware logic.
