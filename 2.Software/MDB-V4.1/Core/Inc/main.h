/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_foc.h"
#include "../../App/Co-simulation/SL_uart.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern uint32_t step,step_last;
extern int16_t adc1[6];
extern int16_t adc2[6];
extern int16_t adc3[4];
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define P_EN_Pin GPIO_PIN_0
#define P_EN_GPIO_Port GPIOB
#define P_FLT_Pin GPIO_PIN_1
#define P_FLT_GPIO_Port GPIOB
#define P_SHDN_Pin GPIO_PIN_2
#define P_SHDN_GPIO_Port GPIOB
#define HALL_U_Pin GPIO_PIN_12
#define HALL_U_GPIO_Port GPIOD
#define HALL_V_Pin GPIO_PIN_13
#define HALL_V_GPIO_Port GPIOD
#define HALL_W_Pin GPIO_PIN_14
#define HALL_W_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_12
#define LED_B_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_4
#define LED_G_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
