#ifndef __SIMUAER_H
#define	__SIMUAER_H

#include "main.h"

#define 	UART_MOD_TTL  1
#define 	USESIFANDUART 1

#define    SIF_NoCONNECT 0
#define    SIF_CONNECT 1


#define   DEF_SUARTBPS    14400
#define  SIMUARTDATAMAX    200
#define   DEF_BIT_SampCount     2
#define   DEF_SUARTBITTime (1000000/DEF_SUARTBPS)
#define   DEF_SUART_SampTime (1000000/DEF_SUARTBPS/DEF_BIT_SampCount)
#define  SIMUart_TIM	TIM3



#define   DEF_SIf_St_count     96


typedef enum
{
	COM_NONE_BIT_DEAL=0,
	COM_START_BIT_DEAL,
	COM_DATA_BIT_DEAL,
	COM_LEVEH_DEAL,
	COM_LEVEL_DEAL,
	COM_STOP_BIT_DEAL,
	COM_CHECK_BIT_DEAL,
	COM_ERR_DEAL

}ComStatENUM;
#define    ModNoll 0
 #define  TxEn  3
 #define  RxEn  1
 #define  SIFTxEn  2
 #define  SIFRxEn  4
typedef struct
{
	ComStatENUM UartStat;
	uint8_t readVal;
	uint8_t rcvFlag;
	uint8_t Mode;
	uint8_t SUartIdelTime;
	uint8_t RecBitCount;
	uint8_t RecdataCount;
	uint8_t TrxdataCount;
	uint8_t DataNum;
	uint8_t RecData[SIMUARTDATAMAX];
	uint8_t TrxData[SIMUARTDATAMAX];
	
}SimUARTSt;
extern SimUARTSt  SUartInfo;
extern uint8_t ReceveAllow;
void SUART_Protocol(void);
void UART2RxDataPro(uint16_t data);
void Pin_Turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
#endif /* __ADC_H */

