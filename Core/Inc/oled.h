/*
 * oled.h
 *
 *  Created on: Jul 31, 2025
 *      Author: misch
 */
#ifndef INC_OLED_H_
#define INC_OLED_H_

#include <stdint.h>
#include "stm32g031xx.h"
#include "font.h"

#define SSD1306_WIDTH      128
#define SSD1306_HEIGHT      64

#define SSD1306_I2C_ADDR   0x3C

#define SSD1306_CONTROL_BYTE_CMD   0x00
#define SSD1306_CONTROL_BYTE_DATA   0x40

typedef enum
{
    Black = 0x00,
    White = 0x01
} SSD1306_COLOR;

void ssd1306_init(void);
void ssd1306_fill_buffer_with_color(SSD1306_COLOR color);
void ssd1306_update_screen(void);
void ssd1306_draw_pixel(uint8_t x, uint8_t y);
void ssd1306_draw_char(const font_t *font, char ch, uint8_t x, uint8_t y);
void ssd1306_draw_string(const font_t *font, const char* str, uint8_t x, uint8_t y);
#endif /* INC_OLED_H_ */

