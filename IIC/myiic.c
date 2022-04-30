#include "myiic.h"
#include "systick.h"

/**
 * @brief IIC ��ʼ��
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
 * @brief ����IIC��ʼ�ź�
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
 * @brief ����IICֹͣ�ź�
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
 * @brief �ȴ�Ӧ���źŵ���
 * @param None
 * @retval �����Ľ��
 * 	1������Ӧ��ʧ��
 *	0������Ӧ��ɹ�
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
 * @brief ����ACKӦ��
 * @param AckBit Ӧ��λ
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
 * @brief IIC����һ���ֽ�
 * @param txd ���͵�����
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
 * @brief ��1���ֽ�
 * @param ack Ӧ��λ
 * @retval ��������
 * @note ack=1ʱ,����ACK
 *		 ack=0������nACK
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
	SDA_SET_IN();//SDA����Ϊ����
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



























