/**
  *****************************************************************************
  *                             STM32Ӳ��IIC���ƺ���
  *
  *                       (C) Copyright 2000-2020, ***
  *                             All Rights Reserved
  *****************************************************************************
  *
  * @File    : hardiic.h
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

#ifndef _hardiic_h
#define _hardiic_h

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
                             ��ֹʱ���ӳ�����ģʽ��Ч��
******************************************************************************/

#define I2C_STRETCH_EN                         1  //�Ƿ��ʱ����չ
//0: Disable
//1: Enable

/******************************************************************************
                               �ⲿ���ù��ܺ���
******************************************************************************/
void MX_I2C2_Init(void);

void Hard_I2C_Init(I2C_TypeDef* I2Cx, uint8_t SlaveAdd, uint32_t Freq_SCL);  //Ӳ��IIC��ʼ��

void Hard_I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);


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