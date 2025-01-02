#pragma bank 31

#include "floor.h"
#include "sound.h"

//------------------------------------------------------------------------------
// Floorwide settings
//------------------------------------------------------------------------------

#define ID 99
#define DEFAULT_X 4
#define DEFAULT_Y 4

//------------------------------------------------------------------------------
// Maps
//------------------------------------------------------------------------------

static const Map maps[] = {
  // id, bank, data, width, height
  { MAP_A, BANK_31, floor_test_data, 32, 32 },
  { MAP_B, BANK_31, floor_test_mini, 8, 8 },
  { MAP_C, BANK_31, floor_test_17x12, 17, 12 },
  { END },
};

//------------------------------------------------------------------------------
// Palette Colors
//------------------------------------------------------------------------------

static const uint16_t palettes[] = {
  // Palette 1 - Core background tiles
  RGB8(190, 200, 190),
  RGB8(100, 100, 140),
  RGB8(40, 60, 40),
  RGB8(24, 0, 0),
  // Palette 2 - Treasure chests
  RGB8(192, 138, 40),
  RGB8(100, 100, 140),
  RGB8(40, 60, 40),
  RGB8(24, 0, 0),
  // Palette 3
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
  // Palette 4
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
  // Palette 5
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
  // Palette 6
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
  // Palette 7
  RGB_WHITE,
  RGB8(120, 120, 120),
  RGB8(60, 60, 60),
  RGB_BLACK,
};

//------------------------------------------------------------------------------
// Chests
//------------------------------------------------------------------------------

static const Chest chests[] = {
  /*
  {
    CHEST_1,    // Always use a CHEST_* here cause it acts like a flag
    MAP_A,      // Map where the chest resides
    0, 0,       // (x, y) location for the chest
    false,      // Whether or not the chest is locked
    false,      // If locked, can it be opened using a magic key?
    "Nice!",    // Message to display when the chest is opened
    NULL,       // Item list contents (optional)
    NULL,       // Scripting "on open" callback (optional)
  }
  */
  // Basic items chest, contains some stuffs
  {
    CHEST_1,
    MAP_A, 10, 5, false, false,
    str_chest_item_2pot_1eth,
    chest_item_2pot_1eth
  },
  // A locked chest that can be unlocked using scripting
  {
    CHEST_2,
    MAP_A, 12, 5, true, false,
    str_chest_item_haste_pot,
    chest_item_haste_pot,
  },
  // An empty chest, default behavior if you don't set any params
  {
    CHEST_3,
    MAP_A, 14, 5, false, false,
  },
  // Can be unlocked using a magic key
  {
    CHEST_4,
    MAP_A, 16, 5, true, true,
    str_chest_item_haste_pot,
    chest_item_haste_pot,
  },
  // Custom chest that gives a magic key using a scripting callback
  {
    CHEST_5,
    MAP_A, 18, 5, false, false,
    NULL,
    NULL,
    chest_add_magic_key,
  },
  // Custom chest that is unlocked using a slightly more involved script
  {
    CHEST_6,
    MAP_A, 20, 5, true, false,
    str_chest_item_regen_pot,
    chest_item_regen_pot,
  },
  { CHEST_7, MAP_A, 10, 2, false, false, NULL, NULL, chest_add_torch },
  { END },
};

//------------------------------------------------------------------------------
// Exits
//------------------------------------------------------------------------------

static const Exit exits[] = {
  /*
  {
    MAP_A,        // Map the exit is on
    0, 0,         // Column and row on that map for the exit
    FLOOR_TEST_ID,    // Floor to which the exit leads (last door, basically)
    DEST_MAP      // Id of the destination map
    0, 0,         // Column and row
    UP,           // Way the player should be facing leaving the exit
    EXIT_STAIRS   // Type of exit (not sure if we'll use this yet)
  },
  */

  { MAP_A, 8, 1, MAP_B, 4, 1, DOWN, EXIT_STAIRS },
  { MAP_B, 4, 1, MAP_A, 8, 1, DOWN, EXIT_STAIRS },

  { MAP_A, 25, 27, MAP_B, 4, 5, DOWN, EXIT_STAIRS },
  { MAP_B, 4, 5, MAP_A, 25, 27, DOWN, EXIT_STAIRS },

  { MAP_A, 9, 27, MAP_C, 3, 3, DOWN, EXIT_STAIRS },
  { MAP_C, 3, 3, MAP_A, 9, 27, DOWN, EXIT_STAIRS },

  { MAP_A, 14, 1, MAP_C, 4, 7, UP, EXIT_STAIRS },
  { MAP_C, 4, 7, MAP_A, 14, 1, DOWN, EXIT_STAIRS },
  { MAP_C, 3, 7, MAP_A, 14, 1, DOWN, EXIT_STAIRS },

  // { MAP_A, 19, 1, MAP_A, 2, 15, UP, EXIT_STAIRS, &floor_test2 },

  { END },
};

//------------------------------------------------------------------------------
// Exits
//------------------------------------------------------------------------------

static const Sign signs[] = {
  /*
  {
    MAP_A,      // Id of the map
    0, 0,       // Position in the map for the sign
    UP,         // Direction the player must be facing
    "Hi there!" // The message to display
  }
  */
  { MAP_A, 4, 1, UP, "This skull\x60\nIs so metal." },
  { MAP_A, 7, 1, UP, "A pair of glowing\neyes peers back\x60" },

  { END },
};

//------------------------------------------------------------------------------
// Levers
//------------------------------------------------------------------------------

static void on_lever(const Lever *lever) {
  if (lever->id == LEVER_1) {
    map_textbox("You hear a click\x60");
    set_chest_unlocked(CHEST_2);
  }

  if (lever->id == LEVER_2) {
    if (is_lever_stuck(LEVER_3)) {
      map_textbox("The other lever\ncreaks.");
      unstick_lever(LEVER_3);
    } else {
      map_textbox("The other lever\ngroans.");
      stick_lever(LEVER_3);
    }
  }

  if (lever->id == LEVER_3) {
    map_textbox("The chest clicks.");
    set_chest_unlocked(CHEST_6);
  }

  if (lever->id == LEVER_4) {
    extinguish_sconce(SCONCE_1);
  }
}

static const Lever levers[] = {
  /*
  {
    LEVER_1,  // Use the LEVER_* constants for ids (again, used as flags)
    MAP_A,    // The map where the lever be
    0, 0,     // (x, y) tile coordinates in the map
    false,    // Can the lever only be pulled once?
    false,    // Does the lever start stuck? (requires scripting to change)
    NULL,     // Scripting callback for the lever
  }
  */
  { LEVER_1, MAP_A, 12, 3, true, false, on_lever },
  { LEVER_2, MAP_A, 22, 3, false, false, on_lever },
  { LEVER_3, MAP_A, 20, 3, true, true, on_lever },
  { LEVER_4, MAP_A, 5, 2, false, false, on_lever },
  { END },
};

//------------------------------------------------------------------------------
// Doors (NOT YET IMPLEMENTED)
//------------------------------------------------------------------------------

static const Door doors[] = {
  /*
  {
    DOOR_1,           // Use DOOR_* constants for ids.
    MAP_A,            // Map for the door
    0, 0              // (x, y) tile for the door
    DOOR_STAIRS_UP    // Kind of door
    true              // Magic key required to unlock
  }
  */
  { DOOR_1, MAP_A, 14, 1, DOOR_STAIRS_UP, true },
  { END }
};

//------------------------------------------------------------------------------
// Sconces (NOT YET IMPLEMENTED)
//------------------------------------------------------------------------------

static const Sconce sconces[] = {
  /*
  {
    SCONCE_1,   // Use SCONCE_* constants for ids.
    MAP_A,      // Map for the sconce
    0, 0,       // (x, y) tile for the sconce
    true,       // Should the sconce start lit
    FLAME_BLUE  // Flame color for the sconce if it starts lit.
  }
  */
  { SCONCE_STATIC, MAP_A, 7, 5, true, FLAME_RED },
  { SCONCE_STATIC, MAP_A, 11, 1, true, FLAME_GREEN },
  { SCONCE_STATIC, MAP_A, 16, 1, true, FLAME_BLUE },
  { SCONCE_STATIC, MAP_A, 23, 1, true, FLAME_RED },
  { SCONCE_1, MAP_A, 6, 1, false, FLAME_NONE },
  { END }
};

//------------------------------------------------------------------------------
// NPCs
//------------------------------------------------------------------------------

static const NPC npcs[] = {
  /*
  {
    NPC_1,    // Use NPC_* constants for ids.
    MAP_A,    // Map for the npc
    0, 0      // (x, y) tile for the npc
  }
  */
  { END }
};

//------------------------------------------------------------------------------
// Random Encounter Table
//------------------------------------------------------------------------------

static const EncounterTable random_encounters[] = {
  { END }
};

//------------------------------------------------------------------------------
// Scripting Callbacks
//------------------------------------------------------------------------------

static bool on_init(void) {
  return false;
}

static bool on_special(void) {
  Monster *monster = encounter.monsters;

  switch (map.active_map->id) {
  case MAP_A:
    if (player_at(3, 8)) {
      reset_encounter(MONSTER_LAYOUT_3S);
      dummy_generator(monster, 10, DUMMY_COWARD);
      monster->id = 'A';
      dummy_generator(++monster, 10, DUMMY_COWARD);
      monster->id = 'B';
      dummy_generator(++monster, 10, DUMMY_COWARD);
      monster->id = 'C';
      start_battle();
      return true;
    }
    if (player_at(3, 4)) {
      // generate_encounter(random_encounters);

      reset_encounter(MONSTER_LAYOUT_1);
      owlbear_generator(monster, 26, C_TIER);
      monster->id = 'A';
      start_battle();
      return true;
    }

    if (player_at(7, 8)) {
      // sfx_no_no_square();
      // take_exit(&no_no_exit);
      // return true;
    }

    break;
  }
  return false;
}

static bool on_move(void) {
  return false;
}

//------------------------------------------------------------------------------
// Area Definition (shouldn't have to touch this)
//------------------------------------------------------------------------------
const Floor floor_test = {
  ID, DEFAULT_X, DEFAULT_Y,
  palettes,
  maps,
  exits,
  chests,
  signs,
  levers,
  doors,
  sconces,
  npcs,
  on_init,
  on_special,
  on_move,
};

