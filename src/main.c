/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f7xx.h"
#include "stm32f7xx_nucleo_144.h"

#include "FreeRTOS.h"
#include "Task.h"

#include "HBL.h"
#include "UV_Sensor.h"
#include "Temperature_Sensor.h"


//=================================================================================
// Communication Task
//=================================================================================
void Task_Communication_Handler(void *params);

//=================================================================================
// Analog Task
//=================================================================================

void Task_Analog_Handler(void *params);

void SystemClock_Config(void);

TaskHandle_t xTask_Handle_Comm = NULL;
TaskHandle_t xTask_Handle_Analog = NULL;


int main(void)
{
    // Reset of all peripherals, Initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Init configured peripherals */
	HBL__Initialize();

	 /* Create the thread(s) */
     xTaskCreate(Task_Communication_Handler,"Task_Communication", (uint16_t)256, NULL, 2, &xTask_Handle_Comm);
     xTaskCreate(Task_Analog_Handler,"Task_Analog", configMINIMAL_STACK_SIZE, NULL, 2, &xTask_Handle_Analog);

    // Start OS Scheduler
     vTaskStartScheduler();

	for(;;);
}

void Task_Communication_Handler(void *params)
{
	const TickType_t xDelay = 10 / portTICK_PERIOD_MS;

	while(1)
	{
	    HBL__UART_Transmit(UV_Sensor__Convert_Raw(), UV_Sensor__Get_Filtered());
	    vTaskDelay( xDelay );
	};
}

void Task_Analog_Handler(void *params)
{
	while(1)
	{

	};
}


void SystemClock_Config()
{
	RCC_OscInitTypeDef osc_config;
	RCC_ClkInitTypeDef clk_config;
	RCC_PeriphCLKInitTypeDef periph_clk_config;
	uint8 flash_latency;

	flash_latency = 0;

	// Clock source configuration
	osc_config.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_config.HSIState = RCC_HSI_ON;
	osc_config.HSICalibrationValue = 16;
	osc_config.PLL.PLLState = RCC_PLL_OFF;

    // Clock frequency 120MHz configuration
    osc_config.PLL.PLLM = 16;
    osc_config.PLL.PLLN = 240;
    osc_config.PLL.PLLP = 2;
	osc_config.PLL.PLLQ = 2;
	osc_config.PLL.PLLR = 2;

	clk_config.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_config.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	clk_config.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_config.APB1CLKDivider = RCC_HCLK_DIV4;
	clk_config.APB2CLKDivider = RCC_HCLK_DIV2;

	flash_latency = FLASH_ACR_LATENCY_3WS;

 if(HAL_RCC_OscConfig(&osc_config) != HAL_OK)
 {
	 asm("bkpt 255");
 }

 if(HAL_RCC_ClockConfig(&clk_config, flash_latency) != HAL_OK)
 {
	 asm("bkpt 255");
 }

 // Peripherals clock configuration
 periph_clk_config.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_CLK48;
 periph_clk_config.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
 periph_clk_config.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
 periph_clk_config.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;

 if (HAL_RCCEx_PeriphCLKConfig(&periph_clk_config) != HAL_OK)
 {
	 asm("bkpt 255");
 }

 // Configure SysTick
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}
