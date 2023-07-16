/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
}GPIO_PinState;
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_R_PORT	 GPIOB
#define LED_R_Pin		 LL_GPIO_PIN_3

#define LED_G_PORT	 GPIOD
#define LED_G_Pin		 LL_GPIO_PIN_3
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
#define TVCC_1   	   LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6)
#define TVCC_0  	   LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6)

#define POWER_Open   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4)
#define POWER_Close  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4)

#define RS485_RxEn   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_9)
#define RS485_RxDen  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_9)
 
#define LED_R(x) 		 GPIO_WritePin(LED_R_PORT, LED_R_Pin,(GPIO_PinState)x)
#define LED_G(x)		 GPIO_WritePin(LED_G_PORT, LED_G_Pin,(GPIO_PinState)x)
#define VPRO(x) 		 GPIO_WritePin(GPIOA, LL_GPIO_PIN_1,(GPIO_PinState)x)
#define SH_SHIP(m)   GPIO_WritePin(GPIOA, LL_GPIO_PIN_7, (GPIO_PinState)m)
#define SING_CHG_DET GPIO_ReadPin(GPIOA, LL_GPIO_PIN_4) 
#define SING_DSG_DET GPIO_ReadPin(GPIOB, LL_GPIO_PIN_8)

void MX_GPIO_Init(void);
void SoftKeyInit(void);
void PowerOffScan(void);
void MX_EXTI_Init(void);
void Sleep_PinInit(void);
void GPIO_OpenWEAK_EXTI(void );
void GPIO_CloseWEAK_EXTI(void );
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t PinMask,GPIO_PinState value);
uint32_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t PinMask);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

