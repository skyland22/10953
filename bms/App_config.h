#ifndef __CONFIG_H
#define __CONFIG_H

#include "main.h"

/************************Project  Config************************************/

/************************Project  Config End************************************/

#define  CFG_BALANCE_USE 1
#define  JISUAN_DASTVALU  1
#define  TEST_CYC 		0
#define  TEST_MOD_LT 0
#define	 CFG_StartSOC  20

//#define ADD_BOOT_FUN
//boot 版本
//#define BOOTSERVIN  	101
//协议版本
//#define CFG_XIEYI_NUM CFG_XIEYI_12
//电池类型
//#define BATTERY_TYPE	B_YTPE_LiFe


//软件测试版本编号，不使用的时候需要屏蔽掉
//#define TestRWSERVIN  7

//项目编码
#define PROJECTCODE 	YWLN_35V13AH
//充电保险使用标志   0：不使用 1：使用
//#define USE_CHG_BAOXIAN       1


#if(TEST_CYC==0)
		//#define 		CFG_BTAUSEFLAG	 0x007FFFF		//BTA使用标志，未用上
		#define 	 	CFG_DESIGN_CAPACITY 	2600L	 	//电池设计容量
		//#define 	 	CFG_DESIGN_CAPACITY 	1300L	 //电池设计容量
		#define 	 	CFG_CURR_RES	125 //0.00125OΩ	//200 //(417/3)		//电流采样电阻	0.01mΩ
		#define 	 	CFG_Cell_NUM	10		//电池串数
		//#define			CFG_TEMP_NUM 	2		//未用上
		#define 		FACTURECODE 	GTDS_FAC_YWLN		//厂商编码
		#define 		HARDCODE_M		(XIN_G*100+X_C8T6*10+S_SINO)//主机硬件编码	//1 + 00 + 0
		#define 		HARDCODE_S		(0*100+0)				//从机硬件编码0 + 0
		//软件版本
	#ifndef TestRWSERVIN
		//#define RWSERVIN  101
	#else
		#define RWSERVIN  TestRWSERVIN
	#endif

		#define CFG_SHUSENUM  1		//前端芯片个数,未用上

#else
		#define			CFG_DESIGN_CAPACITY 	2	 //电池设计容量
		#define 		CFG_CURR_RES	137 //(417/3)	//电流采样电阻  0.01mΩ
		#define			CFG_Cell_NUM	15
		#define			CFG_TEMP_NUM 2
		#define 		FACTURECODE 	0
		#define 		HARDCODE_M	(XIN_G*100+X_F6P6*10+S_LPS)
		#define 		HARDCODE_S	255
#endif

#ifndef RWSERVIN 
#define RWSERVIN 101
#endif
/************************System Macro************************************/
#define DEF_CAP 	 (CFG_DESIGN_CAPACITY/100L)	//充满容量  
#define DESIGN_CAP 2*2600*3600	//(DEF_CAP*3600*50*100)			

// 
#define  CFG_ST_OCC  		20000
#define  DEF_OCC_TIME		20 //100ms 周期

#define  CFG_ST_ODC  		60000
#define  DEF_ODC_TIME		20 //100ms 周期
#define  CFG_ST_ODC2  	70000
#define  DEF_ODC2_TIME	10 //10ms 周期


//休眠延时
#define DEF_SLEEP_sec   (30)

#define RTC_WAKE_SEC  	300 //RTC唤醒秒数20 // 2  // 




//均衡参数
#define CFG_BalanceOpenDiV  100		//10
#define CFG_BalanceCloseDiV 30		//5
#define CFG_BalanceOpenVol  3900	//3400		//平衡开启电压

#define	CFG_BAL_TMAX	  		(60+40)				/*均衡开启最高电池温度*/

//SOC置满清零参数
#define			CFG_SOC_SET_SV					3600	/*SOC置满最高单体电压(mV)停止积分*/
#define			CFG_SOC_SET_VMAX				5000	/*SOC置满最高单体电压范围高(mV)*/
#define			CFG_SOC_SET_VMIN				4250	/*SOC置满最高单体电压范围低(mV)*/

#define			CFG_SOC_CLEAR_SV				3300	/*SOC清零最低单体电压(mV)停止积分*/
#define			CFG_SOC_CLEAR_VMAX			3400	/*SOC清零最高单体电压范围高(mV)*/
#define			CFG_SOC_CLEAR_VMIN			3350	/*SOC清零最高单体电压范围低(mV)*/

//不同工作模式下的休眠条件--
//外部激活输出模式（0x02）休眠
//外部激活+命令确认模式（0x03）休眠

#define			CFG_SLP_VMAX			3550	/*最高单体电压(mV)*/
#define			CFG_SLP_VMIN			2600	/*最低单体电压(mV)*/
#define			CFG_SLP_C					150		/*充放电电流(mA)*/
#define			CFG_SLP_VMUTANT		200		/*电压突变(mV)*/
#define			DEF_SMALL_NoShow	50//150		//深度休眠最低单体电压--		//疑似最小充放电检测电流
#define			CFG_DSLP_VMIN			2300	/*电压突变(mV)*/

/*************************报警参数值*******************************/


#define		CFG_NOTALLOWCHG_UV		1500  // 低压不允许充电电压阈值
#define 	CFG_ST_OV 		3650
#define 	CFG_ST_OTV 		38800		//单体过充电压
//#define 	CFG_ST_OTV 		42500		//单体过充电压
#define 	CFG_ST_OVR 		3400		//过充恢复电压
#define 	CFG_ST_OTVR 	37500
#define 	CFG_Sof_UV		2500		//单体欠压保护 

//充放电温度设定
#define 	Def_SH_OTC 		(60)
#define 	Def_SH_OTCR		(55)
#define 	Def_SH_UTC		(-30) 
#define 	Def_SH_UTCR		(-25) 

#define 	Def_SH_OTD		(70) 
#define 	Def_SH_OTDR		(65) 
#define 	Def_SH_UTD	 	(-30) 
#define 	Def_SH_UTDR 	(-25)  


#define 	Def_Sof_UTC		(3)
#define 	Def_Sof_UTCR	(8) 
#define 	Def_Sof_UTD		(-19) 
#define 	Def_Sof_UTDR	(-10)



#define 	CFG_UV_T		 		1
#define 	CFG_OV_T				1

#define 	CFG_ST_UV     2500	//过放保护电压
#define 	CFG_ST_UVR    2600	//过放恢复电压
#define 	CFG_S0f_UVR   3000
#define 	CFG_ST_UV3		1500	//禁止充电保护mV

#define 	CFG_ST_OTM		130		//(85+40)MOS高温保护
#define 	CFG_ST_OTMR		115		//(70+40)MOS高温保护恢复

#define 	CFG_ST_CME		500		//充电回路MOS断开后，仍有充电电流＞	
#define 	CFG_ST_DME		500		//fang电回路MOS断开后，仍有充电电流＞	

/************************System Macro End************************************/

void SysParaInit(void);
#endif




