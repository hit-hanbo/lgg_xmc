#ifndef LGG_UART_UART_H_
#define LGG_UART_UART_H_

#include "xmc_uart.h"
#include "xmc_gpio.h"
#include "xmc4_usic_map.h"

/*  state machine  */
typedef enum
{
	LGG_UART_RX_READY = 0,
	LGG_UART_RX_RECEIVING,
	LGG_UART_RX_ERROR,
	LGG_UART_RX_HALF_TAIL,
	LGG_UART_RX_TAIL,
}LGG_UART_RX_STATUS_t;

#define  LGG_UART_TAIL_A  0x0D
#define  LGG_UART_TAIL_B  0x0A

void lgg_uart_init(void);
void lgg_uart_transmit(uint8_t* pData, uint32_t length);
void lgg_uart_receive(uint8_t* pData, uint32_t* pLength);
void lgg_uart_send_string(uint8_t* str);


#endif

