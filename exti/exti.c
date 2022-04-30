#define USED_BY_PIONEER
#include "exti.h"
#undef USED_BY_PIONEER


/*
�������ܣ�NVIC����
��ڲ�������
����ֵ����
*/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* �����ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = INT_EXTI_IRQ;
	/* ������ռ���ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	/* ���������ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	/* ʹ���ж�ͨ��*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/*
�������ܣ��ⲿ�жϳ�ʼ��
��ڲ�������
����ֵ����
*/
void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/*���� GPIO �ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(INT_GPIO_CLK,ENABLE);
	
	/* ���� NVIC �ж�*/
	NVIC_Configuration();
	

	/* ѡ�񰴼��õ��� GPIO */
	GPIO_InitStructure.GPIO_Pin = INT_GPIO_PIN;
	/* ����Ϊ�������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* ѡ�� EXTI ���ź�Դ */
	GPIO_EXTILineConfig(INT_EXTI_PORTSOURCE,INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = INT_EXTI_LINE;
	
	/* EXTI Ϊ�ж�ģʽ */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* ʹ���ж� */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}


void INT_IRQHandler(void)
{
	//ȷ���Ƿ������ EXTI Line �ж�
	if (EXTI_GetITStatus(INT_EXTI_LINE) != RESET) 
	{
		//����жϱ�־λ
		EXTI_ClearITPendingBit(INT_EXTI_LINE);
	}
}
