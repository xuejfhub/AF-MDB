/*
 * @Author: xjf
 * @Date: 2023-03-15 21:00:12
 * @LastEditTime: 2023-03-16 17:39:45
 * @LastEditors: xjf
 * @Description: 
 */
#include "app_simulink.h"
#include "usart.h"
#include "string.h"

simulink_pack_TypeDef SL_send;
simulink_pack_TypeDef SL_rec;

void SL_data_send(int16_t *buff)
{
	SL_send.head = 0x00ff;
	SL_send.fun = 0x0000;
	memcpy(SL_send.data, buff, SIMULINK_DATA_LEN*2);
	SL_send.check_sum = SL_send.fun;
	for(uint8_t i=0;i<SIMULINK_DATA_LEN;i++)
	{
		SL_send.check_sum += SL_send.data[i];
	}
	SL_send.tail = 0xff00;
    HAL_UART_AbortTransmit(&huart1);
    HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&SL_send, SIMULINK_PACK_LEN);
}
void SL_data_receive(void)
{
    
}
