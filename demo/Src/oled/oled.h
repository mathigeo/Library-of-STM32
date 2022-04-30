#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "graphics.h"

#define USE_IIC	
//#define USE_SPI	

#ifdef	USE_IIC		
/*-------------------------------------------------*/
#define SCL_PORT			GPIOB
#define SCL_PIN				GPIO_Pin_10
#define OLED_SCL_PORT_CLK 	RCC_APB2Periph_GPIOB
#define SDA_PORT			GPIOB
#define SDA_PIN				GPIO_Pin_11
#define OLED_SDA_PORT_CLK 	RCC_APB2Periph_GPIOB
/*-------------------------------------------------*/
#define OLED_W_SCL(x)		GPIO_WriteBit(SCL_PORT, SCL_PIN, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(SDA_PORT, SDA_PIN, (BitAction)(x))
#endif //USE_IIC	


#ifdef	USE_SPI 
/*---------------------------------------------------*/
#define D0_PORT 		GPIOB			//SCLK
#define D0_PIN 			GPIO_Pin_9
#define D0_PORT_CLK		RCC_APB2Periph_GPIOB

#define D1_PORT			GPIOB				//MOSI
#define D1_PIN			GPIO_Pin_8
#define D1_PORT_CLK		RCC_APB2Periph_GPIOB

#define RES_PORT		GPIOB
#define RES_PIN			GPIO_Pin_7
#define RES_PORT_CLK	RCC_APB2Periph_GPIOB

#define DC_PORT			GPIOB
#define DC_PIN			GPIO_Pin_6
#define DC_PORT_CLK		RCC_APB2Periph_GPIOB

#define CS_PORT			GPIOA
#define CS_PIN			GPIO_Pin_8
#define CS_PORT_CLK		RCC_APB2Periph_GPIOA
/*---------------------------------------------------*/
#define OLED_W_D0(x)		GPIO_WriteBit(D0_PORT, D0_PIN, (BitAction)(x))
#define OLED_W_D1(x)		GPIO_WriteBit(D1_PORT, D1_PIN, (BitAction)(x))
#define OLED_W_RES(x)		GPIO_WriteBit(RES_PORT,RES_PIN,(BitAction)(x))
#define OLED_W_DC(x)		GPIO_WriteBit(DC_PORT, DC_PIN, (BitAction)(x))
#define OLED_W_CS(x)		GPIO_WriteBit(CS_PORT, CS_PIN, (BitAction)(x))
#endif //USE_SPI




void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_WriteCommand(uint8_t Command);
void OLED_ShowChar(uint8_t row,uint8_t col,char Chr,uint8_t inv);
void OLED_ShowString(uint8_t row,uint8_t col,char *str,uint8_t inv);
int showGBK(unsigned char row,unsigned char col,uint8_t *gbk);
int oledPrint(u8 row,u8 col,const char *formate,...);
int showBmp(unsigned char x,unsigned char y,BMP_T *bmp);

#endif
