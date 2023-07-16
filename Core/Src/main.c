/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
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
u32 NewActionTime=0;		//记录最新的动作时间，一段时间无操作后系统关机
rt_mutex_t SH_mutex;

static struct rt_thread led5_thread;
static struct rt_thread usart2modbus_thread;
static struct rt_thread SOC_thread;
static struct rt_thread Balance_thread;

static char led5_thread_stack[256];
static char usart2modbus_thread_stack[1024];
static char SOC_thread_stack[2048];
static char Balance_thread_stack[256];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
void Configure_PWR(void);
u8 EnterPWRMode(u8 PWRflag);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//电量数码管显示线程
static void led5_thread_entry(void *parameter)
{
	while(1)
	{
		if(0==sysflag.bits.socInit_Flag) LED5DisplayWait();		//SOC未初始化完成
		else LED5Display(syspara.SOC,syspara.batStat);
		//rt_thread_mdelay(10);
		//LED5Display(98,'C');
	}
}

//Modbus服务线程
static void usart2modbus_thread_entry(void *parameter)
{
	while(1)
	{
		modbus_service();
		rt_thread_mdelay(100);
	}
}

//SOC计算线程
static void SOC_thread_entry(void *parameter)
{
	static uint32_t currperiodtime= 0;
	static boolean_T OverrunFlag = false;
	while(1)
	{
		SH_Get_CellTemps();
		Update_CellVolt();
		
		syspara.batStat=SH_Get_ChgSta();
		//if(syspara.batStat==STATE_STATIC) //如果静置超过一段时间则socInit_Flag置0，使用OCV查表
		#if(DEBUG_SOC)
			rt_kprintf("batStat=%c\r\n",syspara.batStat);
		#endif
		
		OCV_SOC_Init();
		Soc_ClrOrSetCtrl();
		
		//syspara.Avgcurrent=processavgCurr(syspara.current);

		//根据电流状态选择充电或者放电积分系数
//		if(syspara.batStat==STATE_DSG) syspara.IntegralPowerjisuan=(syspara.IntegralPower*104L/100);
//		else if(syspara.batStat==STATE_CHG) syspara.IntegralPowerjisuan=syspara.IntegralPower_C;
//		else syspara.IntegralPowerjisuan=1050;
		
		EKF_initialize();
		
		//SOC积分
		if(syspara.batStat!=STATE_STATIC)
		{
			syspara.current=SH_Get_CADCCurrent();
			
#if(DEBUG_SOC)
	rt_kprintf("current=%d\r\n",syspara.current);
#endif
			
			syspara.Period_Integral=abs(rt_tick_get()- currperiodtime);
			currperiodtime = rt_tick_get();
			RemainCap_Integral(syspara.current,syspara.Period_Integral); 
		}else
		{
			syspara.current=0;
#if(DEBUG_CADC)
			SH_Get_CADCCurrent();
#endif
		}
		
		/* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }
	
	/* Step the model */
  EKF_step();

  OverrunFlag = true;
		
#if(DEBUG_CURR)
	rt_kprintf("%d\r\n",-syspara.current);
#endif 
		
		//syspara.SOC = Get_Percent(syspara.RemainCap,syspara.FullChargeCap);
	syspara.SOC=rtY.SOC_upd;
		rt_thread_mdelay(250);		//每ms一次积分
		//rt_kprintf("rt_tick=%d\r\n",rt_tick_get());
	}
}

//均衡控制线程
static void Balance_thread_entry(void *parameter)
{
	while(1)
	{
		BalanceMCUCtrl();
		rt_thread_mdelay(500);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	rt_err_t rst;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	
  //LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
  //LL_SYSCFG_DisableDBATT(LL_SYSCFG_UCPD1_STROBE | LL_SYSCFG_UCPD2_STROBE);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  SoftKeyInit();
	LED5Init();
	MX_GPIO_Init();
  MX_USART1_UART_Init();
  USART2_BLE_Init();
	SIM_I2C_PortInit();
	
	SysParaInit();			//系统参数初始化
	SH367309_Config();	//系统配置初始化
	IWDG_Init();				//看门狗初始化
	TIM3_Init();
	Configure_PWR();		//初始化低功耗模式
	
	rt_mutex_init(SH_mutex, "SH_mutex", RT_IPC_FLAG_FIFO);
	
  /* USER CODE BEGIN 2 */
	//LED5显示线程
	rst = rt_thread_init(&led5_thread,
                        "led5display",
                        led5_thread_entry,
                        RT_NULL,
                        &led5_thread_stack[0],
                        sizeof(led5_thread_stack),
                        RT_THREAD_PRIORITY_MAX-10,
                        20);
  if(rst == RT_EOK) rt_thread_startup(&led5_thread);
												
	//串口2蓝牙Modbus线程
	rst = rt_thread_init(&usart2modbus_thread,
                        "usart2modbus",
                        usart2modbus_thread_entry,
                        RT_NULL,
                        &usart2modbus_thread_stack[0],
                        sizeof(usart2modbus_thread_stack),
                        RT_THREAD_PRIORITY_MAX-9,
                        20);
  if(rst == RT_EOK) rt_thread_startup(&usart2modbus_thread);
	
	//SOC计算线程
	rst = rt_thread_init(&SOC_thread,
                        "SOCcalculate",
                        SOC_thread_entry,
                        RT_NULL,
                        &SOC_thread_stack[0],
                        sizeof(SOC_thread_stack),
                        RT_THREAD_PRIORITY_MAX-8,
                        20);
  if(rst == RT_EOK) rt_thread_startup(&SOC_thread);
												
	//根据EEPROM配置值判断是否开启MCU控制均衡线程
	if(sysflag.bits.MCUCtrolBal)
	{
		rst = rt_thread_init(&Balance_thread,
                        "BalanceControl",
                        Balance_thread_entry,
                        RT_NULL,
                        &Balance_thread_stack[0],
                        sizeof(Balance_thread_stack),
                        RT_THREAD_PRIORITY_MAX-7,
                        20);
		if(rst == RT_EOK) rt_thread_startup(&Balance_thread);
	}
	
  /* USER CODE END 2 */
	
	
	u8 PWRflag=0;
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		LL_IWDG_ReloadCounter(IWDG);
		PowerOffScan();
		//EnterPWRMode(PWRflag);
		rt_thread_mdelay(200);
	
	}
    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

//使用HSE配置64Mhz
#if 1
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* LSI configuration and activation */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 16, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(64000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);
#endif

//使用HSI配置16Mhz
#if 0
	/* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

	/* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(16000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(16000000);
#endif
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Function to configure and initialize PWR IP.
  * @param  None
  * @retval None
  */
void Configure_PWR(void)
{
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);		//使能PWR时钟
	
	
//  /* Enable Power Clock */
//  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
//  
//  /* Check if the system was resumed from StandBy mode */
//  if (LL_PWR_IsActiveFlag_SB() != 0)
//  {
//    /* Clear Standby flag */
//    LL_PWR_ClearFlag_SB();
//    
//    /* Change LED speed to SLOW to indicate exit from Standby mode */
//    //LedSpeed = LED_BLINK_SLOW;
//    /* Wait that user release the User push-button */
//    //while(UserButton_GetState() == 0){}
//  }
//  
//  /* Check and Clear the Wakeup flag */
//  if (LL_PWR_IsActiveFlag_WU2() != 0)
//  {
//    LL_PWR_ClearFlag_WU2();
//  }
}

/**
  * @brief  Function to configure and enter in Standby Mode.
  * @param  None
  * @retval None
  */
u8 EnterPWRMode(u8 PWRflag)
{
#if 0
	if((rt_tick_get()>5000)&&(PWRflag==0))
	{
		LL_PWR_EnterLowPowerRunMode();//低功耗运行模式
		PWRflag=1;
	}
	rt_kprintf("IsLowPowerRunMode=%d.\r\n",LL_PWR_IsEnabledLowPowerRunMode());
#endif

#if 0
	if((rt_tick_get()>5000)&&(PWRflag==0))
	{
		LL_LPM_EnableSleepOnExit();
		LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0);
		LL_LPM_EnableSleep();
		PWRflag=1;
	}
	__WFI();
	rt_kprintf("LL_PWR_GetPowerMode=%d.\r\n",LL_PWR_GetPowerMode());
#endif
	
	return PWRflag;
//  /* Wait that user release the User push-button */
//  //while(UserButton_GetState() == 0){}
//  
//  /* Turn-off LED */
//  /* Note: LED state at this step depends on blinking state at the instant of user button is pressed. */
//  //LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
//  
//  /* Disable all used wakeup sources */
//  //LL_PWR_DisableWakeUpPin(LL_PWR_WAKEUP_PIN2);
//  
//  /* Clear all wake up Flag */
//  //LL_PWR_ClearFlag_WU();
//  
//  /* Set wakeup pin polarity */
//  //LL_PWR_SetWakeUpPinPolarityLow(LL_PWR_WAKEUP_PIN2);

//  /* Enable wakeup pin */
//  //LL_PWR_EnableWakeUpPin(LL_PWR_WAKEUP_PIN2);
//  
//  /* As default User push-button state is high level, need to clear all wake up Flag again */
//  //LL_PWR_ClearFlag_WU();

//	LL_LPM_EnableSleepOnExit();
//  /** Request to enter Standby mode
//    * Following procedure describe in STM32G0xx Reference Manual
//    * See PWR part, section Low-power modes, Standby mode
//    */
//  /* Set Standby mode when CPU enters deepsleep */
//  LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0);
//  
//	
//  /* Set SLEEPDEEP bit of Cortex System Control Register */
//  //LL_LPM_EnableDeepSleep();
//  LL_LPM_EnableSleep();
//	
//  /* This option is used to ensure that store operations are completed */
//#if defined ( __CC_ARM)
//  __force_stores();
//#endif
//  /* Request Wait For Interrupt */
//  __WFI();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
