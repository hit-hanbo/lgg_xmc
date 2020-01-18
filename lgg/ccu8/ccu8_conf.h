#ifndef LGG_CCU8_CCU8_CONF_H_
#define LGG_CCU8_CCU8_CONF_H_

#include "xmc_ccu8.h"


const XMC_CCU8_SLICE_COMPARE_CONFIG_t _ccu8_slice_config =
{
		.timer_mode = XMC_CCU8_SLICE_TIMER_COUNT_MODE_CA,
		.monoshot = XMC_CCU8_SLICE_TIMER_REPEAT_MODE_REPEAT,
		.prescaler_mode = XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,
		.prescaler_initval = XMC_CCU8_SLICE_PRESCALER_1,
		.slice_status = XMC_CCU8_SLICE_STATUS_CHANNEL_1,
		.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
		.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
		.invert_out0 = 1,
		.invert_out1 = 0,
		.mcm_ch1_enable = 0,
		.mcm_ch2_enable = 0,
		.shadow_xfer_clear = 0,
		.dither_timer_period = 0,
		.dither_duty_cycle = 0,
		.float_limit = 0,
		.asymmetric_pwm = 0,
};

const XMC_CCU8_SLICE_EVENT_CONFIG_t _ccu8_slice_event0_config =
{
		.mapped_input = XMC_CCU8_SLICE_INPUT_H,                       //  SCU.GSC0
		.edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
		.level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW,
		.duration = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED
};

const XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t _slice_deadtime_config =
{
		.enable_dead_time_channel1 = 1,
		.enable_dead_time_channel2 = 0,
		.channel1_st_path = 1,
		.channel1_inv_st_path = 1,
		.channel2_st_path = 0,
		.channel2_inv_st_path = 0,
		.div = XMC_CCU8_SLICE_DTC_DIV_1,
		.channel1_st_rising_edge_counter = 24,
		.channel1_st_falling_edge_counter = 24,
		.channel2_st_rising_edge_counter = 0,
		.channel2_st_falling_edge_counter = 0
};


#endif
