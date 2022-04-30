#define USED_BY_PIONEER
#include "pwm.h"
#undef USED_BY_PIONEER


/**
 * @brief 通用定时器 PWM 输出用到的 GPIO 初始化
 * @param 无
 * @retval 无
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
 * @brief 通用定时器 PWM 时基初始化
 * @param 无
 * @retval 无
 * @note
 */
static void PWM_BaseConfig(uint16_t psc,uint16_t arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	// 开启定时器时钟,即内部时钟 CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	// 自动重装载寄存器的值，累计 TIM_Period+1 个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=arr;
	// 驱动 CNT 计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// 初始化定时器
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	// 使能计数器
	TIM_Cmd(TIM3, ENABLE);
}



/**
 * @brief PWM 输出比较初始化
 * @param 开始的CCR值
 * @retval None
 */
static void PWM_OC_Config(uint16_t ccr)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// 配置为 PWM 模式 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//Capture Compare Register
	TIM_OCInitStructure.TIM_Pulse = ccr;
	
	// 输出比较通道 1
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
#if 0
	// 输出比较通道 2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
#endif
	TIM_ARRPreloadConfig(TIM3,ENABLE);
}


/**
 * @brief 通用定时器 PWM 输出用到的 GPIO 和 PWM 模式初始化
 * @param 无
 * @retval 无
 */
void PWM_Init(void)
{
	PWM_GPIO_Config();
	PWM_BaseConfig(71,99);
	PWM_OC_Config(0);
}



