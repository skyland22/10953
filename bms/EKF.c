/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EKF.c
 *
 * Code generated for Simulink model 'EKF'.
 *
 * Model version                  : 7.104
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon Jul 10 21:08:47 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "EKF.h"
#define NumBitsPerChar                 8U

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_powd_snf(real_T u0, real_T u1);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
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

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void EKF_step(void)
{
  real_T A1[4];
  real_T A1_0[4];
  real_T P2[4];
  real_T rtb_K_idx_0;
  real_T rtb_K_idx_1;
  real_T rtb_SOC_pre;
  real_T rtb_TmpSignalConversionAtSFun_0;
  real_T rtb_r1;
  real_T rtb_r1_tmp;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  int32_T i;

  /* Outputs for Atomic SubSystem: '<S1>/Cæÿ’Û' */
  /* Fcn: '<S1>/r1' incorporates:
   *  Fcn: '<S1>/c1'
   *  Fcn: '<S4>/C1'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_SOC_pre = rt_powd_snf(rtDW.UnitDelay_DSTATE, 2.0);
  rtb_K_idx_0 = rt_powd_snf(rtDW.UnitDelay_DSTATE, 3.0);
  rtb_K_idx_1 = rt_powd_snf(rtDW.UnitDelay_DSTATE, 4.0);

  /* End of Outputs for SubSystem: '<S1>/Cæÿ’Û' */
  rtb_r1_tmp = rt_powd_snf(rtDW.UnitDelay_DSTATE, 5.0);
  rtb_TmpSignalConversionAtSFun_0 = rt_powd_snf(rtDW.UnitDelay_DSTATE, 6.0);
  rtb_r1 = (((((0.02346 - 0.10537 * rt_powd_snf(rtDW.UnitDelay_DSTATE, 1.0)) +
               1.1371 * rtb_SOC_pre) - 4.55188 * rtb_K_idx_0) + 8.26827 *
             rtb_K_idx_1) - 6.93032 * rtb_r1_tmp) + 2.1787 *
    rtb_TmpSignalConversionAtSFun_0;

  /* Outputs for Atomic SubSystem: '<S1>/Bæÿ’Û' */
  /* Outputs for Atomic SubSystem: '<S1>/Aæÿ’Û' */
  /* Fcn: '<S2>/Fcn' incorporates:
   *  Constant: '<S1>/ts'
   *  Fcn: '<S1>/c1'
   *  Fcn: '<S3>/Fcn'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_r1_tmp = exp(-1.0 / rtb_r1 / ((((((3522.78847 * rtDW.UnitDelay_DSTATE +
    203.1404) - 31392.66753 * rtb_SOC_pre) + 122406.91269 * rtb_K_idx_0) -
    227590.94382 * rtb_K_idx_1) + 198281.56406 * rtb_r1_tmp) - 65171.90395 *
    rtb_TmpSignalConversionAtSFun_0));

  /* End of Outputs for SubSystem: '<S1>/Aæÿ’Û' */
  /* End of Outputs for SubSystem: '<S1>/Bæÿ’Û' */

  /* MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û‘§≤‚' incorporates:
   *  Fcn: '<S2>/Fcn'
   *  UnitDelay: '<S1>/Unit Delay2'
   */
  A1[0] = 1.0;
  A1[2] = 0.0;
  A1[1] = 0.0;

  /* Outputs for Atomic SubSystem: '<S1>/Aæÿ’Û' */
  A1[3] = rtb_r1_tmp;

  /* End of Outputs for SubSystem: '<S1>/Aæÿ’Û' */
  tmp = rtDW.UnitDelay2_DSTATE[0];
  tmp_0 = rtDW.UnitDelay2_DSTATE[1];
  tmp_1 = rtDW.UnitDelay2_DSTATE[2];
  tmp_2 = rtDW.UnitDelay2_DSTATE[3];
  for (i = 0; i < 2; i++) {
    P2[i] = 0.0;
    P2[i] += A1[i] * tmp;
    rtb_TmpSignalConversionAtSFun_0 = A1[i + 2];
    P2[i] += rtb_TmpSignalConversionAtSFun_0 * tmp_1;
    P2[i + 2] = 0.0;
    P2[i + 2] += A1[i] * tmp_0;
    P2[i + 2] += rtb_TmpSignalConversionAtSFun_0 * tmp_2;
    A1_0[i] = 0.0;
    A1_0[i] += P2[i];
    A1_0[i] += P2[i + 2] * 0.0;
    A1_0[i + 2] = 0.0;
    A1_0[i + 2] += P2[i] * 0.0;

    /* Outputs for Atomic SubSystem: '<S1>/Aæÿ’Û' */
    A1_0[i + 2] += P2[i + 2] * rtb_r1_tmp;

    /* End of Outputs for SubSystem: '<S1>/Aæÿ’Û' */
  }

  /* Outputs for Atomic SubSystem: '<S1>/Cæÿ’Û' */
  /* SignalConversion generated from: '<S7>/ SFunction ' incorporates:
   *  Fcn: '<S4>/C1'
   *  MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û∏¸–¬'
   *  MATLAB Function: '<S1>/ø®∂˚¬¸‘ˆ“Êº∆À„'
   *  SignalConversion generated from: '<S5>/ SFunction '
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_TmpSignalConversionAtSFun_0 = (((1.71448 - 7.02494 * rtDW.UnitDelay_DSTATE)
    + 17.12604 * rtb_SOC_pre) - 20.27476 * rtb_K_idx_0) + 9.33495 * rtb_K_idx_1;

  /* End of Outputs for SubSystem: '<S1>/Cæÿ’Û' */

  /* MATLAB Function: '<S1>/ø®∂˚¬¸‘ˆ“Êº∆À„' incorporates:
   *  Constant: '<S1>/π€≤‚‘Î…˘'
   *  MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û∏¸–¬'
   *  MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û‘§≤‚'
   *  SignalConversion generated from: '<S7>/ SFunction '
   */
  P2[0] = A1_0[0] + 2.0E-8;
  P2[2] = A1_0[2];
  P2[1] = A1_0[1];
  P2[3] = A1_0[3] + 1.0E-8;
  rtb_K_idx_0 = (A1_0[0] + 2.0E-8) * rtb_TmpSignalConversionAtSFun_0;
  rtb_SOC_pre = 1.0 / (((rtb_K_idx_0 + -A1_0[1]) *
                        rtb_TmpSignalConversionAtSFun_0 +
                        -(rtb_TmpSignalConversionAtSFun_0 * A1_0[2] + -(A1_0[3]
    + 1.0E-8))) + 1.0E-6);
  rtb_K_idx_0 = (rtb_K_idx_0 + -A1_0[2]) * rtb_SOC_pre;
  rtb_K_idx_1 = (A1_0[1] * rtb_TmpSignalConversionAtSFun_0 + -(A1_0[3] + 1.0E-8))
    * rtb_SOC_pre;

  /* MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û∏¸–¬' incorporates:
   *  SignalConversion generated from: '<S5>/ SFunction '
   */
  A1_0[0] = rtb_K_idx_0 * rtb_TmpSignalConversionAtSFun_0;
  A1_0[1] = rtb_K_idx_1 * rtb_TmpSignalConversionAtSFun_0;
  A1_0[2] = -rtb_K_idx_0;
  A1_0[3] = -rtb_K_idx_1;
  for (i = 0; i < 2; i++) {
    rtb_TmpSignalConversionAtSFun_0 = A1_0[i + 2];
    A1[i] = P2[i] - (rtb_TmpSignalConversionAtSFun_0 * P2[1] + A1_0[i] * P2[0]);
    A1[i + 2] = P2[i + 2] - (rtb_TmpSignalConversionAtSFun_0 * P2[3] + A1_0[i] *
      P2[2]);
  }

  /* Sum: '<S9>/Sum' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Fcn: '<S9>/Fcn'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_SOC_pre = rtConstB.Fcn1 * rtDW.Delay1_DSTATE + rtDW.UnitDelay_DSTATE;

  /* Outputs for Atomic SubSystem: '<S1>/Bæÿ’Û' */
  /* Outputs for Atomic SubSystem: '<S1>/Aæÿ’Û' */
  /* Sum: '<S9>/Sum1' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Fcn: '<S2>/Fcn'
   *  Fcn: '<S3>/Fcn'
   *  Fcn: '<S9>/Fcn1'
   *  Product: '<S9>/Product1'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  rtb_r1 = (1.0 - rtb_r1_tmp) * rtb_r1 * rtDW.Delay1_DSTATE + rtb_r1_tmp *
    rtDW.UnitDelay1_DSTATE;

  /* End of Outputs for SubSystem: '<S1>/Aæÿ’Û' */
  /* End of Outputs for SubSystem: '<S1>/Bæÿ’Û' */

  /* Fcn: '<S1>/uoc' incorporates:
   *  Fcn: '<S1>/ro'
   */
  rtb_r1_tmp = rt_powd_snf(rtb_SOC_pre, 2.0);
  rtb_TmpSignalConversionAtSFun_0 = rt_powd_snf(rtb_SOC_pre, 3.0);
  tmp = rt_powd_snf(rtb_SOC_pre, 4.0);
  tmp_0 = rt_powd_snf(rtb_SOC_pre, 5.0);

  /* Outport: '<Root>/SOC_upd' incorporates:
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtY.SOC_upd = rtDW.UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S1>/Unit Delay2' incorporates:
   *  MATLAB Function: '<S1>/–≠∑Ω≤Óæÿ’Û∏¸–¬'
   */
  rtDW.UnitDelay2_DSTATE[0] = A1[0];
  rtDW.UnitDelay2_DSTATE[1] = A1[2];
  rtDW.UnitDelay2_DSTATE[2] = A1[1];
  rtDW.UnitDelay2_DSTATE[3] = A1[3];

  /* Outputs for Atomic SubSystem: '<S1>/∂ÀµÁ—πº∆À„' */
  /* Fcn: '<S8>/Fcn2' incorporates:
   *  Delay: '<S1>/Delay'
   *  Delay: '<S1>/Delay1'
   *  Fcn: '<S10>/Fcn'
   *  Fcn: '<S1>/ro'
   *  Fcn: '<S1>/uoc'
   *  Fcn: '<S8>/Fcn3'
   */
  rtb_r1_tmp = rtDW.Delay_DSTATE - (((((((1.71448 * rtb_SOC_pre + 3.44003) -
    3.51247 * rtb_r1_tmp) + 5.70868 * rtb_TmpSignalConversionAtSFun_0) - 5.06869
    * tmp) + 1.86699 * tmp_0) - rtb_r1) - (((((((1.19552 * rtb_SOC_pre + 0.04916)
    - 6.25333 * rtb_r1_tmp) + 14.24181 * rtb_TmpSignalConversionAtSFun_0) -
    13.93388 * tmp) + 2.553 * tmp_0) + 4.16285 * rt_powd_snf(rtb_SOC_pre, 6.0))
    - 1.8713 * rt_powd_snf(rtb_SOC_pre, 7.0)) * rtDW.Delay1_DSTATE);

  /* End of Outputs for SubSystem: '<S1>/∂ÀµÁ—πº∆À„' */

  /* Update for UnitDelay: '<S1>/Unit Delay' incorporates:
   *  Fcn: '<S8>/Fcn2'
   */
  rtDW.UnitDelay_DSTATE = rtb_r1_tmp * rtb_K_idx_0 + rtb_SOC_pre;

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  Inport: '<Root>/I_obs'
   */
  rtDW.Delay1_DSTATE = rtU.u_h;

  /* Update for UnitDelay: '<S1>/Unit Delay1' incorporates:
   *  Fcn: '<S8>/Fcn3'
   */
  rtDW.UnitDelay1_DSTATE = rtb_r1_tmp * rtb_K_idx_1 + rtb_r1;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Inport: '<Root>/U_obs'
   */
  rtDW.Delay_DSTATE = rtU.u;
}

/* Model initialize function */
void EKF_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = 1.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
