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
#include "sht3x.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_STACK_SIZE 1024	// stack size definition
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t temperature_read_stack[THREAD_STACK_SIZE];	// thread stack definition
TX_THREAD temperature_read_ptr;	// thread pointer definition

extern float temperature, humidity;	// temperature and humidity variables from main.c definition
extern I2C_HandleTypeDef hi2c1;		// i2c channel form main.c definition
sht3x_handle_t handle = { .i2c_handle = &hi2c1, .device_address =
		SHT3X_I2C_DEVICE_ADDRESS_ADDR_PIN_LOW };	// i2c channel and address definition
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID temperature_read_entry(ULONG initial_input);	// thread definition
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
  tx_thread_create(&temperature_read_ptr, "temperature_read", temperature_read_entry, 0x1234,
		  temperature_read_stack, THREAD_STACK_SIZE, 15, 15, 1, TX_AUTO_START);	// Initialization of SHT30 reading thread.
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
VOID temperature_read_entry(ULONG initial_input)
{
	/**
	 * @note   SHT 30 temperature and humidity reading thread.
	 */
	while(1)
	{

		sht3x_read_temperature_and_humidity(&handle, &temperature, &humidity);
		// read i2c data from temperature and humidity with using defined "handle" parameters.

		tx_thread_sleep(100);	// thread sleeps for 1 seconds
	}
}
/* USER CODE END 1 */
