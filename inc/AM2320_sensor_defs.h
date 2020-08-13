/*
 * AM2320_sensor_defs.h
 *
 *  Created on: 23 May 2020
 *      Author: Yuri ALVARENGA
 */

#ifndef AM2320_SENSOR_DEFS_H_
#define AM2320_SENSOR_DEFS_H_

#define AM2320_ADDR                     0xB8

#define AM2330_REG_HUMI_HIGH            0x00
#define AM2330_REG_HUMI_LOW             0x01
#define AM2330_REG_TEMP_HIGH            0x02
#define AM2330_REG_TEMP_LOW             0x03
#define AM2330_REG_DEVID_HIGH           0x0B
#define AM2330_REG_DEVID_LOW            0x0C

#define AM2330_CMD_READDATA             0x03
#define AM2330_CMD_WRITE_MULTI_DATA     0x10

#endif /* AM2320_SENSOR_DEFS_H_ */
