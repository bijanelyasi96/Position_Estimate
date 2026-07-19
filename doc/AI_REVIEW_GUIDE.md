# AI-Assisted Review Guide

## Intended use

The primary use of AI in this repository is to:

- read CubeMX and Simulink-generated code;
- explain the implemented execution architecture;
- trace model blocks into generated C;
- identify which interrupt, timer, ADC, GPIO, or subsystem owns each behavior;
- compare regenerated versions;
- identify timing, data-type, overflow, calibration, and integration risks;
- prepare review notes and documentation.

The default role of AI is **reviewer and explainer**, not source-code author.

The control algorithm should normally be changed in Simulink. Peripheral configuration should normally be changed in STM32CubeMX. Regenerable C should not become the permanent source of manual fixes.

# Source-of-truth hierarchy

Use this order when interpreting the project.

## 1. Hardware schematic and measured wiring

The schematic and actual PCB determine:

- which MCU pins receive Hall A/B/C;
- signal voltage levels and conditioning;
- phase order;
- current-sensor routing;
- protection signals;
- physical direction conventions.

For the current repository, the committed CubeMX mapping is:

```text
PB6 -> TIM4_CH1 -> Hall A/H1
PB7 -> TIM4_CH2 -> Hall B/H2
PB8 -> TIM4_CH3 -> Hall C/H3
```

The schematic must still confirm that this mapping matches the physical board.

## 2. `Open_Loop.ioc`

Use the CubeMX file to determine intended:

- clock tree;
- pin alternate functions;
- timer mode;
- timer prescaler and period;
- ADC trigger source;
- HAL time-base timer;
- baseline NVIC configuration.

Do not assume that every `.ioc` setting remains the final runtime setting. Simulink-generated initialization can add or overwrite interrupt configuration.

## 3. `Open_Loop2024.slx`

Use the model to understand intended:

- Function-Call Subsystems;
- data flow;
- estimator structure;
- calibration tables;
- control equations;
- state storage;
- sample times;
- hardware-block configuration.

Because `.slx` is binary, Git text diff is insufficient. Pair every model change with a committed generated-C snapshot and a short written change note.

## 4. Simulink-generated C and headers

Generated C is the best source for determining what will actually execute.

Review at least:

- generated `ert_main.c` or equivalent entry point;
- model initialization function;
- generated ADC handler;
- generated TIM4 handler;
- interrupt-registration function;
- timer-capture calls or register accesses;
- model step/function-call code;
- persistent states;
- generated data types;
- math-library calls;
- PWM writes;
- error and flag-clear paths.

If generated sources are not committed, state explicitly that detailed execution behavior is unverified.

## 5. CubeMX-generated C

Use `Core/Src/main.c`, `stm32f3xx_it.c`, and the HAL time-base file to verify what CubeMX emitted.

Remember that weak CubeMX handlers can be overridden by strong Simulink-generated handlers at link time.

## 6. Compiled binary and hardware measurements

The final proof comes from:

- compiler map/listing and disassembly;
- interrupt timing on GPIO instrumentation;
- logic-analyzer Hall captures;
- oscilloscope current and PWM measurements;
- independent speed/angle reference;
- motor and inverter tests.

# Evidence labels for AI responses

Every technical conclusion should be classified as one of:

```text
CONFIRMED — directly visible in committed source/configuration
INFERRED  — logical consequence of confirmed code, but not directly tested
INTENDED  — described by design/model settings but not proven in generated C
UNVERIFIED — requires generated source, build, or hardware evidence
CONTRADICTED — repository files disagree with the stated design
```

Example:

```text
CONFIRMED: TIM4 PSC is 71 and ARR is 65535 in generated CubeMX C.
CONFIRMED: CH1/CH2/CH3 use both-edge direct input capture and XOR is enabled.
UNVERIFIED: Simulink generates one Hall estimator call per physical transition.
UNVERIFIED: the final runtime TIM4 priority is lower than the ADC priority.
```

# Review workflow after a Simulink change

## Step 1: record the intent

Before regeneration, write a one-paragraph change description, for example:

```text
Change Hall capture from three independent events to one XOR/CC1 event,
calculate modulo timestamp difference, validate transitions, and publish
speed/direction to the 10 kHz ADC task.
```

## Step 2: regenerate from the owning tool

- CubeMX owns peripheral and pin changes.
- Simulink owns model and algorithm changes.
- Avoid manual edits in generated source.

## Step 3: inspect Git changes before committing

Use:

```powershell
git status
git diff --stat
git diff -- Open_Loop.ioc
git diff -- Core/Src/main.c
git diff -- Core/Src/stm32f3xx_it.c
```

Binary `.slx` changes will not produce a useful normal text diff. Review the model in Simulink and compare the generated C.

## Step 4: commit the generated embedded source snapshot

Commit model-specific generated `.c` and `.h` files required for static review.

Do not commit ordinary build products:

```text
*.o
*.elf
*.bin
*.hex
Debug/
Release/
```

## Step 5: ask AI for a static trace

A useful request is:

```text
@GitHub Inspect bijanelyasi96/Position_Estimate.

Do not edit code. Trace the exact runtime path for:
1. startup and peripheral initialization;
2. ADC-triggered fast control;
3. every TIM4 Hall capture event;
4. Hall-state validation and direction detection;
5. speed and electrical-angle estimation;
6. shared data between the Hall ISR and ADC ISR;
7. PWM update.

For every conclusion, classify it as CONFIRMED, INFERRED, INTENDED,
or UNVERIFIED. Cite exact file paths and functions.
```

## Step 6: compare against the previous commit

Ask AI to identify:

- peripheral changes;
- interrupt-priority changes;
- changed capture flags;
- sample-time changes;
- new persistent states;
- data-type changes;
- new divisions/trigonometric operations;
- changes to overflow and timeout handling;
- changes to SVM/PWM behavior.

## Step 7: validate on hardware

Static review cannot prove:

- signal integrity;
- Hall ordering;
- electrical offset;
- edge timing under EMI;
- actual ISR execution time;
- motor direction;
- torque behavior;
- startup smoothness;
- protection effectiveness.

Record physical results separately.

# Hall-estimator review checklist

When reviewing generated code, answer these questions explicitly.

## Capture source

```text
[ ] Which TIM4 channel/event triggers the ISR?
[ ] Is CH1 receiving the XOR-combined Hall input or raw PB6 only?
[ ] Are CH2 and CH3 interrupts enabled?
[ ] Can one physical transition produce multiple software events?
[ ] Are both rising and falling transitions captured?
```

## Timestamp and range

```text
[ ] Is TIM4 free-running or reset at every edge?
[ ] Is period derived from timestamp subtraction or direct CCR interval?
[ ] Is 16-bit modulo subtraction correct?
[ ] Are multiple overflows counted?
[ ] Is there a missing-edge/standstill timeout?
[ ] Is division by zero prevented?
```

## Hall state

```text
[ ] Are PB6/PB7/PB8 read without reconfiguring alternate functions?
[ ] Is the H1/H2/H3 bit order documented?
[ ] Are 000 and 111 rejected?
[ ] Are skipped and two-bit transitions rejected?
[ ] Is direction based on calibrated forward/reverse sequences?
```

## Estimator

```text
[ ] Is the first partial edge interval rejected for speed calculation?
[ ] Is speed trusted only after two valid consecutive edges?
[ ] Is electrical speed calculated using five pole pairs?
[ ] Is angle initialized to a calibrated sector value?
[ ] Is angle interpolated at the 100 us fast-task rate?
[ ] Are edge corrections bounded or blended?
[ ] Is reversal handled explicitly?
```

## Interrupt safety

```text
[ ] What are the final generated NVIC priorities?
[ ] Can the Hall ISR preempt the ADC ISR?
[ ] Is the Hall ISR bounded and short?
[ ] Is shared data coherent when the ADC ISR reads it?
[ ] Is an event counter or equivalent atomic publication method used?
[ ] Are all relevant flags cleared exactly once?
```

## Numeric performance

```text
[ ] Are high-rate variables single precision or fixed point?
[ ] Are accidental double-precision operations present?
[ ] Is the STM32F303 single-precision FPU used where expected?
[ ] Are integer products/divisions protected from overflow?
[ ] Are units explicit: ticks, seconds, rad/s, electrical radians, rpm?
```

# Rules for AI-proposed changes

AI should normally provide change instructions at the owning abstraction level.

Preferred:

```text
In CubeMX, change TIM4 input mode and regenerate.
In Simulink, add a TIM4 Hardware Interrupt block and connect it to a
Hall_Capture_ISR Function-Call Subsystem.
```

Avoid:

```text
Edit generated Open_Loop2024.c at line ...
```

A manual C integration layer is acceptable only when:

- the support package cannot represent the required behavior;
- the file is intentionally non-regenerable;
- ownership is documented;
- the interface to generated code is stable;
- the reason is recorded in `CURRENT_STATUS.md`.

# Recommended repository update pattern

After a meaningful model generation:

```powershell
git status
git diff --stat
git add Open_Loop.ioc Open_Loop2024.slx Core Drivers STM32CubeIDE <generated-code-folder> doc
git commit -m "Regenerate position estimator after <change>"
git push
```

Replace `<generated-code-folder>` with the actual model-specific generated source directory.

Do not use `git add .` blindly when the working tree contains unrelated MATLAB caches, build output, measurement exports, or confidential data.

# Useful AI prompts

## Architecture explanation

```text
@GitHub Inspect bijanelyasi96/Position_Estimate and explain the architecture
from reset to PWM update. Do not edit files. Separate confirmed code from
inference and unverified behavior.
```

## Hall capture trace

```text
@GitHub Trace every possible path through TIM4_IRQHandler. State which
capture channel and flag causes execution, which CCR value is read, how timer
rollover is handled, and whether one Hall edge can produce multiple updates.
Do not modify code.
```

## Estimator math review

```text
@GitHub Review the generated Hall speed and angle estimator. Verify pole-pair
scaling, electrical/mechanical unit conversions, startup behavior, reversal,
standstill timeout, rollover, and data types. Do not edit code.
```

## Regeneration comparison

```text
@GitHub Compare the latest two generated versions. Explain only meaningful
changes in peripherals, ISR scheduling, estimator state, calculations, and
PWM behavior. Ignore formatting and vendor-library noise.
```

## FPU and execution-time review

```text
@GitHub Identify all float and double operations in the ADC and TIM4 interrupt
paths. Explain which operations use the Cortex-M4F single-precision FPU and
which require software library routines. Do not edit code.
```

# Documentation maintenance

Update these documents whenever architecture changes:

```text
doc/ARCHITECTURE.md
doc/CURRENT_STATUS.md
doc/AI_REVIEW_GUIDE.md
```

`ARCHITECTURE.md` describes structure and ownership.

`CURRENT_STATUS.md` records what is currently confirmed, missing, risky, or unverified.

`AI_REVIEW_GUIDE.md` defines how future AI reviews should be performed without turning generated C into the source of truth.
