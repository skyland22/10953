/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	
	GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	VPRO(0);	//默认拉低，不烧录EEPROM
	
}

//配置电源软开关初始化
void SoftKeyInit()
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	LL_GPIO_DeInit(GPIOB);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	
	//PB1配置为输入，检测高低电平
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//PB2配置为输出，检测高低电平
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_WritePin(GPIOB, LL_GPIO_PIN_2, GPIO_PIN_SET);
	LL_mDelay(500);
}

/* USER CODE BEGIN 2 */
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t PinMask,GPIO_PinState value)
{
 	if(value==GPIO_PIN_RESET)
 	{
 		LL_GPIO_ResetOutputPin(GPIOx,PinMask);
 	}
 	else
 	{
		LL_GPIO_SetOutputPin(GPIOx,PinMask);
	}
}

uint32_t  GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
 	return LL_GPIO_IsInputPinSet(GPIOx,PinMask);
}

void PowerOffScan()
{
	if(!GPIO_ReadPin(GPIOB,LL_GPIO_PIN_1))
	{
		rt_thread_mdelay(10);		//消个抖
		if(!GPIO_ReadPin(GPIOB,LL_GPIO_PIN_1))
		{
			rt_kprintf("\r\n按键关机.\r\n");
			rt_thread_mdelay(500);
			GPIO_WritePin(GPIOB, LL_GPIO_PIN_2,(GPIO_PinState)GPIO_PIN_RESET);
		}
	}
	if((rt_tick_get()/1000-NewActionTime>120)&&(syspara.batStat!=STATE_CHG))	//超过60s未接收到蓝牙数据
	{
		rt_kprintf("\r\n超时关机.\r\n");
		GPIO_WritePin(GPIOB, LL_GPIO_PIN_2,(GPIO_PinState)GPIO_PIN_RESET);
	}
	//rt_kprintf("rt=%d,ut=%d\r\n",rt_tick_get()/1000,USART2RecvTime);
}
/* USER CODE END 2 */
