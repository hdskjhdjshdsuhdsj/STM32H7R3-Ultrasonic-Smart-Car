#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32h7rsxx_hal.h"

// 定义GPIO引脚
#define Trig_Pin GPIO_PIN_1
#define Echo_Pin GPIO_PIN_0
#define GPIO_PORT GPIOA

// 函数声明
void GPIO_Init(void);
void Ultrasound_TRIG(void);
float Ultrasound_Measure(void);

#endif /* __ULTRASONIC_H */
