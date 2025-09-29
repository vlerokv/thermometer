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

#define SSD1306_WIDTH      128
#define SSD1306_HEIGHT      64

#define SSD1306_I2C_ADDR   0x3C

typedef enum {
    Black = 0x00,
    White = 0x01
} SSD1306_COLOR;

void I2C2_write_bytes_to_addr (I2C_TypeDef *I2Cx, uint8_t control_byte ,uint8_t *buf, uint16_t bytes_count);
void ssd1306_write_command(uint8_t command);
uint8_t ssd1306_init(void);
void ssd1306_fill_buffer_with_color(SSD1306_COLOR color);
void ssd1306_update_screen(void);
void ssd1306_draw_pixel(uint8_t x, uint8_t y);
void ssd1306_draw_char(char ch, const uint8_t font[], uint8_t X, uint8_t Y);
void ssd1306_draw_string(const char* str, const uint8_t font[], uint8_t X, uint8_t Y);
#endif /* INC_OLED_H_ */

