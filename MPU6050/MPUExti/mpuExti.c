#include "mpuExti.h"

/*中断读写变量*/
MPU6050_T mpuSensor={0};


/**
 * @brief 中断优先级配置
 * @param None
 * @retval None
 */
static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*外部中断*/
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
}


/**
 * @brief 外部中断配置
 * @param None
 * @retval None
 */
static void extiInit(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//开启时钟
	
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
 * @brief MPU6050中断初始化
 * @param None
 * @retval None
 */
void MPU6050_EXTI_Init(void)
{
	/*中断优先级*/
	NVIC_Config();  
	/*外部中断*/
	extiInit();
}


/**
 * @brief MPU6050外部中断服务函数
 * @param None
 * @retval None
 */
void EXTI9_5_IRQHandler(void)
{
	/*一级判定*/
	if(EXTI_GetITStatus(EXTI_Line6)!=0)
	{
		/*二级判定*/
		if(PAin(6)==0)
		{
			/*清除中断标志位*/
			EXTI_ClearITPendingBit(EXTI_Line6);
			/*角度*/
			mpu_dmp_get_data(&mpuSensor.Pitch,&mpuSensor.Roll,&mpuSensor.Yaw);	
			/*陀螺仪*/		
			MPU6050_Get_Gyroscope(&mpuSensor.gyrox,&mpuSensor.gyroy,&mpuSensor.gyroz);	
			/*加速度*/		
			MPU6050_Get_Accelerometer(&mpuSensor.aacx,&mpuSensor.aacy,&mpuSensor.aacz);													//转向环
			
		}
	}
}





