/*
 * Temperature_Sensor.h
 *
 *  Created on: 23 May 2020
 *      Author: Yuri ALVARENGA
 */

#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

#include "HBL.h"

typedef enum
{
	RTC_TEMP_SENSOR = 0,
	I2C_AM2320_TEMP_SENSOR
}TEMP_SENSOR_TYPE;

typedef struct
{
	TEMP_SENSOR_TYPE  sensor_type;

}TempSensor_typeDef;

typedef enum
{
  SENSOR_OK       = 0x00U,
  SENSOR_ERROR    = 0x01U,
} Sensor_StatusTypeDef;

typedef enum
{
  I2C_AM2320_TEMP_SENSOR_READ_STATE_INIT       = 0,
  I2C_AM2320_TEMP_SENSOR_READ_STATE_SET_REG
} TEMP_SENSOR_STATE;


#define TEMP_SENS_LIST { \
	/*type                   param1                     */                \
	{I2C_AM2320_TEMP_SENSOR},}


#define TEMP_SENSOR_NUM  1

void Temperature_Sensor__Init(void);
void Temperature_Sensor__ReadValue(uint8_t instance);
void Temperature_Sensor__GetValue(uint8_t instance);

#endif /* TEMPERATURE_SENSOR_H_ */
