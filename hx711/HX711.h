#ifndef __HX711_H
#define __HX711_H

#include "system.h"

/**
 * @note 校准参数
 * 	因为不同的传感器特性曲线不是很一致
 * 	因此，每一个传感器需要矫正这里这个参数才能使测量值很准确
 * 	当发现测试出来的重量偏大时，增加该数值
 *	如果测试出来的重量偏小时，减小改数值
 *	该值可以为小数
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

