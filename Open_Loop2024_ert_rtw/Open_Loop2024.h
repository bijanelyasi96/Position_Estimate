/*
 * File: Open_Loop2024.h
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

#ifndef Open_Loop2024_h_
#define Open_Loop2024_h_
#ifndef Open_Loop2024_COMMON_INCLUDES_
#define Open_Loop2024_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "main.h"
#include "mw_stm32_utils.h"
#endif                                 /* Open_Loop2024_COMMON_INCLUDES_ */

#include "mw_stm32_nvic.h"
#include "Open_Loop2024_types.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S1>/MATLAB Function1' */
typedef struct {
  uint8_T counter;                     /* '<S1>/MATLAB Function1' */
  boolean_T stable_state;              /* '<S1>/MATLAB Function1' */
  boolean_T stable_state_not_empty;    /* '<S1>/MATLAB Function1' */
} DW_MATLABFunction1_Open_Loop2_T;

/* Block signals (default storage) */
typedef struct {
  real32_T Merge;                      /* '<S41>/Merge' */
  uint16_T TmpRTBAtSubsystemOutport1;  /* '<Root>/Subsystem' */
  uint16_T DataTypeConversion;         /* '<S4>/Data Type Conversion' */
  uint16_T Merge_l;                    /* '<S94>/Merge' */
  uint16_T Merge1;                     /* '<S94>/Merge1' */
  uint16_T DelayOneStep;               /* '<S26>/Delay One Step' */
  uint16_T speedCountDelay;            /* '<S25>/speedCountDelay' */
  int16_T Merge2;                      /* '<S94>/Merge2' */
  boolean_T validityDelay;             /* '<S25>/validityDelay' */
} B_Open_Loop2024_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  stm32cube_blocks_AnalogInput__T obj; /* '<S18>/Analog to Digital Converter' */
  stm32cube_blocks_DigitalPortR_T obj_i;/* '<S113>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_h;/* '<S111>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_b;/* '<S109>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_m;/* '<S70>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_mz;/* '<S68>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_g;/* '<S66>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_mb;/* '<S24>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_e;/* '<S22>/Digital Port Read' */
  stm32cube_blocks_DigitalPortR_T obj_i3;/* '<S20>/Digital Port Read' */
  stm32cube_blocks_PWMOutput_Op_T obj_j;/* '<S61>/PWM Output' */
  stm32cube_blocks_DigitalPortW_T obj_d;/* '<S91>/Digital Port Write' */
  stm32cube_blocks_TimerCapture_T obj_p;/* '<S4>/Timer Capture' */
  real_T Delay_DSTATE;                 /* '<S81>/Delay' */
  int32_T Delay_DSTATE_h;              /* '<S77>/Delay' */
  int32_T RampGenerator_DSTATE;        /* '<S73>/Ramp Generator' */
  int32_T clockTickCounter;            /* '<S4>/Pulse Generator' */
  uint32_T GlobalHallState;            /* '<Root>/Data Store Memory4' */
  stm32cube_blocks_AnalogOutput_T obj_gc;/* '<S1>/Digital to Analog Converter' */
  uint16_T DelayOneStep_DSTATE;        /* '<S26>/Delay One Step' */
  uint16_T speedCountDelay_DSTATE;     /* '<S25>/speedCountDelay' */
  int16_T GlobalDirection;             /* '<Root>/Data Store Memory3' */
  volatile uint16_T TmpRTBAtSubsystemOutport1_Buffe;/* synthesized block */
  uint16_T HallStateChangeFlag;        /* '<Root>/Data Store Memory' */
  uint16_T GlobalSpeedCount;           /* '<Root>/Data Store Memory1' */
  uint16_T GlobalSpeedValidity;        /* '<Root>/Data Store Memory2' */
  boolean_T validityDelay_DSTATE;      /* '<S25>/validityDelay' */
  boolean_T DelayOneStep1_DSTATE;      /* '<S26>/Delay One Step1' */
  boolean_T icLoad;                    /* '<S77>/Delay' */
  boolean_T icLoad_m;                  /* '<S81>/Delay' */
  DW_MATLABFunction1_Open_Loop2_T sf_MATLABFunction4;/* '<S1>/MATLAB Function4' */
  DW_MATLABFunction1_Open_Loop2_T sf_MATLABFunction2;/* '<S1>/MATLAB Function2' */
  DW_MATLABFunction1_Open_Loop2_T sf_MATLABFunction1;/* '<S1>/MATLAB Function1' */
} DW_Open_Loop2024_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T SpeedConstData;       /* '<S28>/SpeedConstData' */
} ConstB_Open_Loop2024_T;

/* Real-time Model Data Structure */
struct tag_RTM_Open_Loop2024_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Open_Loop2024_T Open_Loop2024_B;

/* Block states (default storage) */
extern DW_Open_Loop2024_T Open_Loop2024_DW;
extern const ConstB_Open_Loop2024_T Open_Loop2024_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void Open_Loop2024_initialize(void);
extern void Open_Loop2024_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Open_Loop2024_T *const Open_Loop2024_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

#ifdef __cpluscplus

extern "C"
{

#endif

  void ADC1_2_IRQHandler(void);
  void TIM4_IRQHandler(void);
  void Open_Loop2024_configure_interrupts (void);
  void Open_Loop2024_unconfigure_interrupts (void);

#ifdef __cpluscplus

}

#endif

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S74>/Data Type Duplicate' : Unused code path elimination
 * Block '<S71>/Scope' : Unused code path elimination
 * Block '<S71>/Scope1' : Unused code path elimination
 * Block '<S72>/Divide' : Unused code path elimination
 * Block '<S81>/BooleanTypeCast' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate2' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate3' : Unused code path elimination
 * Block '<S81>/Data Type Propagation' : Unused code path elimination
 * Block '<S81>/InpGainDatatype' : Unused code path elimination
 * Block '<S81>/OutGainDatatype' : Unused code path elimination
 * Block '<S81>/Reset' : Unused code path elimination
 * Block '<S72>/Scope' : Unused code path elimination
 * Block '<S72>/Scope2' : Unused code path elimination
 * Block '<S72>/Scope3' : Unused code path elimination
 * Block '<S72>/Scope6' : Unused code path elimination
 * Block '<S72>/Scope7' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S9>/counterSize1' : Eliminate redundant data type conversion
 * Block '<S9>/counterSize2' : Eliminate redundant data type conversion
 * Block '<S74>/Cast To Boolean' : Eliminate redundant data type conversion
 * Block '<S88>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S88>/counterSize' : Eliminate redundant data type conversion
 * Block '<S25>/Order' : Unused code path elimination
 * Block '<S74>/Reset' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Open_Loop2024'
 * '<S1>'   : 'Open_Loop2024/Function-Call Subsystem'
 * '<S2>'   : 'Open_Loop2024/Hardware Interrupt'
 * '<S3>'   : 'Open_Loop2024/Hardware Interrupt_PhaseC'
 * '<S4>'   : 'Open_Loop2024/Subsystem'
 * '<S5>'   : 'Open_Loop2024/Function-Call Subsystem/Analog to Digital Converter'
 * '<S6>'   : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read'
 * '<S7>'   : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read1'
 * '<S8>'   : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read2'
 * '<S9>'   : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position'
 * '<S10>'  : 'Open_Loop2024/Function-Call Subsystem/MATLAB Function'
 * '<S11>'  : 'Open_Loop2024/Function-Call Subsystem/MATLAB Function1'
 * '<S12>'  : 'Open_Loop2024/Function-Call Subsystem/MATLAB Function2'
 * '<S13>'  : 'Open_Loop2024/Function-Call Subsystem/MATLAB Function4'
 * '<S14>'  : 'Open_Loop2024/Function-Call Subsystem/PWM Output'
 * '<S15>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1'
 * '<S16>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2'
 * '<S17>'  : 'Open_Loop2024/Function-Call Subsystem/Analog to Digital Converter/ECSoC'
 * '<S18>'  : 'Open_Loop2024/Function-Call Subsystem/Analog to Digital Converter/ECSoC/ECSimCodegen'
 * '<S19>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read/ECSoC'
 * '<S20>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read/ECSoC/ECSimCodegen'
 * '<S21>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read1/ECSoC'
 * '<S22>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read1/ECSoC/ECSimCodegen'
 * '<S23>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read2/ECSoC'
 * '<S24>'  : 'Open_Loop2024/Function-Call Subsystem/Digital Port Read2/ECSoC/ECSimCodegen'
 * '<S25>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/ExtrapolationOrder'
 * '<S26>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Software Watchdog Timer'
 * '<S27>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant'
 * '<S28>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position'
 * '<S29>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/VaidityCheck'
 * '<S30>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Software Watchdog Timer/Compare To Zero'
 * '<S31>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction'
 * '<S32>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 1'
 * '<S33>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 2'
 * '<S34>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 3'
 * '<S35>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 4'
 * '<S36>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 5'
 * '<S37>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 6'
 * '<S38>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are not valid Position will be set to the middle of the Hall quadrant/independent Direction/Hall Value of 7'
 * '<S39>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/If Action Subsystem'
 * '<S40>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/If Action Subsystem1'
 * '<S41>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1'
 * '<S42>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction'
 * '<S43>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction'
 * '<S44>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/first_order'
 * '<S45>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/second_order'
 * '<S46>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 1'
 * '<S47>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 2'
 * '<S48>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 3'
 * '<S49>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 4'
 * '<S50>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 5'
 * '<S51>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 6'
 * '<S52>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/+ve Direction/Hall Value of 7'
 * '<S53>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 1'
 * '<S54>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 2'
 * '<S55>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 3'
 * '<S56>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 4'
 * '<S57>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 5'
 * '<S58>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 6'
 * '<S59>'  : 'Open_Loop2024/Function-Call Subsystem/Hall Speed and Position/Speed and direction are valid Use speed to extrapolate position/Subsystem1/-ve Direction/Hall Value of 7'
 * '<S60>'  : 'Open_Loop2024/Function-Call Subsystem/PWM Output/ECSoC'
 * '<S61>'  : 'Open_Loop2024/Function-Call Subsystem/PWM Output/ECSoC/ECSimCodegen'
 * '<S62>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read3'
 * '<S63>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read4'
 * '<S64>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read5'
 * '<S65>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read3/ECSoC'
 * '<S66>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read3/ECSoC/ECSimCodegen'
 * '<S67>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read4/ECSoC'
 * '<S68>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read4/ECSoC/ECSimCodegen'
 * '<S69>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read5/ECSoC'
 * '<S70>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem1/Digital Port Read5/ECSoC/ECSimCodegen'
 * '<S71>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq'
 * '<S72>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc'
 * '<S73>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq/Ramp Generator'
 * '<S74>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq/Rate Limiter'
 * '<S75>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq/Rate Limiter/IIR Filter'
 * '<S76>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq/Rate Limiter/IIR Filter/Low-pass'
 * '<S77>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/SpeedRefToFreq/Rate Limiter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S78>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc/MATLAB Function1'
 * '<S79>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc/MATLAB Function2'
 * '<S80>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc/MATLAB Function4'
 * '<S81>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc/Position Generator'
 * '<S82>'  : 'Open_Loop2024/Function-Call Subsystem/Subsystem2/VabcCalc/Saturate output to limits'
 * '<S83>'  : 'Open_Loop2024/Hardware Interrupt/ECSoC'
 * '<S84>'  : 'Open_Loop2024/Hardware Interrupt/ECSoC/ECSimCodegen'
 * '<S85>'  : 'Open_Loop2024/Hardware Interrupt_PhaseC/ECSoC'
 * '<S86>'  : 'Open_Loop2024/Hardware Interrupt_PhaseC/ECSoC/ECSimCodegen'
 * '<S87>'  : 'Open_Loop2024/Subsystem/Digital Port Write2'
 * '<S88>'  : 'Open_Loop2024/Subsystem/Hall Validity'
 * '<S89>'  : 'Open_Loop2024/Subsystem/Subsystem'
 * '<S90>'  : 'Open_Loop2024/Subsystem/Digital Port Write2/ECSoC'
 * '<S91>'  : 'Open_Loop2024/Subsystem/Digital Port Write2/ECSoC/ECSimCodegen'
 * '<S92>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem'
 * '<S93>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Bad hall (glitch or wrong connection)'
 * '<S94>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls'
 * '<S95>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem'
 * '<S96>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem1'
 * '<S97>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem2'
 * '<S98>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem3'
 * '<S99>'  : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem4'
 * '<S100>' : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem5'
 * '<S101>' : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem6'
 * '<S102>' : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem7'
 * '<S103>' : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/If Action Subsystem8'
 * '<S104>' : 'Open_Loop2024/Subsystem/Hall Validity/Subsystem/Valid Halls/Switch Case Action Subsystem'
 * '<S105>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read3'
 * '<S106>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read4'
 * '<S107>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read5'
 * '<S108>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read3/ECSoC'
 * '<S109>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read3/ECSoC/ECSimCodegen'
 * '<S110>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read4/ECSoC'
 * '<S111>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read4/ECSoC/ECSimCodegen'
 * '<S112>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read5/ECSoC'
 * '<S113>' : 'Open_Loop2024/Subsystem/Subsystem/Digital Port Read5/ECSoC/ECSimCodegen'
 */
#endif                                 /* Open_Loop2024_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
