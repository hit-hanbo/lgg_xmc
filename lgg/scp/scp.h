#ifndef LGG_SCP_H_
#define LGG_SCP_H_

#include "bsp_scp.h"

/* LCD parameters */
#define  LGG_SCP_PM_WIDTH   128
#define  LGG_SCP_PM_HEIGHT  160

#define  LGG_SCP_OP_POTRAIT
#ifndef LGG_SCP_OP_POTRAIT
#define  LGG_SCP_OP_LANDSCAPE
#endif

/* Hardware Connection (GPIO) */
#define  LGG_SCP_DC_OUTH   LCD_DC_H
#define  LGG_SCP_DC_OUTL   LCD_DC_L
#define  LGG_SCP_RES_OUTH  LCD_RST_H
#define  LGG_SCP_RES_OUTL  LCD_RST_L
#define  LGG_SCP_CEN_OUTH  LCD_CS_H
#define  LGG_SCP_CEN_OUTL  LCD_CS_L
#define  LGG_SCP_BL_OUTH
#define  LGG_SCP_BL_OUTL

/* Software interface */
/* provide your delay function(ms-level) */
#define  lgg_delay      lgg_delay

#define LGG_SCP_CHARMODE_OVERLYING    0
#define LGG_SCP_CHARMODE_NOOVERLYING  1

typedef struct{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
}LGG_SCP_DS_RGB888;

typedef uint16_t LGG_SCP_DS_RGB565;

/* SCP Function */
void LGG_SCP_transmit_byte(uint8_t data);
void LGG_SCP_transmit_cmd(uint8_t cmd);
void LGG_SCP_transmit_data8(uint8_t data);
void LGG_SCP_transmit_data16(uint16_t data);
void LGG_SCP_address_set(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void LGG_SCP_init(void);
void LGG_SCP_clear(uint16_t color);
void LGG_SCP_fill_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LGG_SCP_draw_point(uint16_t X, uint16_t Y, uint16_t color);
void LGG_SCP_display_char(uint16_t X, uint16_t Y, uint8_t ascii, uint8_t mode, uint16_t font_color, uint16_t bkg_color);
void LGG_SCP_display_string(uint16_t X, uint16_t Y, uint8_t* string, uint8_t mode, uint16_t font_color, uint16_t bkg_color);
void LGG_SCP_display_chinese(uint16_t X, uint16_t Y, uint8_t index, uint16_t font_color, uint16_t bkg_color);
void LGG_SCP_show_image(uint16_t* pImage);

#endif


