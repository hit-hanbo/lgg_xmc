#include "lgg/lgg.h"
#include "ccu4.h"

const XMC_CCU4_SLICE_COMPARE_CONFIG_t _ccu4_dac_trigger_config =
{
		.timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
		.monoshot = 0,
		.shadow_xfer_clear = 0,
		.dither_timer_period = 0,
		.dither_duty_cycle = 0,
		.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
		.mcm_enable = 0,
		.prescaler_initval = 0,
		.float_limit = 0,
		.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
		.timer_concatenation = 0,
};


/*
 * 		CCU4 trigger
 * */
void lgg_ccu40_init(void)
{
	XMC_CCU4_SetModuleClock(CCU40, XMC_CCU4_CLOCK_SCU);
	XMC_CCU4_Init(CCU40, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
	XMC_CCU4_EnableClock(CCU40, 0);
	XMC_CCU4_StartPrescaler(CCU40);

	XMC_CCU4_SLICE_CompareInit(CCU40_CC40, &_ccu4_dac_trigger_config);
	XMC_CCU4_SLICE_EnableEvent(CCU40_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
	XMC_CCU4_SLICE_SetInterruptNode(CCU40_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_1);

	XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC40, 1000 - 1);
	XMC_CCU4_EnableShadowTransfer(CCU40, XMC_CCU4_SHADOW_TRANSFER_SLICE_0);
	XMC_SCU_SetCcuTriggerHigh(SCU_GENERAL_CCUCON_GSC40_Msk);
}


