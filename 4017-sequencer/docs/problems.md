## Problems Encountered

### 1. Misinterpretation of System Behavior

#### Problem
The circuit appeared to be malfunctioning because the LEDs did not behave as expected.

#### Cause
Incorrect assumption about how the CD4017 works.  
Only one output (Q0) was being observed, leading to the belief that the system was not advancing.

#### Solution
Added multiple LEDs (Q0, Q1, Q2) to visualize the sequential behavior.

#### Insight
The system was functioning correctly. The issue was a misunderstanding of how the counter outputs operate.

### 2. Incorrect Debugging Approach

#### Problem
The circuit was repeatedly disassembled and rebuilt due to the belief that it was not working.

#### Cause
Lack of a clear mental model of the system led to unnecessary hardware changes.

#### Solution
Adopted a more controlled approach:
- Observed behavior before modifying hardware
- Changed one variable at a time

#### Insight
Debugging should be driven by observation and reasoning, not assumptions.

### 3. Unnecessary Full Reset of the 555 Circuit

#### Problem
The entire NE555 circuit was rebuilt after changing the capacitor value (100µF → 50µF).

#### Cause
Incorrect assumption that the timing change caused a failure.

#### Solution
Verified that the NE555 continued to function correctly after component changes.

#### Insight
A change in timing does not imply malfunction. The system behavior must be interpreted correctly before resetting hardware.
