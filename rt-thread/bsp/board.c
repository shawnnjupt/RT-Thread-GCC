/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "board.h"

extern void SystemClock_Config(void);

#if 0
#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemCoreClockUpdate(void);

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }
    
    _SYSTICK_LOAD = ticks - 1; 
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;  
    
    return 0;
}

#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
static uint32_t rt_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Clock Update */
#if 0
    SystemCoreClockUpdate();
    
    /* System Tick Configuration */
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
#endif

    HAL_Init();
    SystemClock_Config();

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/RT_TICK_PER_SECOND);
    SystemCoreClockUpdate();




    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
//    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
    //gpio init
    MX_GPIO_Init();
    //uart init
    MX_USART1_UART_Init();
    uart_init();

}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}


#ifdef RT_USING_CONSOLE

 UART_HandleTypeDef UartHandle;

static int uart_init(void)
{
    /* TODO: Please modify the UART port number according to your needs */
    UartHandle.Instance = USART1;
    UartHandle.Init.BaudRate = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        while (1);
    }
    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&huart1);

    size = rt_strlen(str);

    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&UartHandle, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&UartHandle, (uint8_t *)(str + i), 1, 1);
    }
}
#endif


#ifdef RT_USING_FINSH
char rt_hw_console_getchar(void)
{
    int ch = -1;
//    UART_printf(&huart1,"finished\n");

    if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET)
    {
        ch = UartHandle.Instance->RDR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&UartHandle);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}

#endif



