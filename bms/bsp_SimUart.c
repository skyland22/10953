#include "main.h"

SimUARTSt  SUartInfo;
uint8_t ucAcquCx= 0;
uint8_t ucRecvTrueCx= 0;
//static uint8_t ucSendBitCx= 0;
//static uint8_t ucSendByteCx= 0;
 uint8_t ReceveAllow=0;


void UART2RxDataPro(uint16_t data)
{
	if(data!=0xffff)
	{
		SUartInfo.RecData[SUg
		artInfo.DataNum++]=data&0xff;	 
		SUartInfo.DataNum %=SIMUARTDATAMAX;
		SUartInfo.SUartIdelTime= 0;

	}
	else
	{
		if(SUartInfo.DataNum>0)
		{
			SUartInfo.rcvFlag=1;
			SUartInfo.RecdataCount=SUartInfo.DataNum;
			SUartInfo.DataNum=0;
		}
	}
}

uint8_t CHECK_BIT(void)
{
	uint8_t ret= 0xff;
	if(    ucAcquCx == 0)
	{
		ucAcquCx = 1;
		ret= 0xff;
	}
	ucAcquCx++;
	if(ucAcquCx >= DEF_BIT_SampCount)
	{
		ret = 1;
	}
	return ret;
}



void SUART_Protocol(void)
{
	uint8_t i = 0,cmd = 0;//,ret = 0;
	uint16_t len = 0;
	S_WORD sword;
	
	//printf("SUART_Protocol C= %d ",SUartInfo.RecdataCount);
	if(SUartInfo.RecdataCount<5)
	{
		SUartInfo.RecdataCount= 0;
		return ;
	}
	i++;
	
	SIFBUSData.SIFMode = SIF_MODE_GTDS;
	if(0x55 == SUartInfo.RecData[i++])
	{
		if(0xbb == SUartInfo.RecData[i++])
		{
			if(0x03 == SUartInfo.RecData[i++])
			{
				cmd = SUartInfo.RecData[i++];
				sword.word= 0;
				sword.bytes.byte_2 =  SUartInfo.RecData[i++];
				sword.bytes.byte_1 = SUartInfo.RecData[i++];
				len = sword.word;
				SUartInfo.RecData[0]=0xAA;
				//ret=
				BootCmd_Process(cmd,len);
			}
			else
			{
			//	printf("0X03 eRR \r\n");
			}
		}
		else
		{
			//printf("0XAA eRR \r\n");
		}
	}
	else
	{
//		printf("0X55 eRR \r\n");
	}
	//if(ret==0)
	//{
	//	for(i= 0;i<SUartInfo.RecdataCount;i++)
	//	{
	//	}
	//}
}





