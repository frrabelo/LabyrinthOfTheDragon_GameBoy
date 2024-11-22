#include <gb/gb.h>
#include "data.h"

// Include binary tile data
INCBIN(font_tiles, "res/tiles/font.bin")
INCBIN(hero_tiles, "res/tiles/hero.bin")

void load_tilesets(void) {
  set_tile_data(0x00, 0x80, hero_tiles, 0x80);
  set_tile_data(0x00, 0x80, font_tiles, 0x90);
}
