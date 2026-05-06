/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MC.h
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

#ifndef RTW_HEADER_MC_h_
#define RTW_HEADER_MC_h_
#ifndef MC_COMMON_INCLUDES_
#define MC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MC_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define MC_M                           (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay2_DSTATE[2];       /* '<S4>/Unit Delay2' */
  real32_T Delay_DSTATE[4];            /* '<S38>/Delay' */
  real32_T UD_DSTATE[2];               /* '<S55>/UD' */
  real32_T UnitDelay1_DSTATE_h[2];     /* '<S33>/Unit Delay1' */
  real32_T UnitDelay_DSTATE[2];        /* '<S33>/Unit Delay' */
  real32_T UnitDelay2_DSTATE_e[2];     /* '<S33>/Unit Delay2' */
  real32_T UnitDelay_DSTATE_c[2];      /* '<S42>/Unit Delay' */
  real32_T _DSTATE[4];                 /* '<S7>/滞后补偿' */
  real32_T Integrator_DSTATE_d[2];     /* '<S119>/Integrator' */
  real32_T UnitDelay1_DSTATE_a[2];     /* '<S34>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_g[2];      /* '<S34>/Unit Delay' */
  real32_T UnitDelay2_DSTATE_f[2];     /* '<S34>/Unit Delay2' */
  real32_T TSamp[2];                   /* '<S55>/TSamp' */
  real32_T E[2];                       /* '<S38>/Sum5' */
  real32_T Add_c[2];                   /* '<S33>/Add' */
  real32_T Add1_c[2];                  /* '<S42>/Add1' */
  real32_T Sum_mg[2];                  /* '<S128>/Sum' */
  real32_T Add_i[2];                   /* '<S34>/Add' */
  real32_T rtb_Switch_k_m[2];
  real32_T rtb_Switch_o_c[2];
  real32_T fv[2];
  real32_T fv1[2];
  real32_T UnitDelay1_DSTATE;          /* '<S4>/Unit Delay1' */
  real32_T UnitDelay3_DSTATE;          /* '<S4>/Unit Delay3' */
  real32_T UnitDelay1_DSTATE_b;        /* '<S35>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_n;         /* '<S47>/Unit Delay' */
  real32_T Integrator_DSTATE;          /* '<S185>/Integrator' */
  real32_T UD_DSTATE_h;                /* '<S84>/UD' */
  real32_T UD_DSTATE_l;                /* '<S85>/UD' */
  real32_T UnitDelay_DSTATE_d;         /* '<S52>/Unit Delay' */
  real32_T Gain;                       /* '<S36>/Gain' */
  real32_T SinCos_o1;                  /* '<S36>/SinCos' */
  real32_T SinCos_o2;                  /* '<S36>/SinCos' */
  real32_T Sum1;                       /* '<S36>/Sum1' */
  real32_T Sum_l;                      /* '<S36>/Sum' */
  real32_T algDD_o1_l;
  real32_T algDD_o2_h;
  real32_T P_kk1;                      /* '<S35>/Sum4' */
  real32_T Add1;                       /* '<S47>/Add1' */
  real32_T P_kk;                       /* '<S35>/Divide1' */
  real32_T Switch_h1;                  /* '<S53>/Switch' */
  real32_T Gain_na;                    /* '<S54>/Gain' */
  real32_T Sign;                       /* '<S31>/Sign' */
  real32_T ElecAngle;                  /* '<S1>/Manual Switch' */
  real32_T convert_pu;                 /* '<S63>/convert_pu' */
  real32_T indexing;                   /* '<S61>/indexing' */
  real32_T Product2_p;                 /* '<S32>/Product2' */
  real32_T MtrSpeed;                   /* '<S1>/Manual Switch1' */
  real32_T Sum_m;                      /* '<S8>/Sum' */
  real32_T Sum_f;                      /* '<S194>/Sum' */
  real32_T Imag;                       /* '<S11>/Saturation' */
  real32_T Switch;                     /* '<S18>/Switch' */
  real32_T Product_f;                  /* '<S18>/Product' */
  real32_T Abs;                        /* '<S9>/Abs' */
  real32_T Merge_m;                    /* '<S11>/Merge' */
  real32_T Sum1_b;                     /* '<S19>/Sum1' */
  real32_T Gain_ni;                    /* '<S26>/Gain' */
  real32_T SquareRoot_g;               /* '<S20>/Square Root' */
  real32_T Reciprocal_n;               /* '<S20>/Reciprocal' */
  real32_T Switch2_p;                  /* '<S27>/Switch2' */
  real32_T TSamp_k;                    /* '<S84>/TSamp' */
  real32_T Sum2_a;                     /* '<S61>/Sum2' */
  real32_T Sum4;                       /* '<S62>/Sum4' */
  real32_T Sum6;                       /* '<S62>/Sum6' */
  real32_T algDD_o1_m;
  real32_T algDD_o2_l;
  real32_T TSamp_o;                    /* '<S85>/TSamp' */
  real32_T Switch_h;                   /* '<S139>/Switch' */
  real32_T Product_m;                  /* '<S139>/Product' */
  real32_T Sum1_a;                     /* '<S140>/Sum1' */
  real32_T Gain_jp;                    /* '<S147>/Gain' */
  real32_T SquareRoot;                 /* '<S141>/Square Root' */
  real32_T algDD_o1;
  real32_T algDD_o2;
  real32_T Reciprocal;                 /* '<S141>/Reciprocal' */
  real32_T Switch2;                    /* '<S148>/Switch2' */
  real32_T sqrt3_by_two;               /* '<S76>/sqrt3_by_two' */
  real32_T one_by_two;                 /* '<S76>/one_by_two' */
  real32_T add_c;                      /* '<S76>/add_c' */
  real32_T add_b;                      /* '<S76>/add_b' */
  real32_T one_by_two_g;               /* '<S74>/one_by_two' */
  real32_T DeadZone_a;                 /* '<S178>/DeadZone' */
  real32_T IProdOut_c;                 /* '<S182>/IProd Out' */
  real32_T Gain1;                      /* '<S4>/Gain1' */
  real32_T Divide2_n;                  /* '<S35>/Divide2' */
  real32_T rtb_Sum_h_k;
  real32_T rtb_Merge_n_c;
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: sine_table_values_Value
   * Referenced by: '<S61>/sine_table_values'
   */
  real32_T sine_table_values_Value[2002];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Enable;                     /* '<Root>/Enable' */
  real32_T SpeedSet;                   /* '<Root>/SpeedSet' */
  real32_T Vbus;                       /* '<Root>/Vbus' */
  int8_T Hall[3];                      /* '<Root>/Hall' */
  int16_T Encoder_cnt;                 /* '<Root>/Encoder_cnt' */
  int16_T ADC_Iabc[3];                 /* '<Root>/ADC_Iabc' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int16_T Duty[3];                     /* '<Root>/Duty' */
  real32_T ElecAngle;                  /* '<Root>/ElecAngle' */
  real32_T MtrSpeed;                   /* '<Root>/MtrSpeed' */
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

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void MC_initialize(void);
extern void MC_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * hilite_system('MCS/MC')    - opens subsystem MCS/MC
 * hilite_system('MCS/MC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MCS'
 * '<S1>'   : 'MCS/MC'
 * '<S2>'   : 'MCS/MC/MTPA'
 * '<S3>'   : 'MCS/MC/占空比计算'
 * '<S4>'   : 'MCS/MC/反电动势卡尔曼观测器'
 * '<S5>'   : 'MCS/MC/坐标变换'
 * '<S6>'   : 'MCS/MC/数据解算'
 * '<S7>'   : 'MCS/MC/电流控制'
 * '<S8>'   : 'MCS/MC/转速控制'
 * '<S9>'   : 'MCS/MC/MTPA/MTPA Control Reference'
 * '<S10>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System'
 * '<S11>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM'
 * '<S12>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/Compare To Constant1'
 * '<S13>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter'
 * '<S14>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/FWC with CVCP'
 * '<S15>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/MTPA condition'
 * '<S16>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D-Q Equivalence'
 * '<S17>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority'
 * '<S18>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/Inport//Dialog Selection'
 * '<S19>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/Magnitude_calc'
 * '<S20>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D-Q Equivalence/Limiter'
 * '<S21>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D-Q Equivalence/Passthrough'
 * '<S22>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/Compare To Constant'
 * '<S23>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/Compare To Constant1'
 * '<S24>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/flipInputs'
 * '<S25>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/flipInputs1'
 * '<S26>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/limiter'
 * '<S27>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/limiter/limitRef1'
 * '<S28>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/limiter/limitRef2'
 * '<S29>'  : 'MCS/MC/MTPA/MTPA Control Reference/Motor_System/Surface PMSM/DQ Limiter/D//Q Axis Priority/limiter/passThrough'
 * '<S30>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem'
 * '<S31>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem2'
 * '<S32>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem3'
 * '<S33>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计'
 * '<S34>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1'
 * '<S35>'  : 'MCS/MC/反电动势卡尔曼观测器/最优估计'
 * '<S36>'  : 'MCS/MC/反电动势卡尔曼观测器/状态转移'
 * '<S37>'  : 'MCS/MC/反电动势卡尔曼观测器/矢量变换'
 * '<S38>'  : 'MCS/MC/反电动势卡尔曼观测器/转子磁链反电动势'
 * '<S39>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem2/IIR Filter'
 * '<S40>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem2/IIR Filter/IIR Filter'
 * '<S41>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem2/IIR Filter/IIR Filter/Low-pass'
 * '<S42>'  : 'MCS/MC/反电动势卡尔曼观测器/Subsystem2/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S43>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计/IIR Filter'
 * '<S44>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计/Subsystem'
 * '<S45>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计/IIR Filter/IIR Filter'
 * '<S46>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计/IIR Filter/IIR Filter/Low-pass'
 * '<S47>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S48>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1/IIR Filter'
 * '<S49>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1/Subsystem'
 * '<S50>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1/IIR Filter/IIR Filter'
 * '<S51>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1/IIR Filter/IIR Filter/Low-pass'
 * '<S52>'  : 'MCS/MC/反电动势卡尔曼观测器/噪声方差估计1/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S53>'  : 'MCS/MC/反电动势卡尔曼观测器/矢量变换/幅角'
 * '<S54>'  : 'MCS/MC/反电动势卡尔曼观测器/矢量变换/幅角/Per Unit'
 * '<S55>'  : 'MCS/MC/反电动势卡尔曼观测器/转子磁链反电动势/Discrete Derivative2'
 * '<S56>'  : 'MCS/MC/坐标变换/Subsystem11'
 * '<S57>'  : 'MCS/MC/坐标变换/Subsystem2'
 * '<S58>'  : 'MCS/MC/坐标变换/Subsystem3'
 * '<S59>'  : 'MCS/MC/坐标变换/Subsystem4'
 * '<S60>'  : 'MCS/MC/坐标变换/Subsystem5'
 * '<S61>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup'
 * '<S62>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup/Interpolation'
 * '<S63>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup/WrapUp'
 * '<S64>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S65>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S66>'  : 'MCS/MC/坐标变换/Subsystem11/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S67>'  : 'MCS/MC/坐标变换/Subsystem2/Park Transform'
 * '<S68>'  : 'MCS/MC/坐标变换/Subsystem2/Park Transform/Switch_Axis'
 * '<S69>'  : 'MCS/MC/坐标变换/Subsystem3/Clarke Transform'
 * '<S70>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator'
 * '<S71>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Modulation method'
 * '<S72>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Voltage Input'
 * '<S73>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Modulation method/SVPWM'
 * '<S74>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S75>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Voltage Input/Valphabeta'
 * '<S76>'  : 'MCS/MC/坐标变换/Subsystem4/PWM Reference Generator/Voltage Input/Valphabeta/Inverse Clarke Transform'
 * '<S77>'  : 'MCS/MC/坐标变换/Subsystem5/Inverse Park Transform'
 * '<S78>'  : 'MCS/MC/坐标变换/Subsystem5/Inverse Park Transform/Switch_Axis'
 * '<S79>'  : 'MCS/MC/数据解算/电流计算'
 * '<S80>'  : 'MCS/MC/数据解算/电流计算/to zero'
 * '<S81>'  : 'MCS/MC/电流控制/前馈控制'
 * '<S82>'  : 'MCS/MC/电流控制/反馈控制'
 * '<S83>'  : 'MCS/MC/电流控制/限幅'
 * '<S84>'  : 'MCS/MC/电流控制/前馈控制/Discrete Derivative'
 * '<S85>'  : 'MCS/MC/电流控制/前馈控制/Discrete Derivative1'
 * '<S86>'  : 'MCS/MC/电流控制/反馈控制/Anti-windup'
 * '<S87>'  : 'MCS/MC/电流控制/反馈控制/D Gain'
 * '<S88>'  : 'MCS/MC/电流控制/反馈控制/Filter'
 * '<S89>'  : 'MCS/MC/电流控制/反馈控制/Filter ICs'
 * '<S90>'  : 'MCS/MC/电流控制/反馈控制/I Gain'
 * '<S91>'  : 'MCS/MC/电流控制/反馈控制/Ideal P Gain'
 * '<S92>'  : 'MCS/MC/电流控制/反馈控制/Ideal P Gain Fdbk'
 * '<S93>'  : 'MCS/MC/电流控制/反馈控制/Integrator'
 * '<S94>'  : 'MCS/MC/电流控制/反馈控制/Integrator ICs'
 * '<S95>'  : 'MCS/MC/电流控制/反馈控制/N Copy'
 * '<S96>'  : 'MCS/MC/电流控制/反馈控制/N Gain'
 * '<S97>'  : 'MCS/MC/电流控制/反馈控制/P Copy'
 * '<S98>'  : 'MCS/MC/电流控制/反馈控制/Parallel P Gain'
 * '<S99>'  : 'MCS/MC/电流控制/反馈控制/Reset Signal'
 * '<S100>' : 'MCS/MC/电流控制/反馈控制/Saturation'
 * '<S101>' : 'MCS/MC/电流控制/反馈控制/Saturation Fdbk'
 * '<S102>' : 'MCS/MC/电流控制/反馈控制/Sum'
 * '<S103>' : 'MCS/MC/电流控制/反馈控制/Sum Fdbk'
 * '<S104>' : 'MCS/MC/电流控制/反馈控制/Tracking Mode'
 * '<S105>' : 'MCS/MC/电流控制/反馈控制/Tracking Mode Sum'
 * '<S106>' : 'MCS/MC/电流控制/反馈控制/Tsamp - Integral'
 * '<S107>' : 'MCS/MC/电流控制/反馈控制/Tsamp - Ngain'
 * '<S108>' : 'MCS/MC/电流控制/反馈控制/postSat Signal'
 * '<S109>' : 'MCS/MC/电流控制/反馈控制/preSat Signal'
 * '<S110>' : 'MCS/MC/电流控制/反馈控制/Anti-windup/Disc. Clamping Parallel'
 * '<S111>' : 'MCS/MC/电流控制/反馈控制/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S112>' : 'MCS/MC/电流控制/反馈控制/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S113>' : 'MCS/MC/电流控制/反馈控制/D Gain/Disabled'
 * '<S114>' : 'MCS/MC/电流控制/反馈控制/Filter/Disabled'
 * '<S115>' : 'MCS/MC/电流控制/反馈控制/Filter ICs/Disabled'
 * '<S116>' : 'MCS/MC/电流控制/反馈控制/I Gain/External Parameters'
 * '<S117>' : 'MCS/MC/电流控制/反馈控制/Ideal P Gain/Passthrough'
 * '<S118>' : 'MCS/MC/电流控制/反馈控制/Ideal P Gain Fdbk/Disabled'
 * '<S119>' : 'MCS/MC/电流控制/反馈控制/Integrator/Discrete'
 * '<S120>' : 'MCS/MC/电流控制/反馈控制/Integrator ICs/Internal IC'
 * '<S121>' : 'MCS/MC/电流控制/反馈控制/N Copy/Disabled wSignal Specification'
 * '<S122>' : 'MCS/MC/电流控制/反馈控制/N Gain/Disabled'
 * '<S123>' : 'MCS/MC/电流控制/反馈控制/P Copy/Disabled'
 * '<S124>' : 'MCS/MC/电流控制/反馈控制/Parallel P Gain/External Parameters'
 * '<S125>' : 'MCS/MC/电流控制/反馈控制/Reset Signal/Disabled'
 * '<S126>' : 'MCS/MC/电流控制/反馈控制/Saturation/Enabled'
 * '<S127>' : 'MCS/MC/电流控制/反馈控制/Saturation Fdbk/Disabled'
 * '<S128>' : 'MCS/MC/电流控制/反馈控制/Sum/Sum_PI'
 * '<S129>' : 'MCS/MC/电流控制/反馈控制/Sum Fdbk/Disabled'
 * '<S130>' : 'MCS/MC/电流控制/反馈控制/Tracking Mode/Disabled'
 * '<S131>' : 'MCS/MC/电流控制/反馈控制/Tracking Mode Sum/Passthrough'
 * '<S132>' : 'MCS/MC/电流控制/反馈控制/Tsamp - Integral/TsSignalSpecification'
 * '<S133>' : 'MCS/MC/电流控制/反馈控制/Tsamp - Ngain/Passthrough'
 * '<S134>' : 'MCS/MC/电流控制/反馈控制/postSat Signal/Forward_Path'
 * '<S135>' : 'MCS/MC/电流控制/反馈控制/preSat Signal/Forward_Path'
 * '<S136>' : 'MCS/MC/电流控制/限幅/DQ Limiter'
 * '<S137>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D-Q Equivalence'
 * '<S138>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority'
 * '<S139>' : 'MCS/MC/电流控制/限幅/DQ Limiter/Inport//Dialog Selection'
 * '<S140>' : 'MCS/MC/电流控制/限幅/DQ Limiter/Magnitude_calc'
 * '<S141>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D-Q Equivalence/Limiter'
 * '<S142>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D-Q Equivalence/Passthrough'
 * '<S143>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/Compare To Constant'
 * '<S144>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/Compare To Constant1'
 * '<S145>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/flipInputs'
 * '<S146>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/flipInputs1'
 * '<S147>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/limiter'
 * '<S148>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/limiter/limitRef1'
 * '<S149>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/limiter/limitRef2'
 * '<S150>' : 'MCS/MC/电流控制/限幅/DQ Limiter/D//Q Axis Priority/limiter/passThrough'
 * '<S151>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset'
 * '<S152>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Anti-windup'
 * '<S153>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/D Gain'
 * '<S154>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Filter'
 * '<S155>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Filter ICs'
 * '<S156>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/I Gain'
 * '<S157>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Ideal P Gain'
 * '<S158>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk'
 * '<S159>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Integrator'
 * '<S160>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Integrator ICs'
 * '<S161>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/N Copy'
 * '<S162>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/N Gain'
 * '<S163>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/P Copy'
 * '<S164>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Parallel P Gain'
 * '<S165>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Reset Signal'
 * '<S166>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Saturation'
 * '<S167>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk'
 * '<S168>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Sum'
 * '<S169>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Sum Fdbk'
 * '<S170>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tracking Mode'
 * '<S171>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum'
 * '<S172>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral'
 * '<S173>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain'
 * '<S174>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/postSat Signal'
 * '<S175>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/preSat Signal'
 * '<S176>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel'
 * '<S177>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S178>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S179>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/D Gain/Disabled'
 * '<S180>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Filter/Disabled'
 * '<S181>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Filter ICs/Disabled'
 * '<S182>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/I Gain/External Parameters'
 * '<S183>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Ideal P Gain/Passthrough'
 * '<S184>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk/Disabled'
 * '<S185>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Integrator/Discrete'
 * '<S186>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Integrator ICs/Internal IC'
 * '<S187>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/N Copy/Disabled wSignal Specification'
 * '<S188>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/N Gain/Disabled'
 * '<S189>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/P Copy/Disabled'
 * '<S190>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Parallel P Gain/External Parameters'
 * '<S191>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Reset Signal/Disabled'
 * '<S192>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Saturation/Enabled'
 * '<S193>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk/Disabled'
 * '<S194>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Sum/Sum_PI'
 * '<S195>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Sum Fdbk/Disabled'
 * '<S196>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tracking Mode/Disabled'
 * '<S197>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum/Passthrough'
 * '<S198>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral/TsSignalSpecification'
 * '<S199>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain/Passthrough'
 * '<S200>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/postSat Signal/Forward_Path'
 * '<S201>' : 'MCS/MC/转速控制/Discrete PI Controller  with anti-windup & reset/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_MC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
