/*
 * SL_wifi.h
 *
 *  Created on: Dec 13, 2023
 *      Author: xueji
 */

#ifndef _SL_WIFI_H
#define _SL_WIFI_H
#include "stm32h7xx_hal.h"

#define ESP32C3_UDP_MAXIMUM 2920
#define SL_WIFI_FRAME_LEN 10
#define SL_WIFI_PACK_FRAME_LEN ESP32C3_UDP_MAXIMUM/SL_WIFI_FRAME_LEN
#define SL_WIFI_DATA_LEN SL_WIFI_FRAME_LEN/2-1

/*
 * 一帧wifi数据10个字节，一包UDP包2920字节，两个缓冲区乒乓操作。
 */
typedef struct{
	int16_t fun;
	int16_t data[SL_WIFI_DATA_LEN];
}SL_wifi_frame_TypeDef;

typedef struct{
	SL_wifi_frame_TypeDef frame[2][292];
	uint8_t flag[2];	//buff状态标志;	0:空;	1:写;	2:满;	3:发;
	uint16_t frame_index[2];
}SL_wifi_buff_TypeDef;

#endif /* _SL_WIFI_H */
