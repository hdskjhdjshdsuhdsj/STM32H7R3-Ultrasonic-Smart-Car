#ifndef __AX_BEEP_H
#define __AX_BEEP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

// 接口函数
void AX_BEEP_Init(void);

// 蜂鸣器操作函数宏定义
#define AX_BEEP_On()          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)      // 蜂鸣器鸣叫
#define AX_BEEP_Off()         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)    // 蜂鸣器关闭
#define AX_BEEP_Toggle()      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)                   // 蜂鸣器状态翻转

#endif