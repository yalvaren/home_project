/*
 * HBL.c
 *
 *  Created on: 27 Oct 2018
 *      Author: Yuri ALVARENGA
 */


#include "Pin_config.h"
#include "HBL.h"


const PIN_CONFIG_DATA_TYPE PIN_CONFIG[] = PIN_LIST;

ADC_HandleTypeDef Adc_Handle[NUM_OF_ADC];
I2C_HandleTypeDef I2C_Handle[NUM_OF_I2C];
UART_HandleTypeDef UART_Handle[NUM_OF_USART];

void ADC_config(void * adc_id, uint32_t channel, uint8 instance);
void I2C_config(void * i2c_id, uint8_t instance);
void UART_config();



void HBL__Initialize(void)
{
	//Initialize peripherals clock
	GPIO_CLK_ENABLE();
	ADC_CLK_ENABLE();
	UART_CLK_ENABLE();

	uint8 pin_counter;

	uint8 adc_idx = 0;
	uint8 usart_idx = 0;

	GPIO_InitTypeDef gpio_init[NUM_OF_PIN] = {0};

   // Configure the GPIO pins based on the PIN_CONFIG_LIST table
	for (pin_counter = 0; pin_counter < (sizeof(gpio_init)/sizeof(GPIO_InitTypeDef)); pin_counter++)
	{

		// Configure generic I/O pins
		gpio_init[pin_counter].Pin = PIN_CONFIG[pin_counter].Pin;
		gpio_init[pin_counter].Mode = PIN_CONFIG[pin_counter].Mode;
		gpio_init[pin_counter].Pull = PIN_CONFIG[pin_counter].Pull;
		gpio_init[pin_counter].Speed = PIN_CONFIG[pin_counter].Speed;
		gpio_init[pin_counter].Alternate = PIN_CONFIG[pin_counter].Alternate;

		HAL_GPIO_Init(PIN_CONFIG[pin_counter].port, &gpio_init[pin_counter]);

		// Configure ADC
		if(GPIO_MODE_ANALOG == PIN_CONFIG[pin_counter].Mode)
		{
			ADC_config(PIN_CONFIG[pin_counter].Device, PIN_CONFIG[pin_counter].Param0, adc_idx);
			++adc_idx;
		}

		// Configure USART
		if(USART2 || USART3 == PIN_CONFIG[pin_counter].Device)
		{

			UART_Handle[usart_idx].Instance = PIN_CONFIG[pin_counter].Device;
			UART_Handle[usart_idx].Init.BaudRate = 115200;
			UART_Handle[usart_idx].Init.WordLength = UART_WORDLENGTH_8B;
			UART_Handle[usart_idx].Init.StopBits = USART_STOPBITS_1;
			UART_Handle[usart_idx].Init.Parity = USART_PARITY_NONE;
			UART_Handle[usart_idx].Init.Mode = UART_MODE_TX_RX;
			UART_Handle[usart_idx].Init.HwFlowCtl = UART_HWCONTROL_NONE;
			UART_Handle[usart_idx].Init.OverSampling = UART_OVERSAMPLING_16;
			UART_Handle[usart_idx].Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
			UART_Handle[usart_idx].AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

			if (HAL_UART_Init(&UART_Handle[usart_idx]) != HAL_OK)
			{
				asm("bkpt 255");
			}

			++usart_idx;
		}
	}

}
void HBL__SetDigitalOutput(DIGITAL_OUTPUTS_TYPE digital_output, GPIO_PinState state)
{
	if (digital_output < DO_MAX)
	{
		HAL_GPIO_WritePin(PIN_CONFIG[digital_output].port, PIN_CONFIG[digital_output].Pin, state);
	}
}

BOOL_TYPE HBL__GetDigitalOutput(DIGITAL_OUTPUTS_TYPE digital_output)
{
	BOOL_TYPE state;
	state = FALSE;

	return(state);
}


HBL_StatusTypeDef HBL__GetAnalogInput(uint8 pin_instance, uint32_t *adc_value)
{
	HBL_StatusTypeDef result = HBL_ERROR;


	if (HAL_ADC_PollForConversion(&Adc_Handle[pin_instance], ADC_CONVERSION_TIMEOUT) == HAL_OK)
	{
		*adc_value = HAL_ADC_GetValue(&Adc_Handle[pin_instance]);
	}

	return (result);
}

HBL_StatusTypeDef HBL__I2CTransmit(uint8_t instance, uint8_t *pdata, uint16_t data_size)
{
	HBL_StatusTypeDef result = HBL_OK;

	if(HAL_I2C_Master_Transmit(&I2C_Handle[instance], AM2320_ADDR, pdata, sizeof(pdata),1 ) != HAL_OK)
	{
		result = HBL_ERROR;
	}

	return (result);
}

HBL_StatusTypeDef HBL__I2CReceive(uint8_t instance, uint8_t *pdata, uint16_t data_size)
{
	HBL_StatusTypeDef result = HBL_OK;

	if(HAL_I2C_Master_Receive(&I2C_Handle[instance], AM2320_ADDR, pdata, sizeof(pdata), HAL_MAX_DELAY) != HAL_OK)
	{
		result = HBL_ERROR;
	}

	return (result);
}

void I2C1_EV_IRQHandler()
{
    HAL_I2C_EV_IRQHandler(&I2C_Handle[0]);
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    asm("bkpt 255");
}

HBL_StatusTypeDef HBL__UART_Transmit(float32_t data_raw, float32_t data_filtered)
{
	HBL_StatusTypeDef result = HBL_OK;

	char buffer[32];

    if (HAL_UART_Transmit(&UART_Handle[0], (uint8_t *)buffer, sprintf(buffer, "%g,%g\r\n",data_raw, data_filtered ),100) != HAL_OK)
    {
        result = HBL_ERROR;
    }

    return result;
}


void ADC_config(void * adc_id, uint32_t channel, uint8 pin_instance)
{
	ADC_ChannelConfTypeDef adcChannel;

	uint32_t current_adc_id = (uint32_t)adc_id;;
	static uint32_t last_adc_id = 0;

	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

    // Only configure ADC for different ADC instances
	if(current_adc_id != last_adc_id)
	{
		Adc_Handle[pin_instance].Instance = adc_id;

		Adc_Handle[pin_instance].Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
		Adc_Handle[pin_instance].Init.Resolution = ADC_RESOLUTION_10B;
		Adc_Handle[pin_instance].Init.ScanConvMode = DISABLE;
		Adc_Handle[pin_instance].Init.ContinuousConvMode = ENABLE;
		Adc_Handle[pin_instance].Init.DiscontinuousConvMode = DISABLE;
		Adc_Handle[pin_instance].Init.NbrOfDiscConversion = 0;
		Adc_Handle[pin_instance].Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE ;
		Adc_Handle[pin_instance].Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
		Adc_Handle[pin_instance].Init.DataAlign = ADC_DATAALIGN_RIGHT;
		Adc_Handle[pin_instance].Init.NbrOfConversion = 1;
		Adc_Handle[pin_instance].Init.DMAContinuousRequests = ENABLE;
		Adc_Handle[pin_instance].Init.EOCSelection = DISABLE;

		HAL_ADC_Init(&Adc_Handle[pin_instance]);
	}

	last_adc_id = current_adc_id;

	adcChannel.Channel = channel;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;

	if (HAL_ADC_ConfigChannel(&Adc_Handle[pin_instance], &adcChannel) != HAL_OK)
	{
		asm("bkpt 255");
	}

	HAL_ADC_Start(&Adc_Handle[pin_instance]);
}

void I2C_config(void * i2c_id, uint8 instance)
{


	I2C_Handle[instance].Instance = i2c_id;

	I2C_Handle[instance].Init.Timing = 0x2000090E;
	I2C_Handle[instance].Init.OwnAddress1 = 0;
	I2C_Handle[instance].Init.OwnAddress2 = 0;
	I2C_Handle[instance].Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_Handle[instance].Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_Handle[instance].Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	I2C_Handle[instance].Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_Handle[instance].Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


	I2C_CLK_ENABLE();

    if (HAL_I2C_Init(&I2C_Handle[instance]) != HAL_OK)
    {
        asm("bkpt 255");
    }

    NVIC_EnableIRQ(I2C1_EV_IRQn);
}

void UART_config()
{


}
