#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "data.h"
#include "game.h"
#include "graphics.h"
#include "joypad.h"
#include "textbox.h"
#include "util.h"

typedef enum GameState {
  WAITING,
  TEXTBOX
} GameState;

GameState game_state = WAITING;


const char *test_message = "Hello traveler\x60\x03This is the land\nof Athemis.\nA broken land.\x03Will you\x60?\nCould you\x60?\x03Please, help us\x60\0";


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
  init_hero();
  init_text_box();

  // VBK_REG = VBK_TILES;
  // uint8_t *arrow_addr = set_win_tile_xy(18, 4, 0xFF);
  // VBK_REG = VBK_ATTRIBUTES;
  // set_vram_byte(arrow_addr, 0b00001111);
}

void game_loop(void) {
  update_hero();
  if (game_state == WAITING && was_pressed(J_A | J_B)) {
    open_textbox(test_message);
    game_state = TEXTBOX;
  } else if (game_state == TEXTBOX && textbox_state == TEXTBOX_CLOSED) {
    game_state = WAITING;
  }
}

void render(void) {
  if (game_state == TEXTBOX) {
    update_textbox();
  }
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
