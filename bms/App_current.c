#include "main.h"

//实际电流
uint16_t Update_Current(void)
{	  
	uint16_t 	CurrentValue = 0;
	//CurrentValue = SH_Get_Current();
	CurrentValue = SH_Get_CADCCurrent();
	//CurrentValue =(int32_t)(CurrentValue+flashpara.currentRate);
	if((abs(CurrentValue))<=50)
	{
		CurrentValue= 0;
	}
	return 	CurrentValue;
}

//电流标定 校准差异补偿值
int16_t GetClibrationDiff_Current(void)
{
	int16_t offset = 0;
	//CurrentValue = SH_Get_Current();
	offset=SH_Get_CADCCurrent();
	return (int16_t)(offset);
}

uint8_t SH_Get_ChgSta()
{
	uint8_t CHGsta = 0;
	uint8_t DSGsta = 0;
	uint8_t CurrentStaReg=0;
	
	SH367309_ReadRegVal(REG_BSTATUS3,&CurrentStaReg,1);
	
	CHGsta=GetBit(CurrentStaReg,7);
	DSGsta=GetBit(CurrentStaReg,6);
	
	if(CHGsta) return STATE_CHG;
	else if(DSGsta) return STATE_DSG;
	else return STATE_STATIC;
	
}

//检测电池充放电状态
uint8_t  CurrentStateDetect( int32_t val )
{
	static uint16_t chgTime= 0;
	static uint16_t dsgTime= 0;
	static uint16_t SticTime= 0;
	static uint8_t sta = 0;
	
	if(val < (0-DEF_SMALL_NoShow)) //放电状态
	{
		chgTime = 0;
		dsgTime++;
		SticTime	=0;
		if(dsgTime > 1)
		{
			dsgTime = TimeOut(2)+2;
			syspara.IntegralPower_C= 1000;
			sta = STATE_DSG;		
		}	
	}
	else 	if(val > DEF_SMALL_NoShow) //充电状态
	{
		chgTime++;
		dsgTime = 0;
		SticTime	=0;
		if(chgTime > 1)
		{
			chgTime = TimeOut(2)+2;
			syspara.IntegralPower = 1050;
			sta = STATE_CHG;			
		}	
	}
	else	//静置状态
	{
		chgTime = 0;
		dsgTime = 0;
		SticTime++;
		if((abs(syspara.current ))<DEF_SMALL_NoShow)
		{
			syspara.current = 0;
		}
		if(SticTime > 1)
		{
			SticTime = TimeOut(2)+2;
			sta = STATE_STATIC;
		}
	}
	return sta;
}

//ZHQL_1013
#if 0
void CurrAlarmProcess(void)
{
	uint8_t  AlarmCount= 0;

	//电流报警判断 此处电流报警不恢复，在报警文件里统一恢复
	if(syspara.batStat==STATE_CHG)
	{
		AlarmFilter(abs(syspara.current),CFG_ST_OCC,0,MORE,&C_O_C,DEF_OCC_TIME,100);
	}
	else
	{
		C_O_C.Times= 0;
	}
#if 1
	if(syspara.batStat==STATE_DSG)
	{
		AlarmFilter(abs(syspara.current),CFG_ST_ODC,0,MORE,&D_O_C,DEF_ODC_TIME,100);
	}
	else
	{
		D_O_C.Times= 0;
	}
	//放电过流2级
	while(((abs(syspara.current ))>=CFG_ST_ODC2)&&(D_O_C2.alarmFlag==0)&&(AlarmCount<20)&&(syspara.batStat==STATE_DSG))
	{
		//电流采集
		syspara.current = Update_Current();
		//电流状态判断
		syspara.batStat = CurrentStateDetect(syspara.current);	
		AlarmFilter(abs(syspara.current),CFG_ST_ODC2,0,MORE,&D_O_C2,DEF_ODC2_TIME,200);
		LL_mDelay(10);
		AlarmCount++;
	}
	D_O_C2.Times=0;
#endif
}

void DCAlarm_RProcess()
{

	static uint32_t R_ODC_T= 0;

#ifdef DBG_Printf_ALARM
	printf("DCAlarm_RProcess: %x %d\r\n",sysflag.bits.LoadFlag,R_ODC_T);
#endif	

	if((syspara.dsgMos==0)&&(syspara.chgMos==0))
	{
		if((D_O_C.alarmFlag==1)||(D_O_C2.alarmFlag==1)||(S_C_D.alarmFlag==1))
		{
			SH_LOAD_CHECK(1);
		}
		else
		{
			SH_LOAD_CHECK(0);
			R_ODC_T= 0;
		}
		if(sysflag.bits.LoadFlag==0)
		{
			if(R_ODC_T<2)
			{
				R_ODC_T++;
			}
			else
			{
				D_O_C.alarmFlag= 0;
				D_O_C.Times= 0;
				D_O_C2.alarmFlag= 0;
				D_O_C2.Times= 0;
				S_C_D.alarmFlag= 0;
				S_C_D.Times= 0;
				SH_ClrAlarm();
				sysflag.bits.LoadFlag=1;
			}
		}	
		else
		{
			R_ODC_T= 0;
		}
	}
	else
	{
		SH_LOAD_CHECK(0);
		R_ODC_T= 0;
	}
}

void CCAlarm_RProcess()
{
	static uint32_t R_OCC_T= 0;

#ifdef DBG_Printf_ALARM
	printf("CCAlarm_RProcess: %x %d\r\n",sysflag.bits.LoadFlag,R_OCC_T);
#endif	
	if((syspara.dsgMos==0)&&(syspara.chgMos==0))
	{
		if(C_O_C.alarmFlag==1)
		{
			SH_CHGR_CHECK(1);
		}
		else
		{
			SH_CHGR_CHECK(0);
		}
		if(sysflag.bits.CHG_DET==0)
		{
			if(R_OCC_T<2)
			{
				R_OCC_T++;
			}
			else
			{
				C_O_C.alarmFlag= 0;
				C_O_C.Times= 0;
				sysflag.bits.CHG_DET= 1;
			}
		}
		else
		{
			R_OCC_T= 0;
		}
	}
	else
	{
		SH_CHGR_CHECK(0);
		R_OCC_T= 0;
	}
}
#endif

