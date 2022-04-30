#include "vi2c.h"


/**
 * @brief 设置SCL
 * @param i2c 虚拟IIC指针
 * @param SCL_Port GPIO
 * @param SCL_Pin PIN  
 * @param SCL_CLK CLK 
 * @retval 状态值
 */
int setSCL(VI2C_T *i2c,GPIO_TypeDef* SCL_Port,uint16_t SCL_Pin,uint32_t SCL_CLK)
{
	i2c->SCL_Port = SCL_Port;
	i2c->SCL_Pin = SCL_Pin;
	i2c->SCL_PORT_CLK = SCL_CLK;
	return 0;
}


/**
 * @brief 设置SDA
 * @param 虚拟IIC指针
 * @param SDA_Port GPIO
 * @param SDA_Pin PIN
 * @param SDA_CLK CLK
 * @retval 0为成功
 */
int setSDA(VI2C_T *i2c,GPIO_TypeDef* SDA_Port,uint16_t SDA_Pin,uint32_t SDA_CLK)
{
	i2c->SDA_Port = SDA_Port;
	i2c->SDA_Pin = SDA_Pin;
	i2c->SDA_PORT_CLK = SDA_CLK;
	return 0;
}




/**
 * @brief  激活IIC
 * @param  i2c 虚拟IIC指针  
 * @retval 0为成功
 */
int I2C_setup(VI2C_T *i2c)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(i2c->SCL_PORT_CLK|i2c->SDA_PORT_CLK,ENABLE);
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = i2c->SCL_Pin;
 	GPIO_Init(i2c->SCL_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = i2c->SDA_Pin;
 	GPIO_Init(i2c->SDA_Port, &GPIO_InitStructure);
	
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
	
	return 0;
}




/**
 * @brief  I2C的开始
 * @param  i2c 虚拟I2C指针
 * @retval None
 */
void I2C_Start(VI2C_T *i2c)
{
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)0);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
}





/**
 * @brief  I2C的结束
 * @param  i2c 虚拟I2C指针  
 * @retval None 
 */
void I2C_Stop(VI2C_T *i2c)
{
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)0);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
}




/**
 * @brief  I2C接收应答
 * @param  i2c 虚拟I2C指针   
 * @retval 应答位
 */
unsigned char I2C_ReadAck(VI2C_T *i2c)
{
	unsigned char AckBit;
	
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	AckBit = GPIO_ReadInputDataBit(i2c->SDA_Port,i2c->SDA_Pin);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
	
	return AckBit;
}




/**
 * @brief 发送应答
 * @param i2c 虚拟I2C指针 
 * @param AckBit 应答
 * @retval None 
 */
void I2C_SendAck(VI2C_T *i2c,BitAction AckBit)
{
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,AckBit);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
}





/**
 * @brief 发送一个字节
 * @param  i2c 虚拟I2C指针  
 * @param  Byte 数据
 * @retval None 
 */
void I2C_SendByte(VI2C_T *i2c,unsigned char Byte)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)(Byte&(0X80>>i)));
		GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
		GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
	}
}




/**
 * @brief  接收一个字节
 * @param  i2c 虚拟I2C指针
 * @retval None 
 */
unsigned char I2C_ReadByte(VI2C_T *i2c)
{
	unsigned char i,Byte=0X00;
	
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
	
	for(i=0;i<8;i++)
	{
		GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
		if(GPIO_ReadInputDataBit(i2c->SDA_Port,i2c->SDA_Pin))
		{
			Byte |= (0X80>>i);
		}
		GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
	}
	
	return Byte;
}
