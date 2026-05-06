/*
 * @Author: xjf
 * @Date: 2023-03-13 17:21:40
 * @LastEditTime: 2023-03-14 00:21:19
 * @LastEditors: xjf
 * @Description: 
 */
#include "app_foc.h"
#include "tim.h"
#include "MC.h"

extern int16_t adc1[6];
extern int16_t adc2[6];
extern int16_t adc3[6];

void foc_control(void)
{
  int16_t pwm_a, pwm_b, pwm_c;

  rtU.Vbus = 36;
  rtU.ADC_Iabc[0] = adc2[0]+adc2[3];
  rtU.ADC_Iabc[1] = adc1[0]+adc1[3];
  rtU.ADC_Iabc[2] = adc3[0]+adc3[3];
  rtU.Enable = 1;
  rtU.Encoder_cnt = __HAL_TIM_GET_COUNTER(&htim3);
  rtU.Hall[0] = HAL_GPIO_ReadPin(HALL_U_GPIO_Port, HALL_U_Pin);
  rtU.Hall[1] = HAL_GPIO_ReadPin(HALL_V_GPIO_Port, HALL_V_Pin);
  rtU.Hall[2] = HAL_GPIO_ReadPin(HALL_W_GPIO_Port, HALL_W_Pin);
  rtU.SpeedSet = *(int16_t*)SL_rec.data/20.0;
  MC_step();
  pwm_a = rtY.Duty[0];
  pwm_b = rtY.Duty[1];
  pwm_c = rtY.Duty[2];

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,  pwm_a);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,  pwm_b);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,  pwm_c);
}
