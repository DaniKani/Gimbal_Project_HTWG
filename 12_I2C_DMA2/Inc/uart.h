
#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "GY_511.h"

#include "stm32f4xx.h"

void uart2_tx_init(void);
void uart2_write_int16(int16_t value);
void uart2_write(uint8_t ch);
void sendString(const char* str);
void uart2_write_float(float value);
void UART_SendRawBuffer(lsm303MagData* data);
void UART_Send_Test(lsm303MagData* data);
#endif /* UART_H_ */
