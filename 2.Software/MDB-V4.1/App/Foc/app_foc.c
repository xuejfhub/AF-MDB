/*
 * @Author: xjf
 * @Date: 2023-03-13 17:21:40
 * @LastEditTime: 2023-03-14 00:21:19
 * @LastEditors: xjf
 * @Description: FOC控制顶层文件，定义输入输出接口，调用 simulink 文件。
 */
#include "app_foc.h"
#include "tim.h"
#include "adc.h"
#include "dac.h"

RT_MODEL rtM;
ExtU rtU;
ExtY rtY;

void foc_control(void)
{
	int16_t pwm_a, pwm_b, pwm_c;

	/* 设置输入变量 */
	rtU.AD_Vbus = (adc3[0]+adc3[2])*4; //ADC3使用的12位模式，
	rtU.ADC_Iabc[0] = -adc2[0]-adc2[3];
	rtU.ADC_Iabc[1] = -adc2[1]-adc2[4];
	rtU.ADC_Iabc[2] = -adc2[2]-adc2[5];
	rtU.Enable = 1;
	rtU.Encoder = __HAL_TIM_GET_COUNTER(&htim3);
	rtU.Hall[0] = HAL_GPIO_ReadPin(HALL_U_GPIO_Port, HALL_U_Pin);
	rtU.Hall[1] = HAL_GPIO_ReadPin(HALL_V_GPIO_Port, HALL_V_Pin);
	rtU.Hall[2] = HAL_GPIO_ReadPin(HALL_W_GPIO_Port, HALL_W_Pin);
	rtU.Spd_set = SL_rec.data[1]/32.0+SL_rec.data[2]/32.0*sin(2*3.1415926*SL_rec.data[3]*(step%20000)/20000);

	/* 调用simulink算法 */
	FOC_step(&rtM, &rtU, &rtY);

	/* 设置输出变量 */
	if(rtY.PowerOn)
	{
		pwm_a = rtY.Duty[0];
		pwm_b = rtY.Duty[1];
		pwm_c = rtY.Duty[2];
	}
	else
	{
		pwm_a = 5000;
		pwm_b = 5000;
		pwm_c = 5000;
	}
	/* 高频注入 */
	float hf;
	hf = 2*3.1415926*(step%20)/20;
	pwm_a +=  SL_rec.data[4]*cos(hf);
	pwm_b +=  SL_rec.data[4]*cos(hf+2*3.1415926/3);
	pwm_c +=  SL_rec.data[4]*cos(hf-2*3.1415926/3);

	pwm_a = pwm_a>10000?10000:pwm_a;
	pwm_b = pwm_b>10000?10000:pwm_b;
	pwm_c = pwm_c>10000?10000:pwm_c;
	pwm_a = pwm_a<0?0:pwm_a;
	pwm_b = pwm_b<0?0:pwm_b;
	pwm_c = pwm_c<0?0:pwm_c;

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,  pwm_a);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,  pwm_b);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,  pwm_c);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 2048+rtY.Sensor_Speed_m*4096/314.15/3.3);

}
