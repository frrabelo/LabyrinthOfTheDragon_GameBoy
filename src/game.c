#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "data.h"
#include "game.h"
#include "graphics.h"
#include "util.h"

/**
 * Timer used for Noboru's "Walking" animation.
 */
Timer walk_timer;

/**
 * Current walk frame (either 0 or 1).
 */
uint8_t walk_frame;


void init_game(void) {
  load_tilesets();
  load_palettes();
  draw_hello_world();
  init_hero();
}

void game_loop(void) {
  update_hero();
}

void render(void) {
}

void init_hero(void) {
  const uint8_t x = 0x48;
  const uint8_t y = 0x4C;
  const uint8_t offset = 0x00;
  const uint8_t frame = (walk_frame << 1) + offset;

  init_timer(walk_timer, 18);

  set_sprite_tile(0, frame);
  set_sprite_prop(0, 0);
  move_sprite(0, x, y);

  set_sprite_tile(1, frame + 0x01);
  set_sprite_prop(1, 0);
  move_sprite(1, x + 8, y);

  set_sprite_tile(2, frame + 0x10);
  set_sprite_prop(2, 0);
  move_sprite(2, x, y + 8);

  set_sprite_tile(3, frame + 0x11);
  set_sprite_prop(3, 0);
  move_sprite(3, x + 8, y + 8);
}

void update_hero(void) {
  if (update_timer(walk_timer)) {
    reset_timer(walk_timer);
    walk_frame ^= 1;
  }
  const uint8_t offset = 0x00;
  const uint8_t frame = (walk_frame << 1) + offset;
  set_sprite_tile(0, frame);
  set_sprite_tile(1, frame + 0x01);
  set_sprite_tile(2, frame + 0x10);
  set_sprite_tile(3, frame + 0x11);
}

void draw_hello_world(void) {
  // Note: GBDK has methods for string printing (e.g. printf) but this example
  // shows how to set pointers, write arbitrary data to the VRAM, etc.

  // Initialize a VRAM address at the 2nd row and 3rd column.
  uint8_t *char_addr = (void *)(0x9800 + 0x10 * 2 + 3);

  // Initialize a string constant, and step through the character writing
  // data to the VRAM and incremented the VRAM address with each character
  // placed
  const char *hello = "HELLO WORLD!";

  const char *cryptotherion = "Cryptotherion!";
  const uint8_t len = 14;
  for (uint8_t k = 0; k < len; k++) {
    uint8_t c = (uint8_t)cryptotherion[k];
    VBK_REG = VBK_TILES;
    set_vram_byte(char_addr, c);
    VBK_REG = VBK_ATTRIBUTES;
    set_vram_byte(char_addr, 0b00001000);
    char_addr++;
  }
}