/**
  *****************************************************************************
  *                              IIC���豸���ƺ���
  *
  *                       (C) Copyright 2016-2020, ***
  *                             All Rights Reserved
  *****************************************************************************
  *
  * @File    : hardiic_reg.c
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


#include "bsp_hardiic_reg.h"


/******************************************************************************
                                 �������
******************************************************************************/

I2C_DEVICE_TypeDef i2c_dev;

//
//I2C�����ж��õ�����
//
uint8_t I2CAddressOffset = 0;  //����������ַ
uint8_t i2c_sendcount = 0;
uint8_t I2C_DEVICE_REGADDRESS = 0; //���ռĴ�����ַ
uint8_t g_ReceiveBuff_pui[3];
uint8_t g_Receivecount;

uint8_t I2C2TestBuff[100]={0};

//
//�Ĵ����б�
//
uint32_t IIC_TEST_ISRcount[10];





/**
  *****************************************************************************
  * @Name   : �¼��жϷ�����
  *
  * @Brief  : none
  *
  * @Input  : none
  *
  * @Output : none  ���ֽ���ǰ��
  *
  * @Return : none
  *****************************************************************************
**/
void	I2C2_IRQHandler(void)
{
	uint32_t temp = 0;
//	static unsigned char ls_ReceiveCount_ui8 = 0;
	
	/*!< Read Event Flag */
	temp = I2C_DEVICE->ISR;
	i2c_dev.I2C_EventStatus = (uint32_t)(temp & I2C_STATUS_EVT_MASK);
	i2c_dev.I2C_ErrorStatus = (uint32_t)(temp & I2C_STATUS_ERR_MASK);
//	RS485_RxDen;
//	printf("IICTEST:%x %x\r\n",i2c_dev.I2C_EventStatus,i2c_dev.I2C_ErrorStatus);
//	LL_mDelay(2);
//	RS485_RxEn;
	IIC_TEST_ISRcount[0]=1;
	IIC_TEST_ISRcount[1]=0;
	/* ==================================================== */
	/*                    ��ַ�����ж�                       */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_ADDR) != 0)
	{
		#if I2C_STRETCH_EN
		{
			if ((I2C_DEVICE->ISR & I2C_ISR_DIR) != 0)  /*!< Slave enter transmitter mode, Host read data */
			{
				I2C_DEVICE->ISR |= I2C_ISR_TXE;  /*!< set TXE bit */
				i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_DIR_SEND;
			}
			else  /*!< Host write data (slave receive data from host) */
			{
				i2c_dev.I2C_DeviceFlag &= ~I2C_DEVICE_FLAG_DIR_SEND;
			}
		}
		#else
		{
			if ((I2C_DEVICE->ISR & I2C_ISR_DIR) != 0)  /*!< Slave enter transmitter mode, Host read data */
			{
				i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_DIR_SEND;
				I2C_DEVICE->ISR |= I2C_ISR_TXE;  /*!< set TXE bit, I2C_TXDR empty */
				if(I2C_DEVICE_REGADDRESS==0x0100)
				{
					I2C_DEVICE->TXDR = (SysReg_Type[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
				}
				else if(I2C_DEVICE_REGADDRESS==0x0200)
				{
					I2C_DEVICE->TXDR = (SysReg_VF[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
				}
				else if(I2C_DEVICE_REGADDRESS==0x0300)
				{
					I2C_DEVICE->TXDR = (SysReg_VH[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
				}
				else
				{
					I2C_DEVICE->TXDR = (SysRegData[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%256]>>(((i2c_sendcount%2)*8)&0xff));
				}
				//i2c_sendcount++;
			}
			else  //Receiver mode
			{
				i2c_dev.I2C_DeviceFlag &= ~I2C_DEVICE_FLAG_DIR_SEND;
			}
			
		}
		#endif
		LL_I2C_ClearFlag_ADDR(I2C_DEVICE);/*!< set ADDRCF */
	}
	
	/* ==================================================== */
	/*                   �ӻ����������ж�                    */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_TXIS) != 0)
	{
		i2c_dev.Nodatatime= 0;
		//
		//���ݲ�ͬ�ļĴ�����ַ���������ݣ�������ȡ����
		//
		if(I2C_DEVICE_REGADDRESS==0x0100)
		{
			I2C_DEVICE->TXDR = (SysReg_Type[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
		}
		else if(I2C_DEVICE_REGADDRESS==0x0200)
		{
			I2C_DEVICE->TXDR = (SysReg_VF[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
		}
		else if(I2C_DEVICE_REGADDRESS==0x0300)
		{
			I2C_DEVICE->TXDR = (SysReg_VH[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%20]>>(((i2c_sendcount%2)*8)&0xff));
		}
		else
		{
			I2C_DEVICE->TXDR = (SysRegData[(I2C_DEVICE_REGADDRESS+i2c_sendcount/2)%256]>>(((i2c_sendcount%2)*8)&0xff));
		}
		i2c_sendcount++;
	}
	
	/* ==================================================== */
	/*                   �ӻ����������ж�                    */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_RXNE) != 0)
	{
		g_ReceiveBuff_pui[g_Receivecount]= I2C_DEVICE->RXDR;
		g_Receivecount++;
		i2c_sendcount= 0;
		I2C_DEVICE_REGADDRESS= g_ReceiveBuff_pui[0];
		if(g_Receivecount==2)
		{
			I2C_DEVICE_REGADDRESS = ((g_ReceiveBuff_pui[1]<<8)|g_ReceiveBuff_pui[0]);
		}
	}
	
	/* ==================================================== */
	/*                      ��Ӧ���ж�                       */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_NACKF) != 0)
	{
		g_Receivecount= 0;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_NACK;
	}
	
	/* ==================================================== */
	/*                     ֹͣ�ź��ж�                      */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_STOPF) != 0)
	{
		LL_I2C_ClearFlag_NACK(I2C_DEVICE);
		if ((i2c_dev.I2C_DeviceFlag & I2C_DEVICE_FLAG_DIR_SEND) != 0)  /*!< Slave send to host */
		{
			#if I2C_STRETCH_EN
			//do nothing
			#else
			I2C1->ISR |= I2C_ISR_TXE;
			I2C1->ISR |= I2C_ISR_TXIS;
			#endif
			i2c_dev.I2C_DeviceFlag &= ~I2C_DEVICE_FLAG_DIR_SEND;
			i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_READ;
		}
		else
		{
			i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_WRITE;  //�ò�����־
		}

		g_Receivecount= 0;
		LL_I2C_ClearFlag_STOP(I2C_DEVICE);  /*!< set STOPCF */
	}
	
	
	/* ==================================================== */
	/*                       �����ж�                        */
	/* ==================================================== */
	//
	//���ߴ���
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_BERR) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_BERRCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
	//
	//�ܲ�ʧ��
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_ARLO) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_ARLOCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
	//
	//���
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_OVR) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_OVRCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
}














/**
  *****************************************************************************
  * @Name   : IIC���߳�ʼ��
  *
  * @Brief  : none
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
**/
void I2C_DeviceInit(void)
{

	Hard_I2C_Init(I2C_DEVICE, I2C_DEVICEADDRESS, I2C_MAXFREQUENCY_HZ);
}

/**
  *****************************************************************************
  * @Name   : IIC������ס
  *
  * @Brief  : none
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
**/
void I2C_DeviceLock(void)
{
	I2C_DEVICE->CR2 |= I2C_CR2_NACK;
}

/**
  *****************************************************************************
  * @Name   : IIC���߽���
  *
  * @Brief  : none
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
**/
void I2C_DeviceUnLock(void)
{
	I2C_DEVICE->CR2 &= ~I2C_CR2_NACK;
}
