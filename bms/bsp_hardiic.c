/**
  *****************************************************************************
  *                             STM32Ӳ��IIC���ƺ���
  *
  *                       (C) Copyright 2000-2020, ***
  *                             All Rights Reserved
  *****************************************************************************
  *
  * @File    : hardiic.c
  * @By      : �¹�
  * @Version : V1.0
  * @Date    : 2016 / 03 / 08
  *
  *****************************************************************************
  *
  *                                   Update
  *
  * @Version : V1.*
  * @By      : ***
  * @Date    : 20** / ** / **
  * @Brief   : ***
  *
  *****************************************************************************
**/


#include "bsp_hardiic.h"


/******************************************************************************
                                  �������
******************************************************************************/

//uint16_t iic_temp = 0;

/**
  *****************************************************************************
  * @Name   : Ӳ��IIC��ʼ��
  *
  * @Brief  : none
  *
  * @Input  : I2Cx:           IIC��
  *           SlaveAdd:       ��Ϊ���豸ʱʶ���ַ
  *           F103IIC1_Remap: ���F103��IIC1�Ƿ���ӳ��
  *                           0: ����ӳ��
  *                           1: ��ӳ�䡣PB.06 -> PB.08��PB.07 -> PB.09
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
**/
void Hard_I2C_Init(I2C_TypeDef* I2Cx, uint8_t SlaveAdd, uint32_t Freq_SCL)
{
//	NVIC_InitTypeDef NVIC_InitStructure;
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	uint32_t i2c_temp = 0;
	
	//
	//���ݲ�ͬ��I2C�豸���г�ʼ��
	//
	if (I2Cx == I2C2)
	{
		LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		/**I2C2 GPIO Configuration
		PB10   ------> I2C2_SCL
		PB11   ------> I2C2_SDA
		*/
		GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		//��λI2C�豸
		//
		SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST);
		CLEAR_BIT(RCC->APBRSTR1,  RCC_APBRSTR1_I2C2RST);
	}
	
	//
	//��ʼ��I2C�Ĵ���
	//
	I2Cx->CR1 &= ~I2C_CR1_PE;  /*!< Disable I2C */
	I2Cx->CR1 &= 0x00CFE0FF;
	
	/*!< ʱ����չ���� */
#if I2C_STRETCH_EN
	I2Cx->CR1 &= ~I2C_CR1_NOSTRETCH;  /*!< Enable stretch */
#else
	I2Cx->CR1 |= I2C_CR1_NOSTRETCH;  /*!< Disable stretch */
#endif
	
	I2Cx->TIMINGR = 0x00100000;  /*!< Timing register
									  standard mode(100KHz) 0x50E30000
									  fast mode(400KHz) 0x00100000 */
	I2Cx->CR1 |= I2C_CR1_PE;  /*!< Enable I2C */
	
	i2c_temp = 0;
	I2Cx->OAR1 = i2c_temp;
	i2c_temp = (uint32_t)(SlaveAdd & 0x00FF);
	I2Cx->OAR1 |= i2c_temp;  /*!< Slave Address */
	I2Cx->OAR1 |= I2C_OAR1_OA1EN;  /*!< Own Address1 enable */
	
//	I2Cx->OAR2 = 0; 
//	I2Cx->OAR2 = I2C_OAR2_OA2MSK;	
//	I2Cx->OAR2 = I2C_OAR2_OA2EN;
	
	I2Cx->CR2 &= 0x07FF7FFF;
	I2Cx->CR2 &= ~I2C_CR2_NACK;  /*!< ACK enable */
	
	//
	//�¼��ж����ȼ�����
	//
	
	NVIC_SetPriority(I2C2_IRQn, 0);
	NVIC_EnableIRQ(I2C2_IRQn);

	
	//
	//�����ж�
	//
	i2c_temp = 0;
	i2c_temp = (I2C_CR1_ERRIE/*!< Error interrupts enable */  |\
				I2C_CR1_STOPIE/*!< STOP detection Interrupt enable */ |\
				I2C_CR1_NACKIE/*!< Not acknowledge received Interrupt enable */ |\
				I2C_CR1_ADDRIE/*!< Address match Interrupt enable (slave only) */ |\
				I2C_CR1_RXIE/*!< RX Interrupt enable */ |\
				I2C_CR1_TXIE/*!< TX Interrupt enable */);
	I2Cx->CR1 |= i2c_temp;   
	I2Cx->TXDR= 0;
}
#if  0
{
	uint32_t i2c_temp = 0;
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	//
	//���ݲ�ͬ��I2C�豸���г�ʼ��
	//
	if(I2Cx==I2C2)
	{
		//
		//��λI2C�豸
		//
		
		LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		/**I2C2 GPIO Configuration
		PB10   ------> I2C2_SCL
		PB11   ------> I2C2_SDA
		*/
		GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
		LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		/* Peripheral clock enable */
		
		/* I2C2 interrupt Init */
		SET_BIT(RCC->APBRSTR1, RCC_APBRSTR1_I2C2RST);
		CLEAR_BIT(RCC->APBRSTR1,  RCC_APBRSTR1_I2C2RST);
	}
	//
	//��ʼ��I2C�Ĵ���
	//
		NVIC_SetPriority(I2C2_IRQn, 0);
		NVIC_EnableIRQ(I2C2_IRQn);
	LL_I2C_Disable(I2Cx);/*!< Disable I2C */
	
	LL_I2C_EnableSlaveByteControl(I2Cx);
	/*!< ʱ����չ���� */
	#if I2C_STRETCH_EN
	I2Cx->CR1 &= ~I2C_CR1_NOSTRETCH;  /*!< Enable stretch */
	#else
	I2Cx->CR1 |= I2C_CR1_NOSTRETCH;  /*!< Disable stretch */
	#endif
	
	I2Cx->TIMINGR = 0x00100000;  /*!< Timing register
	                                  standard mode(100KHz) 0x50E30000
	                                  fast mode(400KHz) 0x00100000 */
	LL_I2C_Enable(I2Cx);	/*!< Enable I2C */
	
	i2c_temp = 0;
	I2Cx->OAR1 = i2c_temp;
	i2c_temp = (uint32_t)(SlaveAdd & 0x00FF);
	I2Cx->OAR1 |= i2c_temp;  /*!< Slave Address */
	I2Cx->OAR1 |= I2C_OAR1_OA1EN;  /*!< Own Address1 enable */
	
//	I2Cx->OAR2 = 0; 
//  I2Cx->OAR2 = I2C_OAR2_OA2MSK;	
//	I2Cx->OAR2 = I2C_OAR2_OA2EN;
	
	I2Cx->CR2 &= 0x07FF7FFF;
	I2Cx->CR2 &= ~I2C_CR2_NACK;  /*!< ACK enable */
	LL_I2C_SetTransferSize(I2Cx,1);
	//
	//�¼��ж����ȼ�����
	//
	if (I2Cx == I2C2)
	{
		/* I2C2 interrupt Init */
		NVIC_SetPriority(I2C2_IRQn, 0);
		NVIC_EnableIRQ(I2C2_IRQn);
	}
	else
	{
		/* I2C2 interrupt Init */
		NVIC_SetPriority(I2C1_IRQn, 0);
		NVIC_EnableIRQ(I2C1_IRQn);
	}
	
	//
	//�����ж�
	//
	i2c_temp = 0;
	i2c_temp = (I2C_CR1_ERRIE/*!< Error interrupts enable */  |\
	            I2C_CR1_STOPIE/*!< STOP detection Interrupt enable */ |\
	            I2C_CR1_NACKIE/*!< Not acknowledge received Interrupt enable */ |\
	            I2C_CR1_ADDRIE/*!< Address match Interrupt enable (slave only) */ |\
	            I2C_CR1_RXIE/*!< RX Interrupt enable */ |\
	            I2C_CR1_TXIE/*!< TX Interrupt enable */);
	I2Cx->CR1 |= i2c_temp;
	I2Cx->TXDR= 0;
}
#endif

/**
  *****************************************************************************
  * @Name   : Ӳ��IIC�ж�ʹ��
  *
  * @Brief  : none
  *
  * @Input  : I2Cx:           IIC��
  *           SlaveAdd:       ��Ϊ���豸ʱʶ���ַ
  *                           0: ����ӳ��
  *                           1: ��ӳ�䡣PB.06 -> PB.08��PB.07 -> PB.09
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
**/
void Hard_I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	uint32_t i2c_temp = 0;

	//
	//�¼��ж����ȼ�����
	//
	if (I2Cx == I2C2)
	{
		NVIC_SetPriority(I2C2_IRQn, 0);
		NVIC_EnableIRQ(I2C2_IRQn);
	}
	else
	{
		NVIC_SetPriority(I2C1_IRQn, 0);
		NVIC_EnableIRQ(I2C1_IRQn);
	}
	
	
	//
	//�����ж�
	//
	i2c_temp = 0;
	i2c_temp = (I2C_CR1_ERRIE/*!< Error interrupts enable */  |\
	            I2C_CR1_STOPIE/*!< STOP detection Interrupt enable */ |\
	            I2C_CR1_NACKIE/*!< Not acknowledge received Interrupt enable */ |\
	            I2C_CR1_ADDRIE/*!< Address match Interrupt enable (slave only) */ |\
	            I2C_CR1_RXIE/*!< RX Interrupt enable */ |\
	            I2C_CR1_TXIE/*!< TX Interrupt enable */);
	
	if (NewState != DISABLE)
	{
		I2Cx->CR1 |= i2c_temp;
		LL_I2C_Enable(I2Cx);
	}
	else
	{
		I2Cx->CR1 &= ~i2c_temp;
		LL_I2C_Disable(I2Cx);
	}

}
