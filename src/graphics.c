#include "graphics.h"

INCBIN(color_table_clothes, "res/color_tables/clothes.bin")
INCBIN(color_table_outline, "res/color_tables/outline.bin")
INCBIN(color_table_skin, "res/color_tables/skin.bin")

const uint16_t example_bg_palette[] = {
  RGB_BLACK,
  RGB_DARKGRAY,
  RGB_LIGHTGRAY,
  RGB_WHITE
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

  // Use the color tables to load a character palette
  uint16_t player_palette[4] = {
    0,
    color_table_skin[2],
    color_table_clothes[27],
    color_table_outline[20]
  };
  set_sprite_palette(0, 1, player_palette);
}
