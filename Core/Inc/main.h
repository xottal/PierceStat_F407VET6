/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TempMeas1_Pin GPIO_PIN_0
#define TempMeas1_GPIO_Port GPIOC
#define TempMeas2_Pin GPIO_PIN_1
#define TempMeas2_GPIO_Port GPIOC
#define TempMeas3_Pin GPIO_PIN_2
#define TempMeas3_GPIO_Port GPIOC
#define TempMeas4_Pin GPIO_PIN_3
#define TempMeas4_GPIO_Port GPIOC
#define U_Heater_Meas_Pin GPIO_PIN_0
#define U_Heater_Meas_GPIO_Port GPIOA
#define U_POWER_Meas_Pin GPIO_PIN_1
#define U_POWER_Meas_GPIO_Port GPIOA
#define CurrMeas1_A_Pin GPIO_PIN_2
#define CurrMeas1_A_GPIO_Port GPIOA
#define CurrMeas1_B_Pin GPIO_PIN_3
#define CurrMeas1_B_GPIO_Port GPIOA
#define CurrMeas2_A_Pin GPIO_PIN_4
#define CurrMeas2_A_GPIO_Port GPIOA
#define CurrMeas2_B_Pin GPIO_PIN_5
#define CurrMeas2_B_GPIO_Port GPIOA
#define GateL1_A_Pin GPIO_PIN_6
#define GateL1_A_GPIO_Port GPIOA
#define GateL1_B_Pin GPIO_PIN_7
#define GateL1_B_GPIO_Port GPIOA
#define GateH1_A_Pin GPIO_PIN_4
#define GateH1_A_GPIO_Port GPIOC
#define GateH1_B_Pin GPIO_PIN_5
#define GateH1_B_GPIO_Port GPIOC
#define Gates1_A_Dis_Pin GPIO_PIN_0
#define Gates1_A_Dis_GPIO_Port GPIOB
#define Gates1_B_Dis_Pin GPIO_PIN_1
#define Gates1_B_Dis_GPIO_Port GPIOB
#define Gates2_A_Dis_Pin GPIO_PIN_2
#define Gates2_A_Dis_GPIO_Port GPIOB
#define GateL2_A_Pin GPIO_PIN_12
#define GateL2_A_GPIO_Port GPIOD
#define GateL2_B_Pin GPIO_PIN_13
#define GateL2_B_GPIO_Port GPIOD
#define GateH2_A_Pin GPIO_PIN_14
#define GateH2_A_GPIO_Port GPIOD
#define GateH2_B_Pin GPIO_PIN_15
#define GateH2_B_GPIO_Port GPIOD
#define Set_U_Heater_Pin GPIO_PIN_8
#define Set_U_Heater_GPIO_Port GPIOC
#define Disable_DC_DC_Pin GPIO_PIN_9
#define Disable_DC_DC_GPIO_Port GPIOC
#define Gates2_B_Dis_Pin GPIO_PIN_3
#define Gates2_B_Dis_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
