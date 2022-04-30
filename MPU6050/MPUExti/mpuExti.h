#ifndef _MPUEXTI_H
#define _MPUEXTI_H

#include "system.h" 
#include "mpu6050.h"
#include "inv_mpu.h"

/**
 * @brief 
 * @param 
 * @retval 
 */
typedef struct 
{
	float Pitch; 	//������
	float Roll;		//�����
	float Yaw;		//ƫ����
	short gyrox; 	//x���ٶ�
	short gyroy;	//y���ٶ�
	short gyroz;	//z���ٶ�
	short aacx;		//x�Ǽ��ٶ�
	short aacy;		//y�Ǽ��ٶ�
	short aacz;		//z�Ǽ��ٶ�
}MPU6050_T;


extern MPU6050_T mpuSensor;

void MPU6050_EXTI_Init(void);


#endif //_MPUEXTI_H







