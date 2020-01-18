#include "spwm.h"

/*
 * 		200 points
 * */
uint32_t   spwm_cnt = 0;
const uint32_t   spwm_max_cnt = 200;

/*
 * 		spwm parameters
 * */
float32_t  spwm_ma = 0.00f;
float32_t  spwm_wr = 0.00f;
float32_t  spwm_ph = 0.00f;
uint32_t   ccu8_pr = 0;

/*
 *		must configure CCU8 with proper parameters first
 * */
void lgg_spwm_update(lgg_spwm_t* p_spwm)
{
	/*  available point: 0 ~ period-1  */
	if(p_spwm->cnt == p_spwm->period)
	{
		p_spwm->cnt = 0;
	}
	/* calculate cr value */
	p_spwm->cr_u = (p_spwm->ma * arm_sin_f32((float32_t)p_spwm->cnt / p_spwm->period * 2.0*PI             ) + 1.0) * p_spwm->pr;
	p_spwm->cr_v = (p_spwm->ma * arm_sin_f32((float32_t)p_spwm->cnt / p_spwm->period * 2.0*PI - 2.0*PI/3.0) + 1.0) * p_spwm->pr;
	p_spwm->cr_w = (p_spwm->ma * arm_sin_f32((float32_t)p_spwm->cnt / p_spwm->period * 2.0*PI + 2.0*PI/3.0) + 1.0) * p_spwm->pr;
}

