/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtconfig.h>
#include "usart.h"

#include "stm32g4xx_hal_uart.h"

//extern  UART_HandleTypeDef UartHandle;

#ifndef RT_USING_FINSH
#error Please uncomment the line <#include "finsh_config.h"> in the rtconfig.h
#endif

#ifdef RT_USING_FINSH

RT_WEAK char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    int ch = -1;

//    UART_printf(&huart1,"finished\n");

//#error "TODO 4: Read a char from the uart and assign it to 'ch'."

    return ch;
}

#endif /* RT_USING_FINSH */

