#define USED_BY_PIONEER
#include "exti.h"
#undef USED_BY_PIONEER


/*
函数功能：NVIC配置
入口参数：无
返回值：无
*/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 配置中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = INT_EXTI_IRQ;
	/* 配置抢占优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	/* 配置子优先级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	/* 使能中断通道*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/*
函数功能：外部中断初始化
入口参数：无
返回值：无
*/
void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/*开启 GPIO 口的时钟*/
	RCC_APB2PeriphClockCmd(INT_GPIO_CLK,ENABLE);
	
	/* 配置 NVIC 中断*/
	NVIC_Configuration();
	

	/* 选择按键用到的 GPIO */
	GPIO_InitStructure.GPIO_Pin = INT_GPIO_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* 选择 EXTI 的信号源 */
	GPIO_EXTILineConfig(INT_EXTI_PORTSOURCE,INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = INT_EXTI_LINE;
	
	/* EXTI 为中断模式 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* 使能中断 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}


void INT_IRQHandler(void)
{
	//确保是否产生了 EXTI Line 中断
	if (EXTI_GetITStatus(INT_EXTI_LINE) != RESET) 
	{
		//清除中断标志位
		EXTI_ClearITPendingBit(INT_EXTI_LINE);
	}
}
