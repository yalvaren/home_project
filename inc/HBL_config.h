/*
 * HBL_config.h
 *
 *  Created on: 27 Oct 2018
 *      Author: Yuri ALVARENGA
 */

#ifndef HBL_HBL_CONFIG_H_
#define HBL_HBL_CONFIG_H_
//Digital Inputs Enum
typedef enum
{
    DI_SWITCH = 0,
    NUM_OF_DIGITAL_INPUTS
} DIGITAL_INPUTS_TYPE;


// Analog Inputs defines
typedef enum
{
    AI_LIGHT_SENSOR = 0,
    NUM_OF_ANALOG_INPUTS
} ANALOG_INPUTS_TYPE;

// Digital Outputs defines -------------------------------------------------------------------------------------------

typedef enum
{
    DO_LED_BLUE,
	DO_LED_RED,
	DO_LED_GREEN,
    DO_ALL_LOADS            =   0xFF,
	DO_MAX
} DIGITAL_OUTPUTS_TYPE;


//! Analog Output defines ---------------------------------------------------------------------------------------------
typedef enum
{
	NUM_OF_ANALOG_OUTPUTS
} ANALOG_OUTPUTS_TYPE;


#endif /* HBL_HBL_CONFIG_H_ */
