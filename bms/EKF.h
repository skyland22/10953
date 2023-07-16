/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EKF.h
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

#ifndef RTW_HEADER_EKF_h_
#define RTW_HEADER_EKF_h_
#include <stddef.h>
#include <math.h>
#ifndef EKF_COMMON_INCLUDES_
#define EKF_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EKF_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay2_DSTATE[4];         /* '<S1>/Unit Delay2' */
  real_T UnitDelay_DSTATE;             /* '<S1>/Unit Delay' */
  real_T Delay1_DSTATE;                /* '<S1>/Delay1' */
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real_T Delay_DSTATE;                 /* '<S1>/Delay' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Fcn1;                   /* '<S3>/Fcn1' */
} ConstB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T u;                            /* '<Root>/U_obs' */
  real_T u_h;                          /* '<Root>/I_obs' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T SOC_upd;                      /* '<Root>/SOC_upd' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/* Model entry point functions */
extern void EKF_initialize(void);
extern void EKF_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/U1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Improved_EKFSim/EKF')    - opens subsystem Improved_EKFSim/EKF
 * hilite_system('Improved_EKFSim/EKF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Improved_EKFSim'
 * '<S1>'   : 'Improved_EKFSim/EKF'
 * '<S2>'   : 'Improved_EKFSim/EKF/A¾ØÕó'
 * '<S3>'   : 'Improved_EKFSim/EKF/B¾ØÕó'
 * '<S4>'   : 'Improved_EKFSim/EKF/C¾ØÕó'
 * '<S5>'   : 'Improved_EKFSim/EKF/Ð­·½²î¾ØÕó¸üÐÂ'
 * '<S6>'   : 'Improved_EKFSim/EKF/Ð­·½²î¾ØÕóÔ¤²â'
 * '<S7>'   : 'Improved_EKFSim/EKF/¿¨¶ûÂüÔöÒæ¼ÆËã'
 * '<S8>'   : 'Improved_EKFSim/EKF/×´Ì¬¸üÐÂ'
 * '<S9>'   : 'Improved_EKFSim/EKF/×´Ì¬Ô¤²â'
 * '<S10>'  : 'Improved_EKFSim/EKF/¶ËµçÑ¹¼ÆËã'
 */
#endif                                 /* RTW_HEADER_EKF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
