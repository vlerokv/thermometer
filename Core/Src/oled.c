/*
 * oled.c
 *
 *  Created on: Jul 31, 2025
 *      Author: misch
 */
#include <oled.h>
#include <font.h>
#include "stm32g0xx_ll_i2c.h"
#include "font.h"

static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

static SSD1306_t SSD1306;

void I2C2_write_bytes_to_addr(I2C_TypeDef *I2Cx, uint8_t control_byte ,uint8_t *buf, uint16_t bytes_count)
{
	LL_I2C_HandleTransfer(I2Cx, SSD1306_I2C_ADDR << 1, LL_I2C_ADDRSLAVE_7BIT, 1 + bytes_count, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

	// transmit control byte (command or data)
	while(!LL_I2C_IsActiveFlag_TXIS(I2Cx));
	LL_I2C_TransmitData8(I2Cx, control_byte);

	while(!LL_I2C_IsActiveFlag_TXE(I2Cx));
	for(uint16_t i = 0; i < bytes_count; i++)
	{
		LL_I2C_TransmitData8(I2Cx, buf[i]);
		while(!LL_I2C_IsActiveFlag_TXE(I2Cx));
	}

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx));
    LL_I2C_ClearFlag_STOP(I2Cx);
}

void ssd1306_write_command(uint8_t command)
{
	I2C2_write_bytes_to_addr (I2C2, 0x00, &command, 1);
}

uint8_t ssd1306_init(void)
{
	// Wait for the screen to boot
	LL_mDelay(100);

	/* Init LCD */
	ssd1306_write_command(0xAE); //display off
	ssd1306_write_command(0x20); //Set Memory Addressing Mode
	//ssd1306_write_command(0x00);
	ssd1306_write_command(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	ssd1306_write_command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1306_write_command(0xC8); //Set COM Output Scan Direction
	ssd1306_write_command(0x00); //---set low column address
	ssd1306_write_command(0x10); //---set high column address
	ssd1306_write_command(0x40); //--set start line address
	ssd1306_write_command(0x81); //--set contrast control register
	ssd1306_write_command(0xFF);
	ssd1306_write_command(0xA1); //--set segment re-map 0 to 127
	ssd1306_write_command(0xA6); //--set normal display
	ssd1306_write_command(0xA8); //--set multiplex ratio(1 to 64)
	ssd1306_write_command(0x3F); //--- height 64
	//ssd1306_write_command(0x1F); // --- height 32
	ssd1306_write_command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssd1306_write_command(0xD3); //-set display offset
	ssd1306_write_command(0x00); //-not offset
	ssd1306_write_command(0xD5); //--set display clock divide ratio/oscillator frequency
	ssd1306_write_command(0xF0); //--set divide ratio
	ssd1306_write_command(0xD9); //--set pre-charge period
	ssd1306_write_command(0x22); //
	ssd1306_write_command(0xDA); //--set com pins hardware configuration
	ssd1306_write_command(0x12); // -- height 64
	//ssd1306_write_command(0x02); // -- height 32
	ssd1306_write_command(0xDB); //--set vcomh
	ssd1306_write_command(0x20); //0x20,0.77xVcc
	ssd1306_write_command(0x8D); //--set DC-DC enable
	ssd1306_write_command(0x14); //
	ssd1306_write_command(0xAF); //--turn on SSD1306 panel

	ssd1306_fill_buffer_with_color(Black);
	ssd1306_update_screen();
	return 1;
}

void ssd1306_fill_buffer_with_color(SSD1306_COLOR color)
{
	for(uint32_t i = 0; i < sizeof(SSD1306_Buffer); i++)
	{
		SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

void ssd1306_update_screen(void)
{
	for (uint8_t i = 0; i < 8; i++) {
		ssd1306_write_command(0xB0 + i);
		ssd1306_write_command(0x00);
		ssd1306_write_command(0x10);
		I2C2_write_bytes_to_addr(I2C2, 0x40, &SSD1306_Buffer[SSD1306_WIDTH * i], SSD1306_WIDTH);
	}
}

void ssd1306_draw_pixel(uint8_t x, uint8_t y)
{
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return;
	}

	SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
}

void ssd1306_draw_char(char ch, const uint8_t font[], uint8_t X, uint8_t Y)
{
    int index = find_char(ch);

    if ((index < 0) || (index > SPECIAL_FONT_COUNT))
        return;

    uint8_t char_size = font[0];
    uint8_t font_width = font[1];
    uint8_t font_height = font[2];
    uint8_t bytes_per_column = font[3];

    uint8_t* glyph = (uint8_t*)&font[(index * char_size) + 4];

    for (int j = 0; j < font_height; j++)
    {
        for (int i = 0; i < font_width; i++)
        {

            uint8_t column_data = glyph[bytes_per_column * i + ((j & 0xF8) >> 3) + 1];
            uint8_t bitmask = 1 << (j & 0x07);

            if ((column_data & bitmask) != 0x00)
            {
            	ssd1306_draw_pixel(X + i, Y + j);
            }
        }
    }
}
