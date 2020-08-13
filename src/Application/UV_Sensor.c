/*
 * Light_Sensor.c
 *
 *  Created on: 19 May 2020
 *      Author: Yuri ALVARENGA
 */

#include "UV_Sensor.h"

// Define number of filter taps
#define NUM_OF_TAP  3

// Bessel IIR filter parameters
const float32_t IIR_FILTER_PARAMS_B[NUM_OF_TAP + 1] = {0.0000551660403,  0.000165498121, 0.000165498121,  0.0000551660403};
const float32_t IIR_FILTER_PARAMS_A[NUM_OF_TAP + 1] = {0, -2.81193544, 2.6383838, -0.82600703};

/**
    Applies filter to the uv sensor signal
    @param float32_t *uv_filtered
    @return .
*/
void apply_filter(float32_t *uv_filtered);

float32_t UV_Sensor__Convert_Raw(void)
{

	uint32_t  uv_adc_raw = 0;
	float32_t uv_value = 0;

	// get adc raw value
	HBL__GetAnalogInput(0,&uv_adc_raw);

	// convert adc raw into voltage value
	uv_value = (((float32_t)uv_adc_raw)/ADC_10_BITS_RES)*ADC_VCC;

	return(uv_value);
}


float32_t UV_Sensor__Get_Filtered()
{
	float32_t uv_filtered = 0;

	apply_filter(&uv_filtered);

	return (uv_filtered);
}


void apply_filter(float32_t *uv_filtered)
{
	static BOOL_TYPE filter_init = TRUE;

    // Circular data buffers for accumulation of signal input and out samples
	static float32_t buff_in[sizeof(IIR_FILTER_PARAMS_A)/sizeof(float32_t)];
    static float32_t buff_out[sizeof(IIR_FILTER_PARAMS_A)/sizeof(float32_t)];

    float32_t filter_sum = 0;
    float32_t uv_raw;

	// index for counters
	uint8_t i;

	uv_raw = UV_Sensor__Convert_Raw();

	// init buffers
	if(TRUE == filter_init)
	{
		filter_init = FALSE;

		for(i = 0; i < sizeof(IIR_FILTER_PARAMS_A)/sizeof(float32_t); i++)
		{
			buff_in[i] = uv_raw;
			buff_out[i] = uv_raw;
		}
	}
	else
	{
		buff_in[0] = uv_raw;
	}

	filter_sum = 0;

	// calculate filter sum
	for(i = 0; i < sizeof(IIR_FILTER_PARAMS_A)/sizeof(float32_t); i++)
	{
		filter_sum = filter_sum + (IIR_FILTER_PARAMS_B[i]*buff_in[i]) - (IIR_FILTER_PARAMS_A[i]*buff_out[i]);
	}

	// updated buffer with sum value
	buff_out[0] = filter_sum;

	*uv_filtered = buff_out[0];

	// updated circular buffers values
	for(i = sizeof(IIR_FILTER_PARAMS_A)/sizeof(float32_t); i > 1; i--)
	{
		buff_out[i-1] = buff_out[i-2];
		buff_in[i-1]  = buff_in[i-2];
	}

}
