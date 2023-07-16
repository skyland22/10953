#include "main.h"

uint16_t SysRegData[256]= {0};
uint16_t SysReg_Type[20]= {0};
uint16_t SysReg_VF[20]= {0};
uint16_t SysReg_VH[20]= {0};
CHGStatuesSt ChgStatus;

void SIM_I2C_Start()
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
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

	/* �ȷ����ֽڵĸ�λbit7 */
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
		_ucByte <<= 1;	/* ����һ��bit */
		Soft_Delay(2);
		I2C_SCL_0();
		Soft_Delay(1);
		if (i == 7)
		{
			 I2C_SDA_1(); // �ͷ�����
		}
	}
}

uint8_t SIM_I2C_ReadByte()
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
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

	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
	Soft_Delay(2);
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	Soft_Delay(1);
	re = I2C_READ_SDA();	/* CPU��ȡSDA����״̬: re=0��Ӧ�� */ 
	Soft_Delay(1);
	I2C_SCL_0();
	Soft_Delay(2);
	return re;
}

void SIM_I2C_Ack()
{
	I2C_SDA_0();	/* CPU����SDA = 0 */
	Soft_Delay(1);
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	Soft_Delay(2);
	I2C_SCL_0();
	Soft_Delay(2);
	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}


void SIM_I2C_NAck()
{
	I2C_SDA_1();	/* CPU����SDA = 1 */
	Soft_Delay(1);
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	Soft_Delay(2);
	I2C_SCL_0();
	Soft_Delay(2);
}

//ģ��I2C��ʼ��
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
	
	SysRegData[0x08]= syspara.tempMax*10+2732-400;	//�¶�     0.1K
	SysRegData[0x09]= syspara.totalSumVolt;	//	R	Voltage 
	SysRegData[0x0A]= syspara.current/10;	//R	Current 
	SysRegData[0x0B]= syspara.Avgcurrent/10;	//R	Current 
	SysRegData[0x0D]= syspara.SOC;	//	R	RelativeStateOfCharge 
	SysRegData[0x0E]= syspara.SOC;	//	R	AbsoluteStateOfCharge 
	SysRegData[0x0F]= (syspara.RemainCap/3600/5);	//		R	RunTimeToEmpty	0��65535	�Ե�ǰ�����ſ�����ʱ��	min
	SysRegData[0x10]= (syspara.FullChargeCap/3600/5);	//		R	FullChargeCapacity	0��65535	������ĵ������	mAh
	SysRegData[0x11]= ((syspara.current<0)?(syspara.RemainCap/60/5)/(abs(syspara.current)):65535);	//		R	AverageTimeToFull	0��65535	��ƽ��������������ʱ��	min
	SysRegData[0x12]= ((syspara.Avgcurrent<0)?(syspara.RemainCap/60/5)/(abs(syspara.Avgcurrent)):65535);	//		R	AverageTimeToFull	0��65535	��ƽ��������������ʱ��	min
	SysRegData[0x13]= ((syspara.Avgcurrent>0)?((syspara.FullChargeCap/60/5)-(syspara.RemainCap/60/5))/syspara.Avgcurrent:65535);	//		R	AverageTimeToFull	0��65535	��ƽ��������������ʱ��	min
	SysRegData[0x14]= 10000;	//		R	ChargingCurrent 	0��65535	���������	mA
	SysRegData[0x15]= 42500;	//		R	ChargingVoltage 	0��65535	�������ѹ	mV
	if(SysRegData[0x12]<10)
	{
		syspara.batteryStatus.bits.RemanTimeAlarm= 1;
	}
	else
	{
		syspara.batteryStatus.bits.RemanTimeAlarm= 0;
	}
	syspara.batteryStatus.bits.DsgStatu= (syspara.batStat!=STATE_CHG)?1:0;

	SysRegData[0x16]= syspara.batteryStatus.bytes;//		���״̬
	SysRegData[0x17]= flashpara.CycleCount;//		ѭ������
	SysRegData[0x18]= (DEF_CAP*1000);//	��Ƶ�ѹ
	SysRegData[0x19]= 35200;//	��Ƶ�ѹ

	for(i= 0;i<15;i++)
	{
		SysRegData[0x31+i]= syspara.cellVolt[14-i];
	}

	SysRegData[0x1B]=( (flashpara.id[0]+20)*512+flashpara.id[1]*32+flashpara.id[2]);  // ��*512+ ��*32+��
	SysRegData[0x1C]=( (flashpara.id[3]<<8)|flashpara.id[4]); //Number
	SysRegData[0x55]= syspara.ChgStatus.bytes;//		�����״̬

	SysReg_Type[0] = PROJECTCODE;
	SysReg_VF[0] = RWSERVIN;
	SysReg_VH[0] = ((HARDCODE_M<<8)+HARDCODE_S);
}





