#ifndef __BMS_H
#define __BMS_H   
#include "main.h"

#define   NotBit(x,y)         ((x)^=(1<<(y)))
#define   SetBit(x,y)         ((x) |= (1<<(y)))
#define   ClrBit(x,y)         ((x) &= ~(1<<(y)))
#define  	GetBit(x,y)     		(((x)>>(y))&(0x01))

#define TimeOut(n) (n*2L)

typedef union
{
	uint16_t bytes;
	struct 	
	{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
		uint8_t bit8:1;
		uint8_t bit9:1;
		uint8_t bit10:1;
		uint8_t bit11:1;
		uint8_t bit12:1;
		uint8_t bit13:1;
		uint8_t bit14:1;
		uint8_t bit15:1;
	}bits;
}S16_BITS;

typedef union
{
	uint16_t halfword;
	struct 	
	{
		uint8_t byte_l:8;
		uint8_t byte_h:8;
	}bytes;
}S_HALFWORD;

typedef union
{
	int16_t shalfword;
	struct 	
	{
		int8_t byte_l:8;
		int8_t byte_h:8;
	}bytes;
}S_SHALFWORD;

typedef union
{
	uint32_t word;
	struct 	
	{
		uint8_t byte_1:8;
		uint8_t byte_2:8;
		uint8_t byte_3:8;
		uint8_t byte_4:8;
	}bytes;
	struct 	
	{
		uint16_t Short_1:16;
		uint16_t Short_2:16;
	}u16data;
}S_WORD;

typedef union
{
	int32_t ssword;
	struct 	
	{
		int8_t byte_1:8;
		int8_t byte_2:8;
		int8_t byte_3:8;
		int8_t byte_4:8;
	}bytes;
}S_SWORD;

typedef union
{
	int64_t sdword;
	struct 	
	{
		int8_t byte_1:8;
		int8_t byte_2:8;
		int8_t byte_3:8;
		int8_t byte_4:8;
		int8_t byte_5:8;
		int8_t byte_6:8;
		int8_t byte_7:8;
		int8_t byte_8:8;
	}bytes;
}S_SDWORD;

typedef union
{
	uint64_t dword;
	struct 	
	{
		uint8_t byte_1:8;
		uint8_t byte_2:8;
		uint8_t byte_3:8;
		uint8_t byte_4:8;
		uint8_t byte_5:8;
		uint8_t byte_6:8;
		uint8_t byte_7:8;
		uint8_t byte_8:8;
	}bytes;
}S_DWORD;


typedef union
{
	uint8_t bytes;
	struct 	
	{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
		
	}bits;

}S8_BITS;

typedef union
{
	uint16_t bytes;
	struct 	
	{
		uint16_t temperature:5;
		uint16_t Reserved3:3;

		uint16_t PRE_CHARGE :1;
		uint16_t FAST_CHARGE:1;
		uint16_t Reserved2:2;
		
		uint16_t Charge_Inhibit:1;
		uint16_t Charge_Suspend:1;
		uint16_t Reserved1:1;
		uint16_t Charge_Termination:1;
	}bits;
}CHGStatuesSt;

typedef union
{
	uint16_t bytes;
	struct 	
	{
		uint16_t EC3:4;
		
		uint16_t FullDis:1;		//完全放电标志
		uint16_t FullChg:1;		//充满标志
		uint16_t DsgStatu:1;	
		uint16_t Init:1;

		uint16_t RemanTimeAlarm :1;
		uint16_t RemanCapAlarm:1;
		uint16_t Reserved2:1;
		uint16_t TDA:1;
		
		uint16_t OTA:1;
		uint16_t Reserved1:1;
		uint16_t TCA:1;
		uint16_t OCA:1;
		
	}bits;

}BattStatuesSt;

//系统状态参数
typedef struct 
{
	uint16_t alarmByte;
	uint8_t SOC;
	uint8_t SOH;

	uint8_t setSoc;		//设置
	uint8_t batStat;	//充放电静置状态
	uint32_t OCVCalibrateTimer;		//电池静置状态时间,单位:分钟
	
	uint8_t chgMos;
	uint8_t dsgMos;
	

	int8_t cellTemp[6];
	int8_t tempMax;
	int8_t tempMin;
	int8_t tempAvg;
	
	uint8_t balTemp;
	uint8_t mosTemp;
	uint8_t envTemp;
	
	uint16_t cellVolt[16];
	uint16_t batVolt[16];
	int16_t voltMax;
	int8_t 	voltMaxNum;
	int16_t voltMin;
	int16_t voltAvg;
	int16_t voltDiff;
	
	BattStatuesSt batteryStatus;
	CHGStatuesSt ChgStatus;
	uint16_t 	Period_Integral;	//积分周期ms
	uint16_t  IntegralPower;		//ZHQL_1013
	uint16_t  IntegralPower_C;	//ZHQL_1013

	uint16_t  IntegralPowerjisuan;	
	uint16_t 	totalSumVolt;		//单体累加总压

	uint32_t	FullChargeCap;	/*充满容量*/	
	uint32_t 	RemainCap;			/*积分剩余容量*/
	
//	uint32_t AbsCap;/*绝对容量*/	
	
	uint32_t TotalDsgCap;
	int16_t  current;
	uint16_t CADCDisCHGOffset;
	int8_t CADCCHGOffset;
	int16_t  Avgcurrent;
	int8_t 	 CurrCailFalg;		//电流校准标志
	int8_t 	 DeepSleepCMD;
	int8_t 	 SleepCMD;
	uint8_t  SocChangFlag;
}SysPara;

//系统状态标志
typedef union
{
	uint16_t bytes;
	struct 	
	{
		uint16_t flashSave_Flag:1;
		uint16_t socInit_Flag:1;//初始化条件
		uint16_t CHG_DET:1;
		uint16_t LoadFlag:1;
		
		uint16_t StopSocAdddFlag:1;
		uint16_t StopSocCutFlag:1;
		uint16_t CHGingFlag:1;
		uint16_t DSGingFlag:1;

		uint16_t RTCWeak:1;
		uint16_t CHGWeak:1;
		uint16_t IICWeak:1;
		uint16_t ALARMWeak:1;
		
		//uint16_t RS485Weak:1;
		uint16_t MCUCtrolBal:1;
		uint16_t DETWeak:1;
		uint16_t VoltChargeBigFlag:1;
		uint16_t SysWeakFlag:1;
	}bits;
}SysFlag;


//客户通讯指令
typedef union
{
	uint8_t bytes;
	struct 	
	{
		uint8_t sleepCmd:1;
		uint8_t dsgMosOnCmd:1;
		uint8_t dsgMosOffCmd:1;
		uint8_t chgMosOnCmd:1;
		uint8_t chgMosOffCmd:1;
	}bits;

}CustomCmd;

extern SysFlag sysflag;
extern SysPara syspara;

typedef enum 
{
	LONGOUT = 0X01,
	EXITWAKE = 0X02,
	EXITWAKECMD = 0X03,
	BURNIN = 0XA5,
}workMode;

typedef enum 
{
	UNCOM = 0X01,
	COM = 0X02,
}chgMode ;

void Soft_Delay(uint16_t time);
uint8_t CRC8(uint8_t *ptr,uint8_t len);
uint8_t CRC8CheckTab(uint8_t *ptr,uint8_t len);
int8_t CacMax(int8_t a, int8_t b, int8_t c);
int8_t CacMin(int8_t a, int8_t b, int8_t c);

void Process_100ms_CYC(void);
void Process_500ms_CYC1(void);
int16_t processavgCurr(int16_t value);

#endif









