#ifndef LGG_PWM_SPWM_H_
#define LGG_PWM_SPWM_H_

#include "arm_math.h"

typedef struct
{
	uint32_t cr_u;     //  u-phase pwm compare value
	uint32_t cr_v;     //  v-phase pwm compare value
	uint32_t cr_w;     //  w-phase pwm compare value
	uint32_t cnt;      //  current pwm signal index
	uint32_t period;   //  max pwm signal index (how many points in one period)

	float32_t ma;      //
	float32_t pr;

}lgg_spwm_t;

void lgg_spwm(lgg_spwm_t* p_spwm);



#endif
