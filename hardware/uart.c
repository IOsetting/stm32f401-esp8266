#include <stdio.h>
#include "uart.h"

#ifdef PRINT_TO_UART

#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  while(USART_GetFlagStatus(PRINT_USARTX, USART_FLAG_TXE) == RESET){}
  USART_SendData(PRINT_USARTX, ch);
  return(ch);
}

int fgetc(FILE *f) {
  char ch;
  while(USART_GetFlagStatus(PRINT_USARTX, USART_FLAG_RXNE) == RESET){}
  ch = USART_ReceiveData(PRINT_USARTX);
  return((int)ch);
}

int ferror(FILE *f) {
  return EOF;
}

void _ttywrch(int ch) {
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
  USART_SendData(PRINT_USARTX, ch);
}

void _sys_exit(int return_code) {
  while (1); /* endless loop */
}
#endif


/**
 * UART1: AP9, AP10
 */
void USART1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitTypeDef USART_InitStructure;
  USART_DeInit(USART1);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART1, &USART_InitStructure);
  USART_ClearFlag(USART1, USART_FLAG_CTS);
  USART_Cmd(USART1, ENABLE);
  printf("## UART1 Initialized ##\r\n");
}


