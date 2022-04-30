#ifndef __PID_H
#define __PID_H

/**
 * @brief PID结构体
*/
typedef struct _PID_T
{
    float kp;               //比例系数
    float ki;               //积分系数
    float kd;               //微分系数
    float targetValue;      //目标值
    float lastErr;          //上次误差
    float prevErr;          //上上次误差
    float integral;         //误差积分值
    float lastOutput;       //上次输出
}PID_T;



float pidControler(PID_T *pid,float value);
float incPidControler(PID_T *pid,float value);

#endif //__PID_H