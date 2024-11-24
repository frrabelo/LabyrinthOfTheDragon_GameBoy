/**
 * Binary data loading variables and routines.
 */

#ifndef _DATA_H
#define _DATA_H

#include <gbdk/incbin.h>

INCBIN_EXTERN(tile_data_dungeon)
INCBIN_EXTERN(tile_data_font)
INCBIN_EXTERN(tile_data_hero)
INCBIN_EXTERN(tile_data_objects)
INCBIN_EXTERN(tile_data_world_map)


#define TILE_PAGE(ptr,n) (void *)((ptr) + 0x80 * 16 * ((n)-1))

/**
 * Loads graphics tiles into VRAM.
 */
void load_tilesets(void);

void load_font_tiles(void);
void load_character_tiles(void);
void load_dungeon_tiles(void);
void load_objects_tiles(void);

#endif
