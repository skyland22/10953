#include "main.h"

uint16_t SysRegData[256]= {0};
uint16_t SysReg_Type[20]= {0};
uint16_t SysReg_VF[20]= {0};
uint16_t SysReg_VH[20]= {0};
CHGStatuesSt ChgStatus;

void SIM_I2C_Start()
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_SDA_1();
	Soft_Delay(1);
	I2C_SCL_1();
	Soft_Delay(4);
	I2C_SDA_0();
	Soft_Delay(4);
	I2C_SCL_0();
	Soft_Delay(1);
}


void SIM_I2C_Stop()
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SDA_0();
	Soft_Delay(2);
	I2C_SCL_1();
	Soft_Delay(1);
	I2C_SDA_1();
	Soft_Delay(2);
}


void SIM_I2C_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		Soft_Delay(1);
		I2C_SCL_1();
		_ucByte <<= 1;	/* 左移一个bit */
		Soft_Delay(2);
		I2C_SCL_0();
		Soft_Delay(1);
		if (i == 7)
		{
			 I2C_SDA_1(); // 释放总线
		}
	}
}

uint8_t SIM_I2C_ReadByte()
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		Soft_Delay(2);
		I2C_SCL_1();
		Soft_Delay(1);
		value <<= 1;
		if (I2C_READ_SDA())
		{
			value++;
		}
		Soft_Delay(1);
		I2C_SCL_0();
	}
	return value;
}


uint8_t SIM_I2C_WaitAck()
{
	uint8_t re;

	I2C_SDA_1();	/* CPU释放SDA总线 */
	Soft_Delay(2);
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	Soft_Delay(1);
	re = I2C_READ_SDA();	/* CPU读取SDA口线状态: re=0有应答 */ 
	Soft_Delay(1);
	I2C_SCL_0();
	Soft_Delay(2);
	return re;
}

void SIM_I2C_Ack()
{
	I2C_SDA_0();	/* CPU驱动SDA = 0 */
	Soft_Delay(1);
	I2C_SCL_1();	/* CPU产生1个时钟 */
	Soft_Delay(2);
	I2C_SCL_0();
	Soft_Delay(2);
	I2C_SDA_1();	/* CPU释放SDA总线 */
}


void SIM_I2C_NAck()
{
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	Soft_Delay(1);
	I2C_SCL_1();	/* CPU产生1个时钟 */
	Soft_Delay(2);
	I2C_SCL_0();
	Soft_Delay(2);
}

//模拟I2C初始化
//IICNUM=1
//SCL--PA11
//SDA--PA12

//IICNUM=2
//SCL--PB6
//SDA--PB7

//IICNUM=3
//SCL--PB10
//SDA--PB11
void SIM_I2C_PortInit()
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	SIM_I2C_Stop();
}


void SMBUS_DataProcess(void)
{	
	uint8_t i= 0;
	
	SysRegData[0x08]= syspara.tempMax*10+2732-400;	//温度     0.1K
	SysRegData[0x09]= syspara.totalSumVolt;	//	R	Voltage 
	SysRegData[0x0A]= syspara.current/10;	//R	Current 
	SysRegData[0x0B]= syspara.Avgcurrent/10;	//R	Current 
	SysRegData[0x0D]= syspara.SOC;	//	R	RelativeStateOfCharge 
	SysRegData[0x0E]= syspara.SOC;	//	R	AbsoluteStateOfCharge 
	SysRegData[0x0F]= (syspara.RemainCap/3600/5);	//		R	RunTimeToEmpty	0到65535	以当前电流放空所需时间	min
	SysRegData[0x10]= (syspara.FullChargeCap/3600/5);	//		R	FullChargeCapacity	0到65535	充满电的电池容量	mAh
	SysRegData[0x11]= ((syspara.current<0)?(syspara.RemainCap/60/5)/(abs(syspara.current)):65535);	//		R	AverageTimeToFull	0到65535	以平均电流充满所需时间	min
	SysRegData[0x12]= ((syspara.Avgcurrent<0)?(syspara.RemainCap/60/5)/(abs(syspara.Avgcurrent)):65535);	//		R	AverageTimeToFull	0到65535	以平均电流充满所需时间	min
	SysRegData[0x13]= ((syspara.Avgcurrent>0)?((syspara.FullChargeCap/60/5)-(syspara.RemainCap/60/5))/syspara.Avgcurrent:65535);	//		R	AverageTimeToFull	0到65535	以平均电流充满所需时间	min
	SysRegData[0x14]= 10000;	//		R	ChargingCurrent 	0到65535	需求充电电流	mA
	SysRegData[0x15]= 42500;	//		R	ChargingVoltage 	0到65535	需求充电电压	mV
	if(SysRegData[0x12]<10)
	{
		syspara.batteryStatus.bits.RemanTimeAlarm= 1;
	}
	else
	{
		syspara.batteryStatus.bits.RemanTimeAlarm= 0;
	}
	syspara.batteryStatus.bits.DsgStatu= (syspara.batStat!=STATE_CHG)?1:0;

	SysRegData[0x16]= syspara.batteryStatus.bytes;//		电池状态
	SysRegData[0x17]= flashpara.CycleCount;//		循环次数
	SysRegData[0x18]= (DEF_CAP*1000);//	设计电压
	SysRegData[0x19]= 35200;//	设计电压

	for(i= 0;i<15;i++)
	{
		SysRegData[0x31+i]= syspara.cellVolt[14-i];
	}

	SysRegData[0x1B]=( (flashpara.id[0]+20)*512+flashpara.id[1]*32+flashpara.id[2]);  // 年*512+ 月*32+日
	SysRegData[0x1C]=( (flashpara.id[3]<<8)|flashpara.id[4]); //Number
	SysRegData[0x55]= syspara.ChgStatus.bytes;//		充电电池状态

	SysReg_Type[0] = PROJECTCODE;
	SysReg_VF[0] = RWSERVIN;
	SysReg_VH[0] = ((HARDCODE_M<<8)+HARDCODE_S);
}





