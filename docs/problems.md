# Problems Encountered

1. Power Supply Shutdown

### Problem
The power supply turned off immediately when the circuit was powered.

### Cause
Short circuit caused by incorrect wiring and missing current limiting.

### Solution
Rebuilt the circuit step by step and verified each connection.

2. No Oscillation (LED Not Blinking)

### Problem
The LED stayed ON instead of blinking.

### Cause
Incorrect connections between pins 2, 6, and 7 of the 555 timer.

### Solution
Ensured proper wiring:
- Pin 2 connected to pin 6
- Correct resistor placement
- Capacitor properly connected

3. Capacitor Polarity Issues

### Problem
The circuit did not behave correctly.

### Cause
Electrolytic capacitor polarity was incorrect.

### Solution
Connected:
- Positive → pins 2/6
- Negative → GND

4. Breadboard Misalignment

### Problem
Connections looked correct but the circuit did not work.

### Cause
Components were placed in incorrect rows of the breadboard.

### Solution
Carefully verified row connections and rebuilt the circuit.

5. Debugging Complexity

### Problem
Difficult to identify the issue due to multiple possible causes.

### Cause
Too many components connected at once.

### Solution
Adopted incremental debugging:
- Tested power first
- Built the circuit step by step

## Additional Issues During Experimentation R2

### Problem
The circuit frequently stopped working after small modifications.

### Cause
Changing components without maintaining reference points caused wiring mistakes.

### Solution
Adopted a more controlled approach:
- Changed only one component at a time
- Verified connections before powering the circuit


### Problem
Difficulty maintaining a working circuit after multiple changes.

### Cause
Loss of circuit stability due to repeated handling and wiring adjustments.

### Solution
Rebuilt the circuit from scratch when issues became unclear instead of trying to fix everything at once.
