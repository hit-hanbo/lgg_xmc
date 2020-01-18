#include "ccu8.h"
#include "ccu8_conf.h"

uint8_t p_sin = 0;

void lgg_ccu80_init(void)
{
	/* CCU80 : CC80_OUT00 ~ CC80_OUT01 */
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);                    //  P0.5
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 5, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);                    //  P0.2
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 2, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);

	/* CCU80 : CC80_OUT10 ~ CC80_OUT11 */
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);					 //  P0.4
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 4, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);                    //  P0.1
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 1, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);

	/* CCU80 : CC80_OUT20 ~ CC80_OUT21 */
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);                    //  P0.3
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 3, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);                    //  P0.0
	XMC_GPIO_SetOutputStrength(XMC_GPIO_PORT0, 0, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);

	/* CCU80 global init */
	XMC_CCU8_EnableModule(CCU80);
	CCU80->GCTRL &= ~(1 << 4 | 1 << 5);                       //  set prescaler input = module clock
	CCU80->GIDLC  =  (1 << 8);                                //  start prescaler
	CCU80->GCTRL &= ~(1 << 14 | 1 << 15);                     //  PR & CR transfer shadow request

	/* slice compare init */
	XMC_CCU8_SLICE_CompareInit(CCU80_CC80, &_ccu8_slice_config);
	XMC_CCU8_SLICE_CompareInit(CCU80_CC81, &_ccu8_slice_config);
	XMC_CCU8_SLICE_CompareInit(CCU80_CC82, &_ccu8_slice_config);

	/* slice deadtime init */
	XMC_CCU8_SLICE_DeadTimeInit(CCU80_CC80, &_slice_deadtime_config);
	XMC_CCU8_SLICE_DeadTimeInit(CCU80_CC81, &_slice_deadtime_config);
	XMC_CCU8_SLICE_DeadTimeInit(CCU80_CC82, &_slice_deadtime_config);

	/* start configure */
	XMC_CCU8_SLICE_ConfigureEvent(CCU80_CC80, XMC_CCU8_SLICE_EVENT_0, &_ccu8_slice_event0_config);
	XMC_CCU8_SLICE_StartConfig(CCU80_CC80, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
	XMC_CCU8_SLICE_ConfigureEvent(CCU80_CC81, XMC_CCU8_SLICE_EVENT_0, &_ccu8_slice_event0_config);
	XMC_CCU8_SLICE_StartConfig(CCU80_CC81, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
	XMC_CCU8_SLICE_ConfigureEvent(CCU80_CC82, XMC_CCU8_SLICE_EVENT_0, &_ccu8_slice_event0_config);
	XMC_CCU8_SLICE_StartConfig(CCU80_CC82, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);

	/* IRQ init */
	XMC_CCU8_SLICE_EnableEvent(CCU80_CC80, XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH);
	XMC_CCU8_SLICE_SetInterruptNode(CCU80_CC80, XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH, XMC_CCU8_SLICE_SR_ID_0);
	NVIC_SetPriority(CCU80_0_IRQn, 10);
	NVIC_EnableIRQ(CCU80_0_IRQn);

	/* set all PR & CR value */
	CCU80_CC80->PRS = 12000;  CCU80_CC80->CR1S = 0;
	CCU80_CC81->PRS = 12000;  CCU80_CC81->CR1S = 0;
	CCU80_CC82->PRS = 12000;  CCU80_CC82->CR1S = 0;
	/* shadow transfer */
	CCU80->GCSS = (1 << 0) | (1 << 4) | (1 << 8);

	/* Slice 0~3 remove idle mode */
	CCU80->GIDLC = 0x00000007;

	/* sync start CCU80 */
	SCU_GENERAL->CCUCON |= (1 << 8);
}

void CCU80_0_IRQHandler(void)
{
	/* period match */
//	if(CCU80_CC80->INTS & (1 << 0))
//	{
//		CCU80_CC80->SWR  = (1 << 0);
//
//	}
	/* one match, update compare value */
	if(CCU80_CC80->INTS & (1 << 1))
	{
		CCU80_CC80->SWR  = (1 << 1);
		CCU80_CC80->CR1S = (1.0 * arm_sin_f32((float32_t)p_sin / 128.0 * PI             ) + 1.0) * 6000;  //  U
		CCU80_CC81->CR1S = (1.0 * arm_sin_f32((float32_t)p_sin / 128.0 * PI - 2.0/3.0*PI) + 1.0) * 6000;  //  V
		CCU80_CC82->CR1S = (1.0 * arm_sin_f32((float32_t)p_sin / 128.0 * PI + 2.0/3.0*PI) + 1.0) * 6000;  //  W
		CCU80->GCSS = (1 << 0) | (1 << 4) | (1 << 8);     //  update
		p_sin ++;
	}
}

