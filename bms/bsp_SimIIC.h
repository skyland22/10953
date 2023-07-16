#ifndef __SIMIIC_H_
#define	__SIMIIC_H_

#include "main.h"


//#define	IICSCL_Pin  LL_GPIO_PIN_6
//#define	IICSCL_Port GPIOB
//#define	IICSDA_Pin  LL_GPIO_PIN_7
//#define	IICSDA_Port GPIOB

#define  I2C_SCL_1() 	GPIO_WritePin(GPIOB,LL_GPIO_PIN_6,GPIO_PIN_SET)
#define  I2C_SCL_0() 	GPIO_WritePin(GPIOB,LL_GPIO_PIN_6,GPIO_PIN_RESET)
#define  I2C_SDA_1() 	GPIO_WritePin(GPIOB,LL_GPIO_PIN_7,GPIO_PIN_SET)
#define  I2C_SDA_0() 	GPIO_WritePin(GPIOB,LL_GPIO_PIN_7,GPIO_PIN_RESET)
#define  I2C_READ_SDA() 	GPIO_ReadPin(GPIOB,LL_GPIO_PIN_7)

//#define  I2C2_EN(x) 	GPIO_WritePin(GPIOB, LL_GPIO_PIN_13, (GPIO_PinState)x)

extern uint16_t SysRegData[256];
extern uint16_t SysReg_Type[20];
extern uint16_t SysReg_VF[20];
extern uint16_t SysReg_VH[20];

void SIM_I2C_Start(void);
void SIM_I2C_Stop(void);
void SIM_I2C_SendByte(uint8_t _ucByte);
uint8_t SIM_I2C_ReadByte(void);
uint8_t SIM_I2C_WaitAck(void);
void SIM_I2C_Ack(void);
void SIM_I2C_NAck(void);
void SIM_I2C_PortInit(void);
void SMBUS_DataProcess(void);

#endif /* __ADC_H */

