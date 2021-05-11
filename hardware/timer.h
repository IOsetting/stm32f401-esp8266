#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f4xx.h"

void Systick_Init(void);
void Systick_Delay_ms(uint32_t count);

void TIM1_Init(void);

void TIM2_Init(void);

void TIM3_Init(void);

#endif
