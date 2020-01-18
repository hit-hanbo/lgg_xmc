#include "lgg/lgg.h"
#include "scp_font.h"


/*
 *   @ Description: ARM Cortex-M based ST7735S LCD Controller Driverlib
 *   @ Author:      HIT-hanbo
 *   @ History:     2019-07-11  Demo
 *   				2019-11-22  Migrate to XMC4500 from STM32
 *   				2019-11-23  Fix Bugs
 *   				2020-01-18  Add Comments
*/


/*
 *   @ Brief: transmit a byte to st7735s via SPI interface
 *   @ param: data to transmit
 */
void LGG_SCP_transmit_byte(uint8_t data)
{
	LGG_SCP_CEN_OUTL;
	//  provide your spi transmit function
	USIC0_CH0->PSCR = (1 << 12);
	USIC0_CH0->TBUF[5] = data;
	while(
			(USIC0_CH0->PSR_SSCMode & (1 << 12)) == 0
	);
	LGG_SCP_CEN_OUTH;
}

/*
 *   @ Brief: transmit a REGISTER address to st7735s (write command)
 *   @ param: cmd to transmit
 */
void LGG_SCP_transmit_cmd(uint8_t cmd)
{
	LGG_SCP_DC_OUTL;
	LGG_SCP_transmit_byte(cmd);
}

/*
 *   @ Brief: transmit a BYTE DATA to st7735s (write data)
 *   @ param: data byte to transmit
 */
void LGG_SCP_transmit_data8(uint8_t data)
{
	LGG_SCP_DC_OUTH;
	LGG_SCP_transmit_byte(data);
}

/*
 *   @ Brief: transmit a HALFWORD DATA to st7735s (write data)
 *   @ param: data halfword to transmit
 */
void LGG_SCP_transmit_data16(uint16_t data)
{
	LGG_SCP_DC_OUTH;
	LGG_SCP_transmit_byte(data >> 8);
	LGG_SCP_transmit_byte(data);
}

/*
 *  @ Brief: set LCD address to option
 *  @ param: (x1, y1) - start address , (x2, y2) - stop address
 */
void LGG_SCP_address_set(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
#ifdef LGG_SCP_OP_POTRAIT
	LGG_SCP_transmit_cmd(0x2A);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(x1 + 2);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(x2 + 2);

	LGG_SCP_transmit_cmd(0x2B);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(y1 + 1);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(y2 + 1);
#endif
#ifdef LGG_SCP_OP_LANDSCAPE
	LGG_SCP_transmit_cmd(0x2A);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(x1 + 1);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(x2 + 1);

	LGG_SCP_transmit_cmd(0x2B);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(y1 + 2);
	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_data8(y2 + 2);
#endif
	LGG_SCP_transmit_cmd(0x2C);
}

/*
 *  @ Brief: init st7735s controller
 */
void LGG_SCP_init(void)
{
	lgg_bsp_scp_init();
	LGG_SCP_DC_OUTH;
	LGG_SCP_RES_OUTH;
	LGG_SCP_CEN_OUTH;
	/* firstly reset */
	LGG_SCP_RES_OUTL;
	lgg_delay(200);
	LGG_SCP_RES_OUTH;
	lgg_delay(200);

	/* initial lcd */
	LGG_SCP_transmit_cmd(0x11);
	lgg_delay(200);

	LGG_SCP_transmit_cmd(0xB1);
	LGG_SCP_transmit_data8(0x05);	LGG_SCP_transmit_data8(0x3C);	LGG_SCP_transmit_data8(0x3C);
	LGG_SCP_transmit_cmd(0xB2);
	LGG_SCP_transmit_data8(0x05);	LGG_SCP_transmit_data8(0x3C);	LGG_SCP_transmit_data8(0x3C);
	LGG_SCP_transmit_cmd(0xB3);
	LGG_SCP_transmit_data8(0x05);	LGG_SCP_transmit_data8(0x3C);	LGG_SCP_transmit_data8(0x3C);
	LGG_SCP_transmit_data8(0x05);	LGG_SCP_transmit_data8(0x3C);	LGG_SCP_transmit_data8(0x3C);

	LGG_SCP_transmit_cmd(0xB4);
	LGG_SCP_transmit_data8(0x03);

	LGG_SCP_transmit_cmd(0xC0);
	LGG_SCP_transmit_data8(0x28);	LGG_SCP_transmit_data8(0x08);	LGG_SCP_transmit_data8(0x04);
	LGG_SCP_transmit_cmd(0xC1);
	LGG_SCP_transmit_data8(0xC0);
	LGG_SCP_transmit_cmd(0xC2);
	LGG_SCP_transmit_data8(0x0D);	LGG_SCP_transmit_data8(0x00);
	LGG_SCP_transmit_cmd(0xC3);
	LGG_SCP_transmit_data8(0x8D);	LGG_SCP_transmit_data8(0x2A);
	LGG_SCP_transmit_cmd(0xC4);
	LGG_SCP_transmit_data8(0x8D);	LGG_SCP_transmit_data8(0xEE);
	LGG_SCP_transmit_cmd(0xC5);
	LGG_SCP_transmit_data8(0x1A);
	LGG_SCP_transmit_cmd(0x36);
#ifdef LGG_SCP_OP_POTRAIT
	LGG_SCP_transmit_data8(0xC0);
#endif
#ifdef LGG_SCP_OP_LANDSCAPE
	LGG_SCP_transmit_data8(0xA0);
#endif
	LGG_SCP_transmit_cmd(0xE0);
	LGG_SCP_transmit_data8(0x04);	LGG_SCP_transmit_data8(0x22);	LGG_SCP_transmit_data8(0x07);
	LGG_SCP_transmit_data8(0x0A);	LGG_SCP_transmit_data8(0x2E);	LGG_SCP_transmit_data8(0x30);
	LGG_SCP_transmit_data8(0x25);	LGG_SCP_transmit_data8(0x2A);	LGG_SCP_transmit_data8(0x28);
	LGG_SCP_transmit_data8(0x26);	LGG_SCP_transmit_data8(0x2E);	LGG_SCP_transmit_data8(0x3A);
	LGG_SCP_transmit_data8(0x00);	LGG_SCP_transmit_data8(0x01);	LGG_SCP_transmit_data8(0x03);
	LGG_SCP_transmit_data8(0x13);

	LGG_SCP_transmit_cmd(0xE1);
	LGG_SCP_transmit_data8(0x04); LGG_SCP_transmit_data8(0x16); LGG_SCP_transmit_data8(0x06);
	LGG_SCP_transmit_data8(0x0D); LGG_SCP_transmit_data8(0x2D); LGG_SCP_transmit_data8(0x26);
	LGG_SCP_transmit_data8(0x23); LGG_SCP_transmit_data8(0x27); LGG_SCP_transmit_data8(0x27);
	LGG_SCP_transmit_data8(0x25); LGG_SCP_transmit_data8(0x2D); LGG_SCP_transmit_data8(0x3B);
	LGG_SCP_transmit_data8(0x00); LGG_SCP_transmit_data8(0x01); LGG_SCP_transmit_data8(0x04);
	LGG_SCP_transmit_data8(0x13);

	LGG_SCP_transmit_cmd(0x3A);
	LGG_SCP_transmit_data8(0x05);

	LGG_SCP_transmit_cmd(0x29);
}

/*
 *  @ Brief: clear screen with specific color
 *  @ param: color - your expect color filled with full screen
 */
void LGG_SCP_clear(uint16_t color)
{
	uint16_t i, j;
	LGG_SCP_address_set(0, 0, LGG_SCP_PM_WIDTH - 1, LGG_SCP_PM_HEIGHT - 1);
	for(i=0; i<LGG_SCP_PM_WIDTH; i++)
	{
		for(j=0; j<LGG_SCP_PM_HEIGHT; j++)
		{
			LGG_SCP_transmit_data16(color);
		}
	}
}

/*
 *  @ Brief:  fill specific region with specific color
 *  @ param:  x1, y1, x2, y2 - boarder coordinates
 *  		  color - your specific color
 */
void LGG_SCP_fill_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t i, j;
	LGG_SCP_address_set(x1, y1, x2, y2);
	for(i=y1; i<y2+1;i++)
	{
		for(j=x1; j<x2+1; j++)
		{
			LGG_SCP_transmit_data16(color);
		}
	}
}

/*
 *  @ Brief:  show a character on screen
 *  @ param:  X, Y - character coordinate
 *  		  mode - LGG_SCP_CHARMODE_NOOVERLYING(no overlying)
 *  		  		 LGG_SCP_CHARMODE_OVERLYING  (overlying on current content)
 *  		  font_color - font color
 *  		  bkg_color - background color
 */
void LGG_SCP_display_char(uint16_t X, uint16_t Y, uint8_t ascii, uint8_t mode, uint16_t font_color, uint16_t bkg_color)
{
	uint8_t i, j, font;
	uint8_t offset = ascii - ' ';
	if(X>LGG_SCP_PM_WIDTH - 16 || Y > LGG_SCP_PM_HEIGHT)
		return ;
	LGG_SCP_address_set(X, Y, X+7, Y+15);
	if(mode == LGG_SCP_CHARMODE_NOOVERLYING)
	{
		for(i=0; i<16; i++)
		{
			font = ascii_1608[(uint16_t)offset * 16 + i];
			for(j=0; j<8; j++)
			{
				if(font & 0x01)
					LGG_SCP_transmit_data16(font_color);
				else
					LGG_SCP_transmit_data16(bkg_color);
				font >>= 1;
			}
		}
	}
	else if(mode == LGG_SCP_CHARMODE_OVERLYING)
	{
		for(i=0; i<16; i++)
		{
			font = ascii_1608[(uint16_t)offset * 16 + i];
			for(j=0; j<8; j++)
			{
				if(font & 0x01)
					LGG_SCP_draw_point(X + j, Y + i, font_color);
				font >>= 1;
			}
		}
	}
}

/*
 *  @ Brief:  show string on screen
 *  @ param:  X, Y - start position
 *  		  mode - LGG_SCP_CHARMODE_NOOVERLYING(no overlying)
 *  		  		 LGG_SCP_CHARMODE_OVERLYING  (overlying on current content)
 *  		  font_color - font color
 *  		  bkg_color - background color
 */
void LGG_SCP_display_string(uint16_t X, uint16_t Y, uint8_t* string, uint8_t mode, uint16_t font_color, uint16_t bkg_color)
{
	uint16_t p_x = X, p_y = Y;
	uint8_t* p_string = string;

	while(*p_string != '\0')
	{
		if(p_x > LGG_SCP_PM_WIDTH - 16)
		{
			p_x  = 0;
			p_y += 16;
		}
		if(p_y > LGG_SCP_PM_HEIGHT - 16)
		{
			p_x = 0;
			p_y = 0;
			LGG_SCP_clear(bkg_color);
		}
		LGG_SCP_display_char(p_x, p_y, *p_string, mode, font_color, bkg_color);
		p_x += 8;
		p_string ++;
	}
}

/*
 *   Tips: Use "sprintf" function to show digits
 *   (I have try it on my GCC Compiler)
 *   use NewLib-Standard to support FLOAT
 * */

/*
 *  @ Brief:   display Chinese character on screen
 *  @ param:  X, Y - start position
 *            index - Chinese character index in FONT table
 *  		  font_color - font color
 *  		  bkg_color - background color
 */
void LGG_SCP_display_chinese(uint16_t X, uint16_t Y, uint8_t index, uint16_t font_color, uint16_t bkg_color)
{
	uint8_t i = 0, j = 0;
	uint16_t font = 0;

	LGG_SCP_address_set(X, Y, X+15, Y+15);
	/* function to show chinese */
	for(i=0; i<16; i++)
	{
		font = ((uint16_t*)chinese)[(uint16_t)index * 16 + i];
		for(j=0; j<16; j++)
		{
			if(font & 0x0001)
				LGG_SCP_transmit_data16(font_color);
			else
				LGG_SCP_transmit_data16(bkg_color);
			font >>= 1;
		}
	}
}

/*
 *  @ Brief:  draw a point on screen
 *  @ param:  (pos_x, pos_y), color
 */
void LGG_SCP_draw_point(uint16_t X, uint16_t Y, uint16_t color)
{
	LGG_SCP_address_set(X, Y, X, Y);
	LGG_SCP_transmit_data16(color);
}

/*
 *  @ Brief:  show a picture on screen
 *  @ param:  pImage - pointer to image pixel table
 */
void lgg_scp_show_image(uint16_t* pImage)
{
	uint16_t i = 0;
	LGG_SCP_address_set(0, 0, LGG_SCP_PM_WIDTH - 1, LGG_SCP_PM_HEIGHT - 1);
	for(i=0; i<20480; i++)
	{
		LGG_SCP_transmit_data16(pImage[i]);
	}
}

