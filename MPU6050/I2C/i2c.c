#include <i2c.h>
#include <systick.h>


/**
 * @brief I2C���ų�ʼ��
 * @param None
 * @retval None
 */
void IIC_Init(void)
{
	//GPIO��ʼ���ṹ��
	GPIO_InitTypeDef  GPIO_InitStructure;	
	//ʹ��ʱ��
	RCC_APB2PeriphClockCmd(IIC_SCL_PORT_RCC|IIC_SDA_PORT_RCC,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_SCL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
	
	IIC_SCL=1;
	IIC_SDA=1;
}


/**
 * @brief SDA�������ģʽ
 * @param None
 * @retval None
 */
void SDA_OUT()	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	//�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}


/**
 * @brief SDA��������ģʽ
 * @param None
 * @retval None
 */
void SDA_IN(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	//��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}


/**
 * @brief IIC��ʼ�ź�
 * @param None
 * @retval None
 */
void IIC_Start(void)	
{
	//sda�����
	SDA_OUT();     
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	//Ҫ��ʱ��>4.7us
	delay_us(5);	
 	IIC_SDA=0;	
	//Ҫ��ʱ��>4us
	delay_us(6);	
	//ǯסI2C���ߣ�׼�����ͻ��������
	IIC_SCL=0; 
}



/**
 * @brief IICֹͣ�ź�
 * @param None
 * @retval None
 */
void IIC_Stop(void)	
{
	//sda�����
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	IIC_SCL=1; 
	//Ҫ��ʱ��>4us
	delay_us(6); 	
	//����I2C���߽����ź�
	IIC_SDA=1;
	//Ҫ��ʱ��>4us		
	delay_us(6);						   	
}



/**
 * @brief �ȴ�Ӧ���ź�
 * @param None
 * @retval ����0�ɹ�,1ʧ��
 */
u8 IIC_Wait_Ack(void)
{
	u8 tempTime=0;
	
	IIC_SDA=1;
	delay_us(1);
	//SDA����Ϊ����  
	SDA_IN();      	   
	IIC_SCL=1;
	delay_us(1);
	//�ȴ�Ӧ��	 
	while(READ_SDA)	
	{
		tempTime++;
		//�ȴ�Ӧ������ʱ�� ������ʧ��
		if(tempTime>250)	
		{
			IIC_Stop();
			return 1;
		}
	}
	//ʱ�����0 	 
	IIC_SCL=0;  
	return 0;  
} 



/**
 * @brief IIC����Ӧ��
 * @param None
 * @retval None
 */
void IIC_Ack(void)	
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	//Ҫ��>4us
	delay_us(5);	
	IIC_SCL=0;
}



/**
 * @brief ������Ӧ��
 * @param None
 * @retval None
 */
void IIC_NAck(void)	//������Ӧ��
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	//Ҫ��>4us
	delay_us(5);	
	IIC_SCL=0;
}



/**
 * @brief ����һ���ֽ�
 * @param txd Ҫ���͵��ֽ�
 * @retval None
 */
void IIC_Send_Byte(u8 txd)	//����һ���ֽ�
{                        
    u8 t;   
	SDA_OUT(); 	
	//����ʱ�ӿ�ʼ���ݴ���    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {          
		//�����λ��ʼ����    
        if((txd&0x80)>0) 
		{
			IIC_SDA=1;
		}
		else
		{
			IIC_SDA=0;
        }
		txd<<=1; 	 
		//��TEA5767��������ʱ���Ǳ���� 
		delay_us(2);   
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
}



/**
 * @brief ��ȡһ���ֽ�
 * @param ack 1����Ӧ��,0���ͷ�Ӧ��
 * @retval ��ȡ���ֽ�
 */
u8 IIC_Read_Byte(u8 ack)	
{
	u8 i,receive=0;
	//SDA����Ϊ����
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if(!ack)
	{
		//����nACK
        IIC_NAck();
    }
	else
	{
		//����ACK   
		IIC_Ack(); 
	}
	return receive;
}




