#include "sys.h"


//需要用到四个超神波，前后左右，就是8个IO口 
//4个输入 4个输出


void Ultrasound_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	//输入
	GPIO_InitTypeDef GPIO_InitStructur;
	GPIO_InitStructur.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructur.GPIO_Pin=Front_IN_Pin | Back_IN_Pin | Left_IN_Pin | Right_IN_Pin;
	GPIO_InitStructur.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructur.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructur);
	//输出
	GPIO_InitStructur.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructur.GPIO_Pin=Front_OUT_Pin | Back_OUT_Pin | Left_OUT_Pin | Right_OUT_Pin;
	GPIO_InitStructur.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructur.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructur);
	//计时1us
	TIM_TimeBaseInitTypeDef TIM_InitStructur;
	TIM_InitStructur.TIM_Period = 999; 
    TIM_InitStructur.TIM_Prescaler = 83;  
    TIM_InitStructur.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructur.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_InitStructur);

    TIM_Cmd(TIM7, DISABLE);
	
}

void Ultrasound_TRIG(GPIO_TypeDef * GPIOx,uint16_t TRIG_Pin)
{
    GPIO_SetBits(GPIOx,TRIG_Pin);
	Delay_us(20);
	GPIO_ResetBits(GPIOx,TRIG_Pin);
}


float Ultrasound_Measure(GPIO_TypeDef* GPIOx, uint16_t Trig_Pin, uint16_t Echo_Pin) 
{
    uint32_t time_us = 0;
    float distance_cm = 0;
    uint8_t valid_samples = 0;
    float sum_distance = 0;
    for (uint8_t i = 0; i < 3; i++) 
       {
		    Ultrasound_TRIG(GPIOx, Trig_Pin);
            uint32_t timeout = 0;
            while (GPIO_ReadInputDataBit(GPIOx, Echo_Pin) == 0) 
				{
                    if (++timeout > 30000) return -1;  // 超时返回-1（错误）
                    Delay_us(1);
                }
            TIM7->CNT = 0;
            TIM_Cmd(TIM7, ENABLE);
            timeout = 0;
            while (GPIO_ReadInputDataBit(GPIOx, Echo_Pin) == 1) 
				{
                   if (++timeout > 30000) break;  // 超时跳出
                   Delay_us(1);
                }
            TIM_Cmd(TIM7, DISABLE);
            time_us = TIM7->CNT;
            distance_cm = time_us / 58.0f;  // 声速公式：距离 = (时间μs) / 58  CM
            if (distance_cm >= 0 && distance_cm <= 300) 
				{
                    sum_distance += distance_cm;
                    valid_samples++;
                }
             Delay_ms(60); 
       }
       return (valid_samples > 0) ? (sum_distance / valid_samples) : -1;
}

void Ultrasound_Go(void)//操作反应函数
{
//	float Front_Ultrasound,Back_Ultrasound,Left_Ultrasound,Right_Ultrasound;
//	Front_Ultrasound=Ultrasound_Measure(GPIOA,Front_OUT_Pin,Front_IN_Pin);
//	Delay_ms(50);
//	Back_Ultrasound=Ultrasound_Measure(GPIOA,Back_OUT_Pin,Back_IN_Pin);
//	Delay_ms(50);
//	Left_Ultrasound=Ultrasound_Measure(GPIOA,Left_OUT_Pin,Left_IN_Pin);
//	Delay_ms(50);
//	Right_Ultrasound=Ultrasound_Measure(GPIOA,Right_OUT_Pin,Right_IN_Pin);
//	if(Front_Ultrasound<Front_Barrier)
//	{
//		
//	}
	
	
}
