/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "rtthread.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//uint32_t time;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static struct rt_thread led1_thread;
static rt_uint8_t rt_led1_thread_stack[128];

static void led1_thread_entry(void *parameter);


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */



    /* USER CODE END Init */

    /* Configure the system clock */

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */


    /* USER CODE BEGIN 2 */
    rt_kprintf("RT-Thread Begin Main!\n");
    rt_thread_init(&led1_thread, /* 线程控制块 */
                   "led1", /* 线程名字 */
                   led1_thread_entry, /* 线程入口函数 */
                   RT_NULL,
                   &rt_led1_thread_stack[0], /* 线程栈起始地址 */
                   sizeof(rt_led1_thread_stack), /* 线程栈大小 */
                   3, /* 线程的优先级 */
                   20); /* 线程时间片 */

    rt_thread_startup(&led1_thread);
    /* USER CODE END 2 */


}

static void led1_thread_entry(void *parameter) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
        rt_thread_delay(500); /* 延时 500 个 tick */
//        rt_thread_stack_info
    }
}


