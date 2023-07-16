#include "main.h"

int8_t LONGLineRArr[]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

//电池组电压相关数据
void Update_CellVolt(void)
{
	uint8_t i = 0,k=0;
	uint16_t tmpVolt[16];
	uint16_t max = 0;
	uint16_t min = 5000;
	uint16_t total = 0;
	
	if(RT_EOK == rt_mutex_take(SH_mutex,100))
	{
		SH_Get_CellVolts(tmpVolt);
		rt_mutex_release(SH_mutex);
	}
	

	for( i=0; i<CFG_Cell_NUM; i++ )
	{
		//syspara.batVolt[k]= tmpVolt[i]; 
		syspara.cellVolt[k] = tmpVolt[i];//+flashpara.VoltRate[k];	 

		//rt_kprintf("Cell[%d]:%d mV\r\n",k+1,syspara.cellVolt[k]);
		
		//计算Cell max和min
		if (max < syspara.cellVolt[k])
		{
			max = syspara.cellVolt[k];
			syspara.voltMaxNum= i;
		}
		if (syspara.cellVolt[k] < min)
		{
			min = syspara.cellVolt[k];
		}
			total += syspara.cellVolt[k];
			k++;
	}
	syspara.totalSumVolt = total;
	syspara.voltMax = max;
	syspara.voltMin = min;
	syspara.voltDiff = max-min;
	if(k>0)	syspara.voltAvg = syspara.totalSumVolt/k;
	
#if(DEBUG_VOL)
	rt_kprintf("%d.%03d ",syspara.totalSumVolt/1000,syspara.totalSumVolt%1000);
#endif 
}

void battstatusProcess(void)
{
		static uint16_t maxVol_value= 0;
		static uint16_t minVol_value= 0;
		static uint8_t VoltChargeBigTime= 0;
		if((abs(maxVol_value-syspara.voltMax)>200)||(abs(minVol_value-syspara.voltMin)>200))
		{
				sysflag.bits.VoltChargeBigFlag=1;
				if(VoltChargeBigTime<TimeOut(5))
				{
						VoltChargeBigTime++;
				}
				else
				{
					maxVol_value=syspara.voltMax;
					minVol_value=syspara.voltMin;
					VoltChargeBigTime= 0;
				}
		}
		else
		{
				sysflag.bits.VoltChargeBigFlag=0;
				VoltChargeBigTime=0;
				maxVol_value=syspara.voltMax;
				minVol_value=syspara.voltMin;
		}
}


#define  DEF_BALANCE_Mask1 0x9249
#define  DEF_BALANCE_Mask2 0x2492
#define  DEF_BALANCE_Mask3 0x4924

//1.	充电状态；
//2.	电压最低的电芯电压≥3.05V；
//3.	电芯电压＞平均电压+10mV；
//4.	最高电池温度＜60℃。
uint8_t EstimateBalance(uint16_t* bFlag)
{
	//先读取均衡寄存器状态
//	u8 BalReg[2]={0};
//	SH367309_ReadRegVal(REG_BALANCEH,BalReg,2);
//	u16 cellBalState=(BalReg[0]<<8)&BalReg[1];

	uint8_t openBal = 0;
	uint8_t cellVoltMoreFlag = 0;
	uint16_t tmpMask = 0;
	static uint8_t BalanceAllow= 0;
	
	//压差判断
	if(abs( syspara.voltMax- syspara.voltMin ) >= CFG_BalanceOpenDiV) BalanceAllow = 1;
	else if(abs( syspara.voltMax - syspara.voltMin ) <CFG_BalanceCloseDiV ) BalanceAllow = 0;
	if(abs( syspara.voltMax - syspara.voltMin ) >= 1000 ) BalanceAllow = 0;

	//确定需要均衡的电芯位置
	for(u8 i=0;i<CFG_Cell_NUM;i++)
	{
		if((syspara.cellVolt[i] > CFG_BalanceOpenVol)&&(syspara.cellVolt[i] > syspara.voltAvg))
		{
			cellVoltMoreFlag = 1;
			SetBit(tmpMask,i);
		}			
	}
	*bFlag = tmpMask;

	//充电状态  温度小于均衡温度
	if((( syspara.batStat == STATE_CHG )/*||((sysflag.bits.CHG_DET == 1)&&(syspara.chgMos==0))*/)
		&&(syspara.tempMax < CFG_BAL_TMAX)
		&&(cellVoltMoreFlag==1)
		&&(BalanceAllow == 1))
	{
		openBal = 1;
	}

#ifdef DEBUG_Balance
	rt_kprintf("Balance %x %d  %d %d %d %d\r\n",*bFlag,openBal,syspara.batStat,syspara.tempMax,cellVoltMoreFlag,BalanceAllow);
#endif

	return openBal;
}


//均衡控制
void BalanceMCUCtrl( void )
{
	u16 balBitSet = 0;
	if(EstimateBalance(&balBitSet))
	{
		SH_Set_Balance((uint16_t)(balBitSet&0xffff));
	}
	else 
	{
		SH_Set_Balance(0);
	}
}

