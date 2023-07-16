#include "APP_bms.h"

SysPara syspara;
SysFlag sysflag;

static const uint8_t CRC8Table[]=
{							//120424-1			CRC Table
	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
	0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
	0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
	0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
	0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
	0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
	0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
	0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
	0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
	0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
	0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
	0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
	0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
	0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
	0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
	0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
};


void Soft_Delay(uint16_t time)
{
	uint16_t t=time*20;  
	while(t>0)
	{
		t--;
	}
}

//直接计算CRC8
uint8_t CRC8(uint8_t *ptr,uint8_t len)
{
	uint8_t crc = 0;
	uint8_t i = 0;
	while(len--)
	{
		 crc ^= *ptr++;
		 for(i = 0;i < 8;i++)
		 {
				 if(crc & 0x80)
				 {
						 crc = (crc << 1) ^ 0x07;	//x^8+x^2+x+1=100000111=(最高位不需要异或，直接去掉)=0x07
				 }
				 else crc <<= 1;
		 }
	}
	return crc;
}

//查表法计算CRC8，计算量小
uint8_t CRC8CheckTab(uint8_t *ptr, uint8_t len)    		    
{    
  uint8_t crc8 = 0;    
	for( ; len > 0; len--)
	{    
		crc8 = CRC8Table[crc8^*ptr];    
	  ptr++;    
  }    
  return(crc8);    
}

int8_t CacMax(int8_t a, int8_t b, int8_t c)
{
	int8_t max = a>b?a:b;
	return max>c?max:c;
}

int8_t CacMin(int8_t a, int8_t b, int8_t c)
{
	int8_t min = a<b?a:b;
	return min<c?min:c;
}


uint8_t avg20currcount= 0;
uint8_t avg30currcount= 0;
int32_t Temp20curr[10]={0};
int32_t Temp30curr[60]={0};
int32_t avgcurr30add= 0;
int32_t avgcurr20add= 0;
//#define  Def_AvgNum 600


int16_t processavgCurr(int16_t value)
{
	uint8_t i=0;
	Temp20curr[avg20currcount%20]= value;
	avg20currcount++;
	if(avg20currcount>=10)
	{
		avgcurr20add= 0;
		for(i= 0;i<10;i++)
		{
				avgcurr20add +=Temp20curr[i];
		}
		avg20currcount= 0;
		Temp30curr[avg30currcount%60]= avgcurr20add;
		avg30currcount++;
		if((abs(avgcurr20add))<20)
		{
			avg30currcount= 0;
		}
	}
	if(avg30currcount>=60)
	{
		avgcurr30add= 0;
		for(i= 0;i<60;i++)
		{
				avgcurr30add +=Temp30curr[i];
		}
		avg30currcount= 60+avg30currcount%60;
		return avgcurr30add/600;
	}
	else
	{
		avgcurr30add= 0;
		for(i= 0;i<avg30currcount;i++)
		{
				avgcurr30add +=Temp30curr[i];
		}
		if(avg30currcount>0)
		{
			return avgcurr30add/(avg30currcount*10);
		}
		else
		return 0;
	}
}

/******
	* 100ms周期任务
	* 电流采集、充放电积分相关
******/
void Process_100ms_CYC(void)
{
	//static uint32_t currperiodtime= 0;		//静态局部变量，与全局变量共享全局数据区
	
	syspara.current = Update_Current();
	syspara.Avgcurrent= processavgCurr(syspara.current);
	
	//DBG_PRINTF("Actual Current = %d\r\n",syspara.current);
	//DBG_PRINTF("Average Current = %d\r\n",syspara.Avgcurrent);
	//printf("当前平均电流=%d mA\r\n",syspara.Avgcurrent);
	
	if(syspara.CurrCailFalg==0x55)
	{
		syspara.CurrCailFalg= 0;
		flashpara.currentRate=GetClibrationDiff_Current();
		//Flash_WritePara();
	}
	//电流状态判断
	//syspara.batStat = CurrentStateDetect(syspara.current);
	syspara.batStat=SH_Get_ChgSta();
	
#ifdef DBG_Printf_CURR
	printf("Curr  %c = %d %d %d\r\n",syspara.batStat,syspara.current,syspara.Period_Integral);
#endif

	//根据电流状态选择充电或者放电积分系数
	if(syspara.batStat==STATE_DSG)	//放电状态
	{
		//printf("AA");
		//DBG_PRINTF("STATE_DSG\r\n");
		printf("   【电池放电状态】|电流：%dmA\r\n",SH_Get_CADCCurrent());
		syspara.IntegralPowerjisuan=(syspara.IntegralPower*104L/100);
	}
	else if(syspara.batStat==STATE_CHG)	//充电状态
	{
		//DBG_PRINTF("STATE_CHG\r\n");
		printf("   【电池充电状态】|电流：%dmA\r\n",SH_Get_CADCCurrent());
		syspara.IntegralPowerjisuan=syspara.IntegralPower_C;
	}
	else	//静置
	{
		//DBG_PRINTF("STATE_STATIC\r\n");
		//printf("   【电池静置状态】\r\n");
		printf("   【电池静置状态】|电流：%dmA\r\n",SH_Get_CADCCurrent());
		syspara.IntegralPowerjisuan=1050;
	}
	//SOC积分
	//syspara.Period_Integral =  abs(systickCount- currperiodtime);		//systickCount为毫秒
	//currperiodtime= systickCount;
	//RemainCap_Integral(syspara.current,syspara.Period_Integral,syspara.IntegralPowerjisuan);	//ZHQL1013  
	Cycle_Integral(syspara.current,syspara.Period_Integral);	//循环次数，充放电次数
}



void Process_500ms_CYC1(void)
{
	uint32_t testtime[8]={0}; 
	//电压
	//testtime[0]=systickCount;
	SH_Get_CellTemps();
	Update_CellVolt();
	//testtime[1]=systickCount;
	
	//BalanceCtrl();	//均衡控制
	//testtime[2]=systickCount;
//	Update_CellTemps();		//温度
	//testtime[3]=systickCount;

	//AlarmCheck();	//报警判断
	//testtime[4]=systickCount;
	
	//MOS_Ctrl();	//MOS控制获取

	//Soc_Init();		//初始化电压对应一个初始SOC值
	//testtime[5]=systickCount;
	
	//RealRemainCap_Calibration();		//SOC 校准系数计算
	//testtime[6]=systickCount;
	
	//SOC 值
	syspara.SOC = Get_Percent(syspara.RemainCap,syspara.FullChargeCap);
	rt_kprintf("SOC = %d%%\r\n",syspara.SOC);
	//SOH 值
	syspara.SOH = Get_Percent(syspara.FullChargeCap,DESIGN_CAP);
	//SOC 清零置满
	//Soc_ClrOrSetCtrl();
	//深度休眠
	//DeepSleepCheck();
	//休眠
	//SleepCheck();	
	//IIC 数据处理
	//SMBUS_DataProcess();
	//printf("Process_500ms_CYC1 %d %d %d %d %d %d %d \r\n",testtime[0],testtime[1],testtime[2],testtime[3],testtime[4],testtime[5],testtime[6]);
}



