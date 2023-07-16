#include "main.h"


//����modbus��ʱ���,��Ϊ΢��С������20�ֽڷְ����͵�,��0.5msֻ�ܴ���20�ֽ����ڵ�����,ʵ����СԼ20ms��ʱ������
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
	
	//ʹ��TIM3�����ж�
	LL_TIM_EnableIT_UPDATE(TIM3);

	//ʹ��TIM3������
  //LL_TIM_EnableCounter(TIM3);
	LL_TIM_DisableCounter(TIM3);		//�ȹر�һ��,�����һ�ο����Ͳ����ж�
	
	// ����TIM3�ж����ȼ�
  NVIC_SetPriority(TIM3_IRQn,0);
	NVIC_EnableIRQ(TIM3_IRQn);

}
