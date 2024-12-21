#pragma bank 2

#include "floors.h"

//------------------------------------------------------------------------------
// Floorwide settings
//------------------------------------------------------------------------------

#define FLOOR1_ID 1
#define FLOOR1_START_COL 0
#define FLOOR1_START_ROW 0

const Map floor1_maps[] = {
  // id, bank, map data
  { MAP_A, 8, NULL },
  { MAP_B, 8, NULL },
  { MAP_C, 8, NULL },
  { MAP_D, 8, NULL },
};

//------------------------------------------------------------------------------
// Palette Colors
//------------------------------------------------------------------------------
const uint16_t floor1_palettes[] = {
  // Palette 0 - Core background tiles
  RGB8(190, 200, 190),
  RGB8(100, 100, 140),
  RGB8(40, 60, 40),
  RGB8(24, 0, 0),
  // Palette 1 - Treasure chests
  RGB8(192, 138, 40),
  RGB8(100, 100, 140),
  RGB8(40, 60, 40),
  RGB8(24, 0, 0),
  // Palette 2
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
  // Palette 3
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
};

//------------------------------------------------------------------------------
// Chests
//------------------------------------------------------------------------------
#define FLOOR1_NUM_CHESTS 0

const Chest floor1_chests[] = {
  /*
  {
    1,                // id (anything non-zero here works, ptrs amirite?)
    MAP_A,            // Map where the chest is at
    0, 0,             // Column & row in that map
    FLAGS_CHEST_OPEN, // Flag page for the open/closed flag
    CHEST_1           // Open flag
  }
  */
  { 0 }, // Remove me when you add your first chest (pointers amirite?)
};

//------------------------------------------------------------------------------
// Exits
//------------------------------------------------------------------------------
#define FLOOR1_NUM_EXITS 0

const Exit floor1_exits[] = {
  /*
  {
    MAP_A,        // Map the exit is on
    0, 0,         // Column and row on that map for the exit
    FLOOR1_ID,    // Floor to which the exit leads (last door, basically)
    DEST_MAP      // Id of the destination map
    0, 0,         // Column and row
    UP,           // Way the player should be facing leaving the exit
    EXIT_STAIRS   // Type of exit (not sure if we'll use this yet)
  },
  */
  { 0 }, // Remove me when you add your first chest (pointers amirite?)
};

//------------------------------------------------------------------------------
// Scripting Callbacks
//------------------------------------------------------------------------------

void floor1_on_init(void) {
}

void floor1_on_update(void) {
}

void floor1_on_draw(void) {
}

void floor1_on_action(void) {
}

bool floor1_before_chest(Chest *chest) {
  return true;
}

void floor1_on_enter(uint8_t from_id, uint8_t to_id) {
}

void floor1_on_chest(Chest *chest) {
}

bool floor1_on_special(void) {
  return false;
}

bool floor1_on_exit(void) {
  return false;
}

bool floor1_on_move(void) {
  return false;
}

//------------------------------------------------------------------------------
// Area Definition (shouldn't have to touch this)
//------------------------------------------------------------------------------
const Area floor1 = {
  FLOOR1_ID,                   // Id
  FLOOR1_START_COL, FLOOR1_START_ROW,
  &dungeon_tileset,
  floor1_palettes,            // Palettes (always 4 palettes / area)
  4, floor1_maps,             // # of maps, maps
  FLOOR1_NUM_EXITS, floor1_exits,    // # of exits, exits
  FLOOR1_NUM_CHESTS, floor1_chests,  // # of chests, chests
  2,
  floor1_on_init,
  floor1_on_update,
  floor1_on_draw,
  floor1_on_action,
  floor1_before_chest,
  floor1_on_chest,
  floor1_on_enter,
  floor1_on_special,
  floor1_on_exit,
  floor1_on_move,
};
