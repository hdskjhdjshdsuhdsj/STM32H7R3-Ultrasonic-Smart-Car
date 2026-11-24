#include "stm32h7rsxx_hal.h"
#include "ultrasonic.h"
#include "tim.h"
#include "ax_delay.h"
// GPIO初始化
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置Trig引脚为推挽输出
    GPIO_InitStruct.Pin = Trig_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);

    // 配置Echo引脚为浮空输入
    GPIO_InitStruct.Pin = Echo_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);
}

// 产生Trig信号
void Ultrasound_TRIG(void)
{
    HAL_GPIO_WritePin(GPIO_PORT, Trig_Pin, GPIO_PIN_SET);
    AX_Delayus(20);  // 产生20us的脉冲
    HAL_GPIO_WritePin(GPIO_PORT, Trig_Pin, GPIO_PIN_RESET);
}

// 测量距离
float Ultrasound_Measure(void)
{
		__HAL_TIM_CLEAR_IT(&htim5, TIM_IT_UPDATE);
    uint32_t time_us = 0;
    float distance_cm = 0;
    uint8_t valid_samples = 0;
    float sum_distance = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        Ultrasound_TRIG();
        uint32_t timeout = 0;

        // 等待Echo引脚变为高电平
        while (HAL_GPIO_ReadPin(GPIO_PORT, Echo_Pin) == GPIO_PIN_RESET)
        {
            if (++timeout > 30000) return -1;  // 超时返回-1（错误）
            AX_Delayms(1);
        }

        // 开始计时
        __HAL_TIM_SET_COUNTER(&htim5, 0);  // 清零计时器
        while (HAL_GPIO_ReadPin(GPIO_PORT, Echo_Pin) == GPIO_PIN_SET)
        {
            if (++timeout > 30000) break;  // 超时跳出
            AX_Delayms(1);
        }

        // 获取计时结果
        time_us = __HAL_TIM_GET_COUNTER(&htim5);
        distance_cm = time_us / 58.0f;  // 声速公式：距离 = (时间μs) / 58  CM

        if (distance_cm >= 0 && distance_cm <= 300)
        {
            sum_distance += distance_cm;
            valid_samples++;
        }
        AX_Delayms(60);  // 两次测量间隔60ms
    }

    return (valid_samples > 0) ? (sum_distance / valid_samples) : -1;
}