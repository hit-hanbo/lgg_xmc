#include "dac.h"
#include "dac_data.h"

/*
 *   @ Description: DAC output configure
 *   @ Author:      HIT-hanbo
 *   @ History:     2019-XX-XX  initial
 *   				2020-01-18  Add Comments
*/


/*
 * 		struct to init DMA & DAC(XMC Peripheral Library)
 * */
const XMC_DAC_CH_CONFIG_t _bsp_dac_config =
{
		.output_offset = 0,
		.data_type = XMC_DAC_CH_DATA_TYPE_UNSIGNED,
		.output_scale = XMC_DAC_CH_OUTPUT_SCALE_NONE,
		.output_negation = XMC_DAC_CH_OUTPUT_NEGATION_DISABLED,  // xmc44 serires only
};

const XMC_DMA_CH_CONFIG_t _bsp_dac0_dma_config =
{
		{
				.enable_interrupt       = 1,
				.dst_transfer_width     = XMC_DMA_CH_TRANSFER_WIDTH_32,
				.src_transfer_width     = XMC_DMA_CH_TRANSFER_WIDTH_32,
				.dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
				.src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
				.dst_burst_length       = 0,
				.src_burst_length       = 0,
				.enable_src_gather      = 0,
				.enable_dst_scatter     = 0,
				.transfer_flow          = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
		},
		.src_addr = (uint32_t)&lgg_dac_data_harsin[0],
		.dst_addr = (uint32_t)&DAC->DAC0DATA,
		.block_size = LGG_DAC_DATA_SIZE,
		.transfer_type = XMC_DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_RELOAD,
		.priority = XMC_DMA_CH_PRIORITY_0,
		.src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_SOFTWARE,
		.dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE,
		.dst_peripheral_request = DMA0_PERIPHERAL_REQUEST_DAC_SR0_1
};


/*
 * 		Enable DAC0_Channel0 & DMA0_Channel0
 * 		to generate a <custom> signal
 * 		no any other options needed
 * */
void lgg_dac_init(void)
{
	XMC_DMA_Init(LGG_DMA_MODULE);
	XMC_DMA_CH_Init(LGG_DAC0_DMA, &_bsp_dac0_dma_config);
	XMC_DMA_CH_Enable(LGG_DAC0_DMA);

	/* DMA interrupt may cause a delay while a period transmission */
	/* but this junk DMA channel does not support multiblock transmission */
	/* junk MCU !!!! */
//	XMC_DMA_CH_EnableEvent(LGG_DAC1_DMA, XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
//	NVIC_SetPriority(GPDMA0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
//	NVIC_EnableIRQ(GPDMA0_0_IRQn);

	XMC_DAC_Enable(XMC_DAC0);
	XMC_DAC_CH_Init(LGG_DAC_SIG, &_bsp_dac_config);
	XMC_DAC_CH_Init(LGG_DAC_FIL, &_bsp_dac_config);
	XMC_DAC_CH_EnableEvent(LGG_DAC_SIG);
	XMC_DAC_CH_EnableEvent(LGG_DAC_FIL);

	XMC_DAC_CH_StartDataMode(LGG_DAC_SIG, XMC_DAC_CH_TRIGGER_INTERNAL, 80000U);
	XMC_DAC_CH_StartSingleValueMode(LGG_DAC_FIL);

}

/*
 * 		GPDMA0_0 ISR  (not used)
 * 		1.  check if transmission completed, and then do nothing
 * 		2.  check if any error occured, and restart DMA controller
 * */

/*****
void GPDMA0_0_IRQHandler(void)
{
	XMC_DMA_CH_EVENT_t status = 0;
	status = XMC_DMA_CH_GetEventStatus(LGG_DAC_DMA);
	if(status == XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE)
	{
		XMC_DMA_CH_ClearEventStatus(LGG_DAC_DMA, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);
		// used only for debug
	}
	else if(status == XMC_DMA_CH_EVENT_ERROR)
	{
		XMC_DMA_CH_ClearEventStatus(LGG_DAC_DMA, XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
		// error occured, restart DMA
		XMC_DMA_CH_Disable(LGG_DAC_DMA);
		XMC_DMA_CH_SetBlockSize(LGG_DAC_DMA, LGG_DAC_DATA_SIZE);
		XMC_DMA_CH_SetDestinationAddress(LGG_DAC_DMA, (uint32_t)&DAC->DAC0DATA);
		XMC_DMA_CH_SetSourceAddress(LGG_DAC_DMA, (uint32_t)lgg_dac_data);
		XMC_DMA_CH_Enable(LGG_DAC_DMA);
	}
}
****/
