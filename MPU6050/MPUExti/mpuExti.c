#include "mpuExti.h"

/*�ж϶�д����*/
MPU6050_T mpuSensor={0};


/**
 * @brief �ж����ȼ�����
 * @param None
 * @retval None
 */
static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*�ⲿ�ж�*/
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
}


/**
 * @brief �ⲿ�ж�����
 * @param None
 * @retval None
 */
static void extiInit(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//����ʱ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line6;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
}


/**
 * @brief MPU6050�жϳ�ʼ��
 * @param None
 * @retval None
 */
void MPU6050_EXTI_Init(void)
{
	/*�ж����ȼ�*/
	NVIC_Config();  
	/*�ⲿ�ж�*/
	extiInit();
}


/**
 * @brief MPU6050�ⲿ�жϷ�����
 * @param None
 * @retval None
 */
void EXTI9_5_IRQHandler(void)
{
	/*һ���ж�*/
	if(EXTI_GetITStatus(EXTI_Line6)!=0)
	{
		/*�����ж�*/
		if(PAin(6)==0)
		{
			/*����жϱ�־λ*/
			EXTI_ClearITPendingBit(EXTI_Line6);
			/*�Ƕ�*/
			mpu_dmp_get_data(&mpuSensor.Pitch,&mpuSensor.Roll,&mpuSensor.Yaw);	
			/*������*/		
			MPU6050_Get_Gyroscope(&mpuSensor.gyrox,&mpuSensor.gyroy,&mpuSensor.gyroz);	
			/*���ٶ�*/		
			MPU6050_Get_Accelerometer(&mpuSensor.aacx,&mpuSensor.aacy,&mpuSensor.aacz);													//ת��
			
		}
	}
}





