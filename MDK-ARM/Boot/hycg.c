#include "delay.h"
#include "car.h"
#include "stm32h7rsxx_hal.h"

/**************************************************************************************/
/* GPIO初始化配置 */
/**************************************************************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    __HAL_RCC_GPIOB_CLK_ENABLE(); //使能GPIOB时钟
    __HAL_RCC_GPIOD_CLK_ENABLE(); //使能GPIOD时钟

    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIOB
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化GPIOD

    // 配置PB6为浮空输入模式（火焰传感器）
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置PD15为推挽输出模式（LED）
    GPIO_InitStructure.Pin = GPIO_PIN_14;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // 初始状态，熄灭指示灯
}

/**************************************************************************************/
/* 火焰传感器检测 */
/**************************************************************************************/
void MQSensor_Scan(void)
{
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) // 火焰传感器用引脚PB6为低电平
    {
        HAL_Delay(10); // 延时防抖动
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) // 火焰传感器用引脚PB6为低电平
        {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); // 点亮LED
						stop(); // 调用停车函数
        }
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // 熄灭LED
				go_straight();
    }
}