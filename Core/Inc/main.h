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

/*---Debug--*/
#define DEBUGMODE 1

#ifdef 	DEBUGMODE
#define DBG_PRINTF(fmt, args...)  \
{\
	rt_kprintf("{%s L:%d F:%s} ", __FILE__, __LINE__, __FUNCTION__);\
	rt_kprintf(fmt, ##args);\
}
#else
#define DBG_PRINTF(fmt, args...)
#endif

#define DEBUG_MODBUS	0
#define DEBUG_SOC			0
#define DEBUG_CADC		0
#define DEBUG_EEP			0
#define DEBUG_VOL			0
#define DEBUG_CURR		0

/* Includes ------------------------------------------------------------------*/
#include <rtthread.h>
//#include "stm32g0xx_hal.h"
#include "stm32g070xx.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_tim.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"
#include "led5.h"
#include "Flash.h"
#include "rtc.h"
#include "modbus.h"
#include "timer.h"

#include "APP_config_def.h"
#include "APP_bms.h"
#include "bsp_sifbus.h"
#include "bsp_SimUart.h"
#include "bsp_SimIIC.h"
#include "bsp_sh367309.h"
#include "bsp_hardiic.h"
#include "bsp_hardiic_reg.h"
#include "APP_current.h"
#include "APP_soc.h"
#include "APP_alarm.h"
#include "APP_temprature.h"
#include "APP_volt.h"
#include "APP_mos.h"
#include "APP_lowpower.h"
#include "APP_config.h"
#include "APP_flash.h"
#include "PCMonitor_protocol.h"
#include "EKF.h"
#include "rtwtypes.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern u32 NewActionTime;
extern rt_mutex_t SH_mutex;
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
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
