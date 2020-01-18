#include "bsp_scp.h"
#include "bsp_conf.h"

void lgg_bsp_scp_init(void)
{
	/* initial SPI interface */
	/* select USIC0_0 as SPI interface */
	XMC_SPI_CH_Init(XMC_USIC0_CH0, &_lcd_spi_config);
	XMC_SPI_CH_Start(XMC_USIC0_CH0);
	XMC_SPI_CH_SetWordLength(XMC_USIC0_CH0, 8);
	XMC_SPI_CH_SetBitOrderMsbFirst(XMC_USIC0_CH0);
	XMC_SPI_CH_ConfigureShiftClockOutput(XMC_USIC0_CH0, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

	XMC_SPI_CH_SetTransmitMode(XMC_USIC0_CH0, XMC_SPI_CH_MODE_STANDARD_HALFDUPLEX);

	/* select P1.5, P0.8 as SPI */
	XMC_GPIO_Init(XMC_GPIO_PORT1, 5, &_spi_gpio_config);      // MOSI
	XMC_GPIO_Init(XMC_GPIO_PORT0, 8, &_spi_gpio_config);      // SCK

	/* select P0.7, P0.6, P0.5  */
	XMC_GPIO_Init(XMC_GPIO_PORT0, 7, &_lcd_gpio_ctrl_config); // SW CEN
	XMC_GPIO_Init(XMC_GPIO_PORT0, 6, &_lcd_gpio_ctrl_config); // RST
	XMC_GPIO_Init(XMC_GPIO_PORT0, 5, &_lcd_gpio_ctrl_config); // DC

}

