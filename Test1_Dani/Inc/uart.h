#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "GY_511.h"
#include "stm32f4xx.h"



#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<0)
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)
#define CR1_RE			(1U<<2)
#define CR1_RXNEIE		(1U<<5)
#define SR_RXNE			(1U<<5)
#define UART_BAUDRATE	9600//115200
#define CLK				16000000





// Union to help convert between float and byte array
union float_bytes {
    float value;
    uint8_t bytes[sizeof(float)];
};

void uart2_rx_interrupt_init(void);
void uart_receive_data(char* data_buffer);
void uart2_rxtx_init(void);
void uart2_tx_init(void);
void uart2_write_int16(int16_t value);
void uart2_write(uint8_t ch);
void sendString(const char* str);
void uart2_write_float(float value);
void UART_SendRawBuffer(lsm303MagData* data);
void UART_Send_Test(lsm303MagData* data);
int8_t uart2_read(void);
void uart_send_Magneto(lsm303MagData *data);
void uart_send_yaw(lsm303MagData *data);
//void GY_511_update(lsm303MagData *data, int8_t *Offset);
#endif /* UART_H_ */
