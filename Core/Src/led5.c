#include "main.h"

void LED5Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	GPIO_InitStruct.Mode=LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	LEDALLNULL();
}

void LEDALLNULL()
{
	LL_GPIO_SetPinOutputType(GPIOB,LL_GPIO_PIN_11|LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15,LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_11|LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15);
}

void LEDNULL(uint32_t Pin)
{
	LL_GPIO_SetPinOutputType(GPIOB,Pin,LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetOutputPin(GPIOB,Pin);
}

void LEDH(uint32_t Pin)
{
	LL_GPIO_SetPinOutputType(GPIOB,Pin,LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetOutputPin(GPIOB,Pin);
}

void LEDL(uint32_t Pin)
{
	LL_GPIO_SetPinOutputType(GPIOB,Pin,LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_ResetOutputPin(GPIOB,Pin);
}

void DisplayCharge(void)
{
	LEDALLNULL();
	LEDH(LEDP3);LEDL(LEDP5);LED5Delay;
}

void DisplayPercent(void)
{
	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP5); LED5Delay;
}

void DisplaySel1(void)
{
	LEDALLNULL();LEDH(LEDP3);LEDL(LEDP4); LED5Delay;
	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP4); LED5Delay;
}

void DisplaySel2(uint8_t num)
{
	switch(num)
	{
		case 0:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3); LED5Delay;	
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP2);	LED5Delay;
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;
				break;	
		case 1:	LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;
				break;	
		case 2:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP2);	LED5Delay;	//E2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 3:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 4:	LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;	//F2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 5:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;	//F2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 6:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP2);	LED5Delay;	//E2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;	//F2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 7:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
				break;	
		case 8:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP2);	LED5Delay;	//E2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;	//F2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;	
		case 9:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP3);	LED5Delay;	//A2
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP2);	LED5Delay;	//B2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP3);	LED5Delay;	//C2
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP2);	LED5Delay;	//D2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP3);	LED5Delay;	//F2
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
				break;
		default: break;
	}
}

void DisplaySel3(uint8_t num)
{
	switch(num)
	{
		case 0:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP4);	LED5Delay;	//E3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
				break;	
		case 1:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
				break;	
		case 2:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP4);	LED5Delay;	//E3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 3:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 4:	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 5:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 6:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP4);	LED5Delay;	//E3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 7:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
				break;	
		case 8:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP4);	LED5Delay;	//E3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;	
		case 9:	LEDALLNULL();LEDH(LEDP1);LEDL(LEDP2);	LED5Delay;	//A3
						LEDALLNULL();LEDH(LEDP2);LEDL(LEDP1);	LED5Delay;	//B3
						LEDALLNULL();LEDH(LEDP1);LEDL(LEDP3);	LED5Delay;	//C3
						LEDALLNULL();LEDH(LEDP3);LEDL(LEDP1);	LED5Delay;	//D3
						LEDALLNULL();LEDH(LEDP4);LEDL(LEDP1);	LED5Delay;	//F3
						LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
				break;
		default:break;
	}
}

//等待显示SOC
void LED5DisplayWait()
{
	LEDALLNULL();LEDH(LEDP5);LEDL(LEDP4);	LED5Delay;	//G2
	LEDALLNULL();LEDH(LEDP5);LEDL(LEDP1);	LED5Delay;	//G3
	LEDALLNULL();LEDH(LEDP2);LEDL(LEDP5); LED5Delay;	//%
}

void LED5Display(uint8_t SOC,uint8_t state)
{
	DisplayPercent();	//显示百分比
	if(state==STATE_CHG) DisplayCharge(); //是否充电状态
	
	if(SOC>=100){ DisplaySel1(); DisplaySel2(0);DisplaySel3(0);}	//直接显示100
	else if(SOC<10) DisplaySel3(SOC);															//只显示个位数
	else DisplaySel2(SOC/10); DisplaySel3(SOC%10);								//正常显示两位数
}
