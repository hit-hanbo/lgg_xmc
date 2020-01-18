#include "uart.h"

/*
 *    LGG Driver for ARM Cortex-M
 *    UART ( Universal Asynchronous Receiver/Transmitter )
 *    < @History: 2019-XX-XX Debug >
 *    <			  2020-01-18 i want to restruct the driver, but i have no time :)  >
 *
 */

/*
 * 		TX or RX buffer
 * */
#define  lgg_uart_buffer_size 64
uint8_t  lgg_uart_rx_buffer[lgg_uart_buffer_size];
uint32_t lgg_uart_rx_cnt = 0;
LGG_UART_RX_STATUS_t  lgg_uart_rx_flag = LGG_UART_RX_READY;

uint8_t  lgg_uart_tx_buffer[lgg_uart_buffer_size];
uint32_t lgg_uart_tx_cnt = 0;
uint32_t lgg_uart_tx_remain = 0;

/*  UART configuration  */
const XMC_UART_CH_CONFIG_t _uart_config =
{
		.baudrate = 9600,
		.data_bits = 8,
		.frame_length = 8,
		.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE,
		.stop_bits = 1,
};

/*
 *	 init USIC Channel as UART
 *   @ Brief : Init USIC
 *   @ param : none
 *   @ retval: none
 *
 */
void lgg_uart_init(void)
{
	/*
	 * 		GPIO init
	 * */
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 0, XMC_GPIO_MODE_INPUT_PULL_UP);			   //  RxD
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2);      //  TxD

	/*
	 * 		UART init (XMC Peripheral Library)
	 * */
	XMC_UART_CH_Init(XMC_USIC1_CH1, &_uart_config);
	XMC_UART_CH_SetInputSource(XMC_USIC1_CH1, XMC_UART_CH_INPUT_RXD, USIC1_C1_DX0_P0_0);


	/*
	 * 		enable TxD & RxD interrupt
	 * */
	XMC_UART_CH_EnableEvent(XMC_USIC1_CH1, XMC_UART_CH_EVENT_TRANSMIT_BUFFER);
	XMC_USIC_CH_SetInterruptNodePointer(XMC_USIC1_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_TRANSMIT_BUFFER, 0);
	XMC_UART_CH_EnableEvent(XMC_USIC1_CH1, XMC_UART_CH_EVENT_STANDARD_RECEIVE);
	XMC_USIC_CH_SetInterruptNodePointer(XMC_USIC1_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 0);
	XMC_UART_CH_EnableEvent(XMC_USIC1_CH1, XMC_UART_CH_EVENT_ALTERNATIVE_RECEIVE);
	XMC_USIC_CH_SetInterruptNodePointer(XMC_USIC1_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE, 0);

	XMC_UART_CH_EnableEvent(XMC_USIC1_CH1, XMC_UART_CH_EVENT_FRAME_FINISHED);
	XMC_USIC_CH_SetInterruptNodePointer(XMC_USIC1_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL, XMC_UART_CH_EVENT_FRAME_FINISHED);

	/*
	 * 		configure NVIC
	 * */
	NVIC_SetPriority(USIC1_0_IRQn, 1);
	NVIC_EnableIRQ(USIC1_0_IRQn);

	XMC_UART_CH_Start(XMC_USIC1_CH1);
}

/*
 *	 send data to UART using interrupt
 *   @ Brief : transmit data(string) to UART
 *   @ param : pData  - pointer to data,
 *   		   length - data length to transmit
 *   @ retval: none
 *
 */
void lgg_uart_transmit(uint8_t* pData, uint32_t length)
{
	uint32_t i = 0;

	/* check if last transmission is not completed */
	if(lgg_uart_tx_remain != 0)
	{
		return ;
	}
	/* copy data to buffer */
	for(i=1; i<length; i++)
		lgg_uart_tx_buffer[i] = pData[i];
	/* send first byte */
	lgg_uart_tx_remain = length - 1;
	lgg_uart_tx_cnt = 1;
	XMC_UART1_CH1->TBUF[0] = pData[0];
}

/*
 *	 send string to UART using former function
 *   @ Brief : nothing to say
 *   @ param : str - pointer to string (header of char table)
 *   @ retval: none
 *
 */
void lgg_uart_send_string(uint8_t* str)
{
	uint32_t i = 0;
	/* get str length */
	while(str[i] != '\0')
		i ++;
	lgg_uart_transmit(str, i);
}

/*
 *	 get received data from UART using interrupt
 *   @ Brief : get received data from UART using interrupt
 *   @ param : pData - pointer to table to save received data
 *   		   plength - pointer to save received data length
 *   @ retval: none
 *
 */
void lgg_uart_receive(uint8_t* pData, uint32_t* pLength)
{
	uint32_t rx_size = 0;
	uint32_t i = 0;

	/*  check if transmission completed  */
	if(lgg_uart_rx_flag == LGG_UART_RX_TAIL)
	{
		rx_size = lgg_uart_rx_cnt;
		lgg_uart_rx_flag = LGG_UART_RX_READY;
		/*  copy data to pData from rx buffer  */
		for(i=0; i<rx_size; i++)
			pData[i] = lgg_uart_rx_buffer[i];
		*pLength = rx_size;
	}
}

/*
 *	 USIC interrupt service routine
 *   @ Brief : nothing to say
 *   @ param : must be none
 *   @ retval: must be none
 *
 */
void USIC1_0_IRQHandler(void)
{
	uint8_t temp = 0x00;

	/*  tx interrupt  */
	if((USIC1_CH1->PSR_ASCMode) & (1 << 13))
	{
		USIC1_CH1->PSCR = (1 << 13);
		/* send next data to tx buffer */
		if(lgg_uart_tx_remain != 0)
		{
			lgg_uart_tx_remain --;
			USIC1_CH1->TBUF[0] = lgg_uart_tx_buffer[lgg_uart_tx_cnt];
			lgg_uart_tx_cnt ++;
		}
	}

	/*  rx interrupt  */
	else if((USIC1_CH1->PSR_ASCMode) & (1 << 14 | (1 << 15)))
	{
		USIC1_CH1->PSCR = (1 << 14 | (1 << 15));
		/*  get data  */
		temp = USIC1_CH1->RBUF;

		/*  if idle  */
		if(lgg_uart_rx_flag == LGG_UART_RX_READY ||  lgg_uart_rx_flag == LGG_UART_RX_TAIL)
		{
			lgg_uart_rx_buffer[0] = temp;
			lgg_uart_rx_cnt = 1;
			lgg_uart_rx_flag = LGG_UART_RX_RECEIVING;
		}
		/*  if receiving  */
		else if(lgg_uart_rx_flag == LGG_UART_RX_RECEIVING)
		{
			lgg_uart_rx_buffer[lgg_uart_rx_cnt] = temp;
			lgg_uart_rx_cnt ++;
			if(temp == LGG_UART_TAIL_A)
				lgg_uart_rx_flag = LGG_UART_RX_HALF_TAIL;
		}
		/*  if half complete  */
		else if(lgg_uart_rx_flag == LGG_UART_RX_HALF_TAIL)
		{
			lgg_uart_rx_buffer[lgg_uart_rx_cnt] = temp;
			lgg_uart_rx_cnt ++;
			if(temp == LGG_UART_TAIL_B)
				lgg_uart_rx_flag = LGG_UART_RX_TAIL;
			else if(temp == LGG_UART_TAIL_A)
				lgg_uart_rx_flag = LGG_UART_RX_HALF_TAIL;
			else
				lgg_uart_rx_flag = LGG_UART_RX_RECEIVING;
			/*  if complete, echo  */
			if(lgg_uart_rx_flag == LGG_UART_RX_TAIL)
			{
				lgg_uart_transmit(lgg_uart_rx_buffer, lgg_uart_rx_cnt);
			}
		}
	}
}
