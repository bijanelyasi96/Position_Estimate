/*
 * File: ert_main.c
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
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(int argc, char **argv)
{
  float modelBaseRate = 0.0001;
  float systemClock = 72.0;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  MW_EnableNVICPeripheral();

#if !defined(MW_FREERTOS) && defined(MW_MULTI_TASKING_MODE) && (MW_MULTI_TASKING_MODE == 1)

  MW_ASM (" SVC #1");

#endif

  ;

  // Start Peripheral initialization imported from STM32CubeMX project;
  HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_DAC1_Init();
  MX_TIM4_Init();

  // End Peripheral initialization imported from STM32CubeMX project;
  rtmSetErrorStatus(Open_Loop2024_M, 0);
  Open_Loop2024_configure_interrupts();
  Open_Loop2024_initialize();
  __disable_irq();
  ARMCM_SysTick_Config(modelBaseRate);
  runModel =
    rtmGetErrorStatus(Open_Loop2024_M) == (NULL);
  __enable_irq();
  __enable_irq();
  while (runModel) {
    stopRequested = !(
                      rtmGetErrorStatus(Open_Loop2024_M) == (NULL));
    if (stopRequested) {
      SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }

    ;
  }

  /* Terminate model */
  Open_Loop2024_terminate();

#if !defined(MW_FREERTOS) && !defined(USE_RTX)

  (void) systemClock;

#endif

  ;
  Open_Loop2024_unconfigure_interrupts();
  MW_DisableNVICPeripheral();
  __disable_irq();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
