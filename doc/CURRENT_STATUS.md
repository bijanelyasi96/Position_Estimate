# Current Position-Estimation Project Status

## Repository baseline

```text
Repository:        bijanelyasi96/Position_Estimate
Default branch:    main
Reviewed import:   bc0b1dd33430dceed71336e525816e590f88250e
CubeMX project:    Open_Loop.ioc
Simulink model:    Open_Loop2024.slx
Target MCU:        STM32F303RETx, LQFP64
```

This status is based on static inspection of committed CubeMX configuration and generated integration files. No build, processor execution, oscilloscope validation, or motor test was performed as part of this review.

# Confirmed configuration

## Platform

- STM32F303RETx Cortex-M4F target.
- 8 MHz HSE multiplied to a 72 MHz system clock.
- STM32CubeIDE project configured for FPv4-SP-D16 and hard floating-point ABI.
- CubeMX is configured not to generate the final `main()`; the Simulink target is expected to supply the executable entry point.

## Existing PWM and ADC path

Confirmed TIM1 behavior:

- center-aligned three-phase PWM;
- CH1, CH2, CH3 and their complementary outputs;
- `PSC = 0`;
- `ARR = 3599`;
- repetition counter `1`;
- dead time `95`;
- TIM1 update used as TRGO;
- nominal 10 kHz PWM/control timing.

Confirmed ADC1 behavior:

- ADC1_IN7 on PC1;
- 12-bit single-ended conversion;
- one regular conversion;
- TIM1 TRGO rising-edge trigger;
- ADC1_2 NVIC enabled in CubeMX with priority `0`.

## Hall timer resources

Confirmed Hall pin routing:

```text
PB6 -> TIM4_CH1
PB7 -> TIM4_CH2
PB8 -> TIM4_CH3
```

Confirmed TIM4 base settings:

```text
Timer clock         = 72 MHz
PSC                 = 71
Counter frequency   = 1 MHz
Counter resolution  = 1 us
ARR                 = 65535
Counter width       = 16 bit
Counter mode        = Up
```

Confirmed input-capture settings in generated C:

- CH1 direct input capture, both edges, DIV1;
- CH2 direct input capture, both edges, DIV1;
- CH3 direct input capture, both edges, DIV1;
- three-input XOR combination enabled;
- generated filter setting is effectively no digital filter (`FDIV1`);
- TIM4 global interrupt enabled in CubeMX;
- CubeMX TIM4 priority is `0`.

## HAL time base

TIM2 remains the HAL millisecond time base:

```text
TIM2 counter clock  = 1 MHz
TIM2 period         = 999
HAL tick            = 1 kHz
TIM2 priority       = 15
```

# Important interpretation of the current TIM4 configuration

The committed configuration is not yet the standard STM32 Hall reset-mode architecture.

Current generated configuration:

```text
three direct input-capture channels
+ both-edge capture
+ XOR enabled
+ free-running counter
```

Not confirmed in current generated CubeMX C:

```text
TI1F_ED trigger
TRC capture source
slave reset mode at every Hall edge
```

Therefore the current design requires timestamp-difference logic:

```text
PeriodTicks = (CurrentTimestamp - PreviousTimestamp) modulo 65536
```

A single captured CCR value is not automatically the time since the previous edge because TIM4 is not reset by the Hall event in the committed CubeMX initialization.

# Confirmed limitations and risks

## 1. Effective TIM4 ISR is not confirmed

`Core/Src/stm32f3xx_it.c` contains only a weak empty `TIM4_IRQHandler()`.

TIM4 capture is operational only if the Simulink-generated code supplies a strong handler that:

- detects the correct capture-compare event;
- reads the intended CCR register;
- clears the correct event flag;
- executes the Hall Function-Call Subsystem.

That handler was not confirmed from a committed generated-C snapshot during this review.

## 2. Effective ADC ISR is not confirmed

`Core/Src/stm32f3xx_it.c` also contains only a weak empty `ADC1_2_IRQHandler()`.

The fast control algorithm depends on a strong Simulink-generated handler. The binary `.slx` file is present, but detailed generated-C execution was not confirmed in the reviewed paths.

## 3. ADC and TIM4 have equal CubeMX priority

CubeMX currently assigns priority `0` to both ADC1_2 and TIM4.

Consequences:

- they cannot preempt one another;
- one waits pending while the other ISR finishes;
- latency depends on the complete execution time of the active ISR.

Simulink may overwrite these values during generated initialization. The final runtime priorities must be checked in generated C, not inferred only from the `.ioc` file.

## 4. Digital filter does not match the earlier proposed value

The committed generated C sets:

```text
LL_TIM_IC_FILTER_FDIV1
```

for CH1, CH2, and CH3, which is effectively no input digital filtering. The previously discussed filter value `8` is not confirmed in this repository snapshot.

This must be revisited against:

- inverter switching noise;
- Hall conditioning and edge slew rate;
- maximum motor speed;
- false-edge rejection requirements.

## 5. Low-speed range requires explicit handling

At 1 MHz with a 16-bit timer, one unambiguous interval spans 65.536 ms.

For five pole pairs and one Hall transition every 60 electrical degrees:

```text
Minimum theoretical speed without multi-overflow handling = 30.5176 rpm
```

Operation below that speed requires one of:

- genuine TIM4 overflow counting;
- a slower counter clock;
- or explicit low-speed/standstill timeout behavior.

## 6. Exact capture-event ownership is not confirmed

The `.ioc` configures all three channels as direct input captures while XOR is also enabled. The generated model must establish which event owns estimator execution.

Questions still to answer from generated C:

- Is TIM4 CC1 the only interrupt event used?
- Does CH1 receive the XOR-combined Hall signal as intended?
- Are CH2/CH3 capture events disabled, read for diagnostics, or also interrupting?
- Can one physical Hall transition create more than one estimator update?

## 7. Hall calibration is not recorded

The repository does not yet document the measured:

- H1/H2/H3 bit order;
- forward six-state sequence;
- reverse six-state sequence;
- positive mechanical direction;
- U/V/W phase order;
- Hall transition angle relative to rotor d-axis;
- installation offset.

No generic Hall-state-to-angle table should be treated as final before these measurements are recorded.

## 8. Legacy inputs remain

PC6, PC9, and PC15 remain ordinary digital inputs inherited from the earlier open-loop project.

Their purpose must be named explicitly in the Simulink model. They must not be confused with the actual Hall inputs on PB6, PB7, and PB8.

# What is not yet proven

The following are not claimed as complete:

- successful firmware build from a clean checkout;
- strong generated ADC and TIM4 interrupt handlers;
- one capture event for every valid Hall transition;
- correct 16-bit rollover or overflow handling;
- missing-edge timeout;
- invalid-state detection for `000` and `111`;
- legal-transition validation;
- direction detection;
- calibrated Hall angle table;
- reliable speed estimation at low and high speed;
- electrical-angle interpolation at the 10 kHz control rate;
- bumpless Hall-edge angle correction;
- closed-loop FOC;
- phase-current measurement and calibrated `Id/Iq` control;
- hardware validation under inverter switching conditions.

# Recommended next verification sequence

## Stage 1: commit generated sources

After building from Simulink, commit the complete generated embedded-code snapshot, including the model-specific generated C and headers. Do not commit build products such as `.elf`, `.o`, `.bin`, or Debug/Release directories.

## Stage 2: static generated-code review

Verify:

1. generated entry point and initialization order;
2. strong `ADC1_2_IRQHandler()`;
3. strong `TIM4_IRQHandler()`;
4. interrupt registration and final priorities;
5. enabled TIM4 capture events;
6. CCR register used by the model;
7. flag-check and flag-clear behavior;
8. timestamp rollover logic;
9. shared Hall snapshot atomicity;
10. estimator equations and data types.

## Stage 3: low-risk input validation

With PWM torque disabled:

- rotate the motor manually;
- log H1/H2/H3 states;
- confirm six valid states only;
- confirm one estimator event per transition;
- confirm forward and reverse sequences;
- compare timer intervals with an oscilloscope or logic analyzer;
- test timer rollover and missing-edge timeout.

## Stage 4: estimator validation

Before using the estimated angle to drive the inverter:

- compare calculated RPM with an independent speed reference;
- calibrate the Hall boundary-angle table;
- plot raw sector angle, interpolated angle, speed, and correction error;
- verify startup, reversal, creep, and standstill behavior.

## Stage 5: controlled motor operation

Use current-limited, low-DC-link-voltage commissioning before enabling full traction torque. Preserve a selectable fallback to the previously validated open-loop angle while the Hall estimator is being commissioned.

# Current status summary

```text
CubeMX Hall resources configured:             Yes
PB6/PB7/PB8 routed to TIM4:                   Yes
TIM4 1 MHz / 16-bit capture configured:       Yes
Both-edge direct captures configured:         Yes
XOR combination enabled:                      Yes
Standard Hall reset/TRC mode confirmed:       No
Strong generated TIM4 ISR confirmed:          No
Strong generated ADC ISR confirmed:           No
Hall transition table calibrated:             No
Overflow/timeout behavior confirmed:          No
Position interpolation confirmed:             No
Hardware validation completed:                No evidence in repository
Ready to claim closed-loop position control:  No
```
