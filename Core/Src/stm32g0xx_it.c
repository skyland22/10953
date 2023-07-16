/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
//void HardFault_Handler(void)
//{
//  /* USER CODE BEGIN HardFault_IRQn 0 */

//  /* USER CODE END HardFault_IRQn 0 */
//  while (1)
//  {
//    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
//    /* USER CODE END W1_HardFault_IRQn 0 */
//  }
//}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
	u8 data;
	if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART1))//判断接收数据寄存器是否有数据
	{ 
		//清除接收中断标志方式一：读取RDR寄存器以自动清除RXNE标志
		//清除接收中断标志方式二：往RXFRQ寄存器写1(刷新数据)以清除RXNE中断标志
		data = LL_USART_ReceiveData8(USART1); //读接收到的字节，同时相关标志自动清除
		rt_kprintf("%c",data);
		//LL_USART_TransmitData8(USART1,0);
	}
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
	u8 data;
	if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART2))//判断接收数据寄存器是否有数据
	{
		data = LL_USART_ReceiveData8(USART2); //读接收到的字节，同时相关标志自动清除
		//LL_USART_TransmitData8(USART1,data);	//串口1打印,调试用
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{
			LL_TIM_SetCounter(TIM3,0);
			LL_TIM_EnableCounter(TIM3);
			//注释掉这段，即modbus不以换行作为结尾，使用modbus_time计时>3.5个字符
//			if(USART2_RX_STA&0x4000)//接收到了0x0d
//			{
//				if(data!=0x59) USART2_RX_STA=0;//接收错误,重新开始
//				else USART2_RX_STA|=0x8000;	//接收完成了 
//			}
//			else //还没收到0X0D
//			{	
//				if(data==0x58) USART2_RX_STA|=0x4000;
//				else
//				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=data;
					USART2_RX_STA++;
					//modbus_time=rt_tick_get();
					if(USART2_RX_STA>(USART2_REC_LEN-1)) USART2_RX_STA=0;//接收数据错误,重新开始接收
					//if(USART2_RX_STA>7) USART2_RX_STA|=0x8000;						//接收数据完成				
//				}		 
//			}
		}
	}
	NewActionTime=rt_tick_get()/1000;		//串口中断发生时的系统秒数
}

/* USER CODE BEGIN 1 */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */
  /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
 
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */
	if(LL_TIM_IsActiveFlag_UPDATE(TIM3))
	{
		//清除更新中断标志
    LL_TIM_ClearFlag_UPDATE(TIM3);
    LL_TIM_DisableCounter(TIM3);
		USART2_RX_STA|=0x8000;		//串口modbus接收完成标志
		
  }
    /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}
/* USER CODE END 1 */
