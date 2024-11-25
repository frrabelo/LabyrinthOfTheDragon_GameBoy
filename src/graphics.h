/**
 * Graphics & color related state and functions.
 */

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/incbin.h>
#include <stdint.h>
#include "util.h"

#define RGB_SKY_BLUE        RGB8(160, 228, 240)
#define RGB_NOBORU_SKIN     RGB8(199, 172, 131)
#define RGB_NOBORU_PURPLE1  RGB8(135, 32, 216)
#define RGB_NOBORU_PURPLE2  RGB8(126, 0, 125)

#define RGB_HERO_WARRIOR_SKIN   RGB8(245, 213, 135)
#define RGB_HERO_WARRIOR_LIGHT  RGB8(167, 75, 0)
#define RGB_HERO_WARRIOR_DARK   RGB8(8, 46, 54)

#define RGB_TEXTBOX_0 RGB8(32, 32, 150)
#define RGB_TEXTBOX_1 RGB8(200, 200, 200)
#define RGB_TEXTBOX_2 RGB8(32, 32, 32)
#define RGB_TEXTBOX_3 RGB8(255, 255, 255)

void load_palettes(void);




/**
 * Gets a 16-bit color data from the given color table at the given index.
 * @param tbl Color table.
 * @param idx Index offset from table.
 */
#define get_color(tbl,idx)  (uint16_t *)(tbl)[(idx)]

/**
 * Number of colors in the character clothes color table.
 */
#define COLOR_TABLE_CLOTHES_LEN 40

/**
 * Color table holding colors designed for character clothes.
 */
INCBIN_EXTERN_16(color_table_clothes)

/**
 * Number of colors in the character outline color table.
 */
#define COLOR_TABLE_OUTLINE_LEN 32

/**
 * Color table for character clothes.
 */
INCBIN_EXTERN_16(color_table_outline)

/**
 * Number of colors in the character skin color table.
 */
#define COLOR_TABLE_SKIN_LEN 20

/**
 * Color table for character skin.
 */
INCBIN_EXTERN_16(color_table_skin)

/**
 * Palette index for a character's skin tone.
 */
#define CHARACTER_SKIN 1

/**
 * Palette index for a character's clothes color.
 */
#define CHARACTER_CLOTHES 2

/**
 * Paltte index for a character's outline color.
 */
#define CHARACTER_OUTLINE 3

#endif
