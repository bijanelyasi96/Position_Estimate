---
title: "STM32F303RE AI Hardware Reference for PMSM Position Estimation"
document_type: ai_external_knowledge
source_document: "STM32F303xD STM32F303xE datasheet"
source_identifier: "DSH_2102984_00_1 / DocID026415 Rev 5"
source_revision: 5
source_date: "2016-10"
target_device: "STM32F303RET6"
target_family: "STM32F303xD/xE"
target_package: "LQFP64"
repository_context: "PMSM rotor position estimation with three Hall sensors"
language: en
status: derived_reference
---

# STM32F303RE AI Hardware Reference for PMSM Position Estimation

## 1. Purpose

This file converts the STM32F303xD/xE datasheet into structured external knowledge for AI-assisted development in this repository.

It is optimized for:

- selecting MCU resources for three-Hall PMSM rotor position and speed estimation;
- checking whether a proposed architecture fits the STM32F303RET6;
- separating datasheet facts from design decisions and assumptions;
- locating the relevant source pages quickly;
- preventing common mistakes about timer count, counter width, clock rate, pin availability, and electrical limits.

This is a technical rewrite and engineering index, not a bit-for-bit copy of the PDF.

## 2. Source and authority

| Field | Value |
|---|---|
| Manufacturer | STMicroelectronics |
| Source title | STM32F303xD STM32F303xE datasheet |
| Document ID | DocID026415 |
| Revision | Rev 5 |
| Publication state | Production data |
| Publication date | October 2016 |
| PDF length | 173 numbered pages, 174 PDF pages |
| Repository target | STM32F303RET6 |
| Relevant family member | STM32F303RE: 512-Kbyte Flash variant |
| Package code | T: LQFP |
| Temperature code | 6: -40 °C to +85 °C ambient grade |

### 2.1 Authority rules for AI use

Use this document for device capabilities, package availability, and electrical limits.

Do not use it as the sole authority for:

- timer register bit fields;
- timer input selection and internal trigger routing;
- Hall-sensor interface mode;
- XOR combination behavior;
- interrupt-vector names or priorities;
- DMA request mapping;
- clock-tree register configuration;
- GPIO alternate-function numbers;
- errata-sensitive behavior.

For those topics, verify against the matching STM32F303 reference manual, device errata, and the exact STM32CubeF3 device headers or CubeMX database.

If this file conflicts with a newer official ST document, the newer official document wins.

## 3. Exact device interpretation: STM32F303RET6

The project MCU name decodes as follows:

| Token | Meaning |
|---|---|
| STM32 | STMicroelectronics 32-bit MCU family |
| F3 | Mixed-signal and motor-control-oriented STM32 family |
| 303 | STM32F303 product line |
| R | 64-pin device class |
| E | 512-Kbyte Flash density |
| T | LQFP package |
| 6 | -40 °C to +85 °C ambient temperature grade |

### 3.1 Device-specific facts

The STM32F303RE provides:

- ARM Cortex-M4 32-bit core;
- hardware single-precision floating-point unit;
- DSP instructions;
- memory protection unit;
- maximum CPU frequency of 72 MHz;
- 512 Kbytes of embedded Flash;
- 64 Kbytes of SRAM on the data bus;
- 16 Kbytes of core-coupled memory (CCM);
- total embedded SRAM of 80 Kbytes, but split into two regions with different access characteristics;
- LQFP64 package;
- supply range of 2.0 V to 3.6 V;
- no external flexible memory controller on the R-package device;
- four 12-bit ADCs with 22 analog channels available in the 64-pin class;
- two DAC channels;
- seven comparators;
- four operational amplifiers;
- twelve DMA channels;
- CAN and USB interfaces;
- two advanced-control timers on the R device: TIM1 and TIM8;
- one 32-bit general-purpose timer: TIM2;
- 16-bit general-purpose timers including TIM3, TIM4, TIM15, TIM16, and TIM17;
- two 16-bit basic timers: TIM6 and TIM7.

### 3.2 Important family-versus-device warning

The family datasheet describes devices with 64, 100, and 144 pins. Some family features do not exist or are not bonded out on STM32F303RE.

In particular:

- TIM20 appears in family-wide timer descriptions, but the STM32F303Rx device table identifies only TIM1 and TIM8 as its advanced-control timers.
- The flexible memory controller is available on larger V/Z devices, not on STM32F303Rx.
- Pin tables contain rows and alternate functions for packages other than LQFP64.
- A signal listed somewhere in the family table is not automatically available on the selected LQFP64 pinout.

An AI must always filter family data through the STM32F303Rx and LQFP64 columns.

## 4. Architecture summary

### 4.1 Processing core

The MCU uses an ARM Cortex-M4 core with:

- 32-bit instruction and data processing;
- hardware division;
- single-cycle multiplication;
- DSP-oriented instructions;
- single-precision FPU;
- nested vectored interrupt controller;
- SysTick 24-bit downcounter;
- debug and trace support.

For the position-estimation project, the FPU is useful for development and validation, but angle and speed estimation can also be implemented using fixed-point arithmetic if execution time must be tightly bounded.

### 4.2 Memory

| Memory | Size | Engineering use |
|---|---:|---|
| Flash | 512 Kbytes | Program, constants, calibration tables |
| Main SRAM | 64 Kbytes | General data, stacks, DMA-accessible buffers subject to bus architecture |
| CCM SRAM | 16 Kbytes | Fast CPU data/instructions; verify DMA accessibility before placing DMA buffers here |

The first 32 Kbytes of main SRAM have hardware parity checking. CCM also has parity checking.

Do not treat the 80 Kbytes as one uniform RAM block. Linker placement matters.

### 4.3 Buses and DMA

The device contains an AHB and two APB peripheral buses plus a 12-channel DMA controller.

Position-estimation implications:

- Hall edge processing can be interrupt-driven.
- Timer capture values can potentially be moved by DMA when the exact timer/DMA mapping supports it.
- PWM, ADC triggering, control-loop execution, and Hall capture share MCU and bus resources.
- DMA buffers must be placed in memory reachable by the selected DMA controller.
- Exact request mapping must be verified in the reference manual.

## 5. Clocking facts that affect estimation

The device core operates up to 72 MHz. The timer subsystem has a special high-resolution capability:

- TIM1, TIM8, TIM2, TIM3, TIM4, TIM15, TIM16, and TIM17 can use the PLL as a clock source.
- The datasheet states that these timers can therefore be clocked at up to 144 MHz.
- At a 72 MHz timer clock, one timer tick is approximately 13.9 ns.
- At a 144 MHz timer clock, one timer tick is approximately 6.95 ns.

The timer input clock is not necessarily equal to the CPU clock. It depends on the clock-tree and timer clock configuration.

Every speed calculation must use the actual configured timer tick frequency, not an assumed 72 MHz constant.

Recommended runtime constant:

```c
timer_tick_hz = actual_timer_input_clock_hz / (prescaler + 1);
```

For two captures separated by an overflow-safe tick delta:

```c
edge_period_s = delta_ticks / timer_tick_hz;
```

## 6. Timer inventory

### 6.1 Timer comparison

| Timer group | Counter width | Count modes | Capture/compare channels | DMA request | Complementary outputs | Primary project role |
|---|---:|---|---:|---|---|---|
| TIM1, TIM8 | 16-bit | Up, down, center-aligned | 4 | Yes | Yes | Motor-control PWM, synchronized ADC triggers |
| TIM2 | 32-bit | Up, down, center-aligned | 4 | Yes | No | Preferred long-range Hall edge timestamp |
| TIM3, TIM4 | 16-bit | Up, down, center-aligned | 4 | Yes | No | Hall capture, auxiliary timing, encoder mode |
| TIM15 | 16-bit | Up | 2 | Yes | One complementary channel | Auxiliary capture/PWM |
| TIM16, TIM17 | 16-bit | Up | 1 each | Yes | One complementary channel | Single-channel capture or time base |
| TIM6, TIM7 | 16-bit | Up | 0 | Yes | No | Basic time base or DAC trigger |
| SysTick | 24-bit downcounter | Down | 0 | No timer capture | No | OS/system tick, not Hall edge capture |

Prescaler division can be any integer from 1 to 65536 for the listed peripheral timers.

### 6.2 TIM2 is the strongest default capture candidate

TIM2 has:

- a 32-bit counter;
- four independent input-capture/output-compare channels;
- DMA request generation;
- external clock and synchronization features;
- encoder-interface support;
- debug freeze support.

A 32-bit timestamp reduces overflow-handling pressure at low motor speed.

Maximum free-running time before a 32-bit wrap, with no prescaling:

| Timer clock | Tick | Approximate wrap interval |
|---:|---:|---:|
| 72 MHz | 13.9 ns | 59.65 s |
| 144 MHz | 6.95 ns | 29.825 s |

A prescaler increases the wrap interval at the cost of timing resolution.

### 6.3 TIM3 and TIM4

TIM3 and TIM4 each provide:

- a 16-bit counter;
- four capture/compare channels;
- input capture;
- PWM and output compare;
- independent DMA request generation;
- quadrature encoder support;
- timer-link synchronization;
- debug freeze.

They are suitable when a 16-bit period is sufficient or when overflow is extended in software.

### 6.4 Advanced timers

TIM1 and TIM8 are designed for motor control and support:

- three-phase PWM generation;
- complementary outputs;
- programmable dead time;
- emergency/break handling;
- edge- and center-aligned PWM;
- input capture and output compare;
- synchronization and timer linking;
- debug behavior that can stop PWM outputs safely.

If one advanced timer already generates the inverter PWM and triggers ADC sampling, avoid reallocating its channels without first checking the complete PWM, break, trigger, and pin plan.

## 7. Timer electrical limits

The datasheet gives the following timer characteristics:

| Parameter | Limit |
|---|---|
| Timer resolution at 72 MHz | 13.9 ns minimum tick |
| Timer resolution at 144 MHz | 6.95 ns minimum tick |
| External timer clock on CH1-CH4 | Up to half of timer clock |
| Example at 72 MHz timer clock | Up to 36 MHz external input |
| Counter resolution | 16 bits except TIM2 |
| TIM2 resolution | 32 bits |

These limits are device-level timing capabilities. Actual Hall inputs are normally far slower. Signal integrity, digital filtering, ISR latency, and timer configuration are more likely to dominate than the raw input-frequency ceiling.

## 8. LQFP64 pin-awareness

The exact package pinout must be used. The LQFP64 device exposes ports including PA, PB, PC, PD2, PF0, and PF1, subject to package bonding.

Examples of timer-capable pins visible in the family pin table include:

- TIM2 channels on PA0/PA1/PA2/PA3 and alternative pins such as PA5, PA9, PA10, PA15, PB3, PB10, and PB11;
- TIM3 channels on PA6/PA7, PB0/PB1, PB4/PB5, and PC6-PC9;
- TIM4 channels on PB6-PB9 and selected PA pins;
- TIM1 and TIM8 functions on multiple PA, PB, and PC pins.

This list is intentionally not a final board assignment.

Before selecting Hall pins, verify all of the following:

1. the pin exists in the LQFP64 column;
2. the requested timer channel is mapped to that pin;
3. the correct alternate-function number is configured;
4. the pin does not conflict with PWM, ADC, CAN, USB, SWD, crystal, or board functions;
5. the input voltage is compatible with the MCU supply and I/O type;
6. any required pull-up or pull-down is provided;
7. the pin remains available after debug and boot configuration decisions.

Use the schematic, STM32CubeMX, device header, and official alternate-function table together. Do not choose pins from a larger-package diagram.

## 9. GPIO and input-signal considerations

The device provides both standard and 5 V-tolerant I/O types, but tolerance depends on the individual pin and operating conditions.

For each Hall input:

- verify its pin type in the pin-definition table;
- verify the Hall interface voltage;
- do not assume every GPIO is 5 V tolerant;
- configure a defined idle level;
- consider external or internal pull resistors according to the Hall output topology;
- use timer digital filtering if appropriate;
- reject illegal Hall states in software;
- ensure input transitions satisfy the configured timer sampling/filter requirements.

If the Hall outputs are open-drain or open-collector, the pull-up voltage must remain safe for the chosen MCU pin.

## 10. Analog and motor-control resources

### 10.1 ADC subsystem

The STM32F303xD/xE family contains four fast 12-bit ADCs. The R-package device exposes 22 analog channels.

The datasheet advertises:

- selectable resolution of 12, 10, 8, or 6 bits;
- conversion range from 0 V to 3.6 V, constrained by analog supply/reference conditions;
- conversion time down to approximately 0.20 microseconds under qualifying settings;
- separate analog supply;
- external trigger support;
- DMA support;
- analog watchdog features;
- injected and regular conversion capabilities as defined by the reference manual.

For field-oriented control, ADC conversion is commonly synchronized to a stable PWM-counter event. Adding Hall capture should not change the ADC sampling instant. Hall transitions are asynchronous events that update the position/speed observer state used by the next control-loop execution.

### 10.2 DAC, comparators, and op-amps

The device provides:

- two 12-bit DAC channels;
- seven high-speed rail-to-rail comparators;
- four operational amplifiers capable of programmable-gain operation.

These can support current sensing, protection, diagnostics, and test stimulus. Their exact routing and electrical limits must be checked before use.

## 11. Power, reset, and operating limits

### 11.1 Supply

| Item | Datasheet value |
|---|---|
| Main digital and I/O supply range | 2.0 V to 3.6 V |
| Analog supply availability | Separate analog supply pins |
| VBAT | Supports RTC and backup domain |
| Temperature grade for STM32F303RET6 | -40 °C to +85 °C ambient |
| Family junction range | Up to +125 °C as specified by conditions |

Absolute maximum ratings are survival limits, not normal operating targets.

### 11.2 Reset and low-power behavior

The device includes:

- power-on/power-down reset;
- programmable voltage detector;
- external NRST;
- Sleep, Stop, and Standby modes;
- independent and window watchdogs.

The source recommends a 0.1 microfarad capacitor close to NRST as part of the reset network.

For traction or safety-related control, define what happens to PWM, captured position, speed state, and Hall validity after reset, brownout, watchdog reset, or clock failure.

## 12. Communication and debug resources

Available family interfaces include:

- three I2C interfaces;
- four SPI interfaces, with some multiplexed I2S capability;
- three USARTs;
- two UARTs;
- one CAN 2.0B Active interface;
- one USB 2.0 full-speed interface with low-power management;
- SWD/JTAG and embedded trace support;
- a 96-bit unique device identifier.

Availability at a given pin depends on the LQFP64 alternate-function map.

Keep SWD pins available during early position-estimator development unless the pin budget forces a documented tradeoff.

## 13. Position-estimation interpretation

### 13.1 Motor geometry

Project assumptions supplied outside the datasheet:

- PMSM;
- three digital Hall sensors;
- five pole pairs;
- mechanical frequency may be 3 Hz in example analysis.

These are project facts, not MCU-datasheet facts.

Relationships:

```text
electrical_angle = pole_pairs * mechanical_angle
electrical_frequency = pole_pairs * mechanical_frequency
```

For five pole pairs at 3 Hz mechanical speed:

```text
electrical_frequency = 5 * 3 Hz = 15 Hz
electrical_period = 1 / 15 s = 66.6667 ms
```

With ideal six-step Hall commutation, one legal Hall state spans 60 electrical degrees. Therefore:

```text
Hall sector time = electrical_period / 6
                 = 66.6667 ms / 6
                 = 11.1111 ms
```

There are:

```text
6 * pole_pairs = 30
```

legal Hall sectors per mechanical revolution.

### 13.2 Hall states

Three Hall inputs yield eight binary combinations. In a correctly phased, ideal three-Hall arrangement:

- six states are legal;
- 000 and 111 are normally illegal;
- the legal state sequence depends on wiring, sensor placement, phase convention, and direction;
- reversing direction reverses the sequence.

Never hard-code a generic Hall-state-to-angle table without validating the real motor and wiring.

Store and validate:

- current raw Hall state;
- previous raw Hall state;
- decoded sector;
- direction;
- last capture timestamp;
- current capture timestamp;
- overflow-safe tick delta;
- filtered sector period or electrical speed;
- validity/fault flags;
- calibration offset between Hall transitions and the chosen electrical-angle reference.

### 13.3 Angle observability

Three Hall sensors provide coarse absolute electrical position:

- the current legal state identifies one 60-electrical-degree sector;
- it does not directly reveal exact position inside that sector;
- at standstill, the sector is known but intra-sector angle is not;
- between edges, angle can be interpolated using estimated speed;
- interpolation uncertainty grows during acceleration, deceleration, reversal, or missed edges.

A robust estimator should explicitly distinguish:

1. sector angle: directly inferred from Hall state;
2. interpolated angle: predicted inside the current sector;
3. calibrated electrical offset: motor-specific correction;
4. estimator confidence: degraded by stale, illegal, or inconsistent transitions.

### 13.4 Speed from captured time

If every valid Hall transition represents 60 electrical degrees:

```text
electrical_revolutions_per_transition = 1 / 6
mechanical_revolutions_per_transition = 1 / (6 * pole_pairs)
```

Mechanical speed:

```text
mechanical_frequency_hz =
    timer_tick_hz /
    (delta_ticks * 6 * pole_pairs)
```

Mechanical RPM:

```text
mechanical_rpm =
    60 * timer_tick_hz /
    (delta_ticks * 6 * pole_pairs)
```

For five pole pairs:

```text
mechanical_rpm = 2 * timer_tick_hz / delta_ticks
```

The simplified final expression is valid only when:

- every adjacent valid Hall transition is captured;
- each transition corresponds to exactly 60 electrical degrees;
- the timer tick frequency is correct;
- no transition is duplicated or skipped.

### 13.5 Recommended timer allocation

A reasonable starting allocation is:

| Function | Preferred resource | Reason |
|---|---|---|
| Center-aligned inverter PWM | TIM1 or TIM8 | Advanced motor-control features |
| ADC trigger | Event derived from PWM timer | Stable sampling phase |
| FOC/SVM execution | ADC EOC/JEOC or synchronized control interrupt | Keeps control loop phase-locked to sampling |
| Hall transition timestamp | TIM2 | 32-bit range, four input-capture channels |
| System time | SysTick or an already assigned basic/general timer | Separate software scheduling from edge capture |
| Auxiliary diagnostics | Unused TIM3/TIM4/TIM15/TIM16/TIM17 | Depends on final pin map |

This is a recommended architecture, not a datasheet mandate.

One capture timer can be sufficient. Three Hall sensors do not automatically require three timers.

Possible approaches:

- capture a hardware-combined Hall transition signal and read all three GPIO states at each edge;
- connect the three Hall signals to separate channels of one multi-channel timer;
- use EXTI interrupts for state changes and a free-running timer for timestamps;
- use a device-supported Hall-sensor timer mode after verifying the reference manual.

The best choice depends on available pins, noise filtering, desired edge attribution, and the exact internal routing.

### 13.6 Interaction with the existing control architecture

Assumed existing architecture:

- an advanced timer generates center-aligned PWM using an up/down counter;
- ADC start-of-conversion occurs at a PWM counter peak;
- control and SVM execute after ADC end-of-conversion;
- TIM2 may already be used by another internal function.

Adding Hall estimation should normally introduce an asynchronous capture path without moving the PWM or ADC events:

1. A Hall edge arrives.
2. The capture timer latches its counter.
3. A short ISR or DMA path records the timestamp and Hall state.
4. Transition validity and direction are updated.
5. Period/speed is updated or queued for filtering.
6. The PWM-synchronous control loop reads a coherent estimator snapshot.
7. The control loop uses sector plus interpolation to obtain electrical angle.

The Hall ISR should not execute the complete FOC algorithm. Keep it bounded and deterministic.

If TIM2 is already used, first identify its exact responsibility. “System time” is not specific enough to justify replacement. Determine whether it is:

- HAL time base;
- RTOS tick;
- free-running timestamp;
- scheduler trigger;
- communication timeout;
- another peripheral trigger.

Then decide whether that function can move to SysTick, TIM6, TIM7, or another available timer.

## 14. Data model recommended for the codebase

```c
typedef struct {
    uint8_t raw_state;              // Three Hall bits
    uint8_t previous_state;
    int8_t direction;               // -1, 0, +1
    uint8_t sector;                 // 0..5 when valid
    bool state_valid;
    bool transition_valid;
    bool speed_valid;
    bool angle_valid;

    uint32_t capture_ticks;
    uint32_t previous_capture_ticks;
    uint32_t delta_ticks;

    float electrical_speed_rad_s;
    float mechanical_speed_rad_s;
    float sector_start_angle_rad;
    float interpolated_angle_rad;
    float calibration_offset_rad;

    uint32_t illegal_state_count;
    uint32_t illegal_transition_count;
    uint32_t timeout_count;
} HallEstimatorState;
```

This is a design recommendation. Adapt types and floating-point use to the code-generation and real-time constraints.

## 15. Required fault handling

At minimum, detect:

- Hall state 000;
- Hall state 111;
- transition to a nonadjacent sector;
- repeated edge without a state change;
- capture delta below the physical minimum;
- timeout with no edge while torque or speed is expected;
- timer overflow handling failure;
- direction inconsistency;
- implausible acceleration;
- mismatch between command, observer, and Hall direction;
- stale angle interpolation.

On a fault, retain enough information for diagnosis:

- raw state;
- previous state;
- timer capture;
- delta;
- PWM/control-loop timestamp;
- direction;
- fault reason.

The safety response is system-specific and is not defined by this datasheet.

## 16. Startup and low-speed behavior

At startup:

- read all three Hall inputs before enabling torque;
- reject 000 and 111;
- map the legal state to a calibrated electrical sector;
- do not claim an exact angle within the sector;
- initialize speed as invalid or zero according to the control design;
- use a startup strategy that respects the possible 60-degree sector uncertainty;
- transition to interpolation only after valid sequential edges establish direction and period.

Applying a fixed field at the center of an assumed sector can produce reverse torque if the angle convention, calibration offset, or state mapping is wrong. Validate the map with low-current tests and a known rotation direction.

## 17. Implementation checklist

### Hardware and pin mapping

- [ ] Confirm exact part number is STM32F303RET6.
- [ ] Confirm Hall voltage and output topology.
- [ ] Select three LQFP64 pins.
- [ ] Verify timer channel and alternate function for each selected pin.
- [ ] Check conflicts with PWM, ADC, CAN, USB, crystals, boot, and SWD.
- [ ] Define pull resistors and filtering.
- [ ] Document Hall A/B/C to MCU-pin mapping.

### Clock and timer

- [ ] Calculate the actual timer input clock from the clock tree.
- [ ] Choose prescaler for low-speed range and high-speed resolution.
- [ ] Define overflow-safe timestamp subtraction.
- [ ] Define timer wrap behavior.
- [ ] Verify digital input-filter configuration.
- [ ] Verify capture polarity and edge strategy.
- [ ] Verify interrupt or DMA request mapping in the reference manual.
- [ ] Freeze or deliberately continue the timer during debug.

### Estimator

- [ ] Measure the real six-state sequence in both directions.
- [ ] Calibrate sector-to-electrical-angle offset.
- [ ] Reject illegal states and illegal transitions.
- [ ] Calculate speed from valid transition intervals.
- [ ] Filter speed without excessive phase delay.
- [ ] Interpolate angle only when confidence is valid.
- [ ] Define timeout behavior at very low speed and standstill.
- [ ] Make state transfer to the FOC loop atomic/coherent.

### Verification

- [ ] Unit-test all legal forward transitions.
- [ ] Unit-test all legal reverse transitions.
- [ ] Test 000 and 111.
- [ ] Test skipped, repeated, and bouncing transitions.
- [ ] Test timer wrap.
- [ ] Test zero speed and startup.
- [ ] Test acceleration and reversal.
- [ ] Compare measured mechanical speed with a trusted reference.
- [ ] Confirm electrical angle convention matches Park/Clarke/SVM conventions.
- [ ] Verify ISR execution time and control-loop jitter.

## 18. Common AI failure modes

Do not make these claims:

- “The MCU has three Hall sensors.”  
  The motor has Hall sensors; the MCU has GPIO/timer inputs.

- “Three Hall sensors require three timers.”  
  One timer may be sufficient.

- “TIM2 is a 16-bit timer.”  
  TIM2 is 32-bit on this device.

- “All STM32F303xE features apply to STM32F303RE.”  
  Package and device-class filtering is required.

- “TIM20 is available because it appears in the family timer table.”  
  The R-device feature table identifies TIM1 and TIM8 as its two advanced timers.

- “The CPU and all timers run at 72 MHz.”  
  Actual timer clocking depends on configuration; supported timers may reach 144 MHz.

- “The Hall state gives exact rotor angle.”  
  It gives a 60-electrical-degree sector before interpolation/calibration.

- “The Hall sequence is universally 001, 101, 100, 110, 010, 011.”  
  Sequence depends on wiring, convention, direction, and sensor placement.

- “000 and 111 are valid sectors.”  
  They are normally fault states in a three-Hall six-step pattern.

- “Any listed alternate-function pin is available in LQFP64.”  
  The package column must be checked.

- “This datasheet defines the Hall XOR register configuration.”  
  Register-level behavior belongs to the reference manual.

## 19. Compact machine-readable fact block

```yaml
mcu:
  part: STM32F303RET6
  family: STM32F303xD_xE
  package: LQFP64
  flash_kib: 512
  main_sram_kib: 64
  ccm_sram_kib: 16
  cpu:
    core: Cortex-M4
    fpu: true
    max_mhz: 72
  supply_v:
    min: 2.0
    max: 3.6
  ambient_temperature_c:
    min: -40
    max: 85
  timers:
    advanced_available_on_rx: [TIM1, TIM8]
    general_32bit: [TIM2]
    general_16bit: [TIM3, TIM4, TIM15, TIM16, TIM17]
    basic_16bit: [TIM6, TIM7]
    capture_channels:
      TIM2: 4
      TIM3: 4
      TIM4: 4
      TIM15: 2
      TIM16: 1
      TIM17: 1
    max_supported_timer_clock_mhz: 144
  analog:
    adc_count: 4
    adc_resolution_bits: 12
    adc_channels_on_rx: 22
    dac_channels: 2
    comparators: 7
    opamps: 4
  dma_channels: 12
project:
  motor: PMSM
  hall_sensor_count: 3
  pole_pairs: 5
  hall_sectors_per_electrical_revolution: 6
  hall_sectors_per_mechanical_revolution: 30
  preferred_capture_timer: TIM2
source:
  document_id: DocID026415
  revision: 5
  date: 2016-10
```

## 20. Source map

Use these source sections when checking a statement against the original PDF:

| Topic | Datasheet section | Printed pages |
|---|---|---:|
| Device description | 2 | 12-15 |
| Core, memory, power, clocks, GPIO, DMA | 3.1-3.13 | 16-23 |
| ADC, DAC, op-amps, comparators | 3.14-3.17 | 23-25 |
| Timers and watchdogs | 3.18 | 25-28 |
| Communications and debug | 3.20-3.28 | 28-33 |
| LQFP64 pinout | Figure 4 | 35 |
| Pin definitions | Table 13 | 40-52 |
| Alternate-function mapping | Table 14 | 53-63 |
| Memory map | Section 5 | 64-67 |
| Absolute maximum ratings | 6.2 | 70-72 |
| Operating conditions | 6.3 | 72-151 |
| I/O characteristics | 6.3.15 | 118-123 |
| Timer electrical characteristics | 6.3.17, Table 70 | 124 |
| ADC characteristics | 6.3.19 | 132-143 |
| LQFP64 package information | 7.6 | 165-167 |
| Thermal characteristics | 7.7 | 168-170 |
| Part numbering | 8 | 171 |
| Revision history | 9 | 172-173 |

## 21. Documents still required for implementation

Before generating final peripheral initialization code, add or consult:

1. STM32F303xD/xE reference manual covering timer registers, clock tree, DMA, GPIO, ADC, and interrupts.
2. STM32F303xD/xE device errata.
3. Exact board schematic and pin assignment.
4. Motor Hall-state sequence and calibrated electrical offset.
5. Generated STM32 device headers or STM32CubeF3 HAL/LL definitions.
6. Existing PWM, ADC, system-time, and interrupt configuration from this repository.

The datasheet establishes that the hardware can support the proposed architecture. It does not by itself define a complete, verified firmware configuration.
