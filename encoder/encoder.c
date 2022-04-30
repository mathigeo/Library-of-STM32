#include "stm32f10x.h"   // Device header
#include "encoder.h"


/**
 * @brief 编码器端口配置
 * @param None
 * @retval None
 */
static void encoderPortConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能PA端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;   
	//浮空输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//根据设定参数初始化GPIOA
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          	
}


/**
 * @brief 编码器时基配置
 * @param None
 * @retval None
 */
static void encoderTimeBaseConfig(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//使能定时器4的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	// 预分频器
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0000; 
	//设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Period = 0XFFFF; 
	//选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM向上计数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}


/**
 * @brief 编码器模式和输入捕获配置
 * @param None
 * @retval None
 */
static void encoderIC_Config(void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	////使用编码器模式3
    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
	//清除TIM的更新标志位
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    //Reset counter
    TIM_SetCounter(TIM2,0);
    TIM_Cmd(TIM2, ENABLE);
}



/**
 * @brief 初始化编码器接口
 * @param None
 * @retval None
 */
void Encoder_Init(void)
{
	/*端口配置*/
	encoderPortConfig();
	/*时基配置*/
	encoderTimeBaseConfig();
	/*编码器模式和输入捕获配置*/
	encoderIC_Config();
}


/**
 * @brief 读取计数值
 * @param None
 * @retval 计数值
 */
int Read_Encoder(void)
{
    int Encoder_TIM;
    Encoder_TIM= (short)TIM_GetCounter(TIM2);
//	TIM_SetCounter(TIM2,0);
    return Encoder_TIM;
}


/**
 * @brief 定时器2中断服务函数
 * @param None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
	//溢出中断
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
    {
    }
	//清除中断标志位
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}




