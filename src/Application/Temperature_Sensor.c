/*
 * Temperature_Sensor.c
 *
 *  Created on: 23 May 2020
 *      Author: Yuri ALVARENGA
 */

#include "Temperature_Sensor.h"


TempSensor_typeDef TempSensor_Handle[TEMP_SENSOR_NUM] = {0};

void i2c_am2320_sensor_read_value(void);



void Temperature_Sensor__Init(void)
{
  // config sensor array todo: implement config table
	TempSensor_Handle[0].sensor_type = I2C_AM2320_TEMP_SENSOR;
}


void Temperature_Sensor__ReadValue(uint8_t instance)
{
	switch (TempSensor_Handle[instance].sensor_type)
	{
		case I2C_AM2320_TEMP_SENSOR:
			i2c_am2320_sensor_read_value();
			break;
		case RTC_TEMP_SENSOR:
			break;
	//	default:

	}
}



void Temperature_Sensor__GetValue(uint8_t instance)
{

}


void i2c_am2320_sensor_read_value()
{
	 //Sensor_StatusTypeDef result = SENSOR_OK;

	static TEMP_SENSOR_STATE state = I2C_AM2320_TEMP_SENSOR_READ_STATE_INIT;

	 uint8_t data[8];

	//   write at addr 0x03, start reg = 0x00, num regs = 0x04

	  data[0] = 0x03;
	  data[1] = 0x00;
	  data[2] = 0x04;

	  // todo: link sensor and hbl instances
	 if (HBL__I2CTransmit(0, 0x00, 0) != HBL_OK)
	 {

	 }


	 HAL_Delay(1);  //at least 0.8ms, at most 3ms

	 if (HBL__I2CTransmit(0, data, 3) != HBL_OK)
	 {

	 }

//	   wait for AM2320

	  HAL_Delay(2);  //Wait atleast 1.5ms

	  if(HBL__I2CReceive(0, data, 8) != HBL_OK)
	  {

	  }

	  switch (state)
	  {
	  case I2C_AM2320_TEMP_SENSOR_READ_STATE_INIT:
		  break;
	  case I2C_AM2320_TEMP_SENSOR_READ_STATE_SET_REG:
		  break;
	  //default:

	  }

}
