#ifndef __CURRENT_H
#define	__CURRENT_H
#include "main.h"

#define 	STATE_STATIC	'I'
#define 	STATE_CHG			'C'
#define 	STATE_DSG			'D'

uint16_t Update_Current(void);
int16_t GetClibrationDiff_Current(void);
uint8_t CurrentStateDetect( int32_t val );
uint8_t SH_Get_ChgSta(void);
void Cycle_Integral(int32_t curr,uint16_t time);
void CurrAlarmProcess(void);
void DCAlarm_RProcess(void);
void CCAlarm_RProcess(void);

#endif

