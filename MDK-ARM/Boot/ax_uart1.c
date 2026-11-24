#include "ax_uart1.h"
#include <stdio.h>
#include <string.h>

// 定义一个 UART 句柄
UART_HandleTypeDef huart1;

/**
  * @简  述  UART 串口初始化
  * @参  数  baud： 波特率设置
  * @返回值	 无
  */
void AX_UART1_Init(uint32_t baud)
{
    // 初始化 USART1
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud; // 设置波特率
    huart1.Init.WordLength = UART_WORDLENGTH_8B; // 设置数据位
    huart1.Init.StopBits = UART_STOPBITS_1; // 设置停止位
    huart1.Init.Parity = UART_PARITY_NONE; // 设置无校验位
    huart1.Init.Mode = UART_MODE_TX_RX; // 设置模式为发送和接收
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE; // 设置无硬件流控制
    huart1.Init.OverSampling = UART_OVERSAMPLING_16; // 设置过采样
}

/**************************串口打印相关函数重定义********************************/
/**
  * @简  述  重定义putc函数（USART1）	
  */
int fputc(int ch, FILE *f)
{
    // 发送一个字符
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/**
  * @简  述  重定义getc函数（USART1）	
  */
int fgetc(FILE *f)
{
    uint8_t ch;
    // 接收一个字符
    HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
    return ch;
}