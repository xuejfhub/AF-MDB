/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BLUE_Pin GPIO_PIN_4
#define LED_BLUE_GPIO_Port GPIOE
#define LED_RED_Pin GPIO_PIN_6
#define LED_RED_GPIO_Port GPIOE
#define AD_IC_Pin GPIO_PIN_0
#define AD_IC_GPIO_Port GPIOC
#define LAN_IRQ_Pin GPIO_PIN_2
#define LAN_IRQ_GPIO_Port GPIOC
#define LAN_NRST_Pin GPIO_PIN_3
#define LAN_NRST_GPIO_Port GPIOC
#define AD_VC_Pin GPIO_PIN_0
#define AD_VC_GPIO_Port GPIOA
#define AD_VB_Pin GPIO_PIN_3
#define AD_VB_GPIO_Port GPIOA
#define AD_VA_Pin GPIO_PIN_4
#define AD_VA_GPIO_Port GPIOA
#define AD_VBUS_Pin GPIO_PIN_5
#define AD_VBUS_GPIO_Port GPIOA
#define AD_IB_Pin GPIO_PIN_6
#define AD_IB_GPIO_Port GPIOA
#define AD_IA_Pin GPIO_PIN_0
#define AD_IA_GPIO_Port GPIOB
#define AD_IBUS_Pin GPIO_PIN_1
#define AD_IBUS_GPIO_Port GPIOB
#define HALL_U_Pin GPIO_PIN_8
#define HALL_U_GPIO_Port GPIOD
#define HALL_V_Pin GPIO_PIN_9
#define HALL_V_GPIO_Port GPIOD
#define HALL_W_Pin GPIO_PIN_10
#define HALL_W_GPIO_Port GPIOD
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOC
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOD
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOD
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOD
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOD
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
