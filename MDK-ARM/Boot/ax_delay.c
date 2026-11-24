#include "ax_delay.h"
#include "stm32h7rsxx_hal.h"

// SysTick时钟因子 (每微秒的计数值)
static uint32_t clock_factor = 0;

// 检查初始化状态的标志
static uint8_t initialized = 0;

// 内部延迟函数 (使用SysTick)
static void _delay_ticks(uint32_t ticks) {
    if(ticks == 0) return; // 避免无效延迟
    
    uint32_t temp;
    
    // 设置重载值
    if(ticks > SysTick_LOAD_RELOAD_Msk) {
        ticks = SysTick_LOAD_RELOAD_Msk; // 限制最大值
    }
    SysTick->LOAD = ticks;
    
    // 清除当前值并使能SysTick
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    
    // 等待计数完成
    do {
        temp = SysTick->CTRL;
    } while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    
    // 禁用SysTick并清除当前值
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0;
}

/**
 * 初始化延迟功能
 * 配置SysTick定时器并设置时钟因子
 */
void AX_Delay_Init(void) {
    if (initialized) return;
    
    // 获取HCLK频率并计算时钟因子 (每微秒的计数值)
    clock_factor = HAL_RCC_GetHCLKFreq() / 1000000;
    
    // 确保时钟因子有效
    if(clock_factor == 0) {
        clock_factor = 1; // 防止除零错误
    }
    
    // 设置SysTick中断优先级
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    
    initialized = 1;
}

/**
 * 微秒级延迟
 * @param us 延迟时间 (微秒)
 */
void AX_Delayus(uint16_t us) {
    if(!initialized || us == 0) return;
    
    // 计算需要的计数值
    uint32_t ticks = (uint32_t)us * clock_factor;
    
    // 执行延迟
    _delay_ticks(ticks);
}

/**
 * 毫秒级延迟
 * @param ms 延迟时间 (毫秒)
 */
void AX_Delayms(uint16_t ms) {
    if(!initialized || ms == 0) return;
    
    // 大延迟分块处理，防止SysTick溢出
    while(ms > 0) {
        uint16_t chunk = (ms > 500) ? 500 : ms;
        
        // 计算需要的计数值 (毫秒转换为微秒)
        uint32_t ticks = (uint32_t)chunk * 1000 * clock_factor;
        
        // 执行延迟
        _delay_ticks(ticks);
        
        ms -= chunk;
    }
}
