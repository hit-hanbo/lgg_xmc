#ifndef DAC_H_
#define DAC_H_

#include "xmc_dac.h"
#include "xmc_dma.h"
#include "xmc_dma_map.h"
#include "xmc_gpio.h"

#define  LGG_DMA_MODULE  XMC_DMA0
#define  LGG_DAC0_DMA    XMC_DMA0, 0
#define  LGG_DAC1_DMA    XMC_DMA0, 2

#define  LGG_DAC_SIG     XMC_DAC0, 0
#define  LGG_DAC_FIL     XMC_DAC0, 1

#define  BSP_DAC_CH0  XMC_DAC0, 0
#define  BSP_DAC_CH1  XMC_DAC0, 1

#define  BSP_DAC_CH0_SET(X)  XMC_DAC0->DACDATA[0]=X
#define  BSP_DAC_CH1_SET(X)  XMC_DAC0->DACDATA[1]=X

void lgg_dac_init(void);

#endif
