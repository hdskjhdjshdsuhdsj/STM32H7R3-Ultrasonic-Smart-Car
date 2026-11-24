/**
 * @file    ax_delay.h
 * @author  Your Name
 * @version 1.0
 * @date    2025-05-12
 * @brief   延时功能接口
 */

#ifndef AX_DELAY_H
#define AX_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/**
 * @brief 初始化延时功能
 * @param 无
 * @retval 无
 */
void AX_Delay_Init(void);

/**
 * @brief 实现微秒级延时
 * @param us 延时长度，单位为微秒
 * @retval 无
 */
void AX_Delayus(uint16_t us);

/**
 * @brief 实现毫秒级延时
 * @param ms 延时长度，单位为毫秒
 * @retval 无
 */
void AX_Delayms(uint16_t ms);

#endif /* AX_DELAY_H */
