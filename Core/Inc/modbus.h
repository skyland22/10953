//#include "main.h"

#define MODBUS_SLAVE_ADDR 0x01		//´Ó»úµØÖ·

void modbus_service(void);
void modbus_03_function(void);
void modbus_send_data(unsigned char *buff,unsigned char len);
unsigned short int CRC_16_check(unsigned char *ptr,  unsigned char len);
