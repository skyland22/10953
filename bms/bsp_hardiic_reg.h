/**
  *****************************************************************************
  *                              IIC���豸���ƺ���
  *
  *                       (C) Copyright 2016-2020, ***
  *                             All Rights Reserved
  *****************************************************************************
  *
  * @File    : hardiic_reg.h
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


#ifndef _hardiic_reg_h
#define _hardiic_reg_h

/**
  ****************************** Support C++ **********************************
**/
#ifdef __cplusplus
extern "C"{
#endif		
/**
  *****************************************************************************
**/


/******************************************************************************
                               �ⲿ����ͷ�ļ�
******************************************************************************/

#include "main.h"



/******************************************************************************
                          �Ƿ�����ڴ������ݷ��ط�Ӧ��
******************************************************************************/

#define I2C_NACK_ENABLE                          0

/******************************************************************************
                              ����I2C���������Ϣ
******************************************************************************/

#define I2C_MAXFREQUENCY_HZ                      (uint32_t)(100 * 1000)  //����Ƶ��

#define I2C_DEVICEADDRESS                        (uint8_t)0x16  //�豸��ַ

#define I2C_DEVICE                               I2C2
#define I2C_DEVICE_EVENT_IRQ                     void I2C2_IRQHandler(void)

#define I2C_DEVICE_DR_NULL_R                     0xFA
#define I2C_DEVICE_DR_NULL_S                     0xFB

#define I2C_STATUS_EVT_MASK                      (uint32_t)(0x000000FE)
#define I2C_STATUS_ERR_MASK                      (uint32_t)(0x00000700)

/******************************************************************************
                              ����Ĵ����б��С
******************************************************************************/

#define I2C_REG_TEST_SIZE                        10

//
//�Ĵ���ʶ���ַ
//
#define I2C_REG_TEST_ADD                         (uint8_t)0xF0



extern uint32_t IIC_TEST_ISRcount[];

/******************************************************************************
                              ����I2C���߲����ṹ��
******************************************************************************/

#define I2C_DEVICE_FLAG_DIR_SEND                 ((uint32_t)0x80000000)
#define I2C_DEVICE_FLAG_READ                     ((uint32_t)0x40000000)
#define I2C_DEVICE_FLAG_NACK                     ((uint32_t)0x20000000)
#define I2C_DEVICE_FLAG_WRITE                    ((uint32_t)0x10000000)
#define I2C_DEVICE_FLAG_ERROR                    ((uint32_t)0x08000000)

__packed typedef struct
{
	uint32_t I2C_DeviceFlag;  //���������и��ֱ�ʶ����
	
	uint32_t I2C_EventStatus;
	uint32_t I2C_ErrorStatus;
	uint32_t Nodatatime;
} I2C_DEVICE_TypeDef;

extern I2C_DEVICE_TypeDef i2c_dev;
extern unsigned char g_ReceiveBuff_pui[];
extern uint8_t I2C2TestBuff[100];

/******************************************************************************
                               �ⲿ���ù��ܺ���
******************************************************************************/

void I2C_DeviceRegisterInit(void);
void I2C_DeviceSetRegister(uint8_t iicreg, uint8_t Data);
uint8_t I2C_DeviceGetRegister(uint8_t iicreg);


void I2C_DeviceInit(void);
void I2C_DeviceLock(void);
void I2C_DeviceUnLock(void);


/**
  ****************************** Support C++ **********************************
**/
#ifdef __cplusplus
}
#endif
/**
  *****************************************************************************
**/


#endif
