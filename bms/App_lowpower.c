#include "main.h"
S8_BITS deepSleepFlag;

void WakeUpInit(void)
{
	//NVIC_SystemReset();
}

void Enter_Stop_ENable(void)
{
	/* Stop mode with Main Regulator */
	MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, LL_PWR_MODE_STOP1);
	/* Set SLEEPDEEP bit of Cortex System Control Register */
	SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
	/* Request Wait For Interrupt */
	__WFI();
	/* Reset SLEEPDEEP bit of Cortex System Control Register */
	CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
 }


void Enter_StopMode(void)
{
	SH_Set_IDLE();
	
	LL_mDelay(300);
	Sleep_PinInit();
	LL_SYSTICK_DisableIT();

	SetWakeUpTimer_IT( RTC_WAKE_SEC, LL_RTC_WAKEUPCLOCK_CKSPRE);

	Enter_Stop_ENable();
	//NVIC_SystemReset();
	GPIO_CloseWEAK_EXTI();
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	/* Configure the system clock */
	SystemClock_Config(1);
	
	/* USER CODE BEGIN SysInit */
	NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
	LL_SYSTICK_EnableIT();
	bsp_init(1);
}



void DeepSleep(void)
{
	if(0 != Flash_WritePara())
	{
		//printf("Flash_WritePara err!!\r\n");
	}
	//printf("*****GT_ForcePowerDown*****\r\n");
	POWER_Close;
	LL_mDelay(1000);
	SH_SHIP(GPIO_PIN_RESET);
	LL_mDelay(2000);
}

extern uint8_t	Ctrl_CH_FET;
//–›√ﬂºÏ≤‚
void SleepCheck(void)
{
	static uint16_t timeout = 0;//
	static uint8_t SmallCurrTime= 0;
	S16_BITS sleepFlag;
	sleepFlag.bytes = 0;
	if((abs(syspara.current))>CFG_SLP_C)
	{
		if(SmallCurrTime<10)
		{
			SmallCurrTime++;
		}
	}
	else
	{
		SmallCurrTime=0;
	}
	if(i2c_dev.Nodatatime<100) 	i2c_dev.Nodatatime++;

//	sleepFlag.bits.bit1 = (((syspara.tempMin<=(Def_Sof_UTD+TEMP_OFFSET))&&(syspara.dsgMos==1))?1:0);
	sleepFlag.bits.bit2 = ((syspara.tempMax>=(Def_SH_OTC+TEMP_OFFSET))?1:0);
//	sleepFlag.bits.bit3 = (((syspara.voltMax>3500)&&(syspara.chgMos==1))?1:0);
	sleepFlag.bits.bit4 = ((SmallCurrTime>=1)?1:0);
	sleepFlag.bits.bit5 = (shAlarm.bytes== 0)?0:1;
//	sleepFlag.bits.bit6 = (((syspara.tempMin<=(Def_Sof_UTC+TEMP_OFFSET))&&(syspara.chgMos==1))?1:0);
	sleepFlag.bits.bit8 = (deepSleepFlag.bytes==0)?0:1;
	sleepFlag.bits.bit10 = (sysflag.bits.VoltChargeBigFlag== 0)?0:1;
	sleepFlag.bits.bit11 = (RS485Buf.NodataTime<5)?1:0;
	sleepFlag.bits.bit14 = (i2c_dev.Nodatatime<5)?1:0;
	sleepFlag.bits.bit12 = (sysflag.bits.LoadFlag==1);
	sleepFlag.bits.bit13 = (Ctrl_CH_FET==1);
#ifdef DBG_Printf_SLEEP
	RS485_RxDen;
	printf("SleepCheck : %d %x %x\r\n ",timeout,sleepFlag.bytes,sysflag.bytes);
	LL_mDelay(2);
	RS485_RxEn;
#endif
	if(sleepFlag.bytes == 0)
	{
		timeout++;
		if((timeout>TimeOut(DEF_SLEEP_sec))||(sysflag.bits.SysWeakFlag==1))
		{
			sysflag.bits.CHGWeak= 0;
			sysflag.bits.IICWeak= 0;
			sysflag.bits.ALARMWeak= 0;	
			sysflag.bits.RTCWeak= 0; 
			sysflag.bits.DETWeak= 0;
			sysflag.bits.RS485Weak= 0;
			sysflag.bits.SysWeakFlag= 0;
			Enter_StopMode();
#ifdef DBG_Printf_SLEEP
			RS485_RxDen;
			printf("weakFlag : %x \r\n ",sysflag.bytes);
			LL_mDelay(2);
			RS485_RxEn;
#endif
//			sysflag.bits.SysWeakFlag=1;
			if(sysflag.bits.RTCWeak!=0)
			{
				CutCapValue= (DEF_CAP*10+DEF_CAP/10*50);
			}
			timeout= TimeOut(DEF_SLEEP_sec)-TimeOut(5);
		}
	}
	else
	{
		timeout = 0;	
		sysflag.bits.SysWeakFlag= 0;
		if(deepSleepFlag.bytes==0)
		{
			sysflag.bits.RTCWeak= 0;
		}
	}
}
//…Ó∂»–›√ﬂºÏ≤‚
void DeepSleepCheck(void)
{
	
	static uint8_t timeout = 0;
//	static uint8_t boardErrCount= 0;
	deepSleepFlag.bytes = 0;

	deepSleepFlag.bits.bit0 = (syspara.voltMin<CFG_DSLP_VMIN)?1:0;

#ifdef DBG_Printf_SLEEP
	printf("DeepSleepCheck : %x %d %d\r\n ",timeout,deepSleepFlag.bytes,sysflag.bits.RTCWeak);
#endif	
	if(deepSleepFlag.bytes!=0)
	{
		timeout++;
		if(timeout>TimeOut(20))
		{
			timeout = 0;
			sysflag.bits.RTCWeak= 0; 
			DeepSleep();
		}
	}
	else 
	{
		sysflag.bits.RTCWeak= 0; 
		timeout = 0;
	}

}
		




