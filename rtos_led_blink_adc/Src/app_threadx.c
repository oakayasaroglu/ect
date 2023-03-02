/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_STACK_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t blink_blue_led_stack[THREAD_STACK_SIZE];
TX_THREAD blink_blue_led_ptr;

uint8_t calculate_blink_rate_stack[THREAD_STACK_SIZE];
TX_THREAD calculate_blink_rate_ptr;



extern uint32_t aADCxConvertedData[0];

double_t blink_rate=0.5;
uint32_t blink_period=100;
uint32_t set_time=100;
uint32_t reset_time=100;
//ADC_HandleTypeDef hadc1;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID blink_blue_led_entry(ULONG initial_input);
VOID calculate_blink_rate_entry(ULONG initial_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

   /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  tx_thread_create(&blink_blue_led_ptr, "blink_blue_led", blink_blue_led_entry, 0x1234, blink_blue_led_stack, THREAD_STACK_SIZE, 15, 15, 1, TX_AUTO_START);
  tx_thread_create(&calculate_blink_rate_ptr, "calculate_blink_rate", calculate_blink_rate_entry, 0x1234, calculate_blink_rate_stack, THREAD_STACK_SIZE, 14, 14, 1, TX_AUTO_START);
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
VOID blink_blue_led_entry(ULONG initial_input)
{
	while(1)
	{

		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, SET);
		tx_thread_sleep(set_time);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, RESET);
		tx_thread_sleep(reset_time);
	}
}

VOID calculate_blink_rate_entry(ULONG initial_input)
{
	while(1)
	{
		blink_rate = (double_t)aADCxConvertedData[0]/(double_t)4095;
		set_time = blink_rate*blink_period;
		reset_time = (1-blink_rate)*blink_period;
		tx_thread_sleep(20);
	}
}

/* USER CODE END 1 */
