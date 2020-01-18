#include "iic.h"

/*
 * 		ATTENTION! some fake MPU6050 module does not
 * 		support high speed communication
 * 		try to use a lower baud rate
 * */
const XMC_I2C_CH_CONFIG_t _lgg_i2c_config =
{
		.baudrate = 10000,
};

LGG_STATUS lgg_iic_init(void)
{
	/* i2c init */
	XMC_I2C_CH_Init(XMC_USIC2_CH0, &_lgg_i2c_config);
	XMC_I2C_CH_SetInputSource(XMC_USIC2_CH0, XMC_I2C_CH_INPUT_SDA, USIC2_C0_DX0_P5_0);
	XMC_I2C_CH_SetInputSource(XMC_USIC2_CH0, XMC_I2C_CH_INPUT_SCL, USIC2_C0_DX1_P5_2);
	XMC_I2C_CH_Start(XMC_USIC2_CH0);

	/* gpio init */
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT5, 0);
	XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT5, 2);
	XMC_GPIO_SetMode(XMC_GPIO_PORT5, 0, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1);   //  SDA
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT5, 0, XMC_GPIO_OUTPUT_STRENGTH_MEDIUM);
	XMC_GPIO_SetMode(XMC_GPIO_PORT5, 2, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1);   //  SCL
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT5, 2, XMC_GPIO_OUTPUT_STRENGTH_MEDIUM);

	return LGG_SUCCESS;
}




