# PMSM Position-Estimation Software Architecture

## Scope

This document describes the repository state reviewed at initial import commit:

```text
bc0b1dd33430dceed71336e525816e590f88250e
```

Repository:

```text
bijanelyasi96/Position_Estimate
```

The repository is a CubeMX and Simulink project for an STM32F303RETx-based PMSM controller. The committed configuration adds TIM4 Hall-input capture resources to the earlier open-loop motor-control platform. This document distinguishes:

- configuration confirmed from `Open_Loop.ioc` and CubeMX-generated C;
- intended Simulink integration;
- behavior that still requires inspection of a committed Simulink-generated C snapshot or hardware validation.

## Source ownership

The project has four source layers.

### 1. STM32CubeMX configuration

Primary file:

```text
Open_Loop.ioc
```

CubeMX owns:

- MCU and package selection;
- clock tree;
- GPIO alternate functions;
- TIM1 PWM and ADC-trigger configuration;
- ADC1 configuration;
- TIM4 input-capture configuration;
- TIM2 HAL time-base selection;
- NVIC baseline priorities;
- generated LL/HAL initialization functions.

Changes to peripheral routing, timer modes, pin assignments, clock frequencies, or baseline NVIC settings must be made in CubeMX and regenerated.

### 2. Simulink model

Committed model:

```text
Open_Loop2024.slx
```

The model is the intended owner of:

- hardware-interrupt blocks;
- Function-Call Subsystems;
- timer-capture blocks;
- Hall-state decoding;
- transition validation;
- direction and speed estimation;
- electrical-angle interpolation;
- existing motor-control calculations;
- SVM and PWM block behavior.

The `.slx` file is a binary archive. Normal Git text diffs do not provide a reliable block-level review. A committed generated-C snapshot is therefore important for detailed AI review and version comparison.

### 3. CubeMX-generated integration code

Important files include:

```text
Core/Src/main.c
Core/Src/stm32f3xx_it.c
Core/Src/stm32f3xx_hal_timebase_tim.c
Core/Inc/main.h
STM32CubeIDE/.project
STM32CubeIDE/.cproject
```

These files show the actual peripheral initialization emitted from the current `.ioc` file.

### 4. Simulink-generated embedded code

CubeMX is configured with:

```text
ProjectManager.NoMain = true
```

Therefore CubeMX does not provide the final application `main()` entry point. The Simulink-generated target is expected to provide the executable entry point, model initialization, generated interrupt handlers, and control algorithm.

At the reviewed baseline, the expected model-generated source snapshot was not confirmed at the conventional path:

```text
Open_Loop2024_ert_rtw/
```

Future reviews should verify and document the actual generated-code directory after each Simulink build. Do not claim that a timer or estimator algorithm is operational only because it is configured in CubeMX; the generated handler and model logic must also be present.

# Hardware and clock architecture

## MCU

```text
MCU: STM32F303RETx
Package: LQFP64
Core: Cortex-M4F
```

The STM32CubeIDE project uses the single-precision hardware FPU with hard-float ABI:

```text
FPv4-SP-D16
hard floating-point ABI
```

## Clock tree

Confirmed clock configuration:

```text
HSE                    = 8 MHz
PLL multiplier         = x9
SYSCLK / HCLK          = 72 MHz
APB1 peripheral clock  = 36 MHz
APB1 timer clock       = 72 MHz
APB2 peripheral clock  = 72 MHz
APB2 timer clock       = 72 MHz
```

TIM1, TIM2, and TIM4 therefore receive a 72 MHz timer clock in the current configuration.

# Existing fast-control path

## TIM1: inverter PWM and ADC trigger

TIM1 remains the deterministic motor-control timing source.

Configuration:

| Parameter | Value |
|---|---:|
| Prescaler | `0` |
| Counter mode | Center-aligned mode 1 / center-up |
| Auto-reload | `3599` |
| Repetition counter | `1` |
| PWM channels | CH1, CH2, CH3 |
| Complementary outputs | CH1N, CH2N, CH3N |
| Dead time | `95` timer counts |
| Master trigger | Update event |
| Break input | Disabled |

Nominal PWM frequency:

```text
72 MHz / (2 * 3600) = 10 kHz
```

PWM pin mapping:

| Function | Pin |
|---|---|
| TIM1_CH1 | PA8 |
| TIM1_CH2 | PA9 |
| TIM1_CH3 | PA10 |
| TIM1_CH1N | PB13 |
| TIM1_CH2N | PB14 |
| TIM1_CH3N | PB15 |

## ADC1: fast-task trigger

ADC1 configuration:

| Parameter | Value |
|---|---|
| Pin | PC1 |
| Channel | ADC1_IN7 |
| Resolution | 12 bit |
| Sequence length | One conversion |
| Sampling time | 1.5 ADC cycles |
| Trigger | TIM1 TRGO rising edge |
| Conversion mode | Single conversion |
| DMA | Limited configuration; no confirmed model DMA workflow |
| CubeMX NVIC priority | `0` |

The intended fast path is:

```text
TIM1 update / TRGO
    -> ADC1 conversion
        -> ADC1 end-of-sequence interrupt
            -> fast-control Function-Call Subsystem
                -> acquire required measurements
                -> consume estimated rotor angle/speed
                -> execute control calculations
                -> execute SVM
                -> update TIM1 PWM compares
```

`Core/Src/stm32f3xx_it.c` contains only a weak empty `ADC1_2_IRQHandler()`. A functional application therefore depends on a strong handler supplied by Simulink-generated code.

# TIM4 Hall-input capture architecture

## Physical Hall connections

The three Hall signals use STM32 package pins 58, 59, and 61:

| Package pin | GPIO | Timer signal | Logical signal |
|---:|---|---|---|
| 58 | PB6 | TIM4_CH1 | Hall A / H1 |
| 59 | PB7 | TIM4_CH2 | Hall B / H2 |
| 61 | PB8 | TIM4_CH3 | Hall C / H3 |

All three pins are configured as TIM4 alternate-function inputs with no internal pull resistor.

The external Hall-conditioning circuit must provide valid 3.3 V logic levels. Open-collector/open-drain Hall outputs require suitable external pull-ups.

## Actual TIM4 configuration in the committed snapshot

TIM4 is configured as follows:

| Parameter | Value |
|---|---:|
| Timer clock | 72 MHz |
| Timer prescaler | `71` |
| Counter clock | 1 MHz |
| Tick duration | 1 us |
| Counter mode | Up |
| Auto-reload | `65535` |
| Counter width | 16 bit |
| ARR preload | Disabled |
| CH1 input selection | Direct TI1 |
| CH2 input selection | Direct TI2 |
| CH3 input selection | Direct TI3 |
| CH1 polarity | Both edges |
| CH2 polarity | Both edges |
| CH3 polarity | Both edges |
| Input-capture prescaler | No division / DIV1 |
| Generated input filter | No digital filtering / FDIV1 |
| XOR combination | Enabled |
| Master/slave mode | Disabled |
| Trigger output | Reset/default |
| CubeMX NVIC priority | `0` |

`No division` for the input-capture prescaler means every eligible capture event is accepted. It is separate from the timer base prescaler `PSC = 71`.

## Important distinction: current implementation versus Hall reset mode

The current CubeMX-generated C does this conceptually:

```text
CH1 -> direct input capture, both edges
CH2 -> direct input capture, both edges
CH3 -> direct input capture, both edges
three-input XOR combination enabled
free-running TIM4 counter
```

It does not currently show the standard Hall-interface sequence:

```text
TI1F_ED trigger
TRC capture source
slave reset mode on every Hall edge
```

The generated code disables master/slave mode and does not configure timer reset mode. Consequently, the current architecture should be treated as a free-running timestamp design unless the Simulink-generated code performs additional register configuration.

With a free-running timestamp design:

```text
PeriodTicks = (CurrentCapture - PreviousCapture) modulo 65536
```

The model must preserve the previous timestamp and account for timer rollover. Reading one CCR value alone is not an edge-to-edge period.

## XOR and capture-channel behavior

Enabling the TIM4 three-input XOR function routes the combined Hall state into the timer TI1 path. CH1 can therefore be used as the combined transition timestamp channel when the generated configuration and Simulink Timer Capture block agree on this routing.

However, the current `.ioc` also configures CH2 and CH3 as independent direct input captures. The generated Simulink C must be reviewed to confirm:

- which capture-compare event triggers the Hall Function-Call Subsystem;
- whether CH1 is used as the XOR timestamp source;
- whether CH2 and CH3 capture interrupts are enabled or merely configured;
- which capture flags are cleared;
- whether one and only one estimator update occurs per valid Hall transition.

## Timer range

At 1 MHz with a 16-bit counter:

```text
Maximum unambiguous interval for a single modulo difference = 65536 us
                                                        = 65.536 ms
```

For a five-pole-pair motor and one event every 60 electrical degrees:

```text
Hall transitions per mechanical revolution = 6 * 5 = 30
rpm = 2,000,000 / PeriodTicks
```

Without multi-overflow tracking, the theoretical minimum speed is:

```text
rpm_min = 2,000,000 / 65536
        = 30.5176 rpm
```

Below that speed, the design needs either:

- explicit TIM4 overflow counting;
- a lower counter frequency;
- or a low-speed/standstill timeout strategy.

## Intended Hall interrupt path

The intended model-level architecture is:

```text
Hall transition on PB6/PB7/PB8
    -> TIM4 capture hardware stores timestamp
        -> TIM4 capture-compare interrupt
            -> Hall-capture Function-Call Subsystem
                -> read capture timestamp
                -> read H1/H2/H3 state
                -> reject 000 and 111
                -> validate previous-to-current transition
                -> determine direction
                -> calculate complete edge interval
                -> publish coherent Hall snapshot
```

`Core/Src/stm32f3xx_it.c` contains only a weak empty `TIM4_IRQHandler()`. A functional Hall ISR must therefore be generated as a strong handler by Simulink or supplied through an intentional non-regenerable integration layer.

# HAL time base

TIM2 remains reserved for the STM32 HAL 1 ms time base.

```text
TIM2 counter clock = 1 MHz
TIM2 period        = 999
TIM2 update rate   = 1 kHz
TIM2 NVIC priority = 15
```

Execution chain:

```text
TIM2_IRQHandler()
    -> HAL_TIM_IRQHandler(&htim2)
        -> HAL_TIM_PeriodElapsedCallback()
            -> HAL_IncTick()
```

TIM2 must not be repurposed for Hall capture without moving the HAL time base and reviewing the entire generated runtime.

# Interrupt-priority architecture

CubeMX currently assigns:

| Interrupt | CubeMX priority |
|---|---:|
| ADC1_2 | `0` |
| TIM4 | `0` |
| TIM2 HAL tick | `15` |

Lower numerical values are higher priority.

ADC1_2 and TIM4 currently have equal CubeMX preemption priority. Equal-priority interrupts do not preempt one another; the pending ISR waits until the active ISR returns. This may be acceptable only when both handlers are short and worst-case latency is demonstrated.

Simulink Hardware Interrupt blocks can register or overwrite NVIC priorities during generated initialization. The effective runtime priority must therefore be verified in generated C after the model is built.

Recommended intended order:

```text
ADC fast-control ISR     highest
TIM4 Hall-capture ISR    next
TIM2 HAL tick ISR        lowest
```

Do not infer that this order is implemented until the generated interrupt-registration code is inspected.

# Shared estimator data

The Hall ISR should publish only a bounded, coherent snapshot. Suggested values:

| Value | Suggested type |
|---|---|
| Previous Hall state | `uint8` |
| Current Hall state | `uint8` |
| Capture timestamp or complete period | `uint32` |
| Direction | `int8` |
| Transition valid | `boolean` |
| New-event counter | `uint32` |

The event counter should be written last. The fast ADC task should consume a new snapshot only when the event counter changes.

The Hall ISR should not perform trigonometric functions, SVM, current regulation, logging, or slow diagnostics.

# Rotor estimator placement

The fast ADC task should own continuous interpolation:

```text
theta_e[k+1] = wrap(theta_e[k] + omega_e * 100 us)
```

At a new valid Hall transition, it should:

- associate the transition with a calibrated electrical boundary;
- update speed from the complete edge interval;
- correct or blend the estimated angle;
- apply timeout and invalid-transition protection.

The first valid state supplies only a 60-electrical-degree sector. The first edge may establish a boundary and direction. The second valid consecutive edge supplies the first complete sector period.

# Remaining integration constraints

The committed CubeMX project still includes PC6, PC9, and PC15 as ordinary digital inputs inherited from the earlier open-loop design. Their model purpose must be named clearly so they are not confused with the Hall inputs on PB6/PB7/PB8.

The existing DAC1 output on PA5 and PC11 digital output are also retained. Their diagnostic purpose should be documented in the Simulink model.

# Generated-code verification checklist

After every CubeMX or Simulink regeneration, verify:

```text
[ ] Open_Loop.ioc still maps PB6/PB7/PB8 to TIM4 CH1/CH2/CH3.
[ ] TIM4 PSC is 71 and ARR is 65535.
[ ] Capture polarity and input selection match the intended architecture.
[ ] The chosen digital input filter is present in generated C.
[ ] XOR combination is enabled when CH1 is intended to timestamp every Hall transition.
[ ] The generated model contains a strong TIM4_IRQHandler().
[ ] The handler checks the intended capture event and clears the correct flag.
[ ] One Hall transition produces one estimator event.
[ ] Timestamp subtraction handles 16-bit rollover correctly.
[ ] Multi-overflow or standstill-timeout behavior is explicit.
[ ] Invalid states 000 and 111 are rejected.
[ ] Illegal/skipped transitions are rejected.
[ ] Direction is derived from the calibrated transition table.
[ ] The generated model contains a strong ADC1_2_IRQHandler().
[ ] Effective ADC/TIM4/TIM2 priorities are verified in generated C.
[ ] The Hall ISR contains only bounded capture/state work.
[ ] The ADC task consumes estimator data and performs interpolation.
[ ] No permanent fix was made directly inside regenerable generated files.
```
