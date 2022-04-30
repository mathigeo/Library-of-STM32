#define USED_BY_PIONEER
#include "pwm.h"
#undef USED_BY_PIONEER


/**
 * @brief ͨ�ö�ʱ�� PWM ����õ��� GPIO ��ʼ��
 * @param ��
 * @retval ��
 */
static void PWM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#if 0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif 
}


/**
 * @brief ͨ�ö�ʱ�� PWM ʱ����ʼ��
 * @param ��
 * @retval ��
 * @note
 */
static void PWM_BaseConfig(uint16_t psc,uint16_t arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	// ������ʱ��ʱ��,���ڲ�ʱ�� CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ� TIM_Period+1 ��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=arr;
	// ���� CNT ��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM3, ENABLE);
}



/**
 * @brief PWM ����Ƚϳ�ʼ��
 * @param ��ʼ��CCRֵ
 * @retval None
 */
static void PWM_OC_Config(uint16_t ccr)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// ����Ϊ PWM ģʽ 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//Capture Compare Register
	TIM_OCInitStructure.TIM_Pulse = ccr;
	
	// ����Ƚ�ͨ�� 1
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
#if 0
	// ����Ƚ�ͨ�� 2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
#endif
	TIM_ARRPreloadConfig(TIM3,ENABLE);
}


/**
 * @brief ͨ�ö�ʱ�� PWM ����õ��� GPIO �� PWM ģʽ��ʼ��
 * @param ��
 * @retval ��
 */
void PWM_Init(void)
{
	PWM_GPIO_Config();
	PWM_BaseConfig(71,99);
	PWM_OC_Config(0);
}



