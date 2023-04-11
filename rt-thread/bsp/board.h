#ifndef __BOARD_H__
#define __BOARD_H__



#include "stm32g4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32g4xx_hal_uart.h"


void rt_hw_board_init(void);

void SysTick_Handler(void);

void Error_Handler(void);

void SystemClock_Config(void);

static int uart_init(void);

char rt_hw_console_getchar(void);

#endif