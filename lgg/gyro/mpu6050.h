#ifndef LGG_GYRO_MPU6050_H_
#define LGG_GYRO_MPU6050_H_

#include "arm_math.h"
#include "iic.h"

#define    LGG_GYRO_I2C_ADDRESS    0xD0



void lgg_gyro_read_register_byte(uint8_t address, uint8_t* data);
void lgg_gyro_write_register_byte(uint8_t address, uint8_t* data);
void lgg_gyro_write_register_hword(uint8_t address, uint16_t* data);
void lgg_gyro_read_register_hword(uint8_t address, uint16_t* data);
void lgg_gyro_init(void);
void lgg_gyro_get_rawdata(uint16_t* gx, uint16_t* gy, uint16_t* gz,
					uint16_t* ax, uint16_t* ay, uint16_t* az, uint16_t* tem);
void lgg_gyro_get_rawdata_float(float32_t* ax, float32_t* ay, float32_t* az,
								float32_t* gx, float32_t* gy, float32_t* gz, float32_t* tem);

#endif
