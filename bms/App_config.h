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
//boot �汾
//#define BOOTSERVIN  	101
//Э��汾
//#define CFG_XIEYI_NUM CFG_XIEYI_12
//�������
//#define BATTERY_TYPE	B_YTPE_LiFe


//������԰汾��ţ���ʹ�õ�ʱ����Ҫ���ε�
//#define TestRWSERVIN  7

//��Ŀ����
#define PROJECTCODE 	YWLN_35V13AH
//��籣��ʹ�ñ�־   0����ʹ�� 1��ʹ��
//#define USE_CHG_BAOXIAN       1


#if(TEST_CYC==0)
		//#define 		CFG_BTAUSEFLAG	 0x007FFFF		//BTAʹ�ñ�־��δ����
		#define 	 	CFG_DESIGN_CAPACITY 	2600L	 	//����������
		//#define 	 	CFG_DESIGN_CAPACITY 	1300L	 //����������
		#define 	 	CFG_CURR_RES	125 //0.00125O��	//200 //(417/3)		//������������	0.01m��
		#define 	 	CFG_Cell_NUM	10		//��ش���
		//#define			CFG_TEMP_NUM 	2		//δ����
		#define 		FACTURECODE 	GTDS_FAC_YWLN		//���̱���
		#define 		HARDCODE_M		(XIN_G*100+X_C8T6*10+S_SINO)//����Ӳ������	//1 + 00 + 0
		#define 		HARDCODE_S		(0*100+0)				//�ӻ�Ӳ������0 + 0
		//����汾
	#ifndef TestRWSERVIN
		//#define RWSERVIN  101
	#else
		#define RWSERVIN  TestRWSERVIN
	#endif

		#define CFG_SHUSENUM  1		//ǰ��оƬ����,δ����

#else
		#define			CFG_DESIGN_CAPACITY 	2	 //����������
		#define 		CFG_CURR_RES	137 //(417/3)	//������������  0.01m��
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
#define DEF_CAP 	 (CFG_DESIGN_CAPACITY/100L)	//��������  
#define DESIGN_CAP 2*2600*3600	//(DEF_CAP*3600*50*100)			

// 
#define  CFG_ST_OCC  		20000
#define  DEF_OCC_TIME		20 //100ms ����

#define  CFG_ST_ODC  		60000
#define  DEF_ODC_TIME		20 //100ms ����
#define  CFG_ST_ODC2  	70000
#define  DEF_ODC2_TIME	10 //10ms ����


//������ʱ
#define DEF_SLEEP_sec   (30)

#define RTC_WAKE_SEC  	300 //RTC��������20 // 2  // 




//�������
#define CFG_BalanceOpenDiV  100		//10
#define CFG_BalanceCloseDiV 30		//5
#define CFG_BalanceOpenVol  3900	//3400		//ƽ�⿪����ѹ

#define	CFG_BAL_TMAX	  		(60+40)				/*���⿪����ߵ���¶�*/

//SOC�����������
#define			CFG_SOC_SET_SV					3600	/*SOC������ߵ����ѹ(mV)ֹͣ����*/
#define			CFG_SOC_SET_VMAX				5000	/*SOC������ߵ����ѹ��Χ��(mV)*/
#define			CFG_SOC_SET_VMIN				4250	/*SOC������ߵ����ѹ��Χ��(mV)*/

#define			CFG_SOC_CLEAR_SV				3300	/*SOC������͵����ѹ(mV)ֹͣ����*/
#define			CFG_SOC_CLEAR_VMAX			3400	/*SOC������ߵ����ѹ��Χ��(mV)*/
#define			CFG_SOC_CLEAR_VMIN			3350	/*SOC������ߵ����ѹ��Χ��(mV)*/

//��ͬ����ģʽ�µ���������--
//�ⲿ�������ģʽ��0x02������
//�ⲿ����+����ȷ��ģʽ��0x03������

#define			CFG_SLP_VMAX			3550	/*��ߵ����ѹ(mV)*/
#define			CFG_SLP_VMIN			2600	/*��͵����ѹ(mV)*/
#define			CFG_SLP_C					150		/*��ŵ����(mA)*/
#define			CFG_SLP_VMUTANT		200		/*��ѹͻ��(mV)*/
#define			DEF_SMALL_NoShow	50//150		//���������͵����ѹ--		//������С��ŵ������
#define			CFG_DSLP_VMIN			2300	/*��ѹͻ��(mV)*/

/*************************��������ֵ*******************************/


#define		CFG_NOTALLOWCHG_UV		1500  // ��ѹ���������ѹ��ֵ
#define 	CFG_ST_OV 		3650
#define 	CFG_ST_OTV 		38800		//��������ѹ
//#define 	CFG_ST_OTV 		42500		//��������ѹ
#define 	CFG_ST_OVR 		3400		//����ָ���ѹ
#define 	CFG_ST_OTVR 	37500
#define 	CFG_Sof_UV		2500		//����Ƿѹ���� 

//��ŵ��¶��趨
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

#define 	CFG_ST_UV     2500	//���ű�����ѹ
#define 	CFG_ST_UVR    2600	//���Żָ���ѹ
#define 	CFG_S0f_UVR   3000
#define 	CFG_ST_UV3		1500	//��ֹ��籣��mV

#define 	CFG_ST_OTM		130		//(85+40)MOS���±���
#define 	CFG_ST_OTMR		115		//(70+40)MOS���±����ָ�

#define 	CFG_ST_CME		500		//����·MOS�Ͽ������г�������	
#define 	CFG_ST_DME		500		//fang���·MOS�Ͽ������г�������	

/************************System Macro End************************************/

void SysParaInit(void);
#endif




