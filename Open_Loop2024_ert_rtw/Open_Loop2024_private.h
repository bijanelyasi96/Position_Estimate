/*
 * File: Open_Loop2024_private.h
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

#ifndef Open_Loop2024_private_h_
#define Open_Loop2024_private_h_
#include "rtwtypes.h"
#include "Open_Loop2024.h"
#include "Open_Loop2024_types.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */
extern real32_T rt_roundf_snf(real32_T u);
extern real32_T Open_Loop2024_HallValueof1(void);
extern real32_T Open_Loop2024_HallValueof2(void);
extern real32_T Open_Loop2024_HallValueof3(void);
extern real32_T Open_Loop2024_HallValueof4(void);
extern real32_T Open_Loop2024_HallValueof5(void);
extern real32_T Open_Loop2024_HallValueof7(void);
extern void Open_Loop_MATLABFunction1_Reset(DW_MATLABFunction1_Open_Loop2_T
  *localDW);
extern void Open_Loop2024_MATLABFunction1(boolean_T rtu_In, boolean_T *rty_Out,
  DW_MATLABFunction1_Open_Loop2_T *localDW);

#endif                                 /* Open_Loop2024_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
