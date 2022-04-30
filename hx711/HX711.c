#include "HX711.h"
#include "systick.h"

/**
 * @brief ���ų�ʼ��
 * @param None
 * @retval None
 */
void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 

	/*HX711_SCK*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	
	/*HX711_DOUT*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOC,GPIO_Pin_11);			
}


/**
 * @brief ��ȡHX711
 * @param None
 * @retval None
 */
u32 HX711_Read(void)	/*����128*/
{
	unsigned long count; 
	unsigned char i; 
	
  	HX711_DOUT=1; 
	delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		delay_us(1);
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
	
	/*��25�������½�����ʱ��ת������*/
    count=count^0x800000;
	delay_us(1);
	HX711_SCK=0;  
	
	return(count);
}


/**
 * @brief ����
 * @param None
 * @retval ����Ƿ�У׼ģʽ(CALIBRATE_OFF)����������
 *	�����У׼ģʽ(CALIBRATE_ON)��������Чֵ
 * @note ��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�
 * 	ÿһ����������Ҫ���������GapValue���������
 *	�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
 *	������Գ���������ƫСʱ����С����ֵ��
 */
int32_t Get_Weight(uint8_t mode)
{
	static uint32_t HX711_Buffer;
	static uint32_t Cross_Weight=0;
	static int32_t 	Real_Weight;
	
	if(mode == CALIBRATE_ON)
	{
		Cross_Weight = HX711_Read();
		return Cross_Weight;
	}
	else
	{
		HX711_Buffer = HX711_Read();
		
		if(HX711_Buffer > Cross_Weight)			
		{
			/*��ȡʵ���AD������ֵ��*/
			Real_Weight = HX711_Buffer;
			
			Real_Weight = Real_Weight - Cross_Weight;				
			/*����ʵ���ʵ������*/
			Real_Weight = (int32_t)((float)Real_Weight/GapValue); 														
		}
		
		return Real_Weight;
	}
}
