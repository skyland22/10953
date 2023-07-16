#ifndef __PCMONITOR_H
#define __PCMONITOR_H
#include "main.h"

#define BUFFER_MAX 200//���建������С
#define PC_CMDHEAD 3

typedef struct{
	
	uint16_t headPosition;//������ͷ��λ��
	uint16_t tailPosition;
	uint8_t ringBuf[BUFFER_MAX];//����������	
	uint8_t dummy;
	uint8_t rcvFlag;
	uint8_t NodataTime;
}ringBuffer_t;
extern ringBuffer_t RS485Buf;

void RingBuf_Write(uint8_t data);

uint8_t RingBuf_Read(uint8_t* val);


void PCMonitor_Process(uint8_t head);
void RS485_Process(void);
#endif

