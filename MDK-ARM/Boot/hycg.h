#ifndef __GPIO_LED_SENSOR_H
#define __GPIO_LED_SENSOR_H

#include "stm32h7rsxx_hal.h"
#include "delay.h"

/**************************************************************************************/
/* 函数声明 */
/**************************************************************************************/

/**
  * @brief  GPIO初始化配置
  * @param  无
  * @retval 无
  */
void GPIO_Configuration(void);

/**
  * @brief  火焰传感器检测
  * @param  无
  * @retval 无
  */
void MQSensor_Scan(void);

#endif /* __GPIO_LED_SENSOR_H */