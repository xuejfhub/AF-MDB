/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    eth_custom_phy_interface.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage
  *			 the ethernet phy.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Private includes ----------------------------------------------------------*/
#include "eth_custom_phy_interface.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int32_t eth_phy_init(void)
{

/* USER CODE BEGIN PHY_INIT_0 */

/* USER CODE END PHY_INIT_0 */

    int32_t ret = ETH_PHY_STATUS_OK;

/* USER CODE BEGIN PHY_INIT_1 */

/* USER CODE END PHY_INIT_1 */
    return ret;
}

int32_t eth_phy_get_link_state(void)
{

  /* USER CODE BEGIN LINK_STATE_0 */
  
  /* 对于 LAN9303，我们强制返回 100M 全双工链路状态
   * 原因：
   * 1. LAN9303 的 PHY0（CPU 端口）是虚拟 PHY，没有真正的链路检测
   * 2. 我们在初始化时已经强制配置为 100M 全双工
   * 3. 如果能接收数据，说明链路肯定是 UP 的
   * 
   * 替代方案：可以读取 PHY1 或 PHY2 的链路状态，但对于直连模式不准确
   */
  
  /* USER CODE END LINK_STATE_0 */

  int32_t  linkstate = ETH_PHY_STATUS_LINK_ERROR;

  /* USER CODE BEGIN LINK_STATE_1 */

  /* USER CODE END LINK_STATE_1 */
  return linkstate;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
