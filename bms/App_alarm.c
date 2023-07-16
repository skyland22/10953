#include "main.h"

ALARM    O_V;
ALARM    O_TV;
ALARM   U_TV;

ALARM    O_V_3750;
ALARM    U_V_2700;
ALARM    U_V_2300;
ALARM    U_V_1500;
ALARM    O_T_M;
ALARM    O_T_C;
ALARM    O_T_D;
ALARM    U_T_C;
ALARM    U_T_D;
ALARM    C_M_E;
ALARM    D_M_E;
ALARM    C_O_C;
ALARM    D_O_C;
ALARM    D_O_C2;
ALARM    S_C_D;

AlarmSt userAlarm;
AlarmSt shAlarm;

void AlarmFilter( int32_t Value,
					 int32_t AlarmValue,
					 int32_t RecoverValue,
					 COMPARE  CompareType,
					 ALARM*  Buff,
					 uint8_t  Timeout,
					 uint8_t  ReTimeout
					 )
{
    
	if( CompareType == LESS )
	{
		if( Value <= AlarmValue )
		{
			Buff->Times++;
			Buff->ReTimes = 0;
		}
		else if((Value > RecoverValue )&&(0 != RecoverValue))
		{
			Buff->ReTimes++;
			Buff->Times = 0;
		}
		else
		{
			Buff->Times = 0;
			Buff->ReTimes = 0;
		}
	}
	else if( CompareType == MORE )
	{
		if( Value >= AlarmValue )
		{
			Buff->Times++;
			Buff->ReTimes = 0;
		}
		else if((Value < RecoverValue )&&(0 != RecoverValue))
		{
			Buff->ReTimes++;
			Buff->Times = 0;
		}
		else
		{
			Buff->Times = 0;
			Buff->ReTimes = 0;
		}
	}
	if( Buff->Times > Timeout )
	{
		Buff->alarmFlag = 1;
		Buff->Times = Timeout + 10;
	}
	if( Buff->ReTimes > ReTimeout )
	{
		Buff->alarmFlag = 0;
		Buff->ReTimes= ReTimeout + 10;
	}
}

void CHGDSG_MOS_CheckOK(void)
{
	//充放电MOS损坏检测
	if((syspara.chgMos == 0)&&(syspara.current>=CFG_ST_CME))
	{
		C_M_E.Times++;
		if(C_M_E.Times>TimeOut(2))
		{
			C_M_E.Times = TimeOut(2)+2;
			C_M_E.alarmFlag = 1;
		}
	}
	else 
	{
		C_M_E.Times = 0;
		C_M_E.alarmFlag = 0;
	}
	
	if((syspara.dsgMos == 0)&&(syspara.current<=(0-CFG_ST_DME)))
	{
		D_M_E.Times++;
		if(D_M_E.Times>TimeOut(2))
		{
			D_M_E.Times = TimeOut(2)+2;
			D_M_E.alarmFlag = 1;
		}
	}
	else 
	{
		D_M_E.Times = 0;
		D_M_E.alarmFlag = 0;
	}
}

void AlarmCheck(void)
{
	
	SH_Read_Alarm();

	//过压欠压报警
	

#if(USE_CHG_BAOXIAN==1)
	if(syspara.voltMax<5000)
	{
		AlarmFilter(syspara.voltMax, (CFG_ST_OV+100), CFG_ST_OVR, MORE, &(O_V_3750), TimeOut(4),TimeOut(1));
	}
#endif
	AlarmFilter(syspara.voltMax, CFG_ST_OV, CFG_ST_OVR, MORE, &(O_V), TimeOut(CFG_OV_T),TimeOut(1));
	AlarmFilter(syspara.totalSumVolt, CFG_ST_OTV, CFG_ST_OTVR, MORE, &(O_TV), TimeOut(CFG_OV_T),TimeOut(1));
	AlarmFilter(syspara.voltMin, CFG_ST_UV, CFG_S0f_UVR, LESS, &(U_V_2300), TimeOut(CFG_UV_T),TimeOut(1));
	AlarmFilter(syspara.voltMin, CFG_ST_UV3, CFG_S0f_UVR, LESS, &(U_V_1500), TimeOut(CFG_UV_T),TimeOut(1));

	AlarmFilter(syspara.totalSumVolt, 32500, 34000, LESS, &(U_TV), TimeOut(2),TimeOut(1));
	//MOS 高温报警
	AlarmFilter(syspara.mosTemp, CFG_ST_OTM, CFG_ST_OTMR, MORE, &(O_T_M), TimeOut(2),TimeOut(1));
	//充电低温
	AlarmFilter(syspara.tempMin, (Def_Sof_UTC+TEMP_OFFSET), (Def_Sof_UTCR+TEMP_OFFSET), LESS, &(U_T_C), TimeOut(2),TimeOut(1));
	//充电高温
	AlarmFilter(syspara.tempMax, (Def_SH_OTC+TEMP_OFFSET), (Def_SH_OTCR+TEMP_OFFSET), MORE, &(O_T_C), TimeOut(2),TimeOut(1));
	//放电低温
	AlarmFilter(syspara.tempMin, (Def_Sof_UTD+TEMP_OFFSET), (Def_Sof_UTDR+TEMP_OFFSET), LESS, &(U_T_D), TimeOut(2),TimeOut(1));
	//放电高温
	AlarmFilter(syspara.tempMax, (Def_SH_OTD+TEMP_OFFSET), (Def_SH_OTDR+TEMP_OFFSET), MORE, &(O_T_D), TimeOut(2),TimeOut(1));

	if(O_T_C.alarmFlag==1)
	{
		syspara.ChgStatus.bits.temperature=0x10;
	}
	else if(U_T_C.alarmFlag==1)
	{
		syspara.ChgStatus.bits.temperature=1;
	}
 	else if(syspara.tempMax>=(45+TEMP_OFFSET))
	{
		syspara.ChgStatus.bits.temperature=8;
	}
 	else if(syspara.tempMin<=(10+TEMP_OFFSET))
	{
		syspara.ChgStatus.bits.temperature=2;
	}
	else
	{
		syspara.ChgStatus.bits.temperature=4;
	}
	
	

	AlarmFilter(abs(syspara.current), 600000, 1000, MORE, &(C_O_C), TimeOut(2),TimeOut(3));
	AlarmFilter(abs(syspara.current), 600000, 1000, MORE, &(D_O_C), TimeOut(2),TimeOut(3));

	U_V_2300.alarmFlag|= shAlarm.bits.U_V;
#if(USE_CHG_BAOXIAN==1)
	if(O_V_3750.alarmFlag==1)
	{
		BAOXIAN(1);
	}
	else
	{
		BAOXIAN(0);
	}
#endif
	CHGDSG_MOS_CheckOK();

	//这里因为没有RTC所以暂时注释起来了NowTime=GT_GET_RTC();

	userAlarm.bytes=shAlarm.bytes;


	userAlarm.bits.O_V |= O_V.alarmFlag|O_TV.alarmFlag;
	userAlarm.bits.U_V |= U_V_2700.alarmFlag|U_V_1500.alarmFlag|U_V_2300.alarmFlag;
	userAlarm.bits.O_T_M |= O_T_M.alarmFlag;
	userAlarm.bits.C_M_E |= C_M_E.alarmFlag;
	userAlarm.bits.D_M_E |= D_M_E.alarmFlag;
	userAlarm.bits.U_T_D |= U_T_D.alarmFlag;
	userAlarm.bits.U_T_C |= U_T_C.alarmFlag;
	userAlarm.bits.O_T_D |= O_T_D.alarmFlag;
	userAlarm.bits.O_T_C |= O_T_C.alarmFlag;
	//userAlarm.bits.S_C_D |= S_C_D.alarmFlag;
	//userAlarm.bits.O_C_C |= C_O_C.alarmFlag;
	C_O_C.alarmFlag= userAlarm.bits.O_C_C;
	D_O_C.alarmFlag= userAlarm.bits.O_C_D;
	//userAlarm.bits.O_C_D |= D_O_C.alarmFlag|D_O_C2.alarmFlag;

	syspara.batteryStatus.bits.OCA=userAlarm.bits.O_V;
#ifdef DBG_Printf_ALARM
	RS485_RxDen;
	printf("Alarm: %x  %x\r\n",userAlarm.bytes  ,shAlarm.bytes);
	LL_mDelay(2);
	RS485_RxEn;
#endif
}




