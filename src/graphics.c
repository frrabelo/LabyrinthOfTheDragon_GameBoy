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

const uint16_t textbox_palette[] = {
  RGB_TEXTBOX_0,
  RGB_TEXTBOX_1,
  RGB_TEXTBOX_2,
  RGB_TEXTBOX_3
};

void load_palettes (void) {
  set_bkg_palette(0, 1, example_bg_palette);
  set_bkg_palette(7, 1, textbox_palette);
  set_sprite_palette(0, 1, example_fg_palette);
}
