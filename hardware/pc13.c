#include <stdio.h>
#include "pc13.h"

void PC13_Init(void)
{
  GPIO_InitTypeDef  gpioInitTypeDef;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpioInitTypeDef.GPIO_Pin   = GPIO_Pin_13;
	gpioInitTypeDef.GPIO_Mode  = GPIO_Mode_OUT;
	gpioInitTypeDef.GPIO_OType = GPIO_OType_PP;
	gpioInitTypeDef.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC,&gpioInitTypeDef);
  printf("## PC13 Initialized ##\r\n");
}

void PC13_Off(void)
{
  GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void PC13_On(void)
{
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
