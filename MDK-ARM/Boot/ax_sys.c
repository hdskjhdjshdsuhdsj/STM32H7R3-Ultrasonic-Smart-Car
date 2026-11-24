#include "ax_sys.h"
#include "stm32h7rsxx.h"  // 必须包含的芯片头文件

// 手动添加缺失的寄存器定义（当HAL库不完整时）
#define SYSCFG_BASE       (0x58000400UL)    // 根据H7RS手册确认地址
#define SYSCFG_CFGR1      (*(volatile uint32_t*)(SYSCFG_BASE + 0x00))

// RCC寄存器位定义（根据RM0492手册）
#define RCC_APB4ENR_SYSCFGEN_Pos  (1U)      // APB4ENR的SYSCFGEN在第1位

/**
  * @简  述  JTAG/SWD模式设置（适配STM32H7RS）
  */
void AX_JTAG_Set(uint8_t mode)
{
    // 模式映射（对应CFGR1[2:0]）
    const uint32_t swj_cfg = (mode == 0x02) ? 0x4 :  // Disable
                             (mode == 0x01) ? 0x2 :  // SWD
                                             0x0;    // Full

    // 使能SYSCFG时钟（直接操作寄存器位）
    RCC->APB4ENR |= (1 << RCC_APB4ENR_SYSCFGEN_Pos);
    
    // 内存屏障确保写操作完成
    __DSB();
    __ISB();

    // 配置调试端口
    SYSCFG_CFGR1 = (SYSCFG_CFGR1 & ~0x7) | swj_cfg; // 清除后设置[2:0]
}