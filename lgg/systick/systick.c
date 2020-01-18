#include "systick.h"

/*
 *   @ Description: SysTick Configure
 *   @ Author:      HIT-hanbo
 *   @ History:     2019-11-11  Demo
 *   				2020-01-18  Add Comments
*/

volatile uint32_t system_ticks = 0;

/*
 *   @ Brief: init systick timer to generate 1ms interrupt request
 *   @ param: none
 */
void lgg_systick_init(void)
{
	system_ticks = 0;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
	SysTick->VAL = 0x00000000;
	SysTick->LOAD = 120000;
	SysTick->CTRL |= (1 << 0);
}

/*
 *   @ Brief: delay function
 *   @ param: millisecond to delay
 */
void lgg_delay(uint32_t ms)
{
	uint32_t tick_start = system_ticks;
	while(
			system_ticks - tick_start < ms
	);
}

/*
 *   @ Brief: systick interrupt service routine
 *   @ param: must be none
 */
void SysTick_Handler(void)
{
	system_ticks ++;
}
