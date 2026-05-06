/*
 * @Author: xjf
 * @Date: 2023-03-15 21:03:24
 * @LastEditTime: 2023-03-15 21:06:25
 * @LastEditors: xjf
 * @Description: 
 */
#ifndef __SL_UART_H
#define __SL_UART_H
#include "stm32h7xx_hal.h"

#define SL_UART_DATA_LEN 8
#define SL_UART_PACK_LEN SL_UART_DATA_LEN*2+8
typedef struct{
	int16_t head;
	int16_t fun;
	int16_t data[SL_UART_DATA_LEN];
	int16_t check_sum;
	int16_t tail;
}SL_pack_TypeDef;

extern SL_pack_TypeDef SL_send;
extern SL_pack_TypeDef SL_rec;

void SL_uart_send(int16_t *buff);
void SL_uart_receive(void);

#endif
