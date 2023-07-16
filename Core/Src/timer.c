#include "main.h"


//用于modbus超时检测,因为微信小程序是20字节分包发送的,用0.5ms只能处理20字节以内的数据,实测最小约20ms超时检测合适
void TIM3_Init(void)
{
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	
	//64*20000/64=20000us
	TIM_InitStruct.Prescaler = 64-1;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 20000-1;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_Init(TIM3,&TIM_InitStruct);
	
	//使能TIM3更新中断
	LL_TIM_EnableIT_UPDATE(TIM3);

	//使能TIM3计数器
  //LL_TIM_EnableCounter(TIM3);
	LL_TIM_DisableCounter(TIM3);		//先关闭一次,避免第一次开机就产生中断
	
	// 配置TIM3中断优先级
  NVIC_SetPriority(TIM3_IRQn,0);
	NVIC_EnableIRQ(TIM3_IRQn);

}
