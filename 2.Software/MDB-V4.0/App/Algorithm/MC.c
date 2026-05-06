/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MC.c
 *
 * Code generated for Simulink model 'MC'.
 *
 * Model version                  : 1.159
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sun Jul 16 22:24:48 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "MC.h"
#include "rtwtypes.h"
#include "mw_cmsis.h"
#include <math.h>
#include "arm_math.h"
#include <stddef.h>
#define NumBitsPerChar                 8U
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

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);
static void limitRef2(real32_T rtu_ref2satsquare, real32_T rtu_ref2, real32_T
                      *rty_ref2sat);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Output and update for action system:
 *    '<S26>/limitRef2'
 *    '<S147>/limitRef2'
 */
static void limitRef2(real32_T rtu_ref2satsquare, real32_T rtu_ref2, real32_T
                      *rty_ref2sat)
{
  real32_T tmp;

  /* Switch: '<S28>/Switch' incorporates:
   *  Gain: '<S28>/Gain'
   *  Sqrt: '<S28>/Sqrt'
   *  Switch: '<S28>/Switch1'
   */
  if (rtu_ref2 >= 0.0F) {
    /* Switch: '<S28>/Switch1' incorporates:
     *  Constant: '<S28>/Constant'
     */
    if (rtu_ref2satsquare > 0.0F) {
      tmp = rtu_ref2satsquare;
    } else {
      tmp = 0.0F;
    }

    mw_arm_sqrt_f32(tmp, rty_ref2sat);
  } else {
    if (rtu_ref2satsquare > 0.0F) {
      /* Switch: '<S28>/Switch1' */
      tmp = rtu_ref2satsquare;
    } else {
      /* Switch: '<S28>/Switch1' incorporates:
       *  Constant: '<S28>/Constant'
       */
      tmp = 0.0F;
    }

    /* Sqrt: '<S28>/Sqrt' incorporates:
     *  Switch: '<S28>/Switch1'
     */
    mw_arm_sqrt_f32(tmp, &tmp);
    *rty_ref2sat = (-1.0F) * tmp;
  }

  /* End of Switch: '<S28>/Switch' */
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2f((real32_T)tmp, (real32_T)tmp_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

/* Model step function */
void MC_step(void)
{
  real32_T rtb_ErrIdq_idx_0;
  real32_T rtb_ErrIdq_idx_1;
  real32_T rtb_Merge_e;
  real32_T rtb_Merge_o_idx_0;
  real32_T rtb_Merge_o_idx_1;
  real32_T rtb_Sum1_j_idx_0;
  real32_T rtb_Sum1_j_idx_1;
  real32_T rtb_Sum_o4;
  real32_T rtb_u_idx_0;
  real32_T rtb_u_idx_1;
  real32_T u;
  uint16_T rtb_Switch1;
  uint16_T rtb_Switch1_k;
  int8_T tmp;
  int8_T tmp_0;

  /* Gain: '<S36>/Gain' incorporates:
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  rtDW.Gain = (-0.0002F) * rtDW.UnitDelay1_DSTATE;

  /* Trigonometry: '<S36>/SinCos' */
  rtDW.SinCos_o1 = sinf(rtDW.Gain);
  rtDW.SinCos_o2 = cosf(rtDW.Gain);

  /* Sum: '<S36>/Sum1' incorporates:
   *  Product: '<S36>/Product1'
   *  Product: '<S36>/Product2'
   *  UnitDelay: '<S4>/Unit Delay2'
   */
  rtDW.Sum1 = rtDW.UnitDelay2_DSTATE[0] * rtDW.SinCos_o2 +
    rtDW.UnitDelay2_DSTATE[1] * rtDW.SinCos_o1;

  /* Sum: '<S36>/Sum' incorporates:
   *  Product: '<S36>/Product'
   *  Product: '<S36>/Product3'
   *  UnitDelay: '<S4>/Unit Delay2'
   */
  rtDW.Sum_l = rtDW.UnitDelay2_DSTATE[1] * rtDW.SinCos_o2 -
    rtDW.UnitDelay2_DSTATE[0] * rtDW.SinCos_o1;

  /* Gain: '<S79>/Gain' */
  rtb_Sum1_j_idx_1 = (real32_T)27047 * 2.98023224E-8F;

  /* Gain: '<S79>/µçÁ÷¼ÆËã' incorporates:
   *  Gain: '<S79>/Gain'
   *  Inport: '<Root>/ADC_Iabc'
   */
  rtb_u_idx_0 = rtb_Sum1_j_idx_1 * (real32_T)rtU.ADC_Iabc[0] * 7.5757575F;
  rtb_u_idx_1 = rtb_Sum1_j_idx_1 * (real32_T)rtU.ADC_Iabc[1] * 7.5757575F;

  /* MATLAB Function: '<S79>/to zero' incorporates:
   *  Gain: '<S79>/Gain'
   *  Gain: '<S79>/µçÁ÷¼ÆËã'
   *  Inport: '<Root>/ADC_Iabc'
   */
  rtb_Sum1_j_idx_1 = (rtb_Sum1_j_idx_1 * (real32_T)rtU.ADC_Iabc[2] * 7.5757575F
                      + (rtb_u_idx_0 + rtb_u_idx_1)) / 3.0F;

  /* Outputs for Atomic SubSystem: '<S58>/Clarke Transform' */
  /* AlgorithmDescriptorDelegate generated from: '<S69>/a16' incorporates:
   *  MATLAB Function: '<S79>/to zero'
   */
  arm_clarke_f32(rtb_u_idx_0 - rtb_Sum1_j_idx_1, rtb_u_idx_1 - rtb_Sum1_j_idx_1,
                 &rtDW.algDD_o1_l, &rtDW.algDD_o2_h);

  /* End of Outputs for SubSystem: '<S58>/Clarke Transform' */

  /* Sum: '<S35>/Sum4' incorporates:
   *  Gain: '<S4>/Gain'
   *  Math: '<S30>/Math Function'
   *  Math: '<S30>/Math Function2'
   *  Sum: '<S30>/Add'
   *  Sum: '<S4>/Sum1'
   *  UnitDelay: '<S35>/Unit Delay1'
   *  UnitDelay: '<S4>/Unit Delay3'
   */
  rtDW.P_kk1 = ((rtDW.algDD_o1_l * rtDW.algDD_o1_l + rtDW.algDD_o2_h *
                 rtDW.algDD_o2_h) * 2.0E-5F + rtDW.UnitDelay3_DSTATE) +
    rtDW.UnitDelay1_DSTATE_b;

  /* SampleTimeMath: '<S55>/TSamp'
   *
   * About '<S55>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtDW.TSamp[0] = rtDW.algDD_o1_l * 9.0F;
  rtDW.TSamp[1] = rtDW.algDD_o2_h * 9.0F;

  /* Sum: '<S55>/Diff' incorporates:
   *  UnitDelay: '<S55>/UD'
   *
   * Block description for '<S55>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S55>/UD':
   *
   *  Store in Global RAM
   */
  mw_arm_sub_f32(&rtDW.TSamp[0], &rtDW.UD_DSTATE[0], &rtDW.fv[0], 2U);

  /* Sum: '<S38>/Sum5' incorporates:
   *  Delay: '<S38>/Delay'
   *  Gain: '<S38>/R3'
   *  Sum: '<S55>/Diff'
   *
   * Block description for '<S55>/Diff':
   *
   *  Add in CPU
   */
  rtDW.fv1[0] = rtDW.Delay_DSTATE[0] - 0.165F * rtDW.algDD_o1_l;
  rtDW.fv1[1] = rtDW.Delay_DSTATE[1] - 0.165F * rtDW.algDD_o2_h;
  mw_arm_sub_f32(&rtDW.fv1[0], &rtDW.fv[0], &rtDW.E[0], 2U);

  /* Sum: '<S33>/Add' incorporates:
   *  UnitDelay: '<S33>/Unit Delay'
   *  UnitDelay: '<S33>/Unit Delay1'
   *  UnitDelay: '<S33>/Unit Delay2'
   */
  mw_arm_sub_f32(&rtDW.UnitDelay1_DSTATE_h[0], &rtDW.UnitDelay_DSTATE[0],
                 &rtDW.fv[0], 2U);
  mw_arm_sub_f32(&rtDW.fv[0], &rtDW.UnitDelay2_DSTATE_e[0], &rtDW.fv1[0], 2U);
  mw_arm_add_f32(&rtDW.fv1[0], &rtDW.E[0], &rtDW.Add_c[0], 2U);

  /* Sum: '<S47>/Add1' incorporates:
   *  Constant: '<S47>/Filter_Constant'
   *  Constant: '<S47>/One'
   *  Gain: '<S33>/Gain'
   *  Math: '<S44>/Math Function'
   *  Math: '<S44>/Math Function2'
   *  Product: '<S47>/Product'
   *  Product: '<S47>/Product1'
   *  Sum: '<S44>/Add'
   *  UnitDelay: '<S47>/Unit Delay'
   */
  rtDW.Add1 = (rtDW.Add_c[0] * rtDW.Add_c[0] + rtDW.Add_c[1] * rtDW.Add_c[1]) *
    0.25F * 0.01F + 0.99F * rtDW.UnitDelay_DSTATE_n;

  /* Product: '<S35>/Divide1' incorporates:
   *  Sum: '<S35>/Sum3'
   */
  rtDW.P_kk = 1.0F / (rtDW.Add1 + rtDW.P_kk1) * rtDW.P_kk1;

  /* Sum: '<S35>/Sum2' incorporates:
   *  Product: '<S35>/Divide4'
   *  Sum: '<S35>/Sum1'
   */
  rtb_u_idx_1 = (rtDW.E[0] - rtDW.Sum1) * rtDW.P_kk + rtDW.Sum1;
  rtb_u_idx_0 = (rtDW.E[1] - rtDW.Sum_l) * rtDW.P_kk + rtDW.Sum_l;

  /* Outputs for Atomic SubSystem: '<S37>/·ù½Ç' */
  /* Switch: '<S53>/Switch' incorporates:
   *  Constant: '<S53>/Constant'
   *  DataTypeConversion: '<S53>/Data Type Conversion1'
   *  DataTypeConversion: '<S53>/Data Type Conversion2'
   *  Trigonometry: '<S53>/Atan2'
   */
  if (((uint16_T)1U) > ((uint16_T)1U)) {
    /* Outputs for Atomic SubSystem: '<S53>/Per Unit' */
    /* Gain: '<S54>/Gain' incorporates:
     *  DataTypeConversion: '<S53>/Data Type Conversion1'
     *  DataTypeConversion: '<S53>/Data Type Conversion2'
     *  Trigonometry: '<S53>/Atan2'
     */
    rtDW.Gain_na = 0.159154937F * rt_atan2f_snf(rtb_u_idx_0, rtb_u_idx_1);

    /* Switch: '<S54>/Switch' incorporates:
     *  Bias: '<S54>/Bias'
     */
    if (rtDW.Gain_na >= 0.0F) {
      rtDW.Switch_h1 = rtDW.Gain_na;
    } else {
      rtDW.Switch_h1 = rtDW.Gain_na + 1.0F;
    }

    /* End of Switch: '<S54>/Switch' */
    /* End of Outputs for SubSystem: '<S53>/Per Unit' */
  } else {
    rtDW.Switch_h1 = rt_atan2f_snf(rtb_u_idx_0, rtb_u_idx_1);
  }

  /* End of Switch: '<S53>/Switch' */
  /* End of Outputs for SubSystem: '<S37>/·ù½Ç' */

  /* Sum: '<S42>/Add1' incorporates:
   *  Constant: '<S42>/Filter_Constant'
   *  Constant: '<S42>/One'
   *  Product: '<S42>/Product'
   *  Product: '<S42>/Product1'
   *  UnitDelay: '<S42>/Unit Delay'
   */
  rtDW.fv[0] = rtb_u_idx_1 * 0.001F;
  rtDW.fv1[0] = 0.999F * rtDW.UnitDelay_DSTATE_c[0];
  rtDW.fv[1] = rtb_u_idx_0 * 0.001F;
  rtDW.fv1[1] = 0.999F * rtDW.UnitDelay_DSTATE_c[1];
  mw_arm_add_f32(&rtDW.fv[0], &rtDW.fv1[0], &rtDW.Add1_c[0], 2U);

  /* Sum: '<S31>/Sum1' incorporates:
   *  Product: '<S31>/Product'
   *  Product: '<S31>/Product1'
   */
  u = rtDW.Add1_c[0] * rtb_u_idx_0 - rtb_u_idx_1 * rtDW.Add1_c[1];

  /* Signum: '<S31>/Sign' */
  if (rtIsNaNF(u)) {
    rtDW.Sign = (rtNaNF);
  } else if (u < 0.0F) {
    rtDW.Sign = -1.0F;
  } else {
    rtDW.Sign = (real32_T)(u > 0.0F);
  }

  /* End of Signum: '<S31>/Sign' */

  /* ManualSwitch: '<S1>/Manual Switch' incorporates:
   *  AlgorithmDescriptorDelegate generated from: '<S53>/a16'
   *  Constant: '<S32>/Constant2'
   *  Product: '<S32>/Product3'
   *  Sum: '<S32>/Sum'
   */
  if (((uint8_T)0U) == 1) {
    rtDW.ElecAngle = 0.0F;
  } else {
    /* Outputs for Atomic SubSystem: '<S37>/·ù½Ç' */
    rtDW.ElecAngle = (-1.57079637F) * rtDW.Sign + rtDW.Switch_h1;

    /* End of Outputs for SubSystem: '<S37>/·ù½Ç' */
  }

  /* End of ManualSwitch: '<S1>/Manual Switch' */

  /* Gain: '<S63>/convert_pu' */
  rtDW.convert_pu = 0.159154937F * rtDW.ElecAngle;

  /* If: '<S63>/If' incorporates:
   *  Constant: '<S64>/Constant'
   *  DataTypeConversion: '<S65>/Convert_back'
   *  DataTypeConversion: '<S65>/Convert_uint16'
   *  DataTypeConversion: '<S66>/Convert_back'
   *  DataTypeConversion: '<S66>/Convert_uint16'
   *  Gain: '<S61>/indexing'
   *  RelationalOperator: '<S64>/Compare'
   *  Sum: '<S65>/Sum'
   *  Sum: '<S66>/Sum'
   */
  if (rtDW.convert_pu < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem' incorporates:
     *  ActionPort: '<S65>/Action Port'
     */
    u = rtDW.convert_pu - (real32_T)(int16_T)floorf(rtDW.convert_pu);

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S66>/Action Port'
     */
    u = rtDW.convert_pu - (real32_T)(int16_T)rtDW.convert_pu;

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem1' */
  }

  rtDW.indexing = 1600.0F * u;

  /* End of If: '<S63>/If' */

  /* Switch: '<S139>/Switch1' incorporates:
   *  Constant: '<S136>/ReplaceInport_satMethod'
   *  Constant: '<S139>/ChosenMethod'
   *  Constant: '<S139>/enableInportSatMethod'
   *  Constant: '<S13>/ReplaceInport_satMethod'
   *  Constant: '<S18>/ChosenMethod'
   *  Switch: '<S18>/Switch1'
   */
  if (((uint16_T)0U) != 0) {
    rtb_Switch1 = ((uint16_T)0U);
    rtb_Switch1_k = ((uint16_T)0U);
  } else {
    rtb_Switch1 = ((uint16_T)3U);
    rtb_Switch1_k = ((uint16_T)1U);
  }

  /* End of Switch: '<S139>/Switch1' */

  /* Sqrt: '<S37>/Sqrt' incorporates:
   *  Math: '<S37>/Math Function'
   *  Math: '<S37>/Math Function1'
   *  Sum: '<S37>/Add'
   */
  mw_arm_sqrt_f32(rtb_u_idx_1 * rtb_u_idx_1 + rtb_u_idx_0 * rtb_u_idx_0, &u);

  /* Product: '<S32>/Product2' incorporates:
   *  Gain: '<S32>/Gain1'
   *  Sqrt: '<S37>/Sqrt'
   */
  rtDW.Product2_p = u * 23.7509232F * rtDW.Sign;

  /* ManualSwitch: '<S1>/Manual Switch1' */
  if (((uint8_T)0U) == 1) {
    rtDW.MtrSpeed = 0.0F;
  } else {
    rtDW.MtrSpeed = rtDW.Product2_p;
  }

  /* End of ManualSwitch: '<S1>/Manual Switch1' */

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Inport: '<Root>/SpeedSet'
   */
  if (rtU.SpeedSet > 523.598755F) {
    u = 523.598755F;
  } else if (rtU.SpeedSet < (-523.598755F)) {
    u = (-523.598755F);
  } else {
    u = rtU.SpeedSet;
  }

  /* Sum: '<S8>/Sum' incorporates:
   *  Saturate: '<S8>/Saturation1'
   */
  rtDW.Sum_m = u - rtDW.MtrSpeed;

  /* Sum: '<S194>/Sum' incorporates:
   *  Constant: '<S8>/Constant'
   *  DiscreteIntegrator: '<S185>/Integrator'
   *  Product: '<S190>/PProd Out'
   */
  rtDW.Sum_f = rtDW.Sum_m * 0.02F + rtDW.Integrator_DSTATE;

  /* Saturate: '<S192>/Saturation' */
  if (rtDW.Sum_f > 0.636619747F) {
    u = 0.636619747F;
  } else if (rtDW.Sum_f < (-0.636619747F)) {
    u = (-0.636619747F);
  } else {
    u = rtDW.Sum_f;
  }

  /* Gain: '<S11>/Gain' incorporates:
   *  Saturate: '<S192>/Saturation'
   */
  u *= 15.8339481F;

  /* Saturate: '<S11>/Saturation' */
  if (u > 10.080205F) {
    rtDW.Imag = 10.080205F;
  } else if (u < (-10.080205F)) {
    rtDW.Imag = (-10.080205F);
  } else {
    rtDW.Imag = u;
  }

  /* End of Saturate: '<S11>/Saturation' */

  /* Switch: '<S18>/Switch' incorporates:
   *  Constant: '<S13>/ReplaceInport_satLim'
   *  Constant: '<S18>/Constant3'
   *  Constant: '<S18>/enableInportSatLim'
   */
  if (((uint16_T)0U) != 0) {
    rtDW.Switch = 0.0F;
  } else {
    rtDW.Switch = 10.080205F;
  }

  /* End of Switch: '<S18>/Switch' */

  /* Product: '<S18>/Product' */
  rtDW.Product_f = rtDW.Switch * rtDW.Switch;

  /* Abs: '<S9>/Abs' */
  rtDW.Abs = fabsf(rtDW.MtrSpeed);

  /* If: '<S11>/If' incorporates:
   *  Constant: '<S12>/Constant'
   *  RelationalOperator: '<S12>/Compare'
   */
  if (!(rtDW.Abs >= 314.159271F)) {
    /* Outputs for IfAction SubSystem: '<S11>/MTPA condition' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* SignalConversion generated from: '<S15>/idref' incorporates:
     *  Constant: '<S15>/Constant'
     */
    rtDW.Merge_m = 0.0F;

    /* End of Outputs for SubSystem: '<S11>/MTPA condition' */
  } else {
    /* Outputs for IfAction SubSystem: '<S11>/FWC with CVCP' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* Sum: '<S14>/Add' incorporates:
     *  Constant: '<S14>/Constant'
     *  Gain: '<S14>/Gain'
     *  Math: '<S14>/Math Function'
     *
     * About '<S14>/Math Function':
     *  Operator: reciprocal
     */
    rtDW.Merge_m = 1.0F / rtDW.Abs * 7348.46924F - 23.3909035F;

    /* End of Outputs for SubSystem: '<S11>/FWC with CVCP' */
  }

  /* End of If: '<S11>/If' */

  /* Sum: '<S19>/Sum1' incorporates:
   *  Product: '<S19>/Product'
   *  Product: '<S19>/Product1'
   */
  rtDW.Sum1_b = rtDW.Merge_m * rtDW.Merge_m + rtDW.Imag * rtDW.Imag;

  /* If: '<S13>/If' incorporates:
   *  If: '<S16>/If'
   *  RelationalOperator: '<S16>/Relational Operator'
   */
  if ((rtb_Switch1_k == 1) || (rtb_Switch1_k == 2)) {
    /* Outputs for IfAction SubSystem: '<S13>/D//Q Axis Priority' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S22>/Constant'
     *  RelationalOperator: '<S22>/Compare'
     */
    if (rtb_Switch1_k == ((uint16_T)1U)) {
      /* Switch: '<S17>/Switch' */
      rtDW.rtb_Switch_k_m[0] = rtDW.Merge_m;
      rtDW.rtb_Switch_k_m[1] = rtDW.Imag;
    } else {
      /* Switch: '<S17>/Switch' */
      rtDW.rtb_Switch_k_m[0] = rtDW.Imag;
      rtDW.rtb_Switch_k_m[1] = rtDW.Merge_m;
    }

    /* End of Switch: '<S17>/Switch' */

    /* Gain: '<S26>/Gain' */
    rtDW.Gain_ni = (-1.0F) * rtDW.Switch;

    /* Switch: '<S27>/Switch2' incorporates:
     *  RelationalOperator: '<S27>/LowerRelop1'
     *  RelationalOperator: '<S27>/UpperRelop'
     *  Switch: '<S27>/Switch'
     */
    if (rtDW.rtb_Switch_k_m[0] > rtDW.Switch) {
      rtDW.Switch2_p = rtDW.Switch;
    } else if (rtDW.rtb_Switch_k_m[0] < rtDW.Gain_ni) {
      /* Switch: '<S27>/Switch' */
      rtDW.Switch2_p = rtDW.Gain_ni;
    } else {
      rtDW.Switch2_p = rtDW.rtb_Switch_k_m[0];
    }

    /* End of Switch: '<S27>/Switch2' */

    /* Sum: '<S26>/Sum' incorporates:
     *  Product: '<S26>/Product'
     */
    rtDW.rtb_Sum_h_k = rtDW.Product_f - rtDW.Switch2_p * rtDW.Switch2_p;

    /* If: '<S26>/If' incorporates:
     *  Product: '<S26>/Product2'
     *  RelationalOperator: '<S26>/Relational Operator'
     */
    if (rtDW.rtb_Sum_h_k >= rtDW.rtb_Switch_k_m[1] * rtDW.rtb_Switch_k_m[1]) {
      /* Outputs for IfAction SubSystem: '<S26>/passThrough' incorporates:
       *  ActionPort: '<S29>/Action Port'
       */
      /* Merge: '<S26>/Merge' incorporates:
       *  SignalConversion generated from: '<S29>/ref2'
       */
      rtDW.rtb_Merge_n_c = rtDW.rtb_Switch_k_m[1];

      /* End of Outputs for SubSystem: '<S26>/passThrough' */
    } else {
      /* Outputs for IfAction SubSystem: '<S26>/limitRef2' incorporates:
       *  ActionPort: '<S28>/Action Port'
       */
      limitRef2(rtDW.rtb_Sum_h_k, rtDW.rtb_Switch_k_m[1], &rtDW.rtb_Merge_n_c);

      /* End of Outputs for SubSystem: '<S26>/limitRef2' */
    }

    /* End of If: '<S26>/If' */

    /* Switch: '<S17>/Switch1' incorporates:
     *  Constant: '<S23>/Constant'
     *  RelationalOperator: '<S23>/Compare'
     */
    if (rtb_Switch1_k == ((uint16_T)1U)) {
      rtb_Merge_o_idx_0 = rtDW.Switch2_p;
      rtb_Merge_o_idx_1 = rtDW.rtb_Merge_n_c;
    } else {
      rtb_Merge_o_idx_0 = rtDW.rtb_Merge_n_c;
      rtb_Merge_o_idx_1 = rtDW.Switch2_p;
    }

    /* End of Switch: '<S17>/Switch1' */
    /* End of Outputs for SubSystem: '<S13>/D//Q Axis Priority' */

    /* Outputs for IfAction SubSystem: '<S13>/D-Q Equivalence' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
  } else if (rtDW.Sum1_b > rtDW.Product_f) {
    /* Outputs for IfAction SubSystem: '<S16>/Limiter' incorporates:
     *  ActionPort: '<S20>/Action Port'
     */
    /* If: '<S16>/If' incorporates:
     *  Constant: '<S20>/Constant'
     *  Product: '<S20>/Product'
     *  Product: '<S20>/Product1'
     *  Product: '<S20>/Reciprocal'
     *  Sqrt: '<S20>/Square Root'
     *  Switch: '<S20>/Switch'
     */
    mw_arm_sqrt_f32(rtDW.Sum1_b, &rtDW.SquareRoot_g);
    if (rtDW.SquareRoot_g != 0.0F) {
      u = rtDW.SquareRoot_g;
    } else {
      u = 1.0F;
    }

    rtDW.Reciprocal_n = 1.0F / u;
    rtb_Merge_o_idx_0 = rtDW.Merge_m * rtDW.Switch * rtDW.Reciprocal_n;
    rtb_Merge_o_idx_1 = rtDW.Imag * rtDW.Switch * rtDW.Reciprocal_n;

    /* End of Outputs for SubSystem: '<S16>/Limiter' */
  } else {
    /* Outputs for IfAction SubSystem: '<S16>/Passthrough' incorporates:
     *  ActionPort: '<S21>/Action Port'
     */
    /* If: '<S16>/If' incorporates:
     *  SignalConversion generated from: '<S21>/dqRef'
     */
    rtb_Merge_o_idx_0 = rtDW.Merge_m;
    rtb_Merge_o_idx_1 = rtDW.Imag;

    /* End of Outputs for SubSystem: '<S16>/Passthrough' */

    /* End of Outputs for SubSystem: '<S13>/D-Q Equivalence' */
  }

  /* End of If: '<S13>/If' */

  /* SampleTimeMath: '<S84>/TSamp' incorporates:
   *  Sum: '<S2>/Sum'
   *
   * About '<S84>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtDW.TSamp_k = rtb_Merge_o_idx_0 * 9.0F;

  /* Sum: '<S61>/Sum2' incorporates:
   *  DataTypeConversion: '<S61>/Data Type Conversion1'
   *  DataTypeConversion: '<S61>/Get_Integer'
   */
  rtDW.Sum2_a = rtDW.indexing - (real32_T)(uint16_T)rtDW.indexing;

  /* Selector: '<S61>/Lookup' incorporates:
   *  Constant: '<S61>/offset'
   *  Constant: '<S61>/sine_table_values'
   *  DataTypeConversion: '<S61>/Get_Integer'
   *  Sum: '<S61>/Sum'
   *  Sum: '<S62>/Sum3'
   */
  u = rtConstP.sine_table_values_Value[(int32_T)((uint32_T)0 + (uint16_T)
    rtDW.indexing)];

  /* Sum: '<S62>/Sum4' incorporates:
   *  Constant: '<S61>/offset'
   *  Constant: '<S61>/sine_table_values'
   *  DataTypeConversion: '<S61>/Get_FractionVal'
   *  DataTypeConversion: '<S61>/Get_Integer'
   *  Product: '<S62>/Product'
   *  Selector: '<S61>/Lookup'
   *  Sum: '<S61>/Sum'
   *  Sum: '<S62>/Sum3'
   */
  rtDW.Sum4 = (rtConstP.sine_table_values_Value[(int32_T)((uint32_T)1 +
    (uint16_T)rtDW.indexing)] - u) * rtDW.Sum2_a + u;

  /* Selector: '<S61>/Lookup' incorporates:
   *  Constant: '<S61>/offset'
   *  Constant: '<S61>/sine_table_values'
   *  DataTypeConversion: '<S61>/Get_Integer'
   *  Sum: '<S61>/Sum'
   *  Sum: '<S62>/Sum5'
   */
  u = rtConstP.sine_table_values_Value[(int32_T)((uint32_T)400 + (uint16_T)
    rtDW.indexing)];

  /* Sum: '<S62>/Sum6' incorporates:
   *  Constant: '<S61>/offset'
   *  Constant: '<S61>/sine_table_values'
   *  DataTypeConversion: '<S61>/Get_FractionVal'
   *  DataTypeConversion: '<S61>/Get_Integer'
   *  Product: '<S62>/Product1'
   *  Selector: '<S61>/Lookup'
   *  Sum: '<S61>/Sum'
   *  Sum: '<S62>/Sum5'
   */
  rtDW.Sum6 = (rtConstP.sine_table_values_Value[(int32_T)((uint32_T)401 +
    (uint16_T)rtDW.indexing)] - u) * rtDW.Sum2_a + u;

  /* Outputs for Atomic SubSystem: '<S57>/Park Transform' */
  /* AlgorithmDescriptorDelegate generated from: '<S67>/a16' */
  arm_park_f32(rtDW.algDD_o1_l, rtDW.algDD_o2_h, &rtDW.algDD_o1_m,
               &rtDW.algDD_o2_l, rtDW.Sum4, rtDW.Sum6);

  /* End of Outputs for SubSystem: '<S57>/Park Transform' */

  /* SampleTimeMath: '<S85>/TSamp'
   *
   * About '<S85>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtDW.TSamp_o = rtb_Merge_o_idx_1 * 9.0F;

  /* Sum: '<S7>/Sum' incorporates:
   *  Delay: '<S7>/ÖÍºó²¹³¥'
   */
  rtb_ErrIdq_idx_0 = rtDW._DSTATE[0] - rtDW.algDD_o1_m;
  rtb_ErrIdq_idx_1 = rtDW._DSTATE[1] - rtDW.algDD_o2_l;

  /* Sum: '<S128>/Sum' incorporates:
   *  Constant: '<S7>/Kp'
   *  DiscreteIntegrator: '<S119>/Integrator'
   *  Product: '<S124>/PProd Out'
   */
  rtDW.fv[0] = rtb_ErrIdq_idx_0 * 2.0F;
  rtDW.fv[1] = rtb_ErrIdq_idx_1 * 2.0F;
  mw_arm_add_f32(&rtDW.fv[0], &rtDW.Integrator_DSTATE_d[0], &rtDW.Sum_mg[0], 2U);

  /* Saturate: '<S126>/Saturation' */
  if (rtDW.Sum_mg[0] > 3.6F) {
    u = 3.6F;
  } else if (rtDW.Sum_mg[0] < (-3.6F)) {
    u = (-3.6F);
  } else {
    u = rtDW.Sum_mg[0];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Gain: '<S81>/Lq'
   *  Gain: '<S81>/R1'
   *  Product: '<S81>/Divide2'
   *  Saturate: '<S126>/Saturation'
   *  Sum: '<S81>/Sum4'
   *  Sum: '<S84>/Diff'
   *  UnitDelay: '<S84>/UD'
   *
   * Block description for '<S84>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S84>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Sum1_j_idx_0 = (((rtDW.TSamp_k - rtDW.UD_DSTATE_h) + 0.165F *
                       rtDW.algDD_o1_m) - 0.0018F * rtDW.algDD_o2_l *
                      rtDW.MtrSpeed) + u;

  /* Saturate: '<S126>/Saturation' */
  if (rtDW.Sum_mg[1] > 3.6F) {
    u = 3.6F;
  } else if (rtDW.Sum_mg[1] < (-3.6F)) {
    u = (-3.6F);
  } else {
    u = rtDW.Sum_mg[1];
  }

  /* Sum: '<S7>/Sum1' incorporates:
   *  Constant: '<S81>/×ª×Ó´ÅÁ´1'
   *  Gain: '<S81>/Ld'
   *  Gain: '<S81>/R2'
   *  Product: '<S81>/Divide1'
   *  Saturate: '<S126>/Saturation'
   *  Sum: '<S81>/Sum'
   *  Sum: '<S81>/Sum3'
   *  Sum: '<S85>/Diff'
   *  UnitDelay: '<S85>/UD'
   *
   * Block description for '<S85>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S85>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Sum1_j_idx_1 = ((0.0018F * rtDW.algDD_o1_m + 0.0421036258F) *
                      rtDW.MtrSpeed + ((rtDW.TSamp_o - rtDW.UD_DSTATE_l) +
    0.165F * rtDW.algDD_o2_l)) + u;

  /* Switch: '<S139>/Switch' incorporates:
   *  Constant: '<S136>/ReplaceInport_satLim'
   *  Constant: '<S139>/Constant3'
   *  Constant: '<S139>/enableInportSatLim'
   */
  if (((uint16_T)0U) != 0) {
    rtDW.Switch_h = 0.0F;
  } else {
    rtDW.Switch_h = 18.0F;
  }

  /* End of Switch: '<S139>/Switch' */

  /* Product: '<S139>/Product' */
  rtDW.Product_m = rtDW.Switch_h * rtDW.Switch_h;

  /* Sum: '<S140>/Sum1' incorporates:
   *  Product: '<S140>/Product'
   *  Product: '<S140>/Product1'
   */
  rtDW.Sum1_a = rtb_Sum1_j_idx_0 * rtb_Sum1_j_idx_0 + rtb_Sum1_j_idx_1 *
    rtb_Sum1_j_idx_1;

  /* If: '<S136>/If' incorporates:
   *  If: '<S137>/If'
   *  RelationalOperator: '<S137>/Relational Operator'
   */
  if ((rtb_Switch1 == 1) || (rtb_Switch1 == 2)) {
    /* Outputs for IfAction SubSystem: '<S136>/D//Q Axis Priority' incorporates:
     *  ActionPort: '<S138>/Action Port'
     */
    /* Switch: '<S138>/Switch' incorporates:
     *  Constant: '<S143>/Constant'
     *  RelationalOperator: '<S143>/Compare'
     */
    if (rtb_Switch1 == ((uint16_T)1U)) {
      /* Switch: '<S138>/Switch' */
      rtDW.rtb_Switch_o_c[0] = rtb_Sum1_j_idx_0;
      rtDW.rtb_Switch_o_c[1] = rtb_Sum1_j_idx_1;
    } else {
      /* Switch: '<S138>/Switch' */
      rtDW.rtb_Switch_o_c[0] = rtb_Sum1_j_idx_1;
      rtDW.rtb_Switch_o_c[1] = rtb_Sum1_j_idx_0;
    }

    /* End of Switch: '<S138>/Switch' */

    /* Gain: '<S147>/Gain' */
    rtDW.Gain_jp = (-1.0F) * rtDW.Switch_h;

    /* Switch: '<S148>/Switch2' incorporates:
     *  RelationalOperator: '<S148>/LowerRelop1'
     *  RelationalOperator: '<S148>/UpperRelop'
     *  Switch: '<S148>/Switch'
     */
    if (rtDW.rtb_Switch_o_c[0] > rtDW.Switch_h) {
      rtDW.Switch2 = rtDW.Switch_h;
    } else if (rtDW.rtb_Switch_o_c[0] < rtDW.Gain_jp) {
      /* Switch: '<S148>/Switch' */
      rtDW.Switch2 = rtDW.Gain_jp;
    } else {
      rtDW.Switch2 = rtDW.rtb_Switch_o_c[0];
    }

    /* End of Switch: '<S148>/Switch2' */

    /* Sum: '<S147>/Sum' incorporates:
     *  Product: '<S147>/Product'
     */
    rtb_Sum_o4 = rtDW.Product_m - rtDW.Switch2 * rtDW.Switch2;

    /* If: '<S147>/If' incorporates:
     *  Product: '<S147>/Product2'
     *  RelationalOperator: '<S147>/Relational Operator'
     */
    if (rtb_Sum_o4 >= rtDW.rtb_Switch_o_c[1] * rtDW.rtb_Switch_o_c[1]) {
      /* Outputs for IfAction SubSystem: '<S147>/passThrough' incorporates:
       *  ActionPort: '<S150>/Action Port'
       */
      /* Merge: '<S147>/Merge' incorporates:
       *  SignalConversion generated from: '<S150>/ref2'
       */
      rtb_Merge_e = rtDW.rtb_Switch_o_c[1];

      /* End of Outputs for SubSystem: '<S147>/passThrough' */
    } else {
      /* Outputs for IfAction SubSystem: '<S147>/limitRef2' incorporates:
       *  ActionPort: '<S149>/Action Port'
       */
      limitRef2(rtb_Sum_o4, rtDW.rtb_Switch_o_c[1], &rtb_Merge_e);

      /* End of Outputs for SubSystem: '<S147>/limitRef2' */
    }

    /* End of If: '<S147>/If' */

    /* Switch: '<S138>/Switch1' incorporates:
     *  Constant: '<S144>/Constant'
     *  RelationalOperator: '<S144>/Compare'
     */
    if (rtb_Switch1 == ((uint16_T)1U)) {
      rtb_Sum1_j_idx_0 = rtDW.Switch2;
      rtb_Sum1_j_idx_1 = rtb_Merge_e;
    } else {
      rtb_Sum1_j_idx_0 = rtb_Merge_e;
      rtb_Sum1_j_idx_1 = rtDW.Switch2;
    }

    /* End of Switch: '<S138>/Switch1' */
    /* End of Outputs for SubSystem: '<S136>/D//Q Axis Priority' */

    /* Outputs for IfAction SubSystem: '<S136>/D-Q Equivalence' incorporates:
     *  ActionPort: '<S137>/Action Port'
     */
  } else if (rtDW.Sum1_a > rtDW.Product_m) {
    /* Outputs for IfAction SubSystem: '<S137>/Limiter' incorporates:
     *  ActionPort: '<S141>/Action Port'
     */
    /* If: '<S137>/If' incorporates:
     *  Constant: '<S141>/Constant'
     *  Product: '<S141>/Product'
     *  Product: '<S141>/Product1'
     *  Product: '<S141>/Reciprocal'
     *  Sqrt: '<S141>/Square Root'
     *  Switch: '<S141>/Switch'
     */
    mw_arm_sqrt_f32(rtDW.Sum1_a, &rtDW.SquareRoot);
    if (rtDW.SquareRoot != 0.0F) {
      u = rtDW.SquareRoot;
    } else {
      u = 1.0F;
    }

    rtDW.Reciprocal = 1.0F / u;
    rtb_Sum1_j_idx_0 = rtb_Sum1_j_idx_0 * rtDW.Switch_h * rtDW.Reciprocal;
    rtb_Sum1_j_idx_1 = rtb_Sum1_j_idx_1 * rtDW.Switch_h * rtDW.Reciprocal;

    /* End of Outputs for SubSystem: '<S137>/Limiter' */

    /* End of Outputs for SubSystem: '<S136>/D-Q Equivalence' */
  }

  /* End of If: '<S136>/If' */

  /* Outputs for Atomic SubSystem: '<S60>/Inverse Park Transform' */
  /* AlgorithmDescriptorDelegate generated from: '<S77>/a16' */
  arm_inv_park_f32(rtb_Sum1_j_idx_0, rtb_Sum1_j_idx_1, &rtDW.algDD_o1,
                   &rtDW.algDD_o2, rtDW.Sum4, rtDW.Sum6);

  /* End of Outputs for SubSystem: '<S60>/Inverse Park Transform' */

  /* Switch: '<S3>/Switch1' incorporates:
   *  Inport: '<Root>/Enable'
   */
  if (rtU.Enable > 0.0F) {
    /* Gain: '<S76>/sqrt3_by_two' */
    rtDW.sqrt3_by_two = 0.866025388F * rtDW.algDD_o2;

    /* Gain: '<S76>/one_by_two' */
    rtDW.one_by_two = 0.5F * rtDW.algDD_o1;

    /* Sum: '<S76>/add_c' */
    rtDW.add_c = (0.0F - rtDW.one_by_two) - rtDW.sqrt3_by_two;

    /* Sum: '<S76>/add_b' */
    rtDW.add_b = rtDW.sqrt3_by_two - rtDW.one_by_two;

    /* Gain: '<S74>/one_by_two' incorporates:
     *  MinMax: '<S74>/Max'
     *  MinMax: '<S74>/Min'
     *  Sum: '<S74>/Add'
     */
    rtDW.one_by_two_g = (fmaxf(fmaxf(rtDW.algDD_o1, rtDW.add_b), rtDW.add_c) +
                         fminf(fminf(rtDW.algDD_o1, rtDW.add_b), rtDW.add_c)) *
      (-0.5F);

    /* Sum: '<S3>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S59>/Gain'
     *  Gain: '<S73>/Gain'
     *  Inport: '<Root>/Vbus'
     *  Product: '<S3>/Divide'
     *  Sum: '<S73>/Add3'
     */
    u = (rtDW.algDD_o1 + rtDW.one_by_two_g) * 1.15470052F * 0.866025388F /
      rtU.Vbus + 0.5F;

    /* Saturate: '<S3>/ÏÞ·ù' */
    if (u > 0.99F) {
      u = 0.99F;
    } else if (u < 0.01F) {
      u = 0.01F;
    }

    /* Outport: '<Root>/Duty' incorporates:
     *  Gain: '<S3>/Gain1'
     *  Saturate: '<S3>/ÏÞ·ù'
     */
    rtY.Duty[0] = (int16_T)floorf(10000.0F * u);

    /* Sum: '<S3>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S59>/Gain'
     *  Gain: '<S73>/Gain'
     *  Inport: '<Root>/Vbus'
     *  Product: '<S3>/Divide'
     *  Sum: '<S73>/Add1'
     */
    u = (rtDW.add_b + rtDW.one_by_two_g) * 1.15470052F * 0.866025388F / rtU.Vbus
      + 0.5F;

    /* Saturate: '<S3>/ÏÞ·ù' */
    if (u > 0.99F) {
      u = 0.99F;
    } else if (u < 0.01F) {
      u = 0.01F;
    }

    /* Outport: '<Root>/Duty' incorporates:
     *  Gain: '<S3>/Gain1'
     *  Saturate: '<S3>/ÏÞ·ù'
     */
    rtY.Duty[1] = (int16_T)floorf(10000.0F * u);

    /* Sum: '<S3>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S59>/Gain'
     *  Gain: '<S73>/Gain'
     *  Inport: '<Root>/Vbus'
     *  Product: '<S3>/Divide'
     *  Sum: '<S73>/Add2'
     */
    u = (rtDW.one_by_two_g + rtDW.add_c) * 1.15470052F * 0.866025388F / rtU.Vbus
      + 0.5F;

    /* Saturate: '<S3>/ÏÞ·ù' */
    if (u > 0.99F) {
      u = 0.99F;
    } else if (u < 0.01F) {
      u = 0.01F;
    }

    /* Outport: '<Root>/Duty' incorporates:
     *  Gain: '<S3>/Gain1'
     *  Saturate: '<S3>/ÏÞ·ù'
     */
    rtY.Duty[2] = (int16_T)floorf(10000.0F * u);
  } else {
    /* Outport: '<Root>/Duty' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    rtY.Duty[0] = 0;
    rtY.Duty[1] = 0;
    rtY.Duty[2] = 0;
  }

  /* End of Switch: '<S3>/Switch1' */

  /* Sum: '<S34>/Add' incorporates:
   *  UnitDelay: '<S34>/Unit Delay'
   *  UnitDelay: '<S34>/Unit Delay1'
   *  UnitDelay: '<S34>/Unit Delay2'
   */
  mw_arm_sub_f32(&rtDW.UnitDelay1_DSTATE_a[0], &rtDW.UnitDelay_DSTATE_g[0],
                 &rtDW.fv[0], 2U);
  mw_arm_sub_f32(&rtDW.fv[0], &rtDW.UnitDelay2_DSTATE_f[0], &rtDW.fv1[0], 2U);
  rtDW.fv[0] = rtDW.algDD_o1_l;
  rtDW.fv[1] = rtDW.algDD_o2_h;
  mw_arm_add_f32(&rtDW.fv1[0], &rtDW.fv[0], &rtDW.Add_i[0], 2U);

  /* DeadZone: '<S178>/DeadZone' */
  if (rtDW.Sum_f > 0.636619747F) {
    rtDW.DeadZone_a = rtDW.Sum_f - 0.636619747F;
  } else if (rtDW.Sum_f >= (-0.636619747F)) {
    rtDW.DeadZone_a = 0.0F;
  } else {
    rtDW.DeadZone_a = rtDW.Sum_f - (-0.636619747F);
  }

  /* End of DeadZone: '<S178>/DeadZone' */

  /* Product: '<S182>/IProd Out' incorporates:
   *  Constant: '<S8>/Constant1'
   */
  rtDW.IProdOut_c = rtDW.Sum_m * 0.0001F;

  /* Outport: '<Root>/MtrSpeed' */
  rtY.MtrSpeed = rtDW.MtrSpeed;

  /* Gain: '<S4>/Gain1' */
  rtDW.Gain1 = 0.0002F * rtDW.Product2_p;

  /* Product: '<S35>/Divide2' */
  rtDW.Divide2_n = rtDW.Add1 * rtDW.P_kk;

  /* Outport: '<Root>/ElecAngle' */
  rtY.ElecAngle = rtDW.ElecAngle;

  /* Update for UnitDelay: '<S4>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE = rtDW.Product2_p;

  /* Update for UnitDelay: '<S4>/Unit Delay3' incorporates:
   *  Math: '<S4>/Math Function'
   *  Product: '<S4>/Divide5'
   */
  rtDW.UnitDelay3_DSTATE = rtDW.Gain1 * rtDW.Gain1 * rtDW.Divide2_n;

  /* Update for UnitDelay: '<S35>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_b = rtDW.Divide2_n;

  /* Update for UnitDelay: '<S47>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_n = rtDW.Add1;

  /* DeadZone: '<S112>/DeadZone' */
  if (rtDW.Sum_mg[0] > 3.6F) {
    rtb_Sum1_j_idx_1 = rtDW.Sum_mg[0] - 3.6F;
  } else if (rtDW.Sum_mg[0] >= (-3.6F)) {
    rtb_Sum1_j_idx_1 = 0.0F;
  } else {
    rtb_Sum1_j_idx_1 = rtDW.Sum_mg[0] - (-3.6F);
  }

  /* Product: '<S116>/IProd Out' incorporates:
   *  Constant: '<S7>/Ki'
   */
  rtb_ErrIdq_idx_0 *= 0.05F;

  /* Update for UnitDelay: '<S4>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE[0] = rtb_u_idx_1;

  /* Update for Delay: '<S38>/Delay' */
  rtDW.Delay_DSTATE[0] = rtDW.Delay_DSTATE[2];

  /* Update for UnitDelay: '<S55>/UD'
   *
   * Block description for '<S55>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE[0] = rtDW.TSamp[0];

  /* Update for UnitDelay: '<S33>/Unit Delay1' incorporates:
   *  UnitDelay: '<S33>/Unit Delay'
   */
  rtDW.UnitDelay1_DSTATE_h[0] = rtDW.UnitDelay_DSTATE[0];

  /* Update for UnitDelay: '<S33>/Unit Delay' incorporates:
   *  UnitDelay: '<S33>/Unit Delay2'
   */
  rtDW.UnitDelay_DSTATE[0] = rtDW.UnitDelay2_DSTATE_e[0];

  /* Update for UnitDelay: '<S33>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE_e[0] = rtDW.E[0];

  /* Update for UnitDelay: '<S42>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_c[0] = rtDW.Add1_c[0];

  /* DeadZone: '<S112>/DeadZone' */
  if (rtDW.Sum_mg[1] > 3.6F) {
    rtb_Sum1_j_idx_0 = rtDW.Sum_mg[1] - 3.6F;
  } else if (rtDW.Sum_mg[1] >= (-3.6F)) {
    rtb_Sum1_j_idx_0 = 0.0F;
  } else {
    rtb_Sum1_j_idx_0 = rtDW.Sum_mg[1] - (-3.6F);
  }

  /* Product: '<S116>/IProd Out' incorporates:
   *  Constant: '<S7>/Ki'
   */
  rtb_u_idx_1 = rtb_ErrIdq_idx_1 * 0.05F;

  /* Update for UnitDelay: '<S4>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE[1] = rtb_u_idx_0;

  /* Update for Delay: '<S38>/Delay' */
  rtDW.Delay_DSTATE[1] = rtDW.Delay_DSTATE[3];

  /* Update for UnitDelay: '<S55>/UD'
   *
   * Block description for '<S55>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE[1] = rtDW.TSamp[1];

  /* Update for UnitDelay: '<S33>/Unit Delay1' incorporates:
   *  UnitDelay: '<S33>/Unit Delay'
   */
  rtDW.UnitDelay1_DSTATE_h[1] = rtDW.UnitDelay_DSTATE[1];

  /* Update for UnitDelay: '<S33>/Unit Delay' incorporates:
   *  UnitDelay: '<S33>/Unit Delay2'
   */
  rtDW.UnitDelay_DSTATE[1] = rtDW.UnitDelay2_DSTATE_e[1];

  /* Update for UnitDelay: '<S33>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE_e[1] = rtDW.E[1];

  /* Update for UnitDelay: '<S42>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_c[1] = rtDW.Add1_c[1];

  /* Update for Delay: '<S38>/Delay' incorporates:
   *  SignalConversion generated from: '<S38>/Delay'
   */
  rtDW.Delay_DSTATE[2] = rtDW.algDD_o1;
  rtDW.Delay_DSTATE[3] = rtDW.algDD_o2;

  /* Switch: '<S176>/Switch1' incorporates:
   *  Constant: '<S176>/Clamping_zero'
   *  Constant: '<S176>/Constant'
   *  Constant: '<S176>/Constant2'
   *  RelationalOperator: '<S176>/fix for DT propagation issue'
   */
  if (rtDW.DeadZone_a > 0.0F) {
    tmp = 1;
  } else {
    tmp = (-1);
  }

  /* Switch: '<S176>/Switch2' incorporates:
   *  Constant: '<S176>/Clamping_zero'
   *  Constant: '<S176>/Constant3'
   *  Constant: '<S176>/Constant4'
   *  RelationalOperator: '<S176>/fix for DT propagation issue1'
   */
  if (rtDW.IProdOut_c > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = (-1);
  }

  /* Switch: '<S176>/Switch' incorporates:
   *  Constant: '<S176>/Clamping_zero'
   *  Constant: '<S176>/Constant1'
   *  Logic: '<S176>/AND3'
   *  RelationalOperator: '<S176>/Equal1'
   *  RelationalOperator: '<S176>/Relational Operator'
   *  Switch: '<S176>/Switch1'
   *  Switch: '<S176>/Switch2'
   */
  if ((0.0F != rtDW.DeadZone_a) && (tmp == tmp_0)) {
    u = 0.0F;
  } else {
    u = rtDW.IProdOut_c;
  }

  /* Update for DiscreteIntegrator: '<S185>/Integrator' incorporates:
   *  Switch: '<S176>/Switch'
   */
  rtDW.Integrator_DSTATE += 1.0F * u;

  /* Update for UnitDelay: '<S84>/UD'
   *
   * Block description for '<S84>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE_h = rtDW.TSamp_k;

  /* Update for UnitDelay: '<S85>/UD'
   *
   * Block description for '<S85>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE_l = rtDW.TSamp_o;

  /* Update for Delay: '<S7>/ÖÍºó²¹³¥' */
  rtDW._DSTATE[0] = rtDW._DSTATE[2];

  /* Switch: '<S110>/Switch1' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant'
   *  Constant: '<S110>/Constant2'
   *  RelationalOperator: '<S110>/fix for DT propagation issue'
   */
  if (rtb_Sum1_j_idx_1 > 0.0F) {
    tmp = 1;
  } else {
    tmp = (-1);
  }

  /* Switch: '<S110>/Switch2' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant3'
   *  Constant: '<S110>/Constant4'
   *  RelationalOperator: '<S110>/fix for DT propagation issue1'
   */
  if (rtb_ErrIdq_idx_0 > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = (-1);
  }

  /* Switch: '<S110>/Switch' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant1'
   *  Logic: '<S110>/AND3'
   *  RelationalOperator: '<S110>/Equal1'
   *  RelationalOperator: '<S110>/Relational Operator'
   *  Switch: '<S110>/Switch1'
   *  Switch: '<S110>/Switch2'
   */
  if ((0.0F != rtb_Sum1_j_idx_1) && (tmp == tmp_0)) {
    rtb_ErrIdq_idx_0 = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S119>/Integrator' incorporates:
   *  Switch: '<S110>/Switch'
   */
  rtDW.fv[0] = 1.0F * rtb_ErrIdq_idx_0;

  /* Update for Delay: '<S7>/ÖÍºó²¹³¥' */
  rtDW._DSTATE[1] = rtDW._DSTATE[3];

  /* Switch: '<S110>/Switch1' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant'
   *  Constant: '<S110>/Constant2'
   *  RelationalOperator: '<S110>/fix for DT propagation issue'
   */
  if (rtb_Sum1_j_idx_0 > 0.0F) {
    tmp = 1;
  } else {
    tmp = (-1);
  }

  /* Switch: '<S110>/Switch2' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant3'
   *  Constant: '<S110>/Constant4'
   *  RelationalOperator: '<S110>/fix for DT propagation issue1'
   */
  if (rtb_u_idx_1 > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = (-1);
  }

  /* Switch: '<S110>/Switch' incorporates:
   *  Constant: '<S110>/Clamping_zero'
   *  Constant: '<S110>/Constant1'
   *  Logic: '<S110>/AND3'
   *  RelationalOperator: '<S110>/Equal1'
   *  RelationalOperator: '<S110>/Relational Operator'
   *  Switch: '<S110>/Switch1'
   *  Switch: '<S110>/Switch2'
   */
  if ((0.0F != rtb_Sum1_j_idx_0) && (tmp == tmp_0)) {
    rtb_u_idx_1 = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S119>/Integrator' incorporates:
   *  Switch: '<S110>/Switch'
   */
  rtDW.fv[1] = 1.0F * rtb_u_idx_1;

  /* Update for Delay: '<S7>/ÖÍºó²¹³¥' incorporates:
   *  SignalConversion generated from: '<S7>/ÖÍºó²¹³¥'
   *  Sum: '<S2>/Sum'
   */
  rtDW._DSTATE[2] = rtb_Merge_o_idx_0;
  rtDW._DSTATE[3] = rtb_Merge_o_idx_1;

  /* Update for DiscreteIntegrator: '<S119>/Integrator' */
  mw_arm_add_f32(&rtDW.Integrator_DSTATE_d[0], &rtDW.fv[0], &rtDW.fv1[0], 2U);
  rtDW.Integrator_DSTATE_d[0] = rtDW.fv1[0];

  /* Update for UnitDelay: '<S34>/Unit Delay1' incorporates:
   *  UnitDelay: '<S34>/Unit Delay'
   */
  rtDW.UnitDelay1_DSTATE_a[0] = rtDW.UnitDelay_DSTATE_g[0];

  /* Update for UnitDelay: '<S34>/Unit Delay' incorporates:
   *  UnitDelay: '<S34>/Unit Delay2'
   */
  rtDW.UnitDelay_DSTATE_g[0] = rtDW.UnitDelay2_DSTATE_f[0];

  /* Update for DiscreteIntegrator: '<S119>/Integrator' */
  rtDW.Integrator_DSTATE_d[1] = rtDW.fv1[1];

  /* Update for UnitDelay: '<S34>/Unit Delay1' incorporates:
   *  UnitDelay: '<S34>/Unit Delay'
   */
  rtDW.UnitDelay1_DSTATE_a[1] = rtDW.UnitDelay_DSTATE_g[1];

  /* Update for UnitDelay: '<S34>/Unit Delay' incorporates:
   *  UnitDelay: '<S34>/Unit Delay2'
   */
  rtDW.UnitDelay_DSTATE_g[1] = rtDW.UnitDelay2_DSTATE_f[1];

  /* Update for UnitDelay: '<S34>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE_f[0] = rtDW.algDD_o1_l;
  rtDW.UnitDelay2_DSTATE_f[1] = rtDW.algDD_o2_h;

  /* Update for UnitDelay: '<S52>/Unit Delay' incorporates:
   *  Constant: '<S52>/Filter_Constant'
   *  Constant: '<S52>/One'
   *  Gain: '<S34>/Gain'
   *  Math: '<S49>/Math Function'
   *  Math: '<S49>/Math Function2'
   *  Product: '<S52>/Product'
   *  Product: '<S52>/Product1'
   *  Sum: '<S49>/Add'
   *  Sum: '<S52>/Add1'
   */
  rtDW.UnitDelay_DSTATE_d = (rtDW.Add_i[0] * rtDW.Add_i[0] + rtDW.Add_i[1] *
    rtDW.Add_i[1]) * 0.25F * 0.01F + 0.99F * rtDW.UnitDelay_DSTATE_d;
}

/* Model initialize function */
void MC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE = 0.001F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
