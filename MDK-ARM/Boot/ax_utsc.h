
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_UTSC_H
#define __AX_UTSC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

//接口函数
void AX_UTSC_Init(void);       //舵机接口初始化
void AX_UTSC_StartUp(void);         //启动超声波测距
uint32_t AX_UTSC_GetDistance(void);  //获取超声波测距数据


#endif

