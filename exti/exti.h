#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f10x.h"

#ifdef USED_BY_PIONEER
 //Òý½Å¶¨Òå
#define INT_GPIO_PORT 		GPIOA
#define INT_GPIO_CLK 		(RCC_APB2Periph_GPIOA\
							|RCC_APB2Periph_AFIO)
#define INT_GPIO_PIN 		GPIO_Pin_0
#define INT_EXTI_PORTSOURCE GPIO_PortSourceGPIOA
#define INT_EXTI_PINSOURCE 	GPIO_PinSource0
#define INT_EXTI_LINE 		EXTI_Line0
#define INT_EXTI_IRQ 		EXTI0_IRQn

#define INT_IRQHandler 		EXTI0_IRQHandler
#endif //USED_BY_PIONEER


void EXTI_Config(void);

#endif //__EXTI_H



