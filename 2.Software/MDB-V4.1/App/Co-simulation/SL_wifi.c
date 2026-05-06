/*
 * SL_wifi_udp.c
 *
 *  Created on: Dec 13, 2023
 *      Author: xueji
 */
#include "SL_wifi.h"

#include "usart.h"
#include "string.h"


SL_wifi_buff_TypeDef ;

uint8_t SL_wifi_buff_write(SL_wifi_buff_TypeDef* buff,SL_wifi_frame_TypeDef* frame)
{
	static uint8_t p = 0;

	if(buff->flag[p]!=2) //buff1满
	{
		memcpy(	(uint8_t*)&(buff->frame[p][buff->frame_index[p]]),
				(uint8_t*)frame,
				SL_WIFI_FRAME_LEN);
		buff->frame_index[p] +=1;
		if(buff->frame_index[p] < SL_WIFI_PACK_FRAME_LEN)
		{
			buff->flag[p] = 1;
		}
		else
		{
			buff->flag[p] = 2;
			p = p?0:1;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t SL_wifi_send_frame(SL_wifi_buff_TypeDef* buff)
{
	static uint8_t p = 0;
	if(buff->flag[p]==2)
	{
		HAL_UART_AbortTransmit(&huart2);
		HAL_UART_Transmit_DMA(&huart2,
				(uint8_t*)&buff->frame[p],
				ESP32C3_UDP_MAXIMUM);
		buff->flag[p] = 3;
		p = p?0:1;

		return 0;
	}
	else
	{
		return 1;
	}
}

