/**
 * Binary data loading variables and routines.
 */

#ifndef _DATA_H
#define _DATA_H

#include <gbdk/incbin.h>

INCBIN_EXTERN(font_tiles)
INCBIN_EXTERN(hero_tiles)
INCBIN_EXTERN(dungeon_tiles)
INCBIN_EXTERN(world_map_tiles)

/**
 * Loads graphics tiles into VRAM.
 */
void load_tilesets(void);

#endif
