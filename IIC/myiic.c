#include "myiic.h"
#include "systick.h"

/**
 * @brief IIC 初始化
 * @param None
 * @retval None
 */
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	IIC_SCL_PUT(1);
	IIC_SDA_PUT(1);
}

/**
 * @brief 产生IIC起始信号
 * @param None
 * @retval None
 */
void IIC_Start(void)
{
	SDA_SET_OUT();     
	IIC_SDA_PUT(1);	  	  
	IIC_SCL_PUT(1);
	delay_us(4);
 	IIC_SDA_PUT(0);
	delay_us(4);
	IIC_SCL_PUT(0);
}	  


/**
 * @brief 产生IIC停止信号
 * @param None
 * @retval None
 */
void IIC_Stop(void)
{
	SDA_SET_OUT();
	IIC_SCL_PUT(0);
	IIC_SDA_PUT(0);
 	delay_us(4);
	IIC_SCL_PUT(1); 
	IIC_SDA_PUT(1);
	delay_us(4);							   	
}


/**
 * @brief 等待应答信号到来
 * @param None
 * @retval 读到的结果
 * 	1，接收应答失败
 *	0，接收应答成功
 */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	
	SDA_SET_IN();      
	IIC_SDA_PUT(1);
	delay_us(1);	   
	IIC_SCL_PUT(1);
	delay_us(1);	 
	while(IIC_SDA_GET())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_PUT(0);
	return 0;  
} 

/**
 * @brief 产生ACK应答
 * @param AckBit 应答位
 * @retval None
 */
void IIC_Send_Ack(uint8_t AckBit)
{
	IIC_SCL_PUT(0);
	SDA_SET_OUT( );
	IIC_SDA_PUT(AckBit);
	delay_us(2);
	IIC_SCL_PUT(1);
	delay_us(2);
	IIC_SCL_PUT(0);
}					 				     

/**
 * @brief IIC发送一个字节
 * @param txd 发送的数据
 * @retval None
 */
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_SET_OUT(); 	    
    IIC_SCL_PUT(0);
    for(t=0;t<8;t++)
    {              
        IIC_SDA_PUT( (txd&0x80)>>7 );
        txd<<=1; 	  
		delay_us(2);   
		IIC_SCL_PUT(1);
		delay_us(2); 
		IIC_SCL_PUT(0);	
		delay_us(2);
    }	 
} 	    


/**
 * @brief 读1个字节
 * @param ack 应答位
 * @retval 读到的数
 * @note ack=1时,发送ACK
 *		 ack=0，发送nACK
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
	SDA_SET_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_PUT(0); 
        delay_us(2);
		IIC_SCL_PUT(1);
        receive<<=1;
        if(IIC_SDA_GET())
			receive++;   
		delay_us(1); 
    }	
	IIC_Send_Ack(ack);
    return receive;
}



























