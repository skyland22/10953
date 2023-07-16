#include "main.h"

//单位x10Ω，SH_TEMP_TABLE=-40℃ ~ 110℃
const uint16_t SH_TEMP_TABLE[]={	
	19666,	18580,	17562,	16606,	15708,	14866,	14074,	13329,	12628,	11969,	//-40
	11349,	10765,	10215,	 9696,	 9208,	 8747,	 8311,	 7900,   7513,   7147,	//-30
	 6800,	 6473,   6164,   5871,   5594,   5331,   5083,   4848,   4625,   4414,	//-20
	 4213,   4023,   3843,   3672,   3509,   3355,   3208,   3069,   2936,   2810,	//-10
	 2690,   2576,   2468,   2364,   2266,   2172,   2082,   1997,   1916,   1839,	//0
	 1765,   1694,   1627,   1562,   1501,   1443,   1387,   1333,   1282,   1233,	//10
	 1186,   1142,   1099,   1058,   1019,    981,		945, 		911, 		877, 		845,	//20
	  815, 		786, 		758, 		732, 		706, 		681, 		657, 		635, 		613, 		592,	//30
	  572, 		552, 		534, 		516,  	499, 		482, 		466,    451, 		436, 		422,	//40
	  409, 		395, 		383, 		371, 		359, 		347, 		337, 		326, 		316, 		306,	//50
	  297, 		288, 		279, 		271, 		263, 		255, 		247, 		240, 		232, 		226,	//60
	  219, 		213, 		207, 		201, 		195, 		189, 		184, 		179, 		174, 		169,	//70
	  164, 		160, 		155, 		151, 		147, 		143, 		139, 		135, 		132, 		128,	//80
	  125, 		121, 		118, 		115, 		112, 		109, 		106, 		103, 		101,		 98,	//90
	   96, 		 93,  	 91, 		 89, 		 87, 		 84, 		 82, 		 80, 		 78, 		 76,	//100
	   75, 		 73, 		 71, 		 69, 	 	 68, 		 66, 		 64, 		 63, 		 61, 		 60,	//110
	   58
};


CONF_Reg_t CONF_Reg;

uint8_t SHTempCoeff = 50;//57;		//温度内部参考电阻系数,即TR寄存器值，Rref=9.6KΩ=9600 x10Ω

//从机地址
#define SH_ADDRESS		(0x1A<<1)

#define CFG_DEF_WRITEEEP 0		//EEPROM烧写开关

//0x00 SCONF1
//#define CFG_Cell_NUM	10	//电池串数
#define CFG_SH_ENPCH 	1 //0:禁用预充电功能   1:启用预充电功能
#define CFG_SH_ENMOS 	1 //充电MOSFET恢复控制位 0:禁用充电MOSFET恢复控制位 1:启用充电MOSFET恢复控制位,当过充电/温度保护关闭充电MOSFET后,如果检测到放电过流1或者放电状态,则开启充电MOSFET;
#define CFG_SH_OCPM 	1 //充放电过流MOSFET控制位 0:充电过流只关闭充电MOSFET:放电过流只关闭放电MOSFET;  1:充放电过流关闭充放电MOSFET
#define CFG_SH_BAL 		0 //平衡开启电压设置 0:由内部逻辑控制; 1:由MCU控制

//0x01 SCONF2
#define CFG_SH_EUVR 	0 //过放电保护状态释放与负载释放关系
#define CFG_SH_OCRA 	1 //电流保护定时恢复
#define CFG_SH_CTLC 	0 //CTL管脚功能控制
#define CFG_SH_DIS_PF 1 //1:二次过充电保护禁用
#define CFG_SH_UV_OP 	1 //过放电只关闭放电MOSFET
#define CFG_SH_E0VB 	0 //关闭“禁止低压电芯充电”功能

//0x02、0x03
#define CFG_SH_OV 	4250						//单体过充电压mV：寄存器值 X 5mV
#define CFG_SH_LDRT SH_LDRT_100MS 	//负载释放延时
#define CFG_SH_OVT 	SH_OVT_1S 		  //过充电保护延时

//0x04、0x05
#define CFG_SH_OVR 	4170						//过充电恢复电压：寄存器值 X 5mV
#define CFG_SH_UVT 	SH_UVT_1S 		  //过放电保护延时，需要比软件保护延时大1s以上

//0x06
#define CFG_SH_UV 	3000						//过放保护电压：寄存器值 X 20mV

//0x07
#define CFG_SH_UVR 	3100						//过放恢复电压：寄存器值 X 20mV

//0x08
#define CFG_SH_BALV 4200						//平衡开启电压：寄存器值 X 20mV

//0x09
#define CFG_SH_PREV 2400						//预充电电压：寄存器值 X 20mV

//0x0A
#define CFG_SH_L0V	2000						//低电压禁止充电电压：寄存器值 X 20mV

//0x0B
#define CFG_SH_PFV 	4400	 					//二次过充电保护电压：寄存器值 X 20mV

//0x0C
#define CFG_SH_OCD1T 	SH_OCD1T_1S 	 //放电过流1 保护延时
#define CFG_SH_OCD1V 	SH_OCD1V_40mV  //40mV/5mR=8A //放电过流1 保护电压

//0x0D
#define CFG_SH_OCD2T 	SH_OCD2T_100MS //放电过流2 保护延时
#define CFG_SH_OCD2V 	SH_OCD2V_50mV  //50mV/5mR=10A //放电过流2 保护电压

//0x0E
#define CFG_SH_SCT 		SH_SCT_832uS		//SH_SCT_128uS 	 //短路保护延时
#define CFG_SH_SCV 		SH_SCV_50mV  	//50mV/5mR=10A //短路保护保护电压

//0x0F
#define CFG_SH_OCCT 	SH_OCCT_1S		//充电过流保护延时
#define CFG_SH_OCCV   SH_OCCV_20mV	//20mV/5mR=4A //充电过流保护电压

//0x10
#define CFG_SH_PFT 		SH_PFT_8S			//二次过充电保护延时
#define CFG_SH_OCRT 	SH_OCRT_8S		//充放电过流自恢复延时
#define CFG_SH_MOST   SH_MOST_128uS	//充放电MOSFET 开启延时
#define CFG_SH_CHS 		SH_CHS_200uV 	//200uV/5mR=40mA 充放电状态检测电压

//0x11~0x18
//温度保护阈值对应的热敏电阻阻值RT1 (x10Ω)
#define IndexRes(t) SH_TEMP_TABLE[t+40]
#define CFG_SH_OTC 	IndexRes(Def_SH_OTC) 	//SH_TEMP_TABLE[52+40]=SH_TEMP_TABLE[92]=383 		充电高温保护阈值
#define CFG_SH_OTCR IndexRes(Def_SH_OTCR) //SH_TEMP_TABLE[45+40]=SH_TEMP_TABLE[85]=482 		充电高温保护释放阈值
#define CFG_SH_UTC 	IndexRes(Def_SH_UTC)	//SH_TEMP_TABLE[-35+40]=SH_TEMP_TABLE[5]=14866	充电低温保护阈值
#define CFG_SH_UTCR IndexRes(Def_SH_UTCR)	//SH_TEMP_TABLE[-30+40]=SH_TEMP_TABLE[10]=11349 充电低温保护释放阈值
#define CFG_SH_OTD 	IndexRes(Def_SH_OTD)	//SH_TEMP_TABLE[57+40]=SH_TEMP_TABLE[97]=326		放电高温保护阈值
#define CFG_SH_OTDR IndexRes(Def_SH_OTDR)	//SH_TEMP_TABLE[50+40]=SH_TEMP_TABLE[90]=409		放电高温保护释放阈值
#define CFG_SH_UTD 	IndexRes(Def_SH_UTD)	//SH_TEMP_TABLE[-35+40]=SH_TEMP_TABLE[5]=14866	放电低温保护阈值
#define CFG_SH_UTDR IndexRes(Def_SH_UTDR)	//SH_TEMP_TABLE[-30+40]=SH_TEMP_TABLE[10]=11349 放电低温保护释放阈值


//-20	6969
//-15	5459
//0		2749
//5		2218
//55	353
//60	302
//65	259


#define SH367309_I2C_SCL_1 	GPIO_WritePin(GPIOB, LL_GPIO_PIN_6, GPIO_PIN_SET)
#define SH367309_I2C_SCL_0 	GPIO_WritePin(GPIOB, LL_GPIO_PIN_6, GPIO_PIN_RESET)
#define SH367309_I2C_SDA_1 	GPIO_WritePin(GPIOB, LL_GPIO_PIN_7, GPIO_PIN_SET)
#define SH367309_I2C_SDA_0 	GPIO_WritePin(GPIOB, LL_GPIO_PIN_7, GPIO_PIN_RESET)
#define SH367309_READ_SDA 	GPIO_ReadPin(GPIOB,LL_GPIO_PIN_7)

void SH367309_I2C_Start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	Soft_Delay(2);
	SH367309_I2C_SDA_1;
	Soft_Delay(1);
	SH367309_I2C_SCL_1;
	Soft_Delay(4);
	SH367309_I2C_SDA_0;
	Soft_Delay(4);
	SH367309_I2C_SCL_0;
	Soft_Delay(1);
}


void SH367309_I2C_Stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	SH367309_I2C_SDA_0;
	Soft_Delay(2);
	SH367309_I2C_SCL_1;
	Soft_Delay(1);
	SH367309_I2C_SDA_1;
	Soft_Delay(2);
}


void SH367309_I2C_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			SH367309_I2C_SDA_1;
		}
		else
		{
			SH367309_I2C_SDA_0;
		}
		Soft_Delay(1);
		SH367309_I2C_SCL_1;
		_ucByte <<= 1;	/* 左移一个bit */
		Soft_Delay(2);
		SH367309_I2C_SCL_0;
		Soft_Delay(1);
		if (i == 7)
		{
			 SH367309_I2C_SDA_1; // 释放总线
		}
	}
}

uint8_t SH367309_I2C_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		Soft_Delay(2);
		SH367309_I2C_SCL_1;
		Soft_Delay(1);
		value <<= 1;
		if (SH367309_READ_SDA)
		{
			value++;
		}
		Soft_Delay(1);
		SH367309_I2C_SCL_0;
	}
	return value;
}


uint8_t SH367309_I2C_WaitAck(void)
{
	uint8_t re;

	SH367309_I2C_SDA_1;	/* CPU释放SDA总线 */
	Soft_Delay(2);
	SH367309_I2C_SCL_1;	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	Soft_Delay(1);
	re = SH367309_READ_SDA;	/* CPU读取SDA口线状态 */
	Soft_Delay(1);
	SH367309_I2C_SCL_0;
	Soft_Delay(2);
	if(re)
	{
		//rt_kprintf("SH367309 No Wait ACK!\r\n");
	}
	return re;
}

void SH367309_I2C_Ack(void)
{
	SH367309_I2C_SDA_0;	/* CPU驱动SDA = 0 */
	Soft_Delay(1);
	SH367309_I2C_SCL_1;	/* CPU产生1个时钟 */
	Soft_Delay(2);
	SH367309_I2C_SCL_0;
	Soft_Delay(2);
	SH367309_I2C_SDA_1;	/* CPU释放SDA总线 */
}


void SH367309_I2C_NAck(void)
{
	SH367309_I2C_SDA_1;	/* CPU驱动SDA = 1 */
	Soft_Delay(1);
	SH367309_I2C_SCL_1;	/* CPU产生1个时钟 */
	Soft_Delay(2);
	SH367309_I2C_SCL_0;
	Soft_Delay(2);
}

void SH367309_IICPort_Init(void)
{
	SH367309_I2C_Stop();
}


uint8_t SH367309_ReadData(uint8_t ReadAddr,uint8_t* ReadBuf,uint8_t len)
{				  
	uint8_t cksLen = 4;
	uint8_t crc=0;	
	uint8_t checkBuf[50] = {0};
	checkBuf[0] = SH_ADDRESS;
	checkBuf[1] = ReadAddr;
	checkBuf[2] = len;
	checkBuf[3] = SH_ADDRESS|0X01;
	
	SH367309_I2C_Start();
	SH367309_I2C_SendByte(SH_ADDRESS) ;   //发送器件地址写数据 	 
	SH367309_I2C_WaitAck();
	SH367309_I2C_SendByte(ReadAddr);   
	SH367309_I2C_WaitAck();  
	SH367309_I2C_SendByte(len);  
	SH367309_I2C_WaitAck();    
	SH367309_I2C_Start();  	 	   
	SH367309_I2C_SendByte(SH_ADDRESS|0X01);  	   
	SH367309_I2C_WaitAck(); 
	
	while(len--)
	{
		checkBuf[cksLen] = SH367309_I2C_ReadByte();	
		SH367309_I2C_Ack(); 				
		*ReadBuf++ = checkBuf[cksLen++];	
	}		
	crc = SH367309_I2C_ReadByte();	
	SH367309_I2C_NAck(); 	
	
	SH367309_I2C_Stop();
	
	if(crc == CRC8(checkBuf,cksLen))
	{
		return 0;
	}
	else 
	{
		return 0xff;
	}
}

int SH367309_WriteEEpromData(uint8_t WriteAddr,uint8_t DataToWrite)
{
	uint8_t checkData = 0;
	uint8_t i = 0;
	uint8_t DataBuffer[4] = {SH_ADDRESS,WriteAddr,DataToWrite,0};
	DataBuffer[3] = CRC8CheckTab(DataBuffer, 3);

	SH367309_I2C_Start();  	
	for(i=0;i<4;i++)
	{
		SH367309_I2C_SendByte(DataBuffer[i]);   //发送器件地址0XA0,写数据 		 
		SH367309_I2C_WaitAck();	
	}	
	SH367309_I2C_Stop();											//产生一个停止条件 	  
	LL_mDelay(35);
	SH367309_ReadRegVal(WriteAddr,&checkData,1);
#if(DBG_Printf_SH30X==1)
	printf(" W EE DataToWrite-checkData = %x-%x \r\n",DataToWrite,checkData);
#endif				
	//待写数据和已经写进的数据比较
	return (DataToWrite == checkData)?0:-1;
}

int SH367309_WriteRamData(uint8_t WriteAddr,uint8_t DataToWrite)
{
	uint8_t checkData = 0;
	uint8_t i = 0;
	uint8_t DataBuffer[4] = {SH_ADDRESS,WriteAddr,DataToWrite,0};
	DataBuffer[3] = CRC8(DataBuffer, 3);

	SH367309_I2C_Start();  	
	for(i=0;i<4;i++)
	{
		SH367309_I2C_SendByte(DataBuffer[i]); //发送器件地址0XA0,写数据 		 
		SH367309_I2C_WaitAck();		
	}
	SH367309_I2C_Stop();//产生一个停止条件 	  
	LL_mDelay(5);
	SH367309_ReadRegVal(WriteAddr,&checkData,1);
	if(DataToWrite == checkData)
	{
#if(DBG_Printf_SH30X==1)	
		RS485_RxDen;
		printf("Write %2x :%x  r %x\r\n",WriteAddr,DataToWrite,checkData);
		LL_mDelay(2);
		RS485_RxEn;
#endif
		return 0;
	}
	else
	{
		
#if(DBG_Printf_SH30X==1)	
		RS485_RxDen;
		printf("SH367309_Write ERR %2x \r\n",WriteAddr);
		LL_mDelay(2);
		RS485_RxEn;
#endif
	}
	return -1;
}


uint8_t SH367309_ReadRegVal(uint8_t Addr,uint8_t* readBuf,uint8_t len)
{
	int retval = 0;
	uint8_t SampCnt= 0;
	do 
	{
		retval = SH367309_ReadData(Addr,readBuf,len);
		SampCnt++;
	}
	while((retval != 0)&&(SampCnt<3));//如果读取错误 连续读3次
	if(SampCnt>=3)
	{
		//rt_kprintf("SH367309 ReadRegVal Err %X\r\n",Addr);
	}
	return retval;		//返回0成功
}

void SH_Reset(void)
{				  
	uint8_t i = 0;
	uint8_t DataBuffer[4] = {SH_ADDRESS,0xEA,0XC0,0};
	DataBuffer[3] = CRC8(DataBuffer, 3);

	SH367309_I2C_Start();  	
	for(i=0;i<4;i++)
	{
		SH367309_I2C_SendByte(DataBuffer[i]);   //发送器件地址0XA0,写数据 		 
		SH367309_I2C_WaitAck();
	}
	
	SH367309_I2C_Stop();//产生一个停止条件 	 
	//printf("SH Reset\r\n");	
}

void SH_Get_CellVolts(uint16_t * buf)
{
	int i=0;
	uint8_t  ReadRegBuff[64];
	S_HALFWORD halfword;
	SH367309_ReadRegVal(REG_CELL1H,ReadRegBuff,CFG_Cell_NUM*2);

	for(i=0;i<CFG_Cell_NUM;i++)
	{
		halfword.bytes.byte_h = ReadRegBuff[i*2];
		halfword.bytes.byte_l = ReadRegBuff[i*2+1];//
		
		buf[i]=halfword.halfword*5/32;
	}
}


/**
  ******************************************************************************
  * 不带电流校准的CADC寄存器
  ******************************************************************************
  */
int16_t SH_Get_Current(void)
{
	int16_t tempCurr=0;
//	uint8_t state= 0;
	uint8_t  ReadRegBuff[2];
//	S_HALFWORD halfword;
//ZHQL_1013
	int32_t curr = 0;
	SH367309_ReadRegVal(REG_CURH,ReadRegBuff,2);
	
	tempCurr=(int16_t)( ReadRegBuff[0]<<8)|( ReadRegBuff[1] );
	//printf("tempCurr=%d\r\n",tempCurr);
	
//ZHQL_1013
	if(GetBit(tempCurr,15)==0)// 0 充电 ，1 放电
	{
		curr=((abs(tempCurr)*(1000L*10000/CFG_CURR_RES)/(26837/2)));
	}
	else
	{
		curr=0-((abs(tempCurr)*(1000L*10000/CFG_CURR_RES)/(26837/2)));
	}
	
//ZHQL_1013
  return (int16_t)(curr);
}


/**
  ******************************************************************************
  * 读取CADC寄存器并返回电流值
	* 国标规定放电为+、充电为-
	*	但CADC寄存器：CDATA.15为符号位，“1”表示放电；“0”表示充电
  ******************************************************************************
  */
int16_t SH_Get_CADCCurrent(void)
{
	uint16_t tempCurr=0;
	uint8_t state= 0;		// 0充电 1放电
	uint8_t ReadRegBuff[2];
	int16_t curr = 0;
	
	SH367309_ReadRegVal(REG_CADCDH,ReadRegBuff,2);
	
	tempCurr=(uint16_t)(ReadRegBuff[0]<<8)|(ReadRegBuff[1]);
	state=GetBit(tempCurr,15);
	
	//在静态下获取CADC误差补偿值
	if((syspara.batStat==STATE_STATIC)&&state)
	{
		syspara.CADCDisCHGOffset=tempCurr;
		if(syspara.CADCDisCHGOffset>0xFFF8) syspara.CADCCHGOffset=-8;
		else syspara.CADCCHGOffset=+6;
		//syspara.CADCCHGOffset=(0xFFFF-syspara.CADCDisCHGOffset)*2;
	}
	
	#if(DEBUG_CADC)
		rt_kprintf("CADC=%04X  ",tempCurr);
		rt_kprintf("CADCdsgOffset=%04X ",syspara.CADCDisCHGOffset);
		rt_kprintf("CADCchgOffset=%d\r\n",syspara.CADCCHGOffset);
	#endif

	if(state) curr = -(syspara.CADCDisCHGOffset-tempCurr)*176/100;		//放电
	//if(state) curr = -(0xFFF0-tempCurr)*176/100;		//放电
	//else curr =(tempCurr+6)*17857/10000;						//充电
	else curr =(tempCurr+syspara.CADCCHGOffset)*17857/10000;						//充电
	
	if(abs(curr)<30) return 0;
	else return curr;
}

void SH_Set_Balance(uint16_t BalanceFlag)//待修改0x5555
{

	SH367309_WriteRamData(REG_BALANCEH,((BalanceFlag>>8)&0xff));
	SH367309_WriteRamData(REG_BALANCEL,(BalanceFlag&0xff));
}

void SH_Set_CONF(uint8_t val)
{
	uint8_t i = 0;
	uint8_t DataBuffer[4] = {SH_ADDRESS,REG_CONF,val,0};
	DataBuffer[3] = CRC8(DataBuffer, 3);

	SH367309_I2C_Start();  	
	for(i=0;i<4;i++)
	{
		SH367309_I2C_SendByte(DataBuffer[i]);   //发送器件地址0XA0,写数据 		 
		SH367309_I2C_WaitAck();		
	}
	SH367309_I2C_Stop();//产生一个停止条件 

}

//CHGMOS、DSGMOS控制
void SH_MOSCtrl(uint8_t CHGCtrl,uint8_t DSGCtrl)
{
	CONF_Reg.CONF_Bits.IDLE=0;
	CONF_Reg.CONF_Bits.SLEEP=0;
	CONF_Reg.CONF_Bits.ENWDT=0;
	CONF_Reg.CONF_Bits.CADCON=1;
	CONF_Reg.CONF_Bits.CHGMOS=CHGCtrl;
	CONF_Reg.CONF_Bits.DSGMOS=DSGCtrl;
	SH367309_WriteRamData(REG_CONF,CONF_Reg.Vaule);		
}

void SH_Set_IDLE(void)
{
	CONF_Reg.CONF_Bits.IDLE=1;
	CONF_Reg.CONF_Bits.SLEEP=0;
	CONF_Reg.CONF_Bits.ENWDT=0;
	CONF_Reg.CONF_Bits.CADCON=0;
	CONF_Reg.CONF_Bits.OCRC=0;
	
	SH_Set_CONF(CONF_Reg.Vaule);		
}


void SH_SLEEP(void)
{
	CONF_Reg.CONF_Bits.IDLE=0;
	CONF_Reg.CONF_Bits.SLEEP=1;
	CONF_Reg.CONF_Bits.ENWDT=0;
	CONF_Reg.CONF_Bits.CADCON=0;
	CONF_Reg.CONF_Bits.CHGMOS=0;
	CONF_Reg.CONF_Bits.DSGMOS=0;
	CONF_Reg.CONF_Bits.PCHMOS=0;
	CONF_Reg.CONF_Bits.OCRC=0;
	
	SH_Set_CONF(CONF_Reg.Vaule);		
}

//TABLETEMP表数量
#define TABLETEMP_COUNT  (sizeof(SH_TEMP_TABLE)/sizeof(SH_TEMP_TABLE[0]))

static uint8_t SH_TempConvert( uint16_t RT )
{
	uint8_t j;
	uint8_t Tempdata;
	/*查找温度*/
	
	for( j = 0; ( RT < SH_TEMP_TABLE[j] ) && ( j < TABLETEMP_COUNT ); j++ );
	if( j == 0 || j > TABLETEMP_COUNT ) /*判断探头未接入//AD采集的电压为高表示空探头*/
	{
		Tempdata = 0xfe ; /*表示探头故障*/
	}
	else
	{
		Tempdata = j-40; /*正常的温度采样值 = SH_TEMP_TABLE[]第几个元素*/
	}
	return Tempdata;
}

/*
void SH_Get_CellTemps(uint8_t * buf)
{
	uint8_t  ReadRegBuff[6];
	S_HALFWORD halfword;	//TEMP1寄存器值，值越大温度越低

	int i = 0;
	uint16_t temp = 0;
	SH367309_ReadRegVal(REG_TEMP1H,ReadRegBuff,6);
	
	for(i=0;i<3;i++)
	{
		halfword.bytes.byte_h = ReadRegBuff[i*2];
		halfword.bytes.byte_l = ReadRegBuff[i*2+1];
		
		//RT 外部热敏电阻阻值，单位x10Ω，对应SH_TEMP_TABLE[]中的值
		temp=(halfword.halfword*(680L+5L*SHTempCoeff))/(32768-halfword.halfword);
		buf[i] = SH_TempConvert(temp);
	}
#if(DBG_Printf_Temp==1)
	RS485_RxDen;
	printf("SH_Get_CellTemps：%dC %dC %dC \r\n",buf[0],buf[1],buf[2]);
	LL_mDelay(2);
	RS485_RxEn;
#endif
}
*/

void SH_Get_CellTemps()
{
	uint8_t  ReadRegBuff[6];
	S_HALFWORD halfword;	//TEMP1寄存器值，值越大温度越低

	int16_t temp = 0;
	SH367309_ReadRegVal(REG_TEMP1H,ReadRegBuff,6);
	
	for(u8 i=0;i<3;i++)
	{
		halfword.bytes.byte_h = ReadRegBuff[i*2];
		halfword.bytes.byte_l = ReadRegBuff[i*2+1];
		
		//RT 外部热敏电阻阻值，单位x10Ω，对应SH_TEMP_TABLE[]中的值
		temp=(halfword.halfword*(680L+5L*SHTempCoeff))/(32768-halfword.halfword);
		//buf[i] = SH_TempConvert(temp);
		syspara.cellTemp[i]=SH_TempConvert(temp);
		//rt_kprintf("T%d=%d℃  ",i+1,syspara.cellTemp[i]);
	}
	syspara.tempMax = CacMax(syspara.cellTemp[0],syspara.cellTemp[1],syspara.cellTemp[2]);
	syspara.tempMin = CacMin(syspara.cellTemp[0],syspara.cellTemp[1],syspara.cellTemp[2]);
	syspara.tempAvg = (syspara.cellTemp[0]+syspara.cellTemp[1]+syspara.cellTemp[2])/3;

}


void SH_Read_Alarm(void)
{
	uint8_t retValue= 0xff;
	uint8_t reg[3] = {0};
	retValue=SH367309_ReadRegVal(REG_BSTATUS1,reg,3);	
	if(retValue==0)
	{
		shAlarm.bits.O_V = GetBit(reg[0],0);
		shAlarm.bits.U_V = GetBit(reg[0],1);
		shAlarm.bits.O_C_D = GetBit(reg[0],2);
		shAlarm.bits.O_C_C = GetBit(reg[0],4);
		shAlarm.bits.S_C_D = GetBit(reg[0],5);
		
		shAlarm.bits.U_T_C = GetBit(reg[1],0);
		shAlarm.bits.O_T_C = GetBit(reg[1],1);
		shAlarm.bits.U_T_D = GetBit(reg[1],2);
		shAlarm.bits.O_T_D = GetBit(reg[1],3);
		
		shAlarm.bits.U_V_NACHG = GetBit(reg[2],3);
		
		syspara.chgMos = GetBit(reg[2],1);
		syspara.dsgMos = GetBit(reg[2],0);
			
		sysflag.bits.CHGingFlag = GetBit(reg[2],7);
		sysflag.bits.DSGingFlag = GetBit(reg[2],6);
	}
	else
	{
		//printf("SH_Read_Alarm ERR!!!\r\n");
	}
	//printf("SH_BSTATUS: %02x,%02x,%02x\r\n",reg[0],reg[1],reg[2]);
}

#if(CFG_DEF_WRITEEEP)
void SHA_EEPROM_Set(void)
{
	int i=0;
	uint8_t WriteCnt= 0;
	uint8_t WriteFlag= 0;
	uint8_t SampCnt= 0;
	int retval = 0;
	
	uint8_t SHA_READ_EEPOM_MAP[27];		//读出的EEPROM寄存器
	uint8_t SHA_WRITE_EEPOM_MAP[27];	//待写EEPROM寄存器
	
	SCONF1_Reg_t 				 SCONF1;
	SCONF2_Reg_t 				 SCONF2;
	OVR_Threshold_Reg_t  OvrThreshold;  
	OV_Threshold_Reg_t	 OvThreshold;
	UV_Threshold_Reg_t   UvThreshold;
	UVR_Threshold_Reg_t  UvrThreshold;
	PFV_Threshold_Reg_t  PFV_Threshold;
	L0V_Threshold_Reg_t  L0V_Threshold;  
	BALV_Threshold_Reg_t BALV_Threshold;
	OCD1_Reg_t           OCD1V_Reg;
	OCD2_Reg_t           OCD2V_Reg;
	PFV_Threshold_Reg_t	 PFV_Reg;
	SCVSCT_Reg_t         SCVSCT_Reg;
	OCCVOCCT_Reg_t       OCCVOCCT_Reg;  
	MOST_OCRT_PFT_Reg_t  MOST_OCRT_PFT_Reg;
	
	rt_thread_mdelay(250);
	
	//先读取EEPROM
	do 
	{
		retval = SH367309_ReadData(REG_SCONF1,SHA_READ_EEPOM_MAP,26);//读出全部26个寄存器
		SampCnt++;
	}
	while((retval != 0)&&(SampCnt<3));//如果读取错误 连续读3次
	if(SampCnt>=3) 
	{
		rt_kprintf("EEprom Read ERR\r\n");
	}
	
	SHA_READ_EEPOM_MAP[REG_TR]= (SHA_READ_EEPOM_MAP[REG_TR]&0x7f);	//温度参考电阻系数置位
	rt_kprintf("EEP TR=%d\r\n",SHA_READ_EEPOM_MAP[REG_TR]);
	
	//0x00系统配置寄存器1 SCONF1
	SCONF1.Vaule=0;
	SCONF1.SCONF1_Bits.CN=CFG_Cell_NUM;
	SCONF1.SCONF1_Bits.BAL=CFG_SH_BAL;
	SCONF1.SCONF1_Bits.OCPM=CFG_SH_OCPM;
	SCONF1.SCONF1_Bits.ENMOS=CFG_SH_ENMOS;
	SCONF1.SCONF1_Bits.ENPCH=CFG_SH_ENPCH;
	SHA_WRITE_EEPOM_MAP[REG_SCONF1]=SCONF1.Vaule;
	
	//0x01系统配置寄存器2 SCONF2
	SCONF2.Vaule=0;
	SCONF2.SCONF2_Bits.EUVR=CFG_SH_EUVR;
	SCONF2.SCONF2_Bits.OCRA=CFG_SH_OCRA;
	SCONF2.SCONF2_Bits.CTLC=CFG_SH_CTLC;
	SCONF2.SCONF2_Bits.DIS_PF=CFG_SH_DIS_PF;
	SCONF2.SCONF2_Bits.UV_OP=CFG_SH_UV_OP;
	SCONF2.SCONF2_Bits.E0VB=CFG_SH_E0VB;
	SHA_WRITE_EEPOM_MAP[REG_SCONF2]=SCONF2.Vaule;
	
	//0x02-0x03过充电保护电压/过充电保护延时/负载释放延时设置寄存器
	OvThreshold.Vaule=0;
	OvThreshold.OVT_Field.OV=CFG_SH_OV/5;
	OvThreshold.OVT_Field.LDRT=CFG_SH_LDRT;
	OvThreshold.OVT_Field.OVT=CFG_SH_OVT;
	SHA_WRITE_EEPOM_MAP[REG_OVT_LDRT_OVH]=OvThreshold.Vaule>>8;
	SHA_WRITE_EEPOM_MAP[REG_OVL]=OvThreshold.Vaule&0xff;
	
	//0x04-0x05过充电恢复电压/过放电保护延时设置寄存器
	OvrThreshold.Vaule=0;
	OvrThreshold.OVR_Field.OVR=CFG_SH_OVR/5;
	OvrThreshold.OVR_Field.UVT=CFG_SH_UVT;
	SHA_WRITE_EEPOM_MAP[REG_UVT_OVRH]=OvrThreshold.Vaule>>8;
	SHA_WRITE_EEPOM_MAP[REG_OVRL]=OvrThreshold.Vaule&0xff;
	
	//0x06过放电保护电压设置寄存器
	UvThreshold= CFG_SH_UV/20;
	SHA_WRITE_EEPOM_MAP[REG_UV]=UvThreshold;
	
	//0x07过放电恢复电压设置寄存器
	UvrThreshold=CFG_SH_UVR/20;
	SHA_WRITE_EEPOM_MAP[REG_UVR]=UvrThreshold;
	
	//0x08平衡开启电压设置寄存器
	BALV_Threshold=CFG_SH_BALV/20;
	SHA_WRITE_EEPOM_MAP[REG_BALV]=BALV_Threshold;
	
	//0x09预充电电压设置寄存器
	PFV_Threshold=CFG_SH_PREV/20;
	SHA_WRITE_EEPOM_MAP[REG_PREV]=PFV_Threshold;	
	
	//0x0A低电压禁止充电电压设置寄存器
	L0V_Threshold=CFG_SH_L0V/20;
	SHA_WRITE_EEPOM_MAP[REG_L0V]=L0V_Threshold;	
	
	//0x0B二次过充电保护电压设置寄存器
	PFV_Reg=CFG_SH_PFV/20;
	SHA_WRITE_EEPOM_MAP[REG_PFV]=PFV_Reg;
	
	//0x0C放电过流1设置寄存器
	OCD1V_Reg.Vaule=0;
	OCD1V_Reg.OCD1_Field.OCD1V=CFG_SH_OCD1V;
	OCD1V_Reg.OCD1_Field.OCD1T=CFG_SH_OCD1T;
	SHA_WRITE_EEPOM_MAP[REG_OCD1V_OCD1T]=OCD1V_Reg.Vaule;
	
	//0x0D放电过流2设置寄存器
	OCD2V_Reg.Vaule=0;
	OCD2V_Reg.OCD2_Field.OCD2V=CFG_SH_OCD2V;
	OCD2V_Reg.OCD2_Field.OCD2T=CFG_SH_OCD2T;
	SHA_WRITE_EEPOM_MAP[REG_OCD2V_OCD2T]=OCD2V_Reg.Vaule;
	
	//0x0E短路保护设置寄存器
	SCVSCT_Reg.Vaule=0;
	SCVSCT_Reg.SCVSCT_Field.SCT=CFG_SH_SCT;
	SCVSCT_Reg.SCVSCT_Field.SCV=CFG_SH_SCV;
	SHA_WRITE_EEPOM_MAP[REG_SCV_SCT]=SCVSCT_Reg.Vaule;
	
	//0x0F充电过流设置寄存器
	OCCVOCCT_Reg.Vaule=0;
	OCCVOCCT_Reg.OCCVOCCT_Field.OCCT=CFG_SH_OCCT;
	OCCVOCCT_Reg.OCCVOCCT_Field.OCCV=CFG_SH_OCCV;
	SHA_WRITE_EEPOM_MAP[REG_OCCV_OCCT]=OCCVOCCT_Reg.Vaule;
	
	//0x10充放电过流自动恢复/二次过充电保护延时设置寄存器
	MOST_OCRT_PFT_Reg.Vaule=0;
	MOST_OCRT_PFT_Reg.MOST_OCRT_PFT_Bits.CHS=CFG_SH_CHS;
	MOST_OCRT_PFT_Reg.MOST_OCRT_PFT_Bits.MOST=CFG_SH_MOST;
	MOST_OCRT_PFT_Reg.MOST_OCRT_PFT_Bits.OCRT=CFG_SH_OCRT;
	MOST_OCRT_PFT_Reg.MOST_OCRT_PFT_Bits.PFT=CFG_SH_PFT;
	SHA_WRITE_EEPOM_MAP[REG_MOST_OCRT_PFT]=MOST_OCRT_PFT_Reg.Vaule;

	//0x11充电高温保护设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_OTC]=CFG_SH_OTC*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_OTC);
	
	//0x12充电高温保护释放设置寄存器	
	SHA_WRITE_EEPOM_MAP[REG_OTCR]=CFG_SH_OTCR*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_OTCR);
	
	//0x13充电低温保护设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_UTC]=(CFG_SH_UTC*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_UTC))&0xFF;

	//0x14充电低温保护释放设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_UTCR]=(CFG_SH_UTCR*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_UTCR))&0xFF;
	
	//0x15放电高温保护设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_OTD]=CFG_SH_OTD*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_OTD);
	
	//0x16放电高温保护释放设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_OTDR]=CFG_SH_OTDR*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_OTDR);
	
	//0x17放电低温保护设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_UTD]=(CFG_SH_UTD*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_UTD))&0xFF;
	
	//0x18放电低温保护释放设置寄存器
	SHA_WRITE_EEPOM_MAP[REG_UTDR]=(CFG_SH_UTDR*512/(680+5*SHA_READ_EEPOM_MAP[REG_TR]+CFG_SH_UTDR))&0xFF;

	for(i=REG_SCONF1;i<REG_TR;i++)
	{
#if(DEBUG_EEP)
		rt_kprintf("EEP READ-WRTITE %02X-%02X\r\n",SHA_READ_EEPOM_MAP[i],SHA_WRITE_EEPOM_MAP[i]);
#endif
		if(SHA_READ_EEPOM_MAP[i]!=SHA_WRITE_EEPOM_MAP[i])	//比较，有一个不一样就写EEPROM
		{		
			WriteFlag = 1;	//写EEPROM标志
		}
	}
	if(WriteFlag)	//开始写EEPROM寄存器
	{
		rt_kprintf("EEprom Write Enable\r\n");
		
		VPRO(1);	
		rt_thread_mdelay(10);
		
		for(i=REG_SCONF1;i<REG_TR;i++)
		{
			if(SHA_READ_EEPOM_MAP[i]!=SHA_WRITE_EEPOM_MAP[i])
			{
				WriteCnt = 0;
				do 
				{
					//只改写不一样的EEPROM寄存器
					retval = SH367309_WriteEEpromData(i,SHA_WRITE_EEPOM_MAP[i]);
					
					#if(DEBUG_EEP)
						rt_kprintf("EEp %X Changed!\r\n",i);
					#endif
					
					WriteCnt++;
				}
				while((retval != 0)&&(WriteCnt<3));//如果读取错误 连续读3次
				if(WriteCnt>=3)
				{
#if(DBG_Printf_SH30X==1)
					printf("SH W EEp err %X\r\n",i);
#endif				
				}
				else
				{
#if(DBG_Printf_SH30X==1)
					printf("SH W EEp OK %d\r\n",i);
#endif				
				}
			}
		}
		
	}
	else
	{
		rt_kprintf("SH EEprom no change\r\n");
	}
	
}
#endif

void SH_Set_Default(void)
{
	CONF_Reg.CONF_Bits.CADCON=1;
	CONF_Reg.CONF_Bits.CHGMOS=1;
	CONF_Reg.CONF_Bits.DSGMOS=1;
	CONF_Reg.CONF_Bits.PCHMOS=1;
	CONF_Reg.CONF_Bits.ENWDT=0;
	CONF_Reg.CONF_Bits.IDLE=0;
	CONF_Reg.CONF_Bits.SLEEP=0;
	SH_Set_CONF(CONF_Reg.Vaule);
}

void SH367309_Config(void)
{
	int8_t ret= 0;
	uint8_t value= 0;
#if(CFG_DEF_WRITEEEP)
	SHA_EEPROM_Set();		//烧录EEPROM
	VPRO(0);
	rt_thread_mdelay(10);
	SH_Reset();
#endif
	VPRO(0);
	rt_thread_mdelay(250);
	SH_Set_Default();
	
	//读取内部温度参考值TR
	ret= SH367309_ReadRegVal(REG_TR,&value,1);
	if(ret==0)
	{
		SHTempCoeff = value&0x7f;		//清除无用最高位
		rt_kprintf("SHTempCoeff=%d\r\n",SHTempCoeff);
	}
	
	//读取平衡功能寄存器值
	ret= SH367309_ReadRegVal(REG_SCONF1,&value,1);
	if(ret==0)
	{
		sysflag.bits.MCUCtrolBal=GetBit(value,4);
		rt_kprintf("MCUCtrolBal=%d\r\n",sysflag.bits.MCUCtrolBal);
	}
}










