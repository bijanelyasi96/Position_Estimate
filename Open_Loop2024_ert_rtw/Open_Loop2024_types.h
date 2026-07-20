/*
 * File: Open_Loop2024_types.h
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

#ifndef Open_Loop2024_types_h_
#define Open_Loop2024_types_h_
#include "rtwtypes.h"
#include "stm_timer_ll.h"
#include "stm_dac_ll.h"
#include "stm_adc_ll.h"

/* Custom Type definition for MATLABSystem: '<S18>/Analog to Digital Converter' */
#include "stm_adc_ll.h"
#include "stm_adc_ll.h"
#ifndef struct_tag_oqTgs9IQV1qnhaQ2GI62yC
#define struct_tag_oqTgs9IQV1qnhaQ2GI62yC

struct tag_oqTgs9IQV1qnhaQ2GI62yC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                 /* struct_tag_oqTgs9IQV1qnhaQ2GI62yC */

#ifndef typedef_stm32cube_blocks_DigitalPortR_T
#define typedef_stm32cube_blocks_DigitalPortR_T

typedef struct tag_oqTgs9IQV1qnhaQ2GI62yC stm32cube_blocks_DigitalPortR_T;

#endif                             /* typedef_stm32cube_blocks_DigitalPortR_T */

/* Custom Type definition for MATLABSystem: '<S61>/PWM Output' */
#include "stm_timer_ll.h"
#include "stm_timer_ll.h"
#ifndef struct_tag_0RzKA0TA5eXyA1b3sjyvMG
#define struct_tag_0RzKA0TA5eXyA1b3sjyvMG

struct tag_0RzKA0TA5eXyA1b3sjyvMG
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  TIM_Type_T* TimerHandle;
};

#endif                                 /* struct_tag_0RzKA0TA5eXyA1b3sjyvMG */

#ifndef typedef_stm32cube_blocks_PWMOutput_Op_T
#define typedef_stm32cube_blocks_PWMOutput_Op_T

typedef struct tag_0RzKA0TA5eXyA1b3sjyvMG stm32cube_blocks_PWMOutput_Op_T;

#endif                             /* typedef_stm32cube_blocks_PWMOutput_Op_T */

/* Custom Type definition for MATLABSystem: '<S1>/Digital to Analog Converter' */
#include "stm_dac_ll.h"
#include "stm_dac_ll.h"
#ifndef struct_tag_cGeavZ1yonBfGVjKlRiP1D
#define struct_tag_cGeavZ1yonBfGVjKlRiP1D

struct tag_cGeavZ1yonBfGVjKlRiP1D
{
  int32_T isInitialized;
  MW_DAC_Type_T* DACHandle;
};

#endif                                 /* struct_tag_cGeavZ1yonBfGVjKlRiP1D */

#ifndef typedef_stm32cube_blocks_AnalogOutput_T
#define typedef_stm32cube_blocks_AnalogOutput_T

typedef struct tag_cGeavZ1yonBfGVjKlRiP1D stm32cube_blocks_AnalogOutput_T;

#endif                             /* typedef_stm32cube_blocks_AnalogOutput_T */

#ifndef struct_tag_V8NuBFyzhXWrH9W8r74ibE
#define struct_tag_V8NuBFyzhXWrH9W8r74ibE

struct tag_V8NuBFyzhXWrH9W8r74ibE
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  ADC_Type_T* ADCHandle;
};

#endif                                 /* struct_tag_V8NuBFyzhXWrH9W8r74ibE */

#ifndef typedef_stm32cube_blocks_AnalogInput__T
#define typedef_stm32cube_blocks_AnalogInput__T

typedef struct tag_V8NuBFyzhXWrH9W8r74ibE stm32cube_blocks_AnalogInput__T;

#endif                             /* typedef_stm32cube_blocks_AnalogInput__T */

#ifndef struct_tag_92DzsjXuaF7c99tFkgTmuB
#define struct_tag_92DzsjXuaF7c99tFkgTmuB

struct tag_92DzsjXuaF7c99tFkgTmuB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                 /* struct_tag_92DzsjXuaF7c99tFkgTmuB */

#ifndef typedef_stm32cube_blocks_DigitalPortW_T
#define typedef_stm32cube_blocks_DigitalPortW_T

typedef struct tag_92DzsjXuaF7c99tFkgTmuB stm32cube_blocks_DigitalPortW_T;

#endif                             /* typedef_stm32cube_blocks_DigitalPortW_T */

#ifndef struct_tag_2WQTPO8pE0d3918hKhAGFE
#define struct_tag_2WQTPO8pE0d3918hKhAGFE

struct tag_2WQTPO8pE0d3918hKhAGFE
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  TIM_Type_T* TimerHandle;
};

#endif                                 /* struct_tag_2WQTPO8pE0d3918hKhAGFE */

#ifndef typedef_stm32cube_blocks_TimerCapture_T
#define typedef_stm32cube_blocks_TimerCapture_T

typedef struct tag_2WQTPO8pE0d3918hKhAGFE stm32cube_blocks_TimerCapture_T;

#endif                             /* typedef_stm32cube_blocks_TimerCapture_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_Open_Loop2024_T RT_MODEL_Open_Loop2024_T;

#endif                                 /* Open_Loop2024_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
