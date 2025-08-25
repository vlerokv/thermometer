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


typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;


void I2C2_write_bytes_to_addr (I2C_TypeDef *I2Cx, uint8_t control_byte ,uint8_t *buf, uint16_t bytes_count);
void ssd1306_write_command(uint8_t command);
uint8_t ssd1306_init(void);
void ssd1306_fill_buffer_with_color(SSD1306_COLOR color);
void ssd1306_update_screen(void);
#endif /* INC_OLED_H_ */

