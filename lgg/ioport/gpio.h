#ifndef BSP_IOPORT_GPIO_H_
#define BSP_IOPORT_GPIO_H_

#include "xmc_gpio.h"
#include "xmc_eru.h"
#include "xmc4_eru_map.h"

#define  BSP_LED0_IO  XMC_GPIO_PORT1,1
#define  BSP_LED1_IO  XMC_GPIO_PORT1,0
#define  BSP_KEY0_IO  XMC_GPIO_PORT1,14
#define  BSP_KEY1_IO  XMC_GPIO_PORT1,15

#define  BSP_LED0_OFF		PORT1->OUT |=  (1 << 1)
#define  BSP_LED1_OFF		PORT1->OUT |=  (1 << 0)
#define  BSP_LED0_ON		PORT1->OUT &= ~(1 << 1)
#define  BSP_LED1_ON		PORT1->OUT &= ~(1 << 0)
#define  BSP_LED0_TOGGLE	PORT1->OUT ^=  (1 << 1)
#define  BSP_LED1_TOGGLE	PORT1->OUT ^=  (1 << 0)

#define  BSP_KEY0_STATUS	((PORT1->IN & (1 << 14)) == 0)
#define  BSP_KEY1_STATUS	((PORT1->IN & (1 << 15)) == 0)

void bsp_lgg_gpio_init(void);
void bsp_lgg_key_eru_init(void);


#endif

