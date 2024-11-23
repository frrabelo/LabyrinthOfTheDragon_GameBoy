#include <gb/gb.h>
#include "data.h"

// Include binary tile data

INCBIN(dungeon_tiles, "res/tiles/dungeon.bin")
INCBIN(world_map_tiles, "res/tiles/world_map.bin")
INCBIN(font_tiles, "res/tiles/font.bin")
INCBIN(hero_tiles, "res/tiles/hero.bin")

void load_tilesets(void) {
  VBK_REG = VBK_BANK_0;
  set_tile_data(0x00, 0x80, hero_tiles, 0x80);
  set_tile_data(0x00, 0x80, world_map_tiles, 0x88);
  VBK_REG = VBK_BANK_1;
  set_tile_data(0x00, 0x40, world_map_tiles + 0x40, 0x88);
  set_tile_data(0x40, 0x80, dungeon_tiles, 0x88);
  set_tile_data(0x00, 0x80, font_tiles, 0x90);
}
