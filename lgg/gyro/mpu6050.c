#include "mpu6050.h"

/*
 *   @ Description: ARM Cortex-M based MPU6050 Driverlib
 *   @ Author:      HIT-HanBo
 *   @ History:     2019-XX-XX  Demo
 *   				2020-01-18  Add Comments
*/

/*
 * 		ATTENTION! some fake MPU6050 module does not support
 * 		burst transmission, try to read/write byte by byte
 * */

void lgg_gyro_read_register_byte(uint8_t address, uint8_t* data)
{
	/* send address (W) */
	USIC2_CH0->PSCR = (1 << 9);
	XMC_I2C_CH_MasterStart(XMC_USIC2_CH0, 0xD0, XMC_I2C_CH_CMD_WRITE);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send REGISTER address */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, address);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* start read */
	XMC_I2C_CH_MasterRepeatedStart(XMC_USIC2_CH0, 0xD1, XMC_I2C_CH_CMD_READ);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9 | 1 << 14 | 1 << 15);
	/* receive */
	XMC_I2C_CH_MasterReceiveNack(XMC_USIC2_CH0);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 14 | 1 << 15)) == 0
		);
	XMC_I2C_CH_MasterStop(XMC_USIC2_CH0);

	*data = XMC_I2C_CH_GetReceivedData(XMC_USIC2_CH0);
}

void lgg_gyro_write_register_byte(uint8_t address, uint8_t* data)
{
	/* send address (W) */
	USIC2_CH0->PSCR = (1 << 9);
	XMC_I2C_CH_MasterStart(XMC_USIC2_CH0, 0xD0, XMC_I2C_CH_CMD_WRITE);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send REGISTER address */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, address);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send data */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, *data);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* stop */
	XMC_I2C_CH_MasterStop(XMC_USIC2_CH0);
}

void lgg_gyro_write_register_hword(uint8_t address, uint16_t* data)
{
	uint8_t* temp = (uint8_t*) data;
	/* send address (W) */
	USIC2_CH0->PSCR = (1 << 9);
	XMC_I2C_CH_MasterStart(XMC_USIC2_CH0, 0xD0, XMC_I2C_CH_CMD_WRITE);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send REGISTER address */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, address);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send dataH */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, (uint8_t)*(temp+1));
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send dataL */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, (uint8_t)*(temp));
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* stop */
	XMC_I2C_CH_MasterStop(XMC_USIC2_CH0);
}

void lgg_gyro_read_register_hword(uint8_t address, uint16_t* data)
{
	uint8_t* temp = (uint8_t*) data;
	/* send address (W) */
	USIC2_CH0->PSCR = (1 << 9);
	XMC_I2C_CH_MasterStart(XMC_USIC2_CH0, 0xD0, XMC_I2C_CH_CMD_WRITE);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* send REGISTER address */
	XMC_I2C_CH_MasterTransmit(XMC_USIC2_CH0, address);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9);
	/* start read */
	XMC_I2C_CH_MasterRepeatedStart(XMC_USIC2_CH0, 0xD1, XMC_I2C_CH_CMD_READ);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 9)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9 | 1 << 14 | 1 << 15);
	/* receive dataH */
	XMC_I2C_CH_MasterReceiveNack(XMC_USIC2_CH0);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 14 | 1 << 15)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9 | 1 << 14 | 1 << 15);

	*(temp+1) = XMC_I2C_CH_GetReceivedData(XMC_USIC2_CH0);
	/* receive dataL */
	XMC_I2C_CH_MasterReceiveNack(XMC_USIC2_CH0);
	while(
				(USIC2_CH0->PSR_IICMode & (1 << 14 | 1 << 15)) == 0
		);
	USIC2_CH0->PSCR = (1 << 9 | 1 << 14 | 1 << 15);

	XMC_I2C_CH_MasterStop(XMC_USIC2_CH0);

	*(temp) = XMC_I2C_CH_GetReceivedData(XMC_USIC2_CH0);
}

void lgg_gyro_init(void)
{
	uint8_t temp = 0;
	uint32_t i = 0;

	/* iic interface init */
	lgg_iic_init();

	/* reset gyro */
	temp = 0x80;	lgg_gyro_write_register_byte(0x6B, &temp);
	for(i=0; i<0xFFFF; i++);
	temp = 0x00;    lgg_gyro_write_register_byte(0x6B, &temp);

	/* read who am i */
	lgg_gyro_read_register_byte(0x75, &temp);
	if(temp != 0x68)
		return ;

	/* parameters */
	temp=0x18; lgg_gyro_write_register_byte(0x1B, &temp);  /* Set Gyro Full Scale +-2000dps */
	temp=0x00; lgg_gyro_write_register_byte(0x1C, &temp);  /* Set ACCEL Full Scale +-2g */
	temp=0x00; lgg_gyro_write_register_byte(0x38, &temp);  /* Disable IMU Interrupt Output */
	temp=0x00; lgg_gyro_write_register_byte(0x37, &temp);  /* Disable IMU Aux I2C */
	temp=0x01; lgg_gyro_write_register_byte(0x19, &temp);  /* Set Sample rate 500Hz */
	temp=0x02; lgg_gyro_write_register_byte(0x1A, &temp);  /* Set Filter */
}

void lgg_gyro_get_rawdata(uint16_t* gx, uint16_t* gy, uint16_t* gz,
					uint16_t* ax, uint16_t* ay, uint16_t* az, uint16_t* tem)
{
	uint8_t byte_H = 0, byte_L = 0;

	lgg_gyro_read_register_byte(0x3B, &byte_H);
	lgg_gyro_read_register_byte(0x3C, &byte_L);
	(*ax) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x3D, &byte_H);
	lgg_gyro_read_register_byte(0x3E, &byte_L);
	(*ay) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x3F, &byte_H);
	lgg_gyro_read_register_byte(0x40, &byte_L);
	(*az) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x43, &byte_H);
	lgg_gyro_read_register_byte(0x44, &byte_L);
	(*gx) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x45, &byte_H);
	lgg_gyro_read_register_byte(0x46, &byte_L);
	(*gy) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x47, &byte_H);
	lgg_gyro_read_register_byte(0x48, &byte_L);
	(*gz) = (uint16_t) (byte_H << 8) + (byte_L);

	lgg_gyro_read_register_byte(0x41, &byte_H);
	lgg_gyro_read_register_byte(0x42, &byte_L);
	(*tem) = (uint16_t) (byte_H << 8) + (byte_L);

}

void lgg_gyro_get_rawdata_float(float32_t* ax, float32_t* ay, float32_t* az,
								float32_t* gx, float32_t* gy, float32_t* gz, float32_t* tem)
{
	int16_t   igx, igy, igz, iax, iay, iaz, iatem;
//	float32_t fgx, fgy, fgz, fax, fay, faz, fatem;

	/* get raw data */
	lgg_gyro_get_rawdata((uint16_t*)&igx, (uint16_t*)&igy, (uint16_t*)&igz,
						(uint16_t*)&iax, (uint16_t*)&iay, (uint16_t*)&iaz, (uint16_t*)&iatem);
	/* int -> float */
	*ax = (float32_t) iax / 16384;
	*ay = (float32_t) iay / 16384;
	*az = (float32_t) iaz / 16384;
	*gx = (float32_t) igx * 0.001064;
	*gy = (float32_t) igy * 0.001064;
	*gz = (float32_t) igz * 0.001064;
	*tem = (float32_t) iatem / 340 + 36.53;
}

