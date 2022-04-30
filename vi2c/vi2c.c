#include "vi2c.h"


/**
 * @brief ����SCL
 * @param i2c ����IICָ��
 * @param SCL_Port GPIO
 * @param SCL_Pin PIN  
 * @param SCL_CLK CLK 
 * @retval ״ֵ̬
 */
int setSCL(VI2C_T *i2c,GPIO_TypeDef* SCL_Port,uint16_t SCL_Pin,uint32_t SCL_CLK)
{
	i2c->SCL_Port = SCL_Port;
	i2c->SCL_Pin = SCL_Pin;
	i2c->SCL_PORT_CLK = SCL_CLK;
	return 0;
}


/**
 * @brief ����SDA
 * @param ����IICָ��
 * @param SDA_Port GPIO
 * @param SDA_Pin PIN
 * @param SDA_CLK CLK
 * @retval 0Ϊ�ɹ�
 */
int setSDA(VI2C_T *i2c,GPIO_TypeDef* SDA_Port,uint16_t SDA_Pin,uint32_t SDA_CLK)
{
	i2c->SDA_Port = SDA_Port;
	i2c->SDA_Pin = SDA_Pin;
	i2c->SDA_PORT_CLK = SDA_CLK;
	return 0;
}




/**
 * @brief  ����IIC
 * @param  i2c ����IICָ��  
 * @retval 0Ϊ�ɹ�
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
 * @brief  I2C�Ŀ�ʼ
 * @param  i2c ����I2Cָ��
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
 * @brief  I2C�Ľ���
 * @param  i2c ����I2Cָ��  
 * @retval None 
 */
void I2C_Stop(VI2C_T *i2c)
{
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)0);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,(BitAction)1);
}




/**
 * @brief  I2C����Ӧ��
 * @param  i2c ����I2Cָ��   
 * @retval Ӧ��λ
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
 * @brief ����Ӧ��
 * @param i2c ����I2Cָ�� 
 * @param AckBit Ӧ��
 * @retval None 
 */
void I2C_SendAck(VI2C_T *i2c,BitAction AckBit)
{
	GPIO_WriteBit(i2c->SDA_Port,i2c->SDA_Pin,AckBit);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)1);
	GPIO_WriteBit(i2c->SCL_Port,i2c->SCL_Pin,(BitAction)0);
}





/**
 * @brief ����һ���ֽ�
 * @param  i2c ����I2Cָ��  
 * @param  Byte ����
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
 * @brief  ����һ���ֽ�
 * @param  i2c ����I2Cָ��
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
