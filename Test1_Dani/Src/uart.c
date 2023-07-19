#include "uart.h"
#include "GY_511.h"




static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);



int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_rxtx_init(void)
{
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_RX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;
}

void uart2_rx_interrupt_init(void)
{
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_RX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	 /*Enable RXNE inteerupt*/
	 USART2->CR1 |= CR1_RXNEIE;
	 //USART2->CR1 |=CR1_TXNEIE;

	 /*Enable UART2 interrupt in NVIC*/
	 NVIC_EnableIRQ(USART2_IRQn);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;
}


static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk +( baudrate/2U ))/baudrate);
}


static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART2->BRR  = compute_uart_bd(periph_clk,baudrate);
}


void uart2_write_float(float value)
{
    uint8_t *ptr = (uint8_t*)&value;
    for (uint8_t i = 0; i < sizeof(float); i++) {
        uart2_write(*ptr++);
    }
}


void uart2_write(uint8_t ch)
{
    // Warten, bis der Sendepuffer leer ist
    while (!(USART2->SR & SR_TXE)) {}

    // Zeichen in den Sendepuffer schreiben
    USART2->DR = ch;
}

void uart_send_Magneto(lsm303MagData *data)
{
	if (data == NULL)return;

	for(uint8_t i=0; i<(sizeof(data->Raw_Buffer16)/sizeof(data->Raw_Buffer16[0]));i++)
	{
		uint8_t buff[2];
			buff[0] = ((data->Raw_Buffer16[i])>>8)&0xFF;	//high
			buff[1] = (data->Raw_Buffer16[i])&0xFF;		//low

		    for(uint8_t n=0; n<sizeof(buff);n++)
		    {
		    	uart2_write(buff[n]);
		    }
	}
}


void uart_send_yaw(lsm303MagData *data)
{
    if (data == NULL) {
        // Handle error
        return;
    }

    union float_bytes yaw;
    yaw.value = data->yaw;

    for(uint8_t i=0; i<sizeof(yaw.bytes); i++)
    {
        uart2_write(yaw.bytes[i]);
    }
}


int8_t uart2_read(void)
{
    // Gelesenes Zeichen zurückgeben
    return (int8_t)(USART2->DR);
}


void uart_receive_data(char* buffer)
{
    int i = 0;
    while (i < 5) // Annahme, dass der String eine maximale Länge von 5 hat (Hello + Null-Terminator)
    {
        // Warten, bis Daten empfangen werden
        while ((USART2->SR & SR_RXNE) == 0){};

        // Gelesenes Zeichen in den Puffer schreiben
        buffer[i] = USART2->DR;

        i++;
    }
    buffer[i] = '\0'; // Null-Terminator hinzufügen, um den String abzuschließen
}


