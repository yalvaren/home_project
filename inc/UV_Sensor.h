/*
 * Light_Sensor.h
 *
 *  Created on: 23 Jun 2020
 *      Author: Yuri ALVARENGA
 */

#ifndef UV_SENSOR_H_
#define UV_SENSOR_H_


#include "HBL.h"

/**
    Interface for converting UV sensor adc values into voltage value
    @param
    @return float32_t voltage value.
*/
float32_t UV_Sensor__Convert_Raw(void);

/**
    Interface for getting UV filtered value
    @param
    @return float32_t voltage value.
*/
float32_t UV_Sensor__Get_Filtered();




#endif /* UV_SENSOR_H_ */
