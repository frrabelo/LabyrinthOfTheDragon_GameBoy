#include <gb/gb.h>
#include "data.h"

INCBIN(tile_data_dungeon, "res/tiles/dungeon.bin")
INCBIN(tile_data_font, "res/tiles/font.bin")
INCBIN(tile_data_hero, "res/tiles/hero.bin")
INCBIN(tile_data_objects, "res/tiles/objects.bin")
INCBIN(tile_data_world_map, "res/tiles/world_map.bin")

INCBIN(tilemap_textbox, "res/tilemaps/textbox.tilemap")

void load_tilesets(void) {
  load_font_tiles();
  load_dungeon_tiles();
  load_objects_tiles();
  load_character_tiles();
}

void load_character_tiles(void) {
  VBK_REG = VBK_BANK_0;
  set_tile_data(0x00, 0x80, tile_data_hero, 0x80);
}

void load_objects_tiles(void) {
  VBK_REG = VBK_BANK_0;
  set_tile_data(0x00, 0x80, tile_data_objects, 0x88);
}

void load_font_tiles(void) {
  VBK_REG = VBK_BANK_1;
  set_tile_data(0x00, 0x80, tile_data_font, 0x88);
}

void load_dungeon_tiles(void) {
  VBK_REG = VBK_BANK_0;
  set_tile_data(0x00, 0x80, tile_data_dungeon, 0x90);
  VBK_REG = VBK_BANK_1;
  set_tile_data(0x00, 0x80, TILE_PAGE(tile_data_dungeon, 2), 0x90);
}

void load_world_map_tiles(void) {
  VBK_REG = VBK_BANK_0;
  set_tile_data(0x00, 0x80, tile_data_world_map, 0x90);
  VBK_REG = VBK_BANK_1;
  set_tile_data(0x00, 0x80, TILE_PAGE(tile_data_world_map, 2), 0x90);
}
