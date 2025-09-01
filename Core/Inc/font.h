/*
 * font.h
 *
 *  Created on: Aug 29, 2025
 *      Author: misch
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_

#include <stdint.h>

#define FONT special_font_7x13
#define SPECIAL_FONT_COUNT 18

extern const uint8_t special_font_7x13[];
extern const char special_font_chars[];

int find_char(char ch);

#endif /* INC_FONT_H_ */
