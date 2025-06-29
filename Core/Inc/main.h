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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_include.h"


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
#define infrared1_led_Pin GPIO_PIN_0
#define infrared1_led_GPIO_Port GPIOA
#define infrared1_do_Pin GPIO_PIN_1
#define infrared1_do_GPIO_Port GPIOA
#define CAR_PWM_Pin GPIO_PIN_2
#define CAR_PWM_GPIO_Port GPIOA
#define monter_right_1_Pin GPIO_PIN_3
#define monter_right_1_GPIO_Port GPIOA
#define monter_right_2_Pin GPIO_PIN_4
#define monter_right_2_GPIO_Port GPIOA
#define monter_left_1_Pin GPIO_PIN_5
#define monter_left_1_GPIO_Port GPIOA
#define monter_left_2_Pin GPIO_PIN_6
#define monter_left_2_GPIO_Port GPIOA
#define servo_pwm_Pin GPIO_PIN_0
#define servo_pwm_GPIO_Port GPIOB
#define key_Pin GPIO_PIN_1
#define key_GPIO_Port GPIOB
#define keyB10_Pin GPIO_PIN_10
#define keyB10_GPIO_Port GPIOB
#define keyB11_Pin GPIO_PIN_11
#define keyB11_GPIO_Port GPIOB
#define infrared2_do_Pin GPIO_PIN_13
#define infrared2_do_GPIO_Port GPIOB
#define ultrasonic_tx_Pin GPIO_PIN_7
#define ultrasonic_tx_GPIO_Port GPIOB
#define oled_scl_Pin GPIO_PIN_8
#define oled_scl_GPIO_Port GPIOB
#define oled_sda_Pin GPIO_PIN_9
#define oled_sda_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
