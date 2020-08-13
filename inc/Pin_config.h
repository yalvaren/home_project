/*
 * Pin_config.h
 *
 *  Created on: 29 Apr 2020
 *      Author: Yuri ALVARENGA
 */


#ifndef PIN_CONFIG_H_
#define PIN_CONFIG_H_

#include "stm32f7xx_hal.h"

//! Structure to define the pin configuration.
typedef struct
{
	GPIO_TypeDef* port;
	uint32_t      Pin;
	uint32_t      Mode;
	uint32_t      Pull;
	uint32_t      Speed;
	uint32_t      Alternate;
	void *        Device;
	uint32_t      Param0;
	uint32_t      Param1;

} PIN_CONFIG_DATA_TYPE;

// Pin configuration table
#define PIN_LIST { \
	/*port     pin             pin mode                pull             pin speed            alternate func     device     param0                        param1                     */                \
	{GPIOB    ,GPIO_PIN_7     ,GPIO_MODE_OUTPUT_PP    ,GPIO_NOPULL     ,GPIO_SPEED_FAST     ,0                 ,0         ,0                            ,0      },  /* Blue LED     */                \
    {GPIOB    ,GPIO_PIN_14    ,GPIO_MODE_OUTPUT_PP    ,GPIO_NOPULL     ,GPIO_SPEED_FAST     ,0                 ,0         ,0                            ,0      },  /* Red LED      */                \
    {GPIOB    ,GPIO_PIN_1     ,GPIO_MODE_ANALOG       ,GPIO_NOPULL     ,GPIO_SPEED_LOW      ,0                 ,ADC1      ,ADC_CHANNEL_9                ,0      },  /* Light Sensor */                \
    {GPIOC    ,GPIO_PIN_2     ,GPIO_MODE_ANALOG       ,GPIO_NOPULL     ,GPIO_SPEED_LOW      ,0                 ,ADC2      ,ADC_CHANNEL_12               ,0      },  /* Soil Sensor  */                \
    {GPIOB    ,GPIO_PIN_9     ,GPIO_MODE_AF_OD        ,GPIO_PULLUP     ,GPIO_SPEED_FAST     ,GPIO_AF4_I2C1     ,I2C1      ,0                            ,0      },  /* Temp/Humid Sensor I2C SDA  */  \
    {GPIOB    ,GPIO_PIN_8     ,GPIO_MODE_AF_OD        ,GPIO_NOPULL     ,GPIO_SPEED_FAST     ,GPIO_AF4_I2C1     ,0         ,0                            ,0      },  /* Temp/Humid Sensor I2C SCL  */  \
    {GPIOD    ,GPIO_PIN_8     ,GPIO_MODE_AF_PP        ,GPIO_NOPULL     ,GPIO_SPEED_HIGH     ,GPIO_AF7_USART3   ,USART3    ,0                            ,0      },  /* USART3 RX  */                  \
    {GPIOD    ,GPIO_PIN_9     ,GPIO_MODE_AF_PP        ,GPIO_NOPULL     ,GPIO_SPEED_HIGH     ,GPIO_AF7_USART3   ,0         ,0                            ,0      },  /* USART3 TX  */                  \
    {GPIOD    ,GPIO_PIN_5     ,GPIO_MODE_AF_PP        ,GPIO_NOPULL     ,GPIO_SPEED_HIGH     ,GPIO_AF7_USART2   ,USART2    ,0                            ,0      },  /* USART2 RX */                   \
    {GPIOA    ,GPIO_PIN_3     ,GPIO_MODE_AF_PP        ,GPIO_NOPULL     ,GPIO_SPEED_HIGH     ,GPIO_AF7_USART2   ,0         ,0                            ,0      },} /* USART2 TX */

// Define number of pins
#define NUM_OF_PIN   10

// Define peripheral amount used
#define NUM_OF_ADC   2
#define NUM_OF_I2C   1
#define NUM_OF_USART 2

// Macro for peripherals clock enabling
#define GPIO_CLK_ENABLE()    {__HAL_RCC_GPIOA_CLK_ENABLE();__HAL_RCC_GPIOB_CLK_ENABLE(); __HAL_RCC_GPIOC_CLK_ENABLE();__HAL_RCC_GPIOD_CLK_ENABLE();}
#define ADC_CLK_ENABLE()     {__ADC1_CLK_ENABLE();__ADC2_CLK_ENABLE();}
#define I2C_CLK_ENABLE()     {__I2C1_CLK_ENABLE();}
#define UART_CLK_ENABLE()    {__USART3_CLK_ENABLE();__USART2_CLK_ENABLE();}

#endif /* PIN_CONFIG_H_ */
