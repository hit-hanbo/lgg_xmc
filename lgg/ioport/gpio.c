#include "gpio.h"

/*
 * 		IOport configure for KEY, LED and ERU
 * */


const XMC_GPIO_CONFIG_t _led_gpio_config =
{
		.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

const XMC_GPIO_CONFIG_t _key_gpio_config =
{
		.mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

const XMC_ERU_ETL_CONFIG_t _key_etl_config =
{
		.input_a = ERU1_ETL1_INPUTA_P1_15,
		.source = XMC_ERU_ETL_SOURCE_A,
		.edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
		.status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL,
		.enable_output_trigger = true,
		.output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0
};

const XMC_ERU_OGU_CONFIG_t _key_ogu_config =
{
		.service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER
};

void bsp_lgg_gpio_init(void)
{
	XMC_GPIO_Init(BSP_KEY0_IO, &_key_gpio_config);
	XMC_GPIO_Init(BSP_KEY1_IO, &_key_gpio_config);
	XMC_GPIO_Init(BSP_LED0_IO, &_led_gpio_config);
	XMC_GPIO_Init(BSP_LED1_IO, &_led_gpio_config);
	bsp_lgg_key_eru_init();
}


void bsp_lgg_key_eru_init(void)
{
	XMC_ERU_ETL_Init(XMC_ERU1, 1, &_key_etl_config);
	XMC_ERU_OGU_Init(XMC_ERU1, 0, &_key_ogu_config);

	NVIC_SetPriority(ERU1_0_IRQn, 63);
	NVIC_EnableIRQ(ERU1_0_IRQn);
}

void ERU1_0_IRQHandler(void)
{
	if(BSP_KEY1_STATUS)
	{
	}
}
