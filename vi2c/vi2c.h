#ifndef __VI2C_H
#define __VI2C_H

#include "stm32f10x.h"


/**
 * @brief 模拟I2C结构体
 */
typedef struct
{
	GPIO_TypeDef* SCL_Port;
	GPIO_TypeDef* SDA_Port;
	uint16_t SCL_Pin;
	uint16_t SDA_Pin;
	uint32_t SCL_PORT_CLK;
	uint32_t SDA_PORT_CLK;
}VI2C_T;



int setSCL(VI2C_T *i2c,GPIO_TypeDef* SCL_Port,uint16_t SCL_Pin,uint32_t SCL_CLK);
int setSDA(VI2C_T *i2c,GPIO_TypeDef* SDA_Port,uint16_t SDA_Pin,uint32_t SDA_CLK);
int I2C_setup(VI2C_T *i2c);


void I2C_Start(VI2C_T *i2c);
void I2C_Stop(VI2C_T *i2c);
void I2C_SendByte(VI2C_T *i2c,unsigned char Byte);
unsigned char I2C_ReadByte(VI2C_T *i2c);
unsigned char I2C_ReadAck(VI2C_T *i2c);
void I2C_SendAck(VI2C_T *i2c,BitAction AckBit);


#endif //__VI2C_H



