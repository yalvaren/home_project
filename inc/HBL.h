/*
 * HBL.h
    Header file for HBL.c.
    @file HBL.h
    @author Yuri Alvarenga
 */

#ifndef HBL_HBL_H_
#define HBL_HBL_H_

// Define Arm cortex M7 math library
#define ARM_MATH_CM7

// Includes
#include "HBL_config.h"
#include "AM2320_sensor_defs.h"
#include "stm32f7xx_hal.h"
#include "arm_math.h"

// Defines
#define ADC_CONVERSION_TIMEOUT 1000000
#define ADC_10_BITS_RES 1024
#define ADC_VCC  3.3


// Error status enumeration
typedef enum
{
  HBL_OK       = 0x00U,
  HBL_ERROR    = 0x01U,
} HBL_StatusTypeDef;

/**
    Initialize Hardware base line and configure peripherals
    @param
    @return
*/
void HBL__Initialize(void);
/**
    Interface for setting digital outputs states
    @param
    @return.
*/
void HBL__SetDigitalOutput(DIGITAL_OUTPUTS_TYPE digital_output, GPIO_PinState state);

/**
    Interface for getting digital outputs states
    @param DIGITAL_OUTPUTS_TYPE digital_output, GPIO_PinState state
    @return.
*/
BOOL_TYPE HBL__GetDigitalOutput(DIGITAL_OUTPUTS_TYPE digital_output);

/**
    Interface for getting digital intputs states
    @param DIGITAL_OUTPUTS_TYPE digital_output
    @return BOOL_TYPE.
*/
BOOL_TYPE HBL__GetDigitalInput(DIGITAL_INPUTS_TYPE digital_input);

/**
    Interface for getting analog inputs
    @param uint8 pin_instance,uint32_t *adc_value
    @return HBL_OK or HBL_ERROR.
*/
HBL_StatusTypeDef HBL__GetAnalogInput(uint8 pin_instance,uint32_t *adc_value);

/**
    Interface for setting I2C transmission
    @param uint8_t instance, uint8_t *pdata, uint16_t data_size
    @return HBL_OK or HBL_ERROR.
*/
HBL_StatusTypeDef HBL__I2CTransmit(uint8_t instance, uint8_t *pdata, uint16_t data_size);

/**
    Interface for setting I2C data receive
    @param uint8_t instance, uint8_t *pdata, uint16_t data_size
    @return HBL_OK or HBL_ERROR.
*/
HBL_StatusTypeDef HBL__I2CReceive(uint8_t instance, uint8_t *pdata, uint16_t data_size);

/**
    Interface for data transmission through UART
    @param float32_t data_raw, float32_t dat_filtered ** for uv sensor filtering debug porpouses
    @return Result HBL_OK or HBL_ERROR.
*/
HBL_StatusTypeDef HBL__UART_Transmit(float32_t data_raw, float32_t dat_filtered);

#endif /* HBL_HBL_H_ */
