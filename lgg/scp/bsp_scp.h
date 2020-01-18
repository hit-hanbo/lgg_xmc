#ifndef SPI_H_
#define SPI_H_

#include "XMC4500.h"
#include "xmc_spi.h"
#include "xmc_gpio.h"

#define LCD_DC_H   PORT0->OUT |=  (1 << 5)
#define LCD_DC_L   PORT0->OUT &= ~(1 << 5)
#define LCD_CS_H   PORT0->OUT |=  (1 << 7)
#define LCD_CS_L   PORT0->OUT &= ~(1 << 7)
#define LCD_RST_H  PORT0->OUT |=  (1 << 6)
#define LCD_RST_L  PORT0->OUT &= ~(1 << 6)

void lgg_bsp_scp_init(void);

#endif

