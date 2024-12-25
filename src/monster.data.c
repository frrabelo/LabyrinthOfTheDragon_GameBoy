#pragma bank 0

#include "core.h"
#include "data.h"
#include "monster.h"

//------------------------------------------------------------------------------
// Tilesets
//------------------------------------------------------------------------------

const Tileset test_dummy_tileset = { MONSTER_TILES, 14, tile_dummy };
const Tileset kobold_tileset = { MONSTER_TILES, 14, tile_kobold };

//------------------------------------------------------------------------------
// Palettes
//------------------------------------------------------------------------------

const palette_color_t DUMMY_COLORS[4] = {
  RGB_WHITE,
  RGB8(210, 0, 150),
  RGB_DARKBLUE,
  RGB8(24, 0, 24),
};

const palette_color_t MONSTER_KOBOLD_PALETTES[16] = {
  // C-Tier
  RGB_WHITE,
  RGB8(177, 113, 51),
  RGB8(77, 22, 11),
  RGB8(37, 3, 40),
  // B-Tier
  RGB_WHITE,
  RGB8(113, 51, 177),
  RGB8(77, 22, 11),
  RGB8(37, 3, 40),
  // A-Tier
  RGB_WHITE,
  RGB_LIGHTGRAY,
  RGB_DARKGRAY,
  RGB_BLACK,
  // S-Tier
  RGB_WHITE,
  RGB_LIGHTGRAY,
  RGB_DARKGRAY,
  RGB_BLACK,
};
