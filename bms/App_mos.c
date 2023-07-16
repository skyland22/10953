#include "main.h"
uint8_t	Ctrl_CH_FET= 0;
uint8_t	Ctrl_DS_FET= 0;

void LED_Ctrl(void)
{

	static uint8_t  ledVlaue= 0;
	S16_BITS LED_ROffFlag;
	//绿灯
	if(syspara.batStat == STATE_CHG)
	{
		if((sysflag.bits.CHG_DET==1)&&(userAlarm.bits.O_V==1)&&(syspara.SOC>=100))
		{
			ledVlaue= 0;
		}
		else
		{
			ledVlaue= !ledVlaue;
		}
		
		LED_G(ledVlaue);
	}
	else
	{
		if(syspara.batStat == STATE_DSG)
		{
			LED_G(1);
		}
		else
		{
			LED_G(0);
		}

	}
	//红灯

	LED_ROffFlag.bytes = 0;
	LED_ROffFlag.bits.bit0=U_TV.alarmFlag;
	LED_ROffFlag.bits.bit1=U_T_C.alarmFlag;
	LED_ROffFlag.bits.bit2=O_T_C.alarmFlag;
	LED_ROffFlag.bits.bit3=U_T_D.alarmFlag;
	LED_ROffFlag.bits.bit4=O_T_D.alarmFlag;
	LED_ROffFlag.bits.bit5=userAlarm.bits.O_C_D;
	LED_ROffFlag.bits.bit6=userAlarm.bits.O_C_C;
	if(LED_ROffFlag.bytes!=0)
	{
		LED_R(1);
	}
	else
	{
		LED_R(0);
	}
#ifdef DBG_Printf_MOS
	RS485_RxDen;
	printf("LED_R: %4x # ",LED_ROffFlag.bytes);
	LL_mDelay(2);
	RS485_RxEn;
#endif	
}

void MOS_Ctrl(void)
{
	S16_BITS dsgMosOffFlag;
	S16_BITS chgMosOffFlag;
	static uint8_t DSG_OpenDelay = 0;
	static uint8_t CHG_OpenDelay = 0;
//	static uint8_t CHG_time = 0;
//	static uint8_t DSG_time = 0;
	static uint16_t CHG_SmallCurr_time = 0;
	
	dsgMosOffFlag.bytes = 0;
	dsgMosOffFlag.bits.bit0 = userAlarm.bits.U_V;
	dsgMosOffFlag.bits.bit1 = userAlarm.bits.U_T_D;
	dsgMosOffFlag.bits.bit3 = userAlarm.bits.O_T_D;
	dsgMosOffFlag.bits.bit4 = userAlarm.bits.O_T_M;
	dsgMosOffFlag.bits.bit5 = D_O_C.alarmFlag;
	dsgMosOffFlag.bits.bit6 = D_O_C2.alarmFlag;
	dsgMosOffFlag.bits.bit7 = S_C_D.alarmFlag;
	dsgMosOffFlag.bits.bit8 = C_O_C.alarmFlag;
	dsgMosOffFlag.bits.bit9 = (sysflag.bits.LoadFlag==0)?1:0;
	
	sysflag.bits.LoadFlag= SING_DSG_DET;

	if(dsgMosOffFlag.bytes) 	
	{
		syspara.IntegralPower=1050;
		Ctrl_DS_FET= 0;
	}
	else 
	{
		if((((syspara.voltMin>2500)
				&&(syspara.tempMax<(Def_SH_OTD+TEMP_OFFSET))
				&&(syspara.tempMin>(Def_SH_UTD+TEMP_OFFSET))))
		&&(sysflag.bits.LoadFlag==1))
		{
			Ctrl_DS_FET=1;
		}
		else
		{
			//不进行操作
		}
	}
#ifdef DBG_Printf_MOS
	RS485_RxDen;
	printf("DSG_Ctrl: %4x %3d  %3d %3d # ",dsgMosOffFlag.bytes,Ctrl_DS_FET,sysflag.bits.LoadFlag,syspara.dsgMos);
	LL_mDelay(2);
	RS485_RxEn;
#endif	
	//CHG
	chgMosOffFlag.bytes = 0;
	chgMosOffFlag.bits.bit0 = userAlarm.bits.O_V;
	chgMosOffFlag.bits.bit1 = userAlarm.bits.U_T_C;
	chgMosOffFlag.bits.bit3 = userAlarm.bits.O_T_C;
	chgMosOffFlag.bits.bit4 = userAlarm.bits.O_T_M;
	chgMosOffFlag.bits.bit5 = C_O_C.alarmFlag;
	chgMosOffFlag.bits.bit9 = U_V_1500.alarmFlag;
	chgMosOffFlag.bits.bit10 = (syspara.voltMin<=1500)?1:0;
	
	
	if((sysflag.bits.CHG_DET==0)&&(abs(syspara.current<300)))
	{
		if(CHG_SmallCurr_time<30000)
		CHG_SmallCurr_time++;
	}
	else
	{
		CHG_SmallCurr_time= 0;
	}
	chgMosOffFlag.bits.bit11 = (CHG_SmallCurr_time>=TimeOut(120))?1:0;//长时间(1分钟)没有充电电流(小于0.3A)则关闭充电

	
	if(chgMosOffFlag.bytes)
	{
		CHG_OpenDelay= 0;
		syspara.IntegralPower_C=1000;
		if(U_V_1500.alarmFlag==1)
		{
			syspara.ChgStatus.bits.Charge_Inhibit=1;
		}
		else
		{
			
			syspara.ChgStatus.bits.Charge_Inhibit= 0;
			if(userAlarm.bits.O_V==1)
			{
				syspara.ChgStatus.bits.Charge_Termination=1;
				syspara.ChgStatus.bits.Charge_Suspend= 0;
			}
			else
			{
				syspara.ChgStatus.bits.Charge_Suspend= 1;
				syspara.ChgStatus.bits.Charge_Termination= 0;
			}
		}
		Ctrl_CH_FET= 0; 	
	}
	else 
	{		
		if(CHG_OpenDelay<1)
		{
			CHG_OpenDelay++;
		}
		else
		{
			if((((syspara.voltMax<CFG_ST_OV)
					&&(syspara.tempMax<(Def_SH_OTC+TEMP_OFFSET))
					&&(syspara.tempMin>(Def_SH_UTC+TEMP_OFFSET))))	
			&&(sysflag.bits.CHG_DET==1))
			{
				Ctrl_CH_FET=1;
			}
		}
	}
	syspara.batteryStatus.bits.TCA=!Ctrl_CH_FET;
	syspara.batteryStatus.bits.TDA=!Ctrl_DS_FET;
	syspara.batteryStatus.bits.OTA=userAlarm.bits.O_T_D;
	if(syspara.SOC<=10)
	{
		syspara.batteryStatus.bits.RemanCapAlarm=1;
	}
	else
	{
		syspara.batteryStatus.bits.RemanCapAlarm=0;
	}

#ifdef DBG_Printf_MOS
	RS485_RxDen;
		printf("CHG_Ctrl: %4x  %3d  %3d  %3d\r\n",chgMosOffFlag.bytes,Ctrl_CH_FET,sysflag.bits.CHG_DET,syspara.chgMos);
	LL_mDelay(2);
	RS485_RxEn;
#endif
	if((syspara.dsgMos!=Ctrl_DS_FET)||(syspara.chgMos!=Ctrl_CH_FET))
	{
		if((Ctrl_DS_FET==1)&&(syspara.dsgMos!=Ctrl_DS_FET))
		{
			if(DSG_OpenDelay<1)
			{
				DSG_OpenDelay++;
				return ;
			}
		}
		SH_MOSCtrl(Ctrl_CH_FET,Ctrl_DS_FET);
	}
	else
	{
		DSG_OpenDelay= 0;
	}


	LED_Ctrl();
}





