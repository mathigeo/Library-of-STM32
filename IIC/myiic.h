#ifndef __MYIIC_H
#define __MYIIC_H
#include "system.h"

   	   		   
//IO方向设置
#define SDA_SET_IN()  	{GPIOC->CRH&=0XFFFF0FFF; \
						GPIOC->CRH|=8<<12;}
#define SDA_SET_OUT() 	{GPIOC->CRH&=0XFFFF0FFF; \
						GPIOC->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL_PUT(x)    	{PCout(12) = x;} 
#define IIC_SDA_PUT(x)    	{PCout(11) = x;} 
#define IIC_SDA_GET()   	PCin(11)  


//IIC所有操作函数       			 
void IIC_Start(void);			
void IIC_Stop(void);	  	
void IIC_Send_Byte(uint8_t txd);			
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void); 
void IIC_Send_Ack(uint8_t AckBit);		


void IIC_Init(void);  
void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif
















