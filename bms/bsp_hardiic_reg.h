/**
  *****************************************************************************
  *                              IIC从设备控制函数
  *
  *                       (C) Copyright 2016-2020, ***
  *                             All Rights Reserved
  *****************************************************************************
  *
  * @File    : hardiic_reg.h
  * @By      : 陈桂东
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
                               外部函数头文件
******************************************************************************/

#include "main.h"



/******************************************************************************
                          是否打开正在处理数据返回非应答
******************************************************************************/

#define I2C_NACK_ENABLE                          0

/******************************************************************************
                              定义I2C总线相关信息
******************************************************************************/

#define I2C_MAXFREQUENCY_HZ                      (uint32_t)(100 * 1000)  //总线频率

#define I2C_DEVICEADDRESS                        (uint8_t)0x16  //设备地址

#define I2C_DEVICE                               I2C2
#define I2C_DEVICE_EVENT_IRQ                     void I2C2_IRQHandler(void)

#define I2C_DEVICE_DR_NULL_R                     0xFA
#define I2C_DEVICE_DR_NULL_S                     0xFB

#define I2C_STATUS_EVT_MASK                      (uint32_t)(0x000000FE)
#define I2C_STATUS_ERR_MASK                      (uint32_t)(0x00000700)

/******************************************************************************
                              定义寄存器列表大小
******************************************************************************/

#define I2C_REG_TEST_SIZE                        10

//
//寄存器识别地址
//
#define I2C_REG_TEST_ADD                         (uint8_t)0xF0



extern uint32_t IIC_TEST_ISRcount[];

/******************************************************************************
                              定义I2C总线操作结构体
******************************************************************************/

#define I2C_DEVICE_FLAG_DIR_SEND                 ((uint32_t)0x80000000)
#define I2C_DEVICE_FLAG_READ                     ((uint32_t)0x40000000)
#define I2C_DEVICE_FLAG_NACK                     ((uint32_t)0x20000000)
#define I2C_DEVICE_FLAG_WRITE                    ((uint32_t)0x10000000)
#define I2C_DEVICE_FLAG_ERROR                    ((uint32_t)0x08000000)

__packed typedef struct
{
	uint32_t I2C_DeviceFlag;  //操作过程中各种标识集合
	
	uint32_t I2C_EventStatus;
	uint32_t I2C_ErrorStatus;
	uint32_t Nodatatime;
} I2C_DEVICE_TypeDef;

extern I2C_DEVICE_TypeDef i2c_dev;
extern unsigned char g_ReceiveBuff_pui[];
extern uint8_t I2C2TestBuff[100];

/******************************************************************************
                               外部调用功能函数
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
