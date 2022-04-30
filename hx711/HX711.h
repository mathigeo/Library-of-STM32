#ifndef __HX711_H
#define __HX711_H

#include "system.h"

/**
 * @note У׼����
 * 	��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ��
 * 	��ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ
 * 	�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ
 *	������Գ���������ƫСʱ����С����ֵ
 *	��ֵ����ΪС��
 */
#define GapValue 1035

#define CALIBRATE_ON 	1
#define CALIBRATE_OFF 	0

#define HX711_SCK 	PCout(11)
#define HX711_DOUT 	PCin(12)


extern void Init_HX711pin(void);
extern u32 HX711_Read(void);
extern int32_t Get_Weight(uint8_t mode);

#endif /*__HX711_H*/

