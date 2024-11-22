#include "graphics.h"

const uint16_t example_bg_palette[] = {
  RGB_BLACK,
  RGB_DARKGRAY,
  RGB_LIGHTGRAY,
  RGB_WHITE
};

const uint16_t example_fg_palette[] = {
  RGB_BLACK,
  RGB_HERO_WARRIOR_SKIN,
  RGB_HERO_WARRIOR_LIGHT,
  RGB_HERO_WARRIOR_DARK
};

void load_palettes (void) {
  set_bkg_palette(0, 1, example_bg_palette);
  set_sprite_palette(0, 1, example_fg_palette);
}
