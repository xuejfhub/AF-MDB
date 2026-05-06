/*
 * app_task.c
 *
 *  Created on: Dec 13, 2023
 *      Author: xueji
 */
#include "app_task.h"
#include "app_foc.h"

/*
 * 控制任务，通过dma中断触发；
 * 执行频率：20kHz
 */
void control_task()
{
	foc_control();

}
