#include "MLX90393.h"


#define MLX90393_SPI_WRITE 0x00
#define MLX90393_SPI_READ 0x04
#define MLX90393_SPI_X_AXIS 0x00
#define MLX90393_SPI_Y_AXIS 0x01

uint8_t receive_buff[3];
uint8_t transmitt_buff[3];
uint8_t transfer_length = sizeof(receive_buff)+1;

void cs_pin_set(void)
{
	GPIOA->ODR |=(1U<<0);
}

void cs_pin_reset(void)
{
	GPIOA->ODR &= ~(1U<<0);
}

//void Init() {
//
//	cs_pin_set();
//	transfer_add = {MLX90393_SPI_WRITE, 0x60, 0x02};
//	dma2_stream3_spi_transfer((uint32_t) transmitt_buff, (uint32_t) sizeof(transmitt_buff));
//
//	cs_pin_reset();
//}


//****************************************COMMUNICATION*****************************************

void Send_SPI(uint32_t receive_add, uint32_t transfer_add, uint8_t transfer_length, uint8_t receive_length)
{
	cs_pin_set();
 	dma2_stream3_spi_transfer((uint32_t) transfer_add, (uint32_t) transfer_length);
	dma2_stream2_spi_receive((uint32_t) receive_add,(uint32_t) receive_length);
	cs_pin_reset();
}

//*************************************** MAIN FUNCTIONS ***************************************

void EX(uint32_t *receiveBuffer_add)
{
	transmitt_buff[0] = 0x80;
    Send_SPI((uint32_t) receiveBuffer_add, (uint32_t) transmitt_buff, 3, 3);

}
//
//void SB(char *receiveBuffer, char zyxt, int mode)
//{
//    write_buffer[0] = (0x10)|(zyxt);
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void SWOC(char *receiveBuffer, char zyxt, int mode)
//{
//    write_buffer[0] = (0x20)|(zyxt);
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void SM(char *receiveBuffer, char zyxt, int mode)
//{
//    write_buffer[0] = (0x30)|(zyxt);
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void RM(char *receiveBuffer, char zyxt, int mode)
//{
//    write_buffer[0] = (0x40)|(zyxt);
//    for(int i=0; i<2*count_set_bits(zyxt); i++) {
//        write_buffer[i+2] = 0x00;
//    }
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1+2*count_set_bits(zyxt));
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1+2*count_set_bits(zyxt));
//    }
//}
//
//void RR(char *receiveBuffer, int address, int mode)
//{
//    write_buffer[0] = 0x50;
//    write_buffer[1] = address << 2;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 2, 3);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 2, 3);
//    }
//}
//
//void WR(char *receiveBuffer, int address, int data, int mode)
//{
//    write_buffer[0] = 0x60;
//    write_buffer[1] = (data&0xFF00)>>8;
//    write_buffer[2] = data&0x00FF;
//    write_buffer[3] = address << 2;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 4, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 4, 1);
//    }
//}
//
//void RT(char *receiveBuffer, int mode)
//{
//    write_buffer[0] = 0xF0;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void NOP(char *receiveBuffer, int mode)
//{
//    write_buffer[0] = 0x00;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void HR(char *receiveBuffer, int mode)
//{
//    write_buffer[0] = 0xD0;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}
//
//void HS(char *receiveBuffer, int mode)
//{
//    write_buffer[0] = 0xE0;
//    if (mode == 1) {
//        Send_SPI(receiveBuffer, write_buffer, 1, 1);
//    } else {
//        Send_I2C(receiveBuffer, write_buffer, 1, 1);
//    }
//}

