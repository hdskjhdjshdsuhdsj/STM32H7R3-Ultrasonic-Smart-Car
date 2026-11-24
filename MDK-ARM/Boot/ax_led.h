#ifndef __AX_LED_H
#define __AX_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

// 接口函数
void AX_LED_Init(void);

// LED操作函数宏定义
#define AX_LED_Red_Off()          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)      // 红色LED熄灭
#define AX_LED_Red_On()           HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)    // 红色LED点亮
#define AX_LED_Red_Toggle()       HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4)                   // 红色LED状态翻转

#define AX_LED_Green_Off()        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)      // 绿色LED熄灭
#define AX_LED_Green_On()         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)    // 绿色LED点亮
#define AX_LED_Green_Toggle()     HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8)                   // 绿色LED状态翻转

#endif