/*
 * File: Open_Loop2024.c
 *
 * Code generated for Simulink model 'Open_Loop2024'.
 *
 * Model version                  : 2.20
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Mon Jul 20 09:16:43 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Open_Loop2024.h"
#include "rtwtypes.h"
#include "Open_Loop2024_types.h"
#include "Open_Loop2024_private.h"
#include "stm_dac_ll.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "stm_adc_ll.h"
#include <stddef.h>
#include "stm_timer_ll.h"

/* Block signals (default storage) */
B_Open_Loop2024_T Open_Loop2024_B;

/* Block states (default storage) */
DW_Open_Loop2024_T Open_Loop2024_DW;

/* Real-time model */
static RT_MODEL_Open_Loop2024_T Open_Loop2024_M_;
RT_MODEL_Open_Loop2024_T *const Open_Loop2024_M = &Open_Loop2024_M_;

/* Forward declaration for local functions */
static void Open_Loop2024_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj);
static void Open_Loop20_PWMOutput_setupImpl(stm32cube_blocks_PWMOutput_Op_T *obj);

/* Forward declaration for local functions */
static void Open_Loop202_SystemCore_setup_p(stm32cube_blocks_TimerCapture_T *obj);

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 1'
 *    '<S42>/Hall Value of 2'
 */
real32_T Open_Loop2024_HallValueof1(void)
{
  /* SignalConversion generated from: '<S53>/position' incorporates:
   *  Constant: '<S53>/Constant'
   */
  return 0.16667F;
}

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 2'
 *    '<S42>/Hall Value of 3'
 */
real32_T Open_Loop2024_HallValueof2(void)
{
  /* SignalConversion generated from: '<S54>/position' incorporates:
   *  Constant: '<S54>/Constant'
   */
  return 0.33333F;
}

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 3'
 *    '<S42>/Hall Value of 4'
 */
real32_T Open_Loop2024_HallValueof3(void)
{
  /* SignalConversion generated from: '<S55>/position' incorporates:
   *  Constant: '<S55>/Constant'
   */
  return 0.5F;
}

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 4'
 *    '<S42>/Hall Value of 5'
 */
real32_T Open_Loop2024_HallValueof4(void)
{
  /* SignalConversion generated from: '<S56>/position' incorporates:
   *  Constant: '<S56>/Constant'
   */
  return 0.66667F;
}

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 5'
 *    '<S42>/Hall Value of 6'
 */
real32_T Open_Loop2024_HallValueof5(void)
{
  /* SignalConversion generated from: '<S57>/position' incorporates:
   *  Constant: '<S57>/Constant'
   */
  return 0.83333F;
}

/*
 * Output and update for action system:
 *    '<S43>/Hall Value of 7'
 *    '<S42>/Hall Value of 1'
 *    '<S42>/Hall Value of 7'
 *    '<S31>/Hall Value of 7'
 */
real32_T Open_Loop2024_HallValueof7(void)
{
  /* SignalConversion generated from: '<S59>/position' incorporates:
   *  Constant: '<S59>/Constant'
   */
  return 0.0F;
}

/*
 * System reset for atomic system:
 *    '<S1>/MATLAB Function1'
 *    '<S1>/MATLAB Function2'
 *    '<S1>/MATLAB Function4'
 */
void Open_Loop_MATLABFunction1_Reset(DW_MATLABFunction1_Open_Loop2_T *localDW)
{
  localDW->stable_state_not_empty = false;
  localDW->counter = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S1>/MATLAB Function1'
 *    '<S1>/MATLAB Function2'
 *    '<S1>/MATLAB Function4'
 */
void Open_Loop2024_MATLABFunction1(boolean_T rtu_In, boolean_T *rty_Out,
  DW_MATLABFunction1_Open_Loop2_T *localDW)
{
  if (!localDW->stable_state_not_empty) {
    localDW->stable_state = rtu_In;
    localDW->stable_state_not_empty = true;
  }

  if (rtu_In == localDW->stable_state) {
    localDW->counter = 0U;
  } else {
    uint32_T tmp;
    tmp = localDW->counter + 1U;
    if (localDW->counter + 1U > 255U) {
      tmp = 255U;
    }

    localDW->counter = (uint8_T)tmp;
    if (localDW->counter >= 5) {
      localDW->stable_state = rtu_In;
      localDW->counter = 0U;
    }
  }

  *rty_Out = localDW->stable_state;
}

static void Open_Loop2024_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;

  /* Start for MATLABSystem: '<S18>/Analog to Digital Converter' */
  obj->isInitialized = 1;
  adcStructLoc.InternalBufferPtr = (void *)(NULL);

  /* Start for MATLABSystem: '<S18>/Analog to Digital Converter' */
  adcStructLoc.InjectedNoOfConversion = 0U;
  adcStructLoc.peripheralPtr = ADC1;
  adcStructLoc.dmaPeripheralPtr = NULL;
  adcStructLoc.dmastream = 0;
  adcStructLoc.DataTransferMode = ADC_DR_TRANSFER;
  adcStructLoc.DmaTransferMode = ADC_DMA_TRANSFER_LIMITED;
  adcStructLoc.InternalBufferSize = 1U;
  adcStructLoc.RegularNoOfConversion = 1U;
  obj->ADCHandle = ADC_Handle_Init(&adcStructLoc, ADC_INTERRUPT_MODE, 1,
    ADC_TRIGGER_AND_READ, LL_ADC_REG_SEQ_SCAN_DISABLE);
  enableADCAutomaticCalibrationOffset(obj->ADCHandle, 0);
  enableADC(obj->ADCHandle);
  startADCConversionForExternalTrigger(obj->ADCHandle, 1);
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

static void Open_Loop20_PWMOutput_setupImpl(stm32cube_blocks_PWMOutput_Op_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<S61>/PWM Output' */
  b.PeripheralPtr = TIM1;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S61>/PWM Output' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 32);
  enableTimerChannel1(obj->TimerHandle, ENABLE_CH_CHN);
  enableTimerChannel2(obj->TimerHandle, ENABLE_CH_CHN);
  enableTimerChannel3(obj->TimerHandle, ENABLE_CH_CHN);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S61>/PWM Output' */
    enableCounter(obj->TimerHandle, false);
  }
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if (fabsf(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = floorf(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = ceilf(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

static void Open_Loop202_SystemCore_setup_p(stm32cube_blocks_TimerCapture_T *obj)
{
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<S4>/Timer Capture' */
  obj->isInitialized = 1;
  b.PeripheralPtr = TIM4;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<S4>/Timer Capture' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 14);
  enableTimerChannel1(obj->TimerHandle, ENABLE_CH);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<S4>/Timer Capture' */
    enableCounter(obj->TimerHandle, false);
  }

  obj->isSetupComplete = true;
}

/* Model initialize function */
void Open_Loop2024_initialize(void)
{
  /* SystemInitialize for S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem'
   */

  /* System initialize for function-call system: '<Root>/Function-Call Subsystem' */
  {
    MW_DAC_Type_T b;

    /* InitializeConditions for RelationalOperator: '<S30>/Compare' incorporates:
     *  Delay: '<S26>/Delay One Step1'
     */
    Open_Loop2024_DW.DelayOneStep1_DSTATE = true;

    /* InitializeConditions for Delay: '<S26>/Delay One Step' */
    Open_Loop2024_DW.DelayOneStep_DSTATE = 571U;

    /* InitializeConditions for Delay: '<S77>/Delay' */
    Open_Loop2024_DW.icLoad = true;

    /* InitializeConditions for Delay: '<S81>/Delay' */
    Open_Loop2024_DW.icLoad_m = true;

    /* Start for MATLABSystem: '<S66>/Digital Port Read' */
    Open_Loop2024_DW.obj_g.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_g.isInitialized = 1;
    Open_Loop2024_DW.obj_g.isSetupComplete = true;

    /* Start for MATLABSystem: '<S70>/Digital Port Read' */
    Open_Loop2024_DW.obj_m.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_m.isInitialized = 1;
    Open_Loop2024_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<S68>/Digital Port Read' */
    Open_Loop2024_DW.obj_mz.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_mz.isInitialized = 1;
    Open_Loop2024_DW.obj_mz.isSetupComplete = true;

    /* Start for MATLABSystem: '<S18>/Analog to Digital Converter' */
    Open_Loop2024_DW.obj.isInitialized = 0;
    Open_Loop2024_DW.obj.matlabCodegenIsDeleted = false;
    Open_Loop2024_SystemCore_setup(&Open_Loop2024_DW.obj);

    /* Start for MATLABSystem: '<S20>/Digital Port Read' */
    Open_Loop2024_DW.obj_i3.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_i3.isInitialized = 1;
    Open_Loop2024_DW.obj_i3.isSetupComplete = true;

    /* Start for MATLABSystem: '<S22>/Digital Port Read' */
    Open_Loop2024_DW.obj_e.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_e.isInitialized = 1;
    Open_Loop2024_DW.obj_e.isSetupComplete = true;

    /* Start for MATLABSystem: '<S24>/Digital Port Read' */
    Open_Loop2024_DW.obj_mb.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_mb.isInitialized = 1;
    Open_Loop2024_DW.obj_mb.isSetupComplete = true;

    /* Start for MATLABSystem: '<S61>/PWM Output' */
    Open_Loop2024_DW.obj_j.matlabCodegenIsDeleted = false;
    Open_Loop2024_DW.obj_j.isSetupComplete = false;
    Open_Loop2024_DW.obj_j.isInitialized = 1;
    Open_Loop20_PWMOutput_setupImpl(&Open_Loop2024_DW.obj_j);
    Open_Loop2024_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Digital to Analog Converter' */
    Open_Loop2024_DW.obj_gc.isInitialized = 1;
    b.peripheralPtr = DAC1;
    b.dualChannel = 0;
    Open_Loop2024_DW.obj_gc.DACHandle = MW_DAC_Init(&b);
    MW_DAC_Enable(Open_Loop2024_DW.obj_gc.DACHandle, LL_DAC_CHANNEL_2);
  }

  /* End of SystemInitialize for S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' */

  /* SystemInitialize for S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Subsystem'
   */

  /* System initialize for function-call system: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<S109>/Digital Port Read' */
  Open_Loop2024_DW.obj_b.matlabCodegenIsDeleted = false;
  Open_Loop2024_DW.obj_b.isInitialized = 1;
  Open_Loop2024_DW.obj_b.isSetupComplete = true;

  /* Start for MATLABSystem: '<S111>/Digital Port Read' */
  Open_Loop2024_DW.obj_h.matlabCodegenIsDeleted = false;
  Open_Loop2024_DW.obj_h.isInitialized = 1;
  Open_Loop2024_DW.obj_h.isSetupComplete = true;

  /* Start for MATLABSystem: '<S113>/Digital Port Read' */
  Open_Loop2024_DW.obj_i.matlabCodegenIsDeleted = false;
  Open_Loop2024_DW.obj_i.isInitialized = 1;
  Open_Loop2024_DW.obj_i.isSetupComplete = true;

  /* Start for MATLABSystem: '<S4>/Timer Capture' */
  Open_Loop2024_DW.obj_p.isInitialized = 0;
  Open_Loop2024_DW.obj_p.matlabCodegenIsDeleted = false;
  Open_Loop202_SystemCore_setup_p(&Open_Loop2024_DW.obj_p);

  /* Start for MATLABSystem: '<S91>/Digital Port Write' */
  Open_Loop2024_DW.obj_d.matlabCodegenIsDeleted = false;
  Open_Loop2024_DW.obj_d.isInitialized = 1;
  Open_Loop2024_DW.obj_d.isSetupComplete = true;

  /* End of SystemInitialize for S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' */
}

/* Model terminate function */
void Open_Loop2024_terminate(void)
{
  /* Terminate for S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem'
   */

  /* Termination for function-call system: '<Root>/Function-Call Subsystem' */

  /* Terminate for MATLABSystem: '<S66>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_g.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S66>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S70>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_m.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S70>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S68>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_mz.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_mz.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S68>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S18>/Analog to Digital Converter' */
  if (!Open_Loop2024_DW.obj.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj.matlabCodegenIsDeleted = true;
    if ((Open_Loop2024_DW.obj.isInitialized == 1) &&
        Open_Loop2024_DW.obj.isSetupComplete) {
      ADC_Handle_Deinit(Open_Loop2024_DW.obj.ADCHandle, ADC_INTERRUPT_MODE, 1);
    }
  }

  /* End of Terminate for MATLABSystem: '<S18>/Analog to Digital Converter' */

  /* Terminate for MATLABSystem: '<S20>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_i3.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_i3.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S20>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S22>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_e.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S22>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S24>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_mb.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_mb.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S24>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S61>/PWM Output' */
  if (!Open_Loop2024_DW.obj_j.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((Open_Loop2024_DW.obj_j.isInitialized == 1) &&
        Open_Loop2024_DW.obj_j.isSetupComplete) {
      disableCounter(Open_Loop2024_DW.obj_j.TimerHandle);
      disableTimerInterrupts(Open_Loop2024_DW.obj_j.TimerHandle, 32);
      disableTimerChannel1(Open_Loop2024_DW.obj_j.TimerHandle, ENABLE_CH_CHN);
      disableTimerChannel2(Open_Loop2024_DW.obj_j.TimerHandle, ENABLE_CH_CHN);
      disableTimerChannel3(Open_Loop2024_DW.obj_j.TimerHandle, ENABLE_CH_CHN);
    }
  }

  /* End of Terminate for MATLABSystem: '<S61>/PWM Output' */

  /* End of Terminate for S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' */

  /* Terminate for S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Subsystem'
   */

  /* Termination for function-call system: '<Root>/Subsystem' */

  /* Terminate for MATLABSystem: '<S109>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_b.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_b.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S109>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S111>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_h.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_h.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S111>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S113>/Digital Port Read' */
  if (!Open_Loop2024_DW.obj_i.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S113>/Digital Port Read' */

  /* Terminate for MATLABSystem: '<S4>/Timer Capture' */
  if (!Open_Loop2024_DW.obj_p.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((Open_Loop2024_DW.obj_p.isInitialized == 1) &&
        Open_Loop2024_DW.obj_p.isSetupComplete) {
      disableCounter(Open_Loop2024_DW.obj_p.TimerHandle);
      disableTimerInterrupts(Open_Loop2024_DW.obj_p.TimerHandle, 14);
      disableTimerChannel1(Open_Loop2024_DW.obj_p.TimerHandle, ENABLE_CH);
    }
  }

  /* End of Terminate for MATLABSystem: '<S4>/Timer Capture' */

  /* Terminate for MATLABSystem: '<S91>/Digital Port Write' */
  if (!Open_Loop2024_DW.obj_d.matlabCodegenIsDeleted) {
    Open_Loop2024_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S91>/Digital Port Write' */

  /* End of Terminate for S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' */
}

void Open_Loop2024_configure_interrupts(void)
{
  /* Register interrupt service routine */
  MW_NVIC_ConfigureIRQ(33,&ADC1_2_IRQHandler,2);
  MW_NVIC_EnableIRQ(33);

  /* Register interrupt service routine */
  MW_NVIC_ConfigureIRQ(45,&TIM4_IRQHandler,3);
  MW_NVIC_EnableIRQ(45);
}

/* Hardware Interrupt Block: '<S84>/Hardware Interrupt' */
void ADC1_2_IRQHandler(void)
{
  /* Event: ADC1 Reg EoCS */
  /* Check event ADC1 Reg EoCS occurred */
  if (0 != (
#if defined(MW_ADC1_ENABLED) && !defined(MW_ADC1_DMA_ENABLED) && (defined(MW_ADC1_REG_IRQ_ENABLED) && (MW_ADC1_REG_IRQ_ENABLED==1))
            (0 != LL_ADC_IsEnabledIT_EOS(ADC1)) && (0 != ADC_IsActiveFlagEOCS
        (&(MW_ADC1_VAR)))
#else
            (0 != LL_ADC_IsEnabledIT_EOS(ADC1)) && (0 != LL_ADC_IsActiveFlag_EOS
        (ADC1))
#endif
            )) {
    if (1 == runModel) {
      {
        /* RateTransition generated from: '<Root>/Subsystem' */
        Open_Loop2024_B.TmpRTBAtSubsystemOutport1 =
          Open_Loop2024_DW.TmpRTBAtSubsystemOutport1_Buffe;

        /* S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' */

        /* Output and update for function-call system: '<Root>/Function-Call Subsystem' */
        {
          uint32_T channelSelect;
          real_T rtb_Gain1_cv;
          real_T rtb_Product;
          int32_T tmp;
          real32_T cos_t;
          real32_T rtb_Gain;
          real32_T rtb_Merge1_i;
          real32_T rtb_Vc;
          real32_T sin_t;
          uint32_T pinReadLoc;
          uint32_T pinReadLoc_e;
          uint32_T pinReadLoc_p;
          uint16_T Switch;
          uint16_T rtb_Switch;
          uint8_T status;
          boolean_T OR;
          boolean_T rtb_Out;
          boolean_T rtb_Out_f;
          boolean_T rtb_Out_l;
          boolean_T tmp_e;
          boolean_T tmp_p;

          /* Switch: '<S25>/Switch' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           */
          Switch = Open_Loop2024_DW.HallStateChangeFlag;

          /* Delay: '<S25>/validityDelay' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           *  Switch: '<S25>/Switch'
           */
          if (Open_Loop2024_DW.HallStateChangeFlag != 0) {
            /* Delay: '<S25>/validityDelay' */
            Open_Loop2024_B.validityDelay =
              Open_Loop2024_DW.validityDelay_DSTATE;
          }

          /* End of Delay: '<S25>/validityDelay' */

          /* Logic: '<S26>/OR' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           *  DataTypeConversion: '<S9>/Data Type Conversion4'
           *  Delay: '<S26>/Delay One Step1'
           */
          OR = (Open_Loop2024_DW.DelayOneStep1_DSTATE ||
                (Open_Loop2024_DW.HallStateChangeFlag != 0));

          /* Delay: '<S26>/Delay One Step' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           *  DataTypeConversion: '<S9>/Data Type Conversion4'
           */
          if (OR) {
            if (Open_Loop2024_DW.HallStateChangeFlag != 0) {
              Open_Loop2024_DW.DelayOneStep_DSTATE = 571U;
            }

            /* Delay: '<S26>/Delay One Step' incorporates:
             *  DataStoreRead: '<S1>/Data Store Read5'
             *  DataTypeConversion: '<S9>/Data Type Conversion4'
             */
            Open_Loop2024_B.DelayOneStep = Open_Loop2024_DW.DelayOneStep_DSTATE;
          }

          /* End of Delay: '<S26>/Delay One Step' */

          /* RelationalOperator: '<S30>/Compare' incorporates:
           *  Constant: '<S30>/Constant'
           */
          Open_Loop2024_DW.DelayOneStep1_DSTATE = (Open_Loop2024_B.DelayOneStep >
            0);

          /* Switch: '<S29>/watchdog check' incorporates:
           *  Constant: '<S29>/Constant'
           */
          if (Open_Loop2024_DW.DelayOneStep1_DSTATE) {
            /* MinMax: '<S29>/Max' incorporates:
             *  DataStoreRead: '<S1>/Data Store Read2'
             */
            if (Open_Loop2024_DW.GlobalSpeedCount >=
                Open_Loop2024_B.TmpRTBAtSubsystemOutport1) {
              rtb_Switch = Open_Loop2024_DW.GlobalSpeedCount;
            } else {
              rtb_Switch = Open_Loop2024_B.TmpRTBAtSubsystemOutport1;
            }

            /* Switch: '<S29>/speed check' incorporates:
             *  Constant: '<S29>/Constant'
             *  DataStoreRead: '<S1>/Data Store Read4'
             *  DataTypeConversion: '<S25>/Data Type Conversion'
             *  Logic: '<S25>/Logical Operator'
             *  MinMax: '<S29>/Max'
             */
            if (rtb_Switch >= 57143) {
              rtb_Switch = 0U;
            } else {
              rtb_Switch = (uint16_T)((Open_Loop2024_DW.GlobalSpeedValidity != 0)
                && Open_Loop2024_B.validityDelay);
            }

            /* End of Switch: '<S29>/speed check' */
          } else {
            rtb_Switch = 0U;
          }

          /* End of Switch: '<S29>/watchdog check' */

          /* Delay: '<S25>/speedCountDelay' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           *  Switch: '<S25>/Switch'
           */
          if (Open_Loop2024_DW.HallStateChangeFlag != 0) {
            /* Delay: '<S25>/speedCountDelay' */
            Open_Loop2024_B.speedCountDelay =
              Open_Loop2024_DW.speedCountDelay_DSTATE;
          }

          /* End of Delay: '<S25>/speedCountDelay' */

          /* MATLABSystem: '<S66>/Digital Port Read' */
          pinReadLoc = LL_GPIO_ReadInputPort(GPIOB);

          /* MATLABSystem: '<S70>/Digital Port Read' */
          pinReadLoc_p = LL_GPIO_ReadInputPort(GPIOB);

          /* MATLABSystem: '<S68>/Digital Port Read' */
          pinReadLoc_e = LL_GPIO_ReadInputPort(GPIOB);

          /* DataTypeConversion: '<S15>/Data Type Conversion4' incorporates:
           *  Gain: '<S15>/Gain'
           *  Gain: '<S15>/Gain1'
           *  MATLABSystem: '<S66>/Digital Port Read'
           *  MATLABSystem: '<S68>/Digital Port Read'
           *  MATLABSystem: '<S70>/Digital Port Read'
           *  Sum: '<S15>/Sum'
           *  Sum: '<S15>/Sum1'
           * */
          pinReadLoc = (uint32_T)((((((uint64_T)((pinReadLoc_p & 64U) != 0U) <<
            31) >> 1) + ((uint64_T)((pinReadLoc & 256U) != 0U) << 29)) +
            ((uint64_T)((pinReadLoc_e & 128U) != 0U) << 31)) >> 29);

          /* If: '<S9>/If' */
          if (rtb_Switch != 0) {
            /* Outputs for IfAction SubSystem: '<S9>/Speed and direction are valid Use speed to extrapolate position' incorporates:
             *  ActionPort: '<S28>/Action Port'
             */
            /* Outputs for Enabled SubSystem: '<S28>/Subsystem1' incorporates:
             *  EnablePort: '<S41>/Enable'
             */
            /* Outputs for IfAction SubSystem: '<S41>/second_order' incorporates:
             *  ActionPort: '<S45>/Action Port'
             */
            /* If: '<S41>/If1' incorporates:
             *  Constant: '<S45>/Constant'
             *  DataStoreRead: '<S1>/Data Store Read2'
             *  DataTypeConversion: '<S45>/countData'
             *  DataTypeConversion: '<S45>/currentSpeedData'
             *  DataTypeConversion: '<S45>/previousSpeedData'
             *  Gain: '<S45>/Gain'
             *  Gain: '<S45>/Gain1'
             *  Product: '<S45>/Divide'
             *  Product: '<S45>/Divide1'
             *  Product: '<S45>/Product'
             *  Sum: '<S45>/Sum'
             *  Sum: '<S45>/Sum1'
             */
            rtb_Gain = (real32_T)Open_Loop2024_B.TmpRTBAtSubsystemOutport1 /
              (real32_T)Open_Loop2024_DW.GlobalSpeedCount;
            rtb_Gain = ((rtb_Gain - (real32_T)
                         Open_Loop2024_B.TmpRTBAtSubsystemOutport1 / (real32_T)
                         Open_Loop2024_B.speedCountDelay) * 0.5F + 1.0F) *
              rtb_Gain * 0.166666672F;

            /* End of Outputs for SubSystem: '<S41>/second_order' */

            /* Saturate: '<S41>/Saturation' */
            if (rtb_Gain > 0.16667F) {
              rtb_Gain = 0.16667F;
            } else if (rtb_Gain < 0.0F) {
              rtb_Gain = 0.0F;
            }

            /* End of Saturate: '<S41>/Saturation' */

            /* If: '<S41>/If' incorporates:
             *  DataStoreRead: '<S1>/Data Store Read3'
             */
            if (Open_Loop2024_DW.GlobalDirection != 1) {
              /* Outputs for IfAction SubSystem: '<S41>/-ve Direction' incorporates:
               *  ActionPort: '<S43>/Action Port'
               */
              /* SwitchCase: '<S43>/Switch Case' */
              switch ((int32_T)pinReadLoc) {
               case 5:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 1' incorporates:
                 *  ActionPort: '<S53>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof1();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 1' */
                break;

               case 4:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 2' incorporates:
                 *  ActionPort: '<S54>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof2();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 2' */
                break;

               case 6:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 3' incorporates:
                 *  ActionPort: '<S55>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof3();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 3' */
                break;

               case 2:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 4' incorporates:
                 *  ActionPort: '<S56>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof4();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 4' */
                break;

               case 3:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 5' incorporates:
                 *  ActionPort: '<S57>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof5();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 5' */
                break;

               case 1:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 6' incorporates:
                 *  ActionPort: '<S58>/Action Port'
                 */
                /* SignalConversion generated from: '<S58>/position' incorporates:
                 *  Constant: '<S58>/Constant'
                 */
                rtb_Merge1_i = 1.0F;

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 6' */
                break;

               default:
                /* Outputs for IfAction SubSystem: '<S43>/Hall Value of 7' incorporates:
                 *  ActionPort: '<S59>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof7();

                /* End of Outputs for SubSystem: '<S43>/Hall Value of 7' */
                break;
              }

              /* End of SwitchCase: '<S43>/Switch Case' */

              /* Merge: '<S41>/Merge' incorporates:
               *  Sum: '<S43>/Sum'
               */
              Open_Loop2024_B.Merge = rtb_Merge1_i - rtb_Gain;

              /* End of Outputs for SubSystem: '<S41>/-ve Direction' */
            } else {
              /* Outputs for IfAction SubSystem: '<S41>/+ve Direction' incorporates:
               *  ActionPort: '<S42>/Action Port'
               */
              /* SwitchCase: '<S42>/Switch Case' */
              switch ((int32_T)pinReadLoc) {
               case 5:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 1' incorporates:
                 *  ActionPort: '<S46>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof7();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 1' */
                break;

               case 4:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 2' incorporates:
                 *  ActionPort: '<S47>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof1();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 2' */
                break;

               case 6:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 3' incorporates:
                 *  ActionPort: '<S48>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof2();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 3' */
                break;

               case 2:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 4' incorporates:
                 *  ActionPort: '<S49>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof3();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 4' */
                break;

               case 3:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 5' incorporates:
                 *  ActionPort: '<S50>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof4();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 5' */
                break;

               case 1:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 6' incorporates:
                 *  ActionPort: '<S51>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof5();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 6' */
                break;

               default:
                /* Outputs for IfAction SubSystem: '<S42>/Hall Value of 7' incorporates:
                 *  ActionPort: '<S52>/Action Port'
                 */
                rtb_Merge1_i = Open_Loop2024_HallValueof7();

                /* End of Outputs for SubSystem: '<S42>/Hall Value of 7' */
                break;
              }

              /* End of SwitchCase: '<S42>/Switch Case' */

              /* Merge: '<S41>/Merge' incorporates:
               *  Sum: '<S42>/Sum'
               */
              Open_Loop2024_B.Merge = rtb_Merge1_i + rtb_Gain;

              /* End of Outputs for SubSystem: '<S41>/+ve Direction' */
            }

            /* End of If: '<S41>/If' */
            /* End of Outputs for SubSystem: '<S28>/Subsystem1' */

            /* SignalConversion generated from: '<S28>/rawPosition' */
            rtb_Gain = Open_Loop2024_B.Merge;

            /* End of Outputs for SubSystem: '<S9>/Speed and direction are valid Use speed to extrapolate position' */
          } else {
            /* Outputs for IfAction SubSystem: '<S9>/Speed and direction are not valid Position will be set to the middle of the Hall quadrant' incorporates:
             *  ActionPort: '<S27>/Action Port'
             */
            /* SwitchCase: '<S31>/Switch Case' */
            switch ((int32_T)pinReadLoc) {
             case 5:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 1' incorporates:
               *  ActionPort: '<S32>/Action Port'
               */
              /* SignalConversion generated from: '<S32>/position' incorporates:
               *  Constant: '<S32>/Constant'
               */
              rtb_Gain = 0.083333F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 1' */
              break;

             case 4:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 2' incorporates:
               *  ActionPort: '<S33>/Action Port'
               */
              /* SignalConversion generated from: '<S33>/position' incorporates:
               *  Constant: '<S33>/Constant'
               */
              rtb_Gain = 0.25F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 2' */
              break;

             case 6:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 3' incorporates:
               *  ActionPort: '<S34>/Action Port'
               */
              /* SignalConversion generated from: '<S34>/position' incorporates:
               *  Constant: '<S34>/Constant'
               */
              rtb_Gain = 0.41667F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 3' */
              break;

             case 2:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 4' incorporates:
               *  ActionPort: '<S35>/Action Port'
               */
              /* SignalConversion generated from: '<S35>/position' incorporates:
               *  Constant: '<S35>/Constant'
               */
              rtb_Gain = 0.58333F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 4' */
              break;

             case 3:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 5' incorporates:
               *  ActionPort: '<S36>/Action Port'
               */
              /* SignalConversion generated from: '<S36>/position' incorporates:
               *  Constant: '<S36>/Constant'
               */
              rtb_Gain = 0.75F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 5' */
              break;

             case 1:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 6' incorporates:
               *  ActionPort: '<S37>/Action Port'
               */
              /* SignalConversion generated from: '<S37>/position' incorporates:
               *  Constant: '<S37>/Constant'
               */
              rtb_Gain = 0.91667F;

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 6' */
              break;

             default:
              /* Outputs for IfAction SubSystem: '<S31>/Hall Value of 7' incorporates:
               *  ActionPort: '<S38>/Action Port'
               */
              rtb_Gain = Open_Loop2024_HallValueof7();

              /* End of Outputs for SubSystem: '<S31>/Hall Value of 7' */
              break;
            }

            /* End of SwitchCase: '<S31>/Switch Case' */
            /* End of Outputs for SubSystem: '<S9>/Speed and direction are not valid Position will be set to the middle of the Hall quadrant' */
          }

          /* End of If: '<S9>/If' */

          /* Gain: '<S1>/Gain' incorporates:
           *  Gain: '<S9>/PositionUnit'
           */
          rtb_Gain = 360.0F * rtb_Gain * 10.0F;

          /* Switch: '<S9>/Switch' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read5'
           */
          if (Open_Loop2024_DW.HallStateChangeFlag != 0) {
            /* DataStoreWrite: '<S1>/Data Store Write2' incorporates:
             *  Constant: '<S9>/WatchDog'
             */
            Open_Loop2024_DW.HallStateChangeFlag = 0U;
          }

          /* End of Switch: '<S9>/Switch' */

          /* MATLABSystem: '<S18>/Analog to Digital Converter' */
          if (Open_Loop2024_DW.obj.TunablePropsChanged) {
            Open_Loop2024_DW.obj.TunablePropsChanged = false;
          }

          regularReadADCIntr(Open_Loop2024_DW.obj.ADCHandle,
                             ADC_TRIGGER_AND_READ, &rtb_Switch);

          /* End of MATLABSystem: '<S18>/Analog to Digital Converter' */

          /* MATLABSystem: '<S20>/Digital Port Read' */
          pinReadLoc = LL_GPIO_ReadInputPort(GPIOC);

          /* MATLAB Function: '<S1>/MATLAB Function4' incorporates:
           *  MATLABSystem: '<S20>/Digital Port Read'
           * */
          Open_Loop2024_MATLABFunction1(((pinReadLoc & 64U) != 0U), &rtb_Out,
            &Open_Loop2024_DW.sf_MATLABFunction4);

          /* MATLABSystem: '<S22>/Digital Port Read' */
          pinReadLoc = LL_GPIO_ReadInputPort(GPIOC);

          /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
           *  MATLABSystem: '<S22>/Digital Port Read'
           * */
          Open_Loop2024_MATLABFunction1(((pinReadLoc & 512U) != 0U), &rtb_Out_f,
            &Open_Loop2024_DW.sf_MATLABFunction1);

          /* MATLABSystem: '<S24>/Digital Port Read' */
          pinReadLoc = LL_GPIO_ReadInputPort(GPIOC);

          /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
           *  MATLABSystem: '<S24>/Digital Port Read'
           * */
          Open_Loop2024_MATLABFunction1(((pinReadLoc & 32768U) != 0U),
            &rtb_Out_l, &Open_Loop2024_DW.sf_MATLABFunction2);

          /* Delay: '<S77>/Delay' */
          if (Open_Loop2024_DW.icLoad) {
            /* Sum: '<S77>/Add1' incorporates:
             *  Constant: '<S74>/IC'
             */
            Open_Loop2024_DW.Delay_DSTATE_h = 0;
          }

          /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
           *  MATLAB Function: '<S72>/MATLAB Function2'
           */
          tmp_p = (rtb_Out && rtb_Out_f);
          tmp_e = (tmp_p && rtb_Out_l);
          if (tmp_e) {
            tmp = 0;
          } else if (tmp_p && (!rtb_Out_l)) {
            tmp = 60;
          } else if (rtb_Out && (!rtb_Out_f) && (!rtb_Out_l)) {
            tmp = 120;
          } else if ((!rtb_Out) && (!rtb_Out_f) && (!rtb_Out_l)) {
            tmp = 180;
          } else if ((!rtb_Out) && (!rtb_Out_f) && rtb_Out_l) {
            tmp = 240;
          } else if ((!rtb_Out) && rtb_Out_f && rtb_Out_l) {
            tmp = 300;
          } else if ((!rtb_Out) && rtb_Out_f && (!rtb_Out_l)) {
            tmp = 600;
          } else {
            tmp = 0;
          }

          /* Sum: '<S77>/Add1' incorporates:
           *  Delay: '<S77>/Delay'
           *  Gain: '<S71>/rpm2freq'
           *  MATLAB Function: '<S1>/MATLAB Function'
           *  Product: '<S77>/Product'
           *  Product: '<S77>/Product1'
           */
          Open_Loop2024_DW.Delay_DSTATE_h = (int32_T)(((((tmp << 17) *
            1431655765LL) >> 34) * 13LL) >> 17) + (int32_T)((131059LL *
            Open_Loop2024_DW.Delay_DSTATE_h) >> 17);

          /* Gain: '<S72>/Gain2' incorporates:
           *  Abs: '<S72>/Abs'
           *  DataTypeConversion: '<S71>/Data Type Conversion'
           *  DiscreteIntegrator: '<S73>/Ramp Generator'
           *  Gain: '<S72>/V-by-f'
           *  Product: '<S71>/Product'
           *  Sum: '<S77>/Add1'
           */
          rtb_Product = fabs((real_T)(int32_T)(((int64_T)
            Open_Loop2024_DW.Delay_DSTATE_h *
            Open_Loop2024_DW.RampGenerator_DSTATE) >> 17) * 7.62939453125E-6) *
            0.01 * 40.0;

          /* Switch: '<S82>/Switch' incorporates:
           *  Constant: '<S16>/Boost Voltage'
           *  RelationalOperator: '<S82>/Relational Operator'
           */
          if (!(rtb_Product > 0.5)) {
            rtb_Product = 0.5;
          }

          /* Saturate: '<S82>/Saturation' incorporates:
           *  Switch: '<S82>/Switch'
           */
          if (rtb_Product > 20.0) {
            rtb_Product = 20.0;
          }

          /* Gain: '<S72>/Gain1' incorporates:
           *  Saturate: '<S82>/Saturation'
           */
          rtb_Gain1_cv = 0.75 * rtb_Product;

          /* MATLAB Function: '<S72>/MATLAB Function2' */
          if (tmp_e) {
            rtb_Product = 0.376;
          } else if (tmp_p && (!rtb_Out_l)) {
            rtb_Product = 1.2;
          } else if (rtb_Out && (!rtb_Out_f) && (!rtb_Out_l)) {
            rtb_Product = 1.9;
          } else if ((!rtb_Out) && (!rtb_Out_f) && (!rtb_Out_l)) {
            rtb_Product = 2.5;
          } else if ((!rtb_Out) && (!rtb_Out_f) && rtb_Out_l) {
            rtb_Product = 3.2;
          } else if ((!rtb_Out) && rtb_Out_f && rtb_Out_l) {
            rtb_Product = 4.0;
          } else if ((!rtb_Out) && rtb_Out_f && (!rtb_Out_l)) {
            rtb_Product = 8.5;
          } else {
            rtb_Product = 0.376;
          }

          if (rtb_Gain1_cv > rtb_Product) {
            rtb_Gain1_cv = rtb_Product;
          } else if (rtb_Gain1_cv < 0.376) {
            rtb_Gain1_cv = 0.376;
          }

          /* Product: '<S81>/Product' incorporates:
           *  Constant: '<S81>/InputGain'
           *  DataTypeConversion: '<S71>/Data Type Conversion'
           *  DiscreteIntegrator: '<S73>/Ramp Generator'
           *  Gain: '<S72>/position_increment'
           *  Product: '<S71>/Product'
           *  Sum: '<S77>/Add1'
           */
          rtb_Product = (real_T)(int32_T)(((int64_T)
            Open_Loop2024_DW.Delay_DSTATE_h *
            Open_Loop2024_DW.RampGenerator_DSTATE) >> 17) * 7.62939453125E-6 *
            0.00062831853071795862 * 0.15915494309189535;

          /* Delay: '<S81>/Delay' */
          if (Open_Loop2024_DW.icLoad_m) {
            /* Sum: '<S81>/Sum' incorporates:
             *  Constant: '<S81>/InputGain'
             *  Constant: '<S81>/Offset'
             *  Product: '<S81>/Product1'
             *  Sum: '<S81>/Sum1'
             */
            Open_Loop2024_DW.Delay_DSTATE = 0.0 - rtb_Product;
          }

          /* Sum: '<S81>/Sum' incorporates:
           *  Delay: '<S81>/Delay'
           */
          Open_Loop2024_DW.Delay_DSTATE += rtb_Product;

          /* Switch: '<S81>/Switch1' */
          if (!(Open_Loop2024_DW.Delay_DSTATE > 0.0)) {
            /* Sum: '<S81>/Sum' incorporates:
             *  Constant: '<S81>/Bias1'
             *  Sum: '<S81>/Sum2'
             */
            Open_Loop2024_DW.Delay_DSTATE++;
          }

          /* End of Switch: '<S81>/Switch1' */

          /* Switch: '<S81>/Switch2' */
          if (Open_Loop2024_DW.Delay_DSTATE >= 1.0) {
            /* Sum: '<S81>/Sum' incorporates:
             *  Sum: '<S81>/Sum3'
             */
            Open_Loop2024_DW.Delay_DSTATE--;
          }

          /* End of Switch: '<S81>/Switch2' */

          /* Product: '<S81>/Product2' incorporates:
           *  Constant: '<S81>/OutputGain'
           */
          rtb_Product = Open_Loop2024_DW.Delay_DSTATE * 6.2831853071795862;

          /* MATLAB Function: '<S72>/MATLAB Function4' incorporates:
           *  Constant: '<S72>/Constant'
           */
          if (rtIsNaNF((real32_T)rtb_Product)) {
            rtb_Merge1_i = (rtNaNF);
          } else if (rtIsInfF((real32_T)rtb_Product)) {
            rtb_Merge1_i = (rtNaNF);
          } else {
            rtb_Merge1_i = fabsf((real32_T)rtb_Product / 6.28318548F);
            if (fabsf(rtb_Merge1_i - floorf(rtb_Merge1_i + 0.5F)) >
                1.1920929E-7F * rtb_Merge1_i) {
              rtb_Merge1_i = fmodf((real32_T)rtb_Product, 6.28318548F);
            } else {
              rtb_Merge1_i = 0.0F;
            }

            if (rtb_Merge1_i == 0.0F) {
              rtb_Merge1_i = 0.0F;
            } else if (rtb_Merge1_i < 0.0F) {
              rtb_Merge1_i += 6.28318548F;
            }
          }

          cos_t = cosf(rtb_Merge1_i);
          sin_t = sinf(rtb_Merge1_i);
          rtb_Merge1_i = 0.0F * cos_t - (real32_T)rtb_Gain1_cv * sin_t;
          rtb_Vc = -0.5F * rtb_Merge1_i;
          sin_t = (0.0F * sin_t + (real32_T)rtb_Gain1_cv * cos_t) * 0.866F;
          cos_t = rtb_Vc + sin_t;
          rtb_Vc -= sin_t;

          /* MATLAB Function: '<S72>/MATLAB Function1' incorporates:
           *  MATLAB Function: '<S72>/MATLAB Function4'
           */
          sin_t = (0.866025388F * cos_t - 0.866025388F * rtb_Vc) * 0.666666687F;
          rtb_Vc = ((rtb_Merge1_i - 0.5F * cos_t) - 0.5F * rtb_Vc) *
            0.666666687F * 0.0416666679F - 0.0240562614F * sin_t;
          cos_t = 0.0481125228F * sin_t;
          sin_t = rtb_Vc + cos_t;
          switch ((uint8_T)((((cos_t >= 0.0F) << 1) + (rtb_Vc >= 0.0F)) +
                            ((sin_t >= 0.0F) << 2))) {
           case 7U:
            rtb_Merge1_i = ((1.0F - rtb_Vc) - cos_t) * 0.5F;
            sin_t = 1.0F - rtb_Merge1_i;
            rtb_Vc = cos_t + rtb_Merge1_i;
            cos_t = rtb_Merge1_i;
            break;

           case 6U:
            rtb_Merge1_i = ((1.0F - sin_t) - (-rtb_Vc)) * 0.5F;
            rtb_Vc = 1.0F - rtb_Merge1_i;
            sin_t += rtb_Merge1_i;
            cos_t = rtb_Merge1_i;
            break;

           case 2U:
            rtb_Merge1_i = ((1.0F - cos_t) - (-sin_t)) * 0.5F;
            rtb_Vc = 1.0F - rtb_Merge1_i;
            cos_t = -sin_t + rtb_Merge1_i;
            sin_t = rtb_Merge1_i;
            break;

           case 0U:
            rtb_Merge1_i = ((1.0F - (-rtb_Vc)) - (-cos_t)) * 0.5F;
            cos_t = 1.0F - rtb_Merge1_i;
            rtb_Vc = -rtb_Vc + rtb_Merge1_i;
            sin_t = rtb_Merge1_i;
            break;

           case 1U:
            rtb_Merge1_i = ((1.0F - (-sin_t)) - rtb_Vc) * 0.5F;
            cos_t = 1.0F - rtb_Merge1_i;
            sin_t = rtb_Vc + rtb_Merge1_i;
            rtb_Vc = rtb_Merge1_i;
            break;

           default:
            rtb_Merge1_i = ((1.0F - (-cos_t)) - sin_t) * 0.5F;
            sin_t = 1.0F - rtb_Merge1_i;
            cos_t = -cos_t + rtb_Merge1_i;
            rtb_Vc = rtb_Merge1_i;
            break;
          }

          /* MATLABSystem: '<S61>/PWM Output' incorporates:
           *  Constant: '<S1>/Constant2'
           *  Constant: '<S1>/Constant3'
           *  MATLAB Function: '<S72>/MATLAB Function1'
           */
          pinReadLoc = checkFrequencyAndDutyCycleLimits
            (Open_Loop2024_DW.obj_j.TimerHandle, 3599U);
          setFrequencyAccToInput(Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          rtb_Merge1_i = rt_roundf_snf(3599.0F * sin_t);
          if (rtb_Merge1_i < 4.2949673E+9F) {
            if (rtb_Merge1_i >= 0.0F) {
              pinReadLoc = (uint32_T)rtb_Merge1_i;
            } else {
              pinReadLoc = 0U;
            }
          } else {
            pinReadLoc = MAX_uint32_T;
          }

          pinReadLoc = checkFrequencyAndDutyCycleLimits
            (Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          setDutyCycleChannel1(Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          rtb_Merge1_i = rt_roundf_snf(3599.0F * rtb_Vc);
          if (rtb_Merge1_i < 4.2949673E+9F) {
            if (rtb_Merge1_i >= 0.0F) {
              pinReadLoc = (uint32_T)rtb_Merge1_i;
            } else {
              pinReadLoc = 0U;
            }
          } else {
            pinReadLoc = MAX_uint32_T;
          }

          pinReadLoc = checkFrequencyAndDutyCycleLimits
            (Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          setDutyCycleChannel2(Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          rtb_Merge1_i = rt_roundf_snf(3599.0F * cos_t);
          if (rtb_Merge1_i < 4.2949673E+9F) {
            if (rtb_Merge1_i >= 0.0F) {
              pinReadLoc = (uint32_T)rtb_Merge1_i;
            } else {
              pinReadLoc = 0U;
            }
          } else {
            pinReadLoc = MAX_uint32_T;
          }

          pinReadLoc = checkFrequencyAndDutyCycleLimits
            (Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          setDutyCycleChannel3(Open_Loop2024_DW.obj_j.TimerHandle, pinReadLoc);
          setMOEBitAccToInput(Open_Loop2024_DW.obj_j.TimerHandle, true);

          /* End of MATLABSystem: '<S61>/PWM Output' */

          /* Update for Delay: '<S25>/validityDelay' incorporates:
           *  DataStoreRead: '<S1>/Data Store Read2'
           *  DataStoreRead: '<S1>/Data Store Read4'
           *  DataTypeConversion: '<S25>/Data Type Conversion'
           *  Delay: '<S25>/speedCountDelay'
           */
          if (Switch != 0) {
            Open_Loop2024_DW.validityDelay_DSTATE =
              (Open_Loop2024_DW.GlobalSpeedValidity != 0);
            Open_Loop2024_DW.speedCountDelay_DSTATE =
              Open_Loop2024_DW.GlobalSpeedCount;
          }

          /* End of Update for Delay: '<S25>/validityDelay' */

          /* Update for Delay: '<S26>/Delay One Step' incorporates:
           *  Constant: '<S26>/Constant2'
           *  Sum: '<S26>/Sum'
           */
          if (OR) {
            Open_Loop2024_DW.DelayOneStep_DSTATE = (uint16_T)
              (Open_Loop2024_B.DelayOneStep - 1);
          }

          /* End of Update for Delay: '<S26>/Delay One Step' */

          /* Update for Delay: '<S77>/Delay' */
          Open_Loop2024_DW.icLoad = false;

          /* Update for DiscreteIntegrator: '<S73>/Ramp Generator' incorporates:
           *  Constant: '<S71>/Ramp_Time (sec)'
           *  Constant: '<S73>/One'
           *  Gain: '<S73>/Sample_Time'
           *  Product: '<S73>/Divide'
           */
          Open_Loop2024_DW.RampGenerator_DSTATE += 2;
          if (Open_Loop2024_DW.RampGenerator_DSTATE > 131072) {
            Open_Loop2024_DW.RampGenerator_DSTATE = 131072;
          } else if (Open_Loop2024_DW.RampGenerator_DSTATE < 0) {
            Open_Loop2024_DW.RampGenerator_DSTATE = 0;
          }

          /* End of Update for DiscreteIntegrator: '<S73>/Ramp Generator' */

          /* Update for Delay: '<S81>/Delay' */
          Open_Loop2024_DW.icLoad_m = false;

          /* MATLABSystem: '<S1>/Digital to Analog Converter' incorporates:
           *  DataTypeConversion: '<S1>/Data Type Conversion1'
           */
          channelSelect = LL_DAC_CHANNEL_2;
          status = MW_DAC_IsEnabled(Open_Loop2024_DW.obj_gc.DACHandle,
            channelSelect);
          if (status == 0) {
            /* DataTypeConversion: '<S1>/Data Type Conversion1' */
            rtb_Merge1_i = floorf(rtb_Gain);
            if (rtIsNaNF(rtb_Merge1_i) || rtIsInfF(rtb_Merge1_i)) {
              rtb_Merge1_i = 0.0F;
            } else {
              rtb_Merge1_i = fmodf(rtb_Merge1_i, 65536.0F);
            }

            MW_DAC_SetDHR(Open_Loop2024_DW.obj_gc.DACHandle, channelSelect,
                          (uint32_T)(rtb_Merge1_i < 0.0F ? (int32_T)(uint16_T)
              -(int16_T)(uint16_T)-rtb_Merge1_i : (int32_T)(uint16_T)
              rtb_Merge1_i), true, true, 4095U);
          }

          /* End of MATLABSystem: '<S1>/Digital to Analog Converter' */
        }

        /* End of Outputs for S-Function (HardwareInterrupt_sfun): '<S84>/Hardware Interrupt' */
      }
    }

    /* Clear occurred ADC1 Reg EoCS event */
    LL_ADC_ClearFlag_EOS(ADC1);
  }

  __ISB();
  __DSB();
}

/* Hardware Interrupt Block: '<S86>/Hardware Interrupt' */
void TIM4_IRQHandler(void)
{
  /* Event: TIM4 CC1 */
  /* Check event TIM4 CC1 occurred */
  if (0 != (
#if defined(MW_TIM4_ENABLED) && defined(MW_TIM4_CAPTURE_VAR)
            (0 != LL_TIM_IsEnabledIT_CC1(TIM4)) && (0 != TIM_IsActiveFlag_CC1
        (&(MW_TIM4_CAPTURE_VAR)))
#else
            (0 != LL_TIM_IsEnabledIT_CC1(TIM4)) && (0 != LL_TIM_IsActiveFlag_CC1
        (TIM4))
#endif
            )) {
    if (1 == runModel) {
      {
        /* S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' */

        /* Output and update for function-call system: '<Root>/Subsystem' */
        {
          GPIO_TypeDef * portNameLoc;
          uint32_T shiftVal;
          int32_T rtb_PulseGenerator;
          uint32_T pinReadLoc;
          uint32_T pinReadLoc_e;
          uint32_T pinReadLoc_p;
          int16_T rtb_Merge1_i;
          uint8_T rtb_DataTypeConversion3_k;
          boolean_T rtb_Merge3;

          /* MATLABSystem: '<S109>/Digital Port Read' */
          pinReadLoc = LL_GPIO_ReadInputPort(GPIOB);

          /* MATLABSystem: '<S111>/Digital Port Read' */
          pinReadLoc_p = LL_GPIO_ReadInputPort(GPIOB);

          /* MATLABSystem: '<S113>/Digital Port Read' */
          pinReadLoc_e = LL_GPIO_ReadInputPort(GPIOB);

          /* DataTypeConversion: '<S89>/Data Type Conversion3' incorporates:
           *  Gain: '<S89>/Gain'
           *  Gain: '<S89>/Gain1'
           *  MATLABSystem: '<S109>/Digital Port Read'
           *  MATLABSystem: '<S111>/Digital Port Read'
           *  MATLABSystem: '<S113>/Digital Port Read'
           *  Sum: '<S89>/Sum'
           *  Sum: '<S89>/Sum1'
           * */
          rtb_DataTypeConversion3_k = (uint8_T)((int32_T)(((((uint32_T)
            (((pinReadLoc_e & 64U) != 0U) << 7) << 1) + (uint32_T)
            (((pinReadLoc_p & 128U) != 0U) << 7)) >> 1) + ((uint32_T)
            ((pinReadLoc & 256U) != 0U) << 5)) >> 5);

          /* SwitchCase: '<S88>/Detects if the halls reading is valid' incorporates:
           *  DataTypeConversion: '<S88>/Data Type Conversion1'
           */
          switch (rtb_DataTypeConversion3_k) {
           case 5:
           case 4:
           case 6:
           case 2:
           case 3:
           case 1:
            {
              uint16_T Merge3;

              /* Outputs for IfAction SubSystem: '<S92>/Valid Halls' incorporates:
               *  ActionPort: '<S94>/Action Port'
               */
              /* SwitchCase: '<S94>/Switch Case' */
              switch (rtb_DataTypeConversion3_k) {
               case 5:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem' incorporates:
                 *  ActionPort: '<S95>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S95>/previous'
                 *  SignalConversion generated from: '<S95>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 1U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S95>/next'
                 *  SignalConversion generated from: '<S95>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 4U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem' */
                break;

               case 4:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem1' incorporates:
                 *  ActionPort: '<S96>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S96>/previous'
                 *  SignalConversion generated from: '<S96>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 5U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S96>/next'
                 *  SignalConversion generated from: '<S96>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 6U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem1' */
                break;

               case 6:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem2' incorporates:
                 *  ActionPort: '<S97>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S97>/previous'
                 *  SignalConversion generated from: '<S97>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 4U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S97>/next'
                 *  SignalConversion generated from: '<S97>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 2U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem2' */
                break;

               case 2:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem3' incorporates:
                 *  ActionPort: '<S98>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S98>/previous'
                 *  SignalConversion generated from: '<S98>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 6U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S98>/next'
                 *  SignalConversion generated from: '<S98>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 3U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem3' */
                break;

               case 3:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem4' incorporates:
                 *  ActionPort: '<S99>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S99>/previous'
                 *  SignalConversion generated from: '<S99>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 2U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S99>/next'
                 *  SignalConversion generated from: '<S99>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 1U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem4' */
                break;

               case 1:
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem5' incorporates:
                 *  ActionPort: '<S100>/Action Port'
                 */
                /* Merge: '<S94>/Merge' incorporates:
                 *  Constant: '<S100>/previous'
                 *  SignalConversion generated from: '<S100>/Out1'
                 */
                Open_Loop2024_B.Merge_l = 3U;

                /* Merge: '<S94>/Merge1' incorporates:
                 *  Constant: '<S100>/next'
                 *  SignalConversion generated from: '<S100>/Out2'
                 */
                Open_Loop2024_B.Merge1 = 5U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem5' */
                break;
              }

              /* End of SwitchCase: '<S94>/Switch Case' */

              /* If: '<S94>/If' incorporates:
               *  DataStoreRead: '<S4>/Data Store Read'
               *  DataTypeConversion: '<S4>/Data Type Conversion2'
               */
              if ((uint8_T)Open_Loop2024_DW.GlobalHallState ==
                  Open_Loop2024_B.Merge_l) {
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem6' incorporates:
                 *  ActionPort: '<S101>/Action Port'
                 */
                /* Merge: '<S94>/Merge2' incorporates:
                 *  Constant: '<S101>/Constant'
                 *  SignalConversion generated from: '<S101>/direction'
                 */
                Open_Loop2024_B.Merge2 = 1;

                /* Merge: '<S94>/Merge3' incorporates:
                 *  Constant: '<S101>/Constant1'
                 *  SignalConversion generated from: '<S101>/sequence_check'
                 */
                Merge3 = 0U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem6' */
              } else if ((uint8_T)Open_Loop2024_DW.GlobalHallState ==
                         Open_Loop2024_B.Merge1) {
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem7' incorporates:
                 *  ActionPort: '<S102>/Action Port'
                 */
                /* Merge: '<S94>/Merge2' incorporates:
                 *  Constant: '<S102>/Constant'
                 *  SignalConversion generated from: '<S102>/direction'
                 */
                Open_Loop2024_B.Merge2 = -1;

                /* Merge: '<S94>/Merge3' incorporates:
                 *  Constant: '<S102>/Constant1'
                 *  SignalConversion generated from: '<S102>/sequence_check'
                 */
                Merge3 = 0U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem7' */
              } else {
                /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem8' incorporates:
                 *  ActionPort: '<S103>/Action Port'
                 */
                /* Merge: '<S94>/Merge3' incorporates:
                 *  Constant: '<S103>/Constant'
                 *  SignalConversion generated from: '<S103>/sequence_check'
                 */
                Merge3 = 1U;

                /* End of Outputs for SubSystem: '<S94>/If Action Subsystem8' */
              }

              /* End of If: '<S94>/If' */

              /* SignalConversion: '<S94>/Signal Conversion1' */
              rtb_Merge1_i = Open_Loop2024_B.Merge2;

              /* Switch: '<S94>/Switch' incorporates:
               *  Constant: '<S94>/Constant'
               *  DataStoreRead: '<S4>/Data Store Read1'
               *  RelationalOperator: '<S94>/Relational Operator'
               */
              if (Merge3 != 0) {
                rtb_Merge3 = false;
              } else {
                rtb_Merge3 = (Open_Loop2024_B.Merge2 ==
                              Open_Loop2024_DW.GlobalDirection);
              }

              /* End of Switch: '<S94>/Switch' */
              /* End of Outputs for SubSystem: '<S92>/Valid Halls' */
            }
            break;

           default:
            /* Outputs for IfAction SubSystem: '<S92>/Bad hall (glitch or wrong connection)' incorporates:
             *  ActionPort: '<S93>/Action Port'
             */
            /* SignalConversion: '<S93>/Signal Conversion' incorporates:
             *  DataStoreRead: '<S4>/Data Store Read1'
             */
            rtb_Merge1_i = Open_Loop2024_DW.GlobalDirection;

            /* SignalConversion generated from: '<S93>/directional_speed_valid_flag' incorporates:
             *  Constant: '<S93>/Constant1'
             */
            rtb_Merge3 = false;

            /* End of Outputs for SubSystem: '<S92>/Bad hall (glitch or wrong connection)' */
            break;
          }

          /* End of SwitchCase: '<S88>/Detects if the halls reading is valid' */

          /* DataTypeConversion: '<S92>/Data Type Conversion' incorporates:
           *  DataStoreWrite: '<S4>/Data Store Write'
           */
          Open_Loop2024_DW.GlobalSpeedValidity = rtb_Merge3;

          /* DataStoreWrite: '<S4>/Data Store Write1' */
          Open_Loop2024_DW.GlobalDirection = rtb_Merge1_i;

          /* DataStoreWrite: '<S4>/Data Store Write2' incorporates:
           *  Constant: '<S88>/Constant'
           */
          Open_Loop2024_DW.HallStateChangeFlag = 1U;

          /* MATLABSystem: '<S4>/Timer Capture' incorporates:
           *  DataStoreWrite: '<S4>/Data Store Write3'
           */
          getCCR1RegisterValuePollingMode(Open_Loop2024_DW.obj_p.TimerHandle,
            &Open_Loop2024_DW.GlobalSpeedCount, &pinReadLoc);

          /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
           *  DataStoreWrite: '<S4>/Data Store Write3'
           */
          Open_Loop2024_B.DataTypeConversion = Open_Loop2024_DW.GlobalSpeedCount;

          /* DataTypeConversion: '<S4>/Data Type Conversion1' incorporates:
           *  DataStoreWrite: '<S4>/Data Store Write7'
           */
          Open_Loop2024_DW.GlobalHallState = rtb_DataTypeConversion3_k;

          /* DiscretePulseGenerator: '<S4>/Pulse Generator' */
          rtb_PulseGenerator = ((Open_Loop2024_DW.clockTickCounter < 1) &&
                                (Open_Loop2024_DW.clockTickCounter >= 0));
          if (Open_Loop2024_DW.clockTickCounter >= 1) {
            Open_Loop2024_DW.clockTickCounter = 0;
          } else {
            Open_Loop2024_DW.clockTickCounter++;
          }

          /* End of DiscretePulseGenerator: '<S4>/Pulse Generator' */

          /* MATLABSystem: '<S91>/Digital Port Write' */
          portNameLoc = GPIOC;
          shiftVal = MW_GPIO_BIT_SHIFT;
          if (rtb_PulseGenerator != 0) {
            pinReadLoc = 2048U;
          } else {
            pinReadLoc = 0U;
          }

          pinReadLoc = mw_shift(pinReadLoc, shiftVal);
          pinReadLoc_p = mw_shift(2048U, shiftVal);
          LL_GPIO_SetOutputPin(portNameLoc, pinReadLoc);
          LL_GPIO_ResetOutputPin(portNameLoc, ~pinReadLoc & pinReadLoc_p);

          /* End of MATLABSystem: '<S91>/Digital Port Write' */
        }

        /* End of Outputs for S-Function (HardwareInterrupt_sfun): '<S86>/Hardware Interrupt' */

        /* RateTransition generated from: '<Root>/Subsystem' */
        Open_Loop2024_DW.TmpRTBAtSubsystemOutport1_Buffe =
          Open_Loop2024_B.DataTypeConversion;
      }
    }

    /* Clear occurred TIM4 CC1 event */
    LL_TIM_ClearFlag_CC1(TIM4);
  }

  __ISB();
  __DSB();
}

void Open_Loop2024_unconfigure_interrupts (void)
{
  MW_NVIC_DisableIRQ(33);
  MW_NVIC_DisableIRQ(45);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
