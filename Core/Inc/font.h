/*
 * font.h
 *
 *  Created on: Aug 29, 2025
 *      Author: misch
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_

#include <stdint.h>

#define FONT_GLYPH_SIZE_BYTES 49

typedef enum
{
    FONT_SPECIAL_7x13,
} font_e;

typedef struct
{
    char symbol;
    uint8_t glyph[FONT_GLYPH_SIZE_BYTES];
} font_glyph_t;

typedef struct
{
    uint8_t glyph_width;
    uint8_t glyph_height;
    uint8_t bytes_per_line;
    uint8_t glyph_count;
    const font_glyph_t* glyphs;
} font_t;

const uint8_t* font_get_glyph(const font_t *font, char ch);
uint8_t font_get_width(const font_t* font);
uint8_t font_get_height(const font_t *font);
uint8_t font_get_bytes_per_line(const font_t* font);
uint8_t font_get_glyph_count(const font_t* font);
const font_t* font_get_special_7x13(void);
#endif /* INC_FONT_H_ */
