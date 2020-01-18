#ifndef LCD_CONF_H_
#define LCD_CONF_H_

#include "XMC4500.h"
#include "xmc_spi.h"
#include "xmc_gpio.h"

const XMC_SPI_CH_CONFIG_t _lcd_spi_config =
{
		.bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
		.baudrate = 30000000,  // spi speed up to 40MHz
		.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE,
		.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS
};

const XMC_GPIO_CONFIG_t _spi_gpio_config =
{
		.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
};

const XMC_GPIO_CONFIG_t _lcd_gpio_ctrl_config =
{
		.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

#endif
