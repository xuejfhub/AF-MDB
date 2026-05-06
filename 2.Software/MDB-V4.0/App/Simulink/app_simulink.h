/*
 * @Author: xjf
 * @Date: 2023-03-15 21:03:24
 * @LastEditTime: 2023-03-15 21:06:25
 * @LastEditors: xjf
 * @Description: 
 */
#ifndef __APP_SIMULINK_H
#define __APP_SIMULINK_H
#include "stm32h7xx_hal.h"

#define SIMULINK_DATA_LEN 12
#define SIMULINK_PACK_LEN SIMULINK_DATA_LEN*2+8
typedef struct{
	int16_t head;
	int16_t fun;
	int16_t data[SIMULINK_DATA_LEN];
	int16_t check_sum;
	int16_t tail;
}simulink_pack_TypeDef;

extern simulink_pack_TypeDef SL_send;
extern simulink_pack_TypeDef SL_rec;

void SL_data_send(int16_t *buff);
void SL_data_receive(void);

#endif
