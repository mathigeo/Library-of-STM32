#include "stm32f10x.h"   // Device header
#include "encoder.h"


/**
 * @brief �������˿�����
 * @param None
 * @retval None
 */
static void encoderPortConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��PA�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;   
	//��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//�����趨������ʼ��GPIOA
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          	
}


/**
 * @brief ������ʱ������
 * @param None
 * @retval None
 */
static void encoderTimeBaseConfig(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	// Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0000; 
	//�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Period = 0XFFFF; 
	//ѡ��ʱ�ӷ�Ƶ������Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}


/**
 * @brief ������ģʽ�����벶������
 * @param None
 * @retval None
 */
static void encoderIC_Config(void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	////ʹ�ñ�����ģʽ3
    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
	//���TIM�ĸ��±�־λ
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    //Reset counter
    TIM_SetCounter(TIM2,0);
    TIM_Cmd(TIM2, ENABLE);
}



/**
 * @brief ��ʼ���������ӿ�
 * @param None
 * @retval None
 */
void Encoder_Init(void)
{
	/*�˿�����*/
	encoderPortConfig();
	/*ʱ������*/
	encoderTimeBaseConfig();
	/*������ģʽ�����벶������*/
	encoderIC_Config();
}


/**
 * @brief ��ȡ����ֵ
 * @param None
 * @retval ����ֵ
 */
int Read_Encoder(void)
{
    int Encoder_TIM;
    Encoder_TIM= (short)TIM_GetCounter(TIM2);
//	TIM_SetCounter(TIM2,0);
    return Encoder_TIM;
}


/**
 * @brief ��ʱ��2�жϷ�����
 * @param None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
	//����ж�
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
    {
    }
	//����жϱ�־λ
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}




