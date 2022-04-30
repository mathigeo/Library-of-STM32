#define USED_BY_PIONEER
#include "pid.h"
#undef USED_BY_PIONEER


/**
 * @brief 位置式PID控制器
 * @param pid PID指针
 * @param value 当前的实际值
 * @retval 计算的结果
*/
float pidControler(PID_T *pid,float value)
{
    float ret;
    float err;

    err = pid->targetValue - value;

    ret = pid->kp*err + pid->ki*pid->integral \
    + pid->kd*(err-pid->lastErr);

    pid->integral += err;
    pid->lastErr = err;

    return ret;
}



/**
 * @brief 增量式PID控制器
 * @param pid PID指针
 * @param value 当前的实际值
 * @retval 计算的结果
*/
float incPidControler(PID_T *pid,float value)
{
    float ret,temp;
    float err;

    err = pid->targetValue - value;

    temp = pid->kp*(err-pid->lastErr) + pid->ki*err + \
    pid->kd*(err-2*pid->lastErr+pid->prevErr);

    pid->prevErr = pid->lastErr;
    pid->lastErr = err;

    ret = pid->lastOutput + temp;

    pid->lastOutput = ret;

    return ret;    
}



