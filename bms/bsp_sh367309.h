#ifndef __SH367309_H
#define __SH367309_H

#include "main.h"

//0x04过放电保护延时设置控制位
typedef enum
{
	SH_UVT_100MS    = 0x000,
	SH_UVT_200MS    = 0x001,
	SH_UVT_300MS    = 0x002,
	SH_UVT_400MS    = 0x003,
	SH_UVT_600MS   	= 0x004,
	SH_UVT_800MS   	= 0x005,
	SH_UVT_1S   		= 0x006,
	SH_UVT_2S   		= 0x007,
	SH_UVT_3S   		= 0x008,
	SH_UVT_4S   		= 0x009,
	SH_UVT_6S   		= 0x00a,
	SH_UVT_8S   		= 0x00b,
	SH_UVT_10S   		= 0x00c,
	SH_UVT_20S   		= 0x00d,
	SH_UVT_30S   		= 0x00e,
	SH_UVT_40S   		= 0x00f
} SH_UVT_t;

//0x02过充电保护延时设置控制位
typedef enum
{
    SH_OVT_100MS    = 0x000,
    SH_OVT_200MS    = 0x001,
    SH_OVT_300MS    = 0x002,
    SH_OVT_400MS    = 0x003,
    SH_OVT_600MS   	= 0x004,
    SH_OVT_800MS  	= 0x005,
    SH_OVT_1S   		= 0x006,
    SH_OVT_2S   		= 0x007,
		SH_OVT_3S   		= 0x008,
		SH_OVT_4S   		= 0x009,
		SH_OVT_6S   		= 0x00a,
		SH_OVT_8S   		= 0x00b,
		SH_OVT_10S   		= 0x00c,
		SH_OVT_20S   		= 0x00d,
		SH_OVT_30S   		= 0x00e,
		SH_OVT_40S   		= 0x00f
} SH_OVT_t;

//0x0C放电过流1保护电压设置控制位
typedef enum
{
	SH_OCD1V_20mV    		= 0x000,
	SH_OCD1V_30mV   	 	= 0x001,
	SH_OCD1V_40mV    		= 0x002,
	SH_OCD1V_50mV    		= 0x003,
	SH_OCD1V_60mV   		= 0x004,
	SH_OCD1V_70mV  			= 0x005,
	SH_OCD1V_80mV   		= 0x006,
	SH_OCD1V_90mV   		= 0x007,
	SH_OCD1V_100mV   		= 0x008,
	SH_OCD1V_110mV   		= 0x009,
	SH_OCD1V_120mV   		= 0x00a,
	SH_OCD1V_130mV   		= 0x00b,
	SH_OCD1V_140mV   		= 0x00c,
	SH_OCD1V_160mV   		= 0x00d,
	SH_OCD1V_180mV   		= 0x00e,
	SH_OCD1V_200mV   		= 0x00f
} SH_OCD1V_t;

//0x0C放电过流1保护延时设置控制位
typedef enum
{
	SH_OCD1T_50MS     = 0x00,
	SH_OCD1T_100MS    = 0x01,
	SH_OCD1T_200MS    = 0x02,
	SH_OCD1T_400MS    = 0x03,
	SH_OCD1T_600MS   	= 0x04,
	SH_OCD1T_800MS  	= 0x05,
	SH_OCD1T_1S   		= 0x06,
	SH_OCD1T_2S   		= 0x07,
	SH_OCD1T_4S   		= 0x08,
	SH_OCD1T_6S   		= 0x09,
	SH_OCD1T_8S   		= 0x0a,
	SH_OCD1T_10S   		= 0x0b,
	SH_OCD1T_15S   		= 0x0c,
	SH_OCD1T_20S   		= 0x0d,
	SH_OCD1T_30S   		= 0x0e,
	SH_OCD1T_40S   		= 0x0f
} SH_OCD1T_t;

//0x0D放电过流2保护电压设置控制位
typedef enum
{
	SH_OCD2V_30mV   	 	= 0x000,
	SH_OCD2V_40mV    		= 0x001,
	SH_OCD2V_50mV    		= 0x002,
	SH_OCD2V_60mV    		= 0x003,
	SH_OCD2V_70mV   		= 0x004,
	SH_OCD2V_80mV  			= 0x005,
	SH_OCD2V_90mV   		= 0x006,
	SH_OCD2V_100mV   		= 0x007,
	SH_OCD2V_120mV   		= 0x008,
	SH_OCD2V_140mV   		= 0x009,
	SH_OCD2V_160mV   		= 0x00a,
	SH_OCD2V_180mV   		= 0x00b,
	SH_OCD2V_200mV   		= 0x00c,
	SH_OCD2V_300mV   		= 0x00d,
	SH_OCD2V_400mV   		= 0x00e,
	SH_OCD2V_500mV   		= 0x00f
} SH_OCD2V_t;

//0x0D放电过流2保护延时设置控制位
typedef enum
{
	SH_OCD2T_10MS    	= 0x000,
	SH_OCD2T_20MS    	= 0x001,
	SH_OCD2T_40MS   	= 0x002,
	SH_OCD2T_60MS    	= 0x003,
	SH_OCD2T_80MS   	= 0x004,
	SH_OCD2T_100MS  	= 0x005,
	SH_OCD2T_200MS   	= 0x006,
	SH_OCD2T_400MS   	= 0x007,
	SH_OCD2T_600MS   	= 0x008,
	SH_OCD2T_800MS   	= 0x009,
	SH_OCD2T_1S   		= 0x00a,
	SH_OCD2T_2S   		= 0x00b,
	SH_OCD2T_4S   		= 0x00c,
	SH_OCD2T_8S   		= 0x00d,
	SH_OCD2T_10S   	= 0x00e,
	SH_OCD2T_20S   	= 0x00f
} SH_OCD2T_t;


//0x0E短路保护保护电压设置控制位
typedef enum
{
	SH_SCV_50mV    		= 0x000,
	SH_SCV_80mV    		= 0x001,
	SH_SCV_110mV    	= 0x002,
	SH_SCV_140mV    	= 0x003,
	SH_SCV_170mV   		= 0x004,
	SH_SCV_200mV  		= 0x005,
	SH_SCV_230mV   		= 0x006,
	SH_SCV_260mV   		= 0x007,
	SH_SCV_290mV   		= 0x008,
	SH_SCV_320mV   		= 0x009,
	SH_SCV_350mV   		= 0x00a,
	SH_SCV_400mV   		= 0x00b,
	SH_SCV_500mV   		= 0x00c,
	SH_SCV_600mV   		= 0x00d,
	SH_SCV_800mV   		= 0x00e,
	SH_SCV_1000mV   	= 0x00f
} SH_SCV_t;

//0x0E短路保护延时设置控制位
typedef enum
{
	SH_SCT_0uS    		= 0x000,
	SH_SCT_64uS    		= 0x001,
	SH_SCT_128uS   		= 0x002,
	SH_SCT_192uS    	= 0x003,
	SH_SCT_256uS   		= 0x004,
	SH_SCT_320uS  		= 0x005,
	SH_SCT_384uS   		= 0x006,
	SH_SCT_448uS   		= 0x007,
	SH_SCT_512uS   		= 0x008,
	SH_SCT_576uS   		= 0x009,
	SH_SCT_640uS   		= 0x00a,
	SH_SCT_704uS   		= 0x00b,
	SH_SCT_768uS   		= 0x00c,
	SH_SCT_832uS   		= 0x00d,
	SH_SCT_896uS   		= 0x00e,
	SH_SCT_960uS   		= 0x00f
} SH_SCT_t;

//0x0F充电过流保护电压设置控制位
typedef enum
{
    SH_OCCV_20mV    		= 0x000,
    SH_OCCV_30mV    		= 0x001,
    SH_OCCV_40mV    		= 0x002,
    SH_OCCV_50mV    		= 0x003,
    SH_OCCV_60mV   			= 0x004,
    SH_OCCV_70mV  			= 0x005,
    SH_OCCV_80mV   			= 0x006,
    SH_OCCV_90mV   			= 0x007,
		SH_OCCV_100mV   		= 0x008,
		SH_OCCV_110mV   		= 0x009,
		SH_OCCV_120mV   		= 0x00a,
		SH_OCCV_130mV   		= 0x00b,
		SH_OCCV_140mV   		= 0x00c,
		SH_OCCV_160mV   		= 0x00d,
		SH_OCCV_180mV   		= 0x00e,
		SH_OCCV_200mV   		= 0x00f
} SH_OCCV_t;

//0x0F充电过流保护延时设置控制位
typedef enum
{
    SH_OCCT_10mS    			= 0x000,
    SH_OCCT_20mS    			= 0x001,
    SH_OCCT_40mS   				= 0x002,
    SH_OCCT_60mS    			= 0x003,
    SH_OCCT_80mS   				= 0x004,
    SH_OCCT_100mS  				= 0x005,
    SH_OCCT_200mS   			= 0x006,
    SH_OCCT_400mS   			= 0x007,
		SH_OCCT_600mS   			= 0x008,
		SH_OCCT_800mS   			= 0x009,
		SH_OCCT_1S   					= 0x00a,
		SH_OCCT_2S   					= 0x00b,
		SH_OCCT_4S   					= 0x00c,
		SH_OCCT_8S   					= 0x00d,
		SH_OCCT_10S   				= 0x00e,
		SH_OCCT_20S   				= 0x00f
} SH_OCCT_t;

//0x10充放电过流自恢复延时设置
typedef enum
{
    SH_OCRT_8S    			= 0x000,
    SH_OCRT_16S    			= 0x001,
    SH_OCRT_32S   			= 0x002,
    SH_OCRT_64S    			= 0x003
} SH_OCRT_t;


//0x10二次过充电保护延时设置
typedef enum
{
    SH_PFT_8S    				= 0x000,
    SH_PFT_16S    			= 0x001,
    SH_PFT_32S   				= 0x002,
    SH_PFT_64S    			= 0x003
} SH_PFT_t;


//0x72看门狗溢出时间控制位
typedef enum
{
    SH_WDT_32S    				= 0x000,
    SH_WDT_16S    				= 0x001,
    SH_WDT_8S   					= 0x002,
    SH_WDT_4S    					= 0x003
} SH_WDT_t;


//0x00串数配置控制位
typedef enum
{
    SH_CN_5S    				= 0x005,
    SH_CN_6S    				= 0x006,
    SH_CN_7S   					= 0x007,
    SH_CN_8S    				= 0x008,
	  SH_CN_9S    				= 0x009,
    SH_CN_10S    				= 0x00a,
    SH_CN_11S   				= 0x00b,
    SH_CN_12S    				= 0x00c,
	  SH_CN_13S   				= 0x00d,
    SH_CN_14S    				= 0x00e,
	  SH_CN_15S   				= 0x00f,
    SH_CN_16S    				= 0x000,
} SH_CN_t;



//0x02负载释放延时设置控制位
typedef enum
{
    SH_LDRT_100MS    		= 0x000,
    SH_LDRT_500MS    		= 0x001,
    SH_LDRT_1000MS    	= 0x002,
    SH_LDRT_2000MS    	= 0x003
} SH_LDRT_t;


//0x10充放电状态检测电压设置
typedef enum
{
    SH_CHS_200uV    		= 0x000,
    SH_CHS_500uV    		= 0x001,
    SH_CHS_1000uV    		= 0x002,
    SH_CHS_2000uV    		= 0x003
} SH_CHS_t;

//0x10充放电MOSFET开启延时设置
typedef enum
{
    SH_MOST_64uS    		= 0x000,
    SH_MOST_128uS    		= 0x001,
    SH_MOST_256uS    		= 0x002,
    SH_MOST_512uS    		= 0x003
} SH_MOST_t;

//系统状态寄存器REG_BSTATUS1--0x43
typedef union
{
	struct
	{
		uint8_t OV: 1;		//1：发生过压保护 0：未发生过压保护
		uint8_t UV : 1;		//1：发生欠压保护 0：未发生欠压保护
		uint8_t OCD1 : 1;	//1：发生放电过流1保护 0：未发生放电过流1保护
		uint8_t OCD2 : 1;	//1：发生放电过流2保护 0：未发生放电过流2保护
		uint8_t OCC:1;		//1：发生充电过流保护 0：未发生充电过流保护
		uint8_t SC:1;			//1：发生短路保护 0：未发生短路保护
		uint8_t PF:1;			//1：发生二次过充电保护 0：未发生二次过充电保护
		uint8_t WDT:1;		//1：看门狗溢出 0：看门狗正常
	}Status_Bits;
	uint8_t Vaule;
}BSTATUS1_Reg_t;

//系统标志寄存器REG_BFLAG1--0x70
typedef union
{
	struct
	{
		uint8_t OV_FLG: 1;		//1：发生过过压保护 0：未发生过过压保护
		uint8_t UV_FLG : 1;		//1：发生过欠压保护 0：未发生过欠压保护
		uint8_t OCD_FLG : 1;	//1：发生过放电过流保护 0：未发生过放电过流保护
		uint8_t LOAD_FLG : 1;	//1：发生过过流 0：未发生过过流
		uint8_t OCC_FLG:1;		//1：发生过充电过流保护 0：未发生过充电过流保护
		uint8_t SC_FLG:1;			//1：发生过短路保护 0：未发生过短路保护
		uint8_t PF_FLG:1;			//1：发生过二次过充电保护 0：未发生过二次过充电保护
		uint8_t WDT_FLG:1;		//1：发生过看门狗溢出 0：未发生过看门狗溢出
	}Flag_Bits;
	uint8_t Vaule;
}BFLAG1_Reg_t;

//0x03、0x04过充电保护电压/过充电保护延时/负载释放延时设置寄存器REG_OVT_LDRT_OVH、REG_OVL
typedef union                                                  
{
	struct
	{
		uint16_t OV: 10;	//过充电保护电压，计算方式：寄存器值 X 5mV
		uint16_t LDRT: 2;	//负载释放延时设置控制位
		uint16_t OVT : 4;	//过充保护延时设置控制位
	}OVT_Field;
	uint16_t Vaule;
}OV_Threshold_Reg_t;

//0x04、0x05过充电恢复电压/过放电保护延时设置寄存器REG_UVT_OVRH、REG_OVRL
typedef union
{
	struct
	{
		uint16_t OVR: 10;			//过充电恢复电压，计算方式：寄存器值 X 5mV
		uint16_t Reserved: 2;	
		uint16_t UVT : 4;			//过放电保护延时设置控制位:0000~1111
	}OVR_Field;
	uint16_t Vaule;
}OVR_Threshold_Reg_t;

//0x01系统配置寄存器2 SCONF2
typedef union
{
	struct
	{
		uint8_t EUVR: 1;		//0：过放电保护状态释放与负载释放无关 1：过放电保护状态释放还需负载释放
		uint8_t OCRA: 1;		//0：不允许电流保护定时恢复 1：允许电流保护定时恢复
		uint8_t CTLC: 2;		//CTL管脚功能设置控制位：00~11
		uint8_t DIS_PF: 1;	//0：启用二次过充电保护 1：禁止二次过充电保护
		uint8_t UV_OP: 1;		//0：过放电只关闭放电MOSFET 1：过放电关闭充放电MOSFET
		uint8_t Reserved:1;
		uint8_t E0VB:1;			//0：关闭“禁止低压电芯充电”功能 1：开启“禁止低压电芯充电”功能
	}SCONF2_Bits;
	uint8_t Vaule;
}SCONF2_Reg_t;

//0x00系统配置寄存器1 SCONF1
typedef union
{
	struct
	{
		//STM32小端模式
		//结构体位域：bit0~bit7
		uint8_t CN: 4;		//串数配置控制位：0101~1111 其他
		uint8_t BAL: 1;		//0：平衡开启由SH367309内部逻辑控制 1：平衡开启由外部MCU控制，平衡时序仍由SH367309内部逻辑控制
		uint8_t OCPM: 1;	//0：充电过流只关闭充电MOSFET；放电过流只关闭放电MOSFET 1：充放电过流关闭充放电MOSFET
		uint8_t ENMOS: 1;	//0：禁用充电MOSFET恢复控制位 1：启用充电MOSFET恢复控制位。当过充电/温度保护关闭充电MOSFET后，如果检测到放电过流1或者放电状态，则开启充电MOSFET
		uint8_t ENPCH: 1; //0：禁用预充电功能 1：启用预充电功能
	}SCONF1_Bits;
	uint8_t Vaule;
}SCONF1_Reg_t;


typedef uint8_t UV_Threshold_Reg_t;

typedef uint8_t UVR_Threshold_Reg_t;

//0x0C放电过流1设置寄存器
typedef union
{
	struct
	{
		uint8_t OCD1T: 4;	//放电过流1 保护延时设置控制位
		uint8_t OCD1V: 4;	//放电过流1 保护电压设置控制位
	}OCD1_Field;
	uint8_t Vaule;
}OCD1_Reg_t;

//0x0D放电过流2设置寄存器
typedef union
{
	struct
	{
		uint8_t OCD2T: 4;	//放电过流2 保护延时设置控制位
		uint8_t OCD2V: 4;	//放电过流2 保护电压设置控制位
	}OCD2_Field;
	uint8_t Vaule;
}OCD2_Reg_t;

//0x0E短路保护设置寄存器
typedef union
{
	struct
	{
		uint8_t SCT: 4;	//短路保护延时设置控制位
		uint8_t SCV: 4;	//短路保护保护电压设置控制位
	}SCVSCT_Field;
	uint8_t Vaule;
}SCVSCT_Reg_t;

//0x0F充电过流设置寄存器
typedef union
{
	struct
	{
		uint8_t OCCT: 4;	//充电过流保护延时设置控制位
		uint8_t OCCV: 4;	//充电过流保护电压设置控制位
	}OCCVOCCT_Field;
	uint8_t Vaule;
}OCCVOCCT_Reg_t;

//0x10充放电过流自动恢复/二次过充电保护延时设置寄存器
typedef union
{
	struct
	{
		uint8_t PFT: 2;		//二次过充电置
		uint8_t OCRT: 2;	//充放电过流自恢复延时设置
		uint8_t MOST: 2;	//充放电MOSFET
		uint8_t CHS: 2;		//充放电状态检测电压设置
	}MOST_OCRT_PFT_Bits;
	uint8_t Vaule;
}MOST_OCRT_PFT_Reg_t;


typedef uint8_t PFV_Threshold_Reg_t;
typedef uint8_t L0V_Threshold_Reg_t;
typedef uint8_t BALV_Threshold_Reg_t;


typedef uint16_t BALANCE_Reg_t;
typedef uint8_t RSTSTAT_Reg_t;

//0x40系统配置寄存器REG_CONF
typedef union
{
	struct
	{
		uint8_t IDLE: 1;		//0：SH367309不进入IDLE状态 1：SH367309将进入IDLE状态，唤醒后硬件自动清零
		uint8_t SLEEP :1;		//0：SH367309不进入SLEEP状态 1：SH367309将进入SLEEP状态，唤醒后硬件自动清零
		uint8_t ENWDT :1;		//0：SH367309关闭看门狗模块 1：SH367309开启看门狗模块
		uint8_t CADCON :1;	//0：SH367309关闭CADC 1：SH367309开启CADC进行电流采集
		uint8_t CHGMOS:1;		//0：充电MOSFET关闭 1：充电MOSFET由硬件保护模块决定
		uint8_t DSGMOS:1;		//0：放电MOSFET关闭 1：放电MOSFET由硬件保护模块决定
		uint8_t PCHMOS:1;		//0：预充电MOSFET关闭 1：预充电MOSFET由硬件保护模块决定
		uint8_t OCRC:1;			//过流保护控制位--过流保护状态清除需在OCRC位连续写：0-1-0
	}CONF_Bits;
	uint8_t Vaule;
}CONF_Reg_t;

//0x43系统状态寄存器BSTATUS1
typedef union
{
	struct
	{
		uint8_t OV: 1;		//1：发生过压保护 0：未发生过压保护
		uint8_t UV :1;		//1：发生欠压保护 0：未发生欠压保护
		uint8_t OCD1 :1;	//1：发生放电过流1保护 0：未发生放电过流1保护
		uint8_t OCD2 :1;	//1：发生放电过流2保护 0：未发生放电过流2保护
		uint8_t OCC:1;		//1：发生充电过流保护 0：未发生充电过流保护
		uint8_t SC:1;			//1：发生短路保护 0：未发生短路保护
		uint8_t PF:1;			//1：发生二次过充电保护 0：未发生二次过充电保护
		uint8_t WDT:1;		//1：看门狗溢出 0：看门狗正常
	}CONF_Bits;
	uint8_t Vaule;
}Batstatu1_Reg_t;

//0x44系统状态寄存器BSTATUS2
typedef union
{
	struct
	{
		uint8_t UTC: 1;		//1：发生充电低温保护 0：未发生充电低温保护
		uint8_t OTC :1;		//1：发生充电高温保护 0：未发生充电高温保护
		uint8_t UTD :1;		//1：发生放电低温保护 0：未发生放电低温保护
		uint8_t OTD :1;		//1：发生放电高温保护 0：未发生放电高温保护
		uint8_t Reseved:4;
	}CONF_Bits;
	uint8_t Vaule;
}Batstatu2_Reg_t;

//0x45系统状态寄存器BSTATUS3
typedef union
{
	struct
	{
		uint8_t DSG_FET :1;		//1：放电MOSFET开启 0：放电MOSFET关闭
		uint8_t CHG_FET :1;		//1：充电MOSFET开启 0：充电MOSFET关闭
		uint8_t PCHG_FET :1;	//1：预充电MOSFET开启 0：预充电MOSFET关闭
		uint8_t L0V:1;				//1：发生低电压禁止充电 0：未发生低电压禁止充电
		uint8_t EEPR_WR:1;		//1：EEPROM写操作错误 0：EEPROM写操作正确
		uint8_t Reseved:1;		
		uint8_t BatStatus:2;	//放电状态位+充电状态位
	}CONF_Bits;
	uint8_t Vaule;
}Batstatu3_Reg_t;

//#define PH_EDL 0
//#define PH_DSG 1
//#define PH_CHG 2

typedef uint8_t PREV_Reg_t;

//0x71系统标志寄存器BFLAG2
typedef union
{
	struct
	{
		uint8_t UTC_FLG: 1;		//1：发生过充电低温保护 0：未发生过充电低温保护
		uint8_t OTC_FLG : 1;	//1：发生过充电高温保护 0：未发生过充电高温保护
		uint8_t UTD_FLG : 1;	//1：发生过放电低温保护 0：未发生过放电低温保护
		uint8_t OTD_FLG : 1;	//1：发生过放电高温保护 0：未发生过放电高温保护
		uint8_t VADC_FLG:1;		//1：发生过VADC中断 0：未发生过VADC中断 该bit被读取之后，硬件会自动清零
		uint8_t CADC_FLG:1;		//1：发生过CADC中断 0：未发生过CADC中断 该bit被读取之后，硬件会自动清零
		uint8_t WAKE_FLG:1;		//1：从IDLE状态（检测到充放电电流）或者SLEEP状态（充电器连接）被唤醒 0：未被唤醒
		uint8_t RST_FLG:1;		//1：系统复位后，自动置1，需MCU清零 0：未被唤醒
	}Flag_Bits;
	uint8_t Vaule;
}BFLAG2_Reg_t;

//
typedef struct
{
	Batstatu1_Reg_t BatstatuA1;
	Batstatu2_Reg_t BatstatuA2;
	Batstatu3_Reg_t BatstatuA3;
	Batstatu1_Reg_t BatstatuB1;
	Batstatu2_Reg_t BatstatuB2;
	Batstatu3_Reg_t BatstatuB3;
}BatstateSt;

extern BatstateSt Batstate;

extern CONF_Reg_t CONF_Reg;

//以下为EEPROM寄存器地址：00H~19H
#define REG_SCONF1    				0x00		//系统配置寄存器1
#define REG_SCONF2    				0x01		//系统配置寄存器2
#define REG_OVT_LDRT_OVH    	0x02		//过充电保护电压/过充电保护延时/负载释放延时设置寄存器
#define REG_OVL          			0x03		//同上
#define REG_UVT_OVRH          0x04		//过充电恢复电压/过放电保护延时设置寄存器
#define REG_OVRL          		0x05		//同上
#define REG_UV      					0x06		//过放电保护电压设置寄存器
#define REG_UVR               0x07		//过放电恢复电压设置寄存器
#define REG_BALV              0x08		//平衡开启电压设置寄存器
#define REG_PREV              0x09		//预充电电压设置寄存器
#define REG_L0V               0x0A		//低电压禁止充电电压设置寄存器
#define REG_PFV               0x0B		//二次过充电保护电压设置寄存器
#define REG_OCD1V_OCD1T       0x0C		//放电过流1设置寄存器
#define REG_OCD2V_OCD2T       0x0D		//放电过流2设置寄存器
#define REG_SCV_SCT        		0x0E		//短路保护设置寄存器
#define REG_OCCV_OCCT         0x0F		//充电过流设置寄存器充电过流设置寄存器
#define REG_MOST_OCRT_PFT     0x10		//充放电过流自动恢复/二次过充电保护延时设置寄存器
#define REG_OTC               0x11		//充电高温保护设置寄存器
#define REG_OTCR              0x12		//充电高温保护释放设置寄存器
#define REG_UTC               0x13		//充电低温保护设置寄存器
#define REG_UTCR              0x14		//充电低温保护释放设置寄存器
#define REG_OTD               0x15		//放电高温保护设置寄存器
#define REG_OTDR              0x16		//放电高温保护释放设置寄存器
#define REG_UTD               0x17		//放电低温保护设置寄存器
#define REG_UTDR              0x18		//放电低温保护释放设置寄存器
#define REG_TR                0x19		//温度内部参考电阻系数寄存器,只读!

//以下为RAM寄存器地址40H~72H
#define REG_CONF    				  0x40		//系统配置寄存器
#define REG_BALANCEH   				0x41		//平衡寄存器
#define REG_BALANCEL    			0x42		//平衡寄存器
#define REG_BSTATUS1          0x43		//系统状态寄存器BSTATUS1
#define REG_BSTATUS2          0x44		//系统状态寄存器BSTATUS2
#define REG_BSTATUS3          0x45		//系统状态寄存器BSTATUS3
#define REG_TEMP1H      			0x46		//T1温度寄存器
#define REG_TEMP1L            0x47		
#define REG_TEMP2H            0x48		//T2温度寄存器
#define REG_TEMP2L            0x49
#define REG_TEMP3H            0x4A		//T3温度寄存器
#define REG_TEMP3L            0x4B
#define REG_CURH            	0x4C		//电流寄存器
#define REG_CURL            	0x4D
#define REG_CELL1H       			0x4E		
#define REG_CELL1L       			0x4F
#define REG_CELL2H       			0x50
#define REG_CELL2L       			0x51
#define REG_CELL3H       			0x52
#define REG_CELL3L       			0x53
#define REG_CELL4H       			0x54
#define REG_CELL4L       			0x55
#define REG_CELL5H       			0x56
#define REG_CELL5L       			0x57
#define REG_CELL6H       			0x58
#define REG_CELL6L       			0x59
#define REG_CELL7H       			0x5A
#define REG_CELL7L       			0x5B
#define REG_CELL8H       			0x5C
#define REG_CELL8L       			0x5D
#define REG_CELL9H       			0x5E
#define REG_CELL9L       			0x5F
#define REG_CELL10H       		0x60
#define REG_CELL10L       		0x61
#define REG_CELL11H       		0x62
#define REG_CELL11L       		0x63
#define REG_CELL12H       		0x64
#define REG_CELL12L       		0x65
#define REG_CELL13H       		0x66
#define REG_CELL13L       		0x67
#define REG_CELL14H       		0x68
#define REG_CELL14L       		0x69
#define REG_CELL15H       		0x6A
#define REG_CELL15L       		0x6B
#define REG_CELL16H       		0x6C
#define REG_CELL16L       		0x6D
#define REG_CADCDH       			0x6E		//CADC电流寄存器
#define REG_CADCDL       			0x6F
#define REG_BFLAG1       			0x70		//系统标志寄存器BFLAG1
#define REG_BFLAG2       			0x71		//系统标志寄存器BFLAG2
#define REG_RSTSTAT       		0x72		//看门狗寄存器


void SH_Get_CellVolts(uint16_t * buf);
void SH_Get_CellTemps(void);
int16_t SH_Get_Current(void);
int16_t SH_Get_CADCCurrent(void);
void SH_SLEEP(void);
void SH_Set_IDLE(void);
void SH_MOSCtrl(uint8_t CHGCtrl,uint8_t DSGCtrl);

void SH_Set_CONF(uint8_t val);
void SH_Set_Balance(uint16_t BalanceFlag);
uint8_t SH367309_ReadData(uint8_t ReadAddr,uint8_t* ReadBuf,uint8_t len);
uint8_t SH367309_ReadRegVal(uint8_t Addr,uint8_t* readBuf,uint8_t len);
void SH367309_Config(void);
void SH_Reset(void);
void SH_Read_Alarm(void);

#endif

