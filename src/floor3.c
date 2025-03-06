#pragma bank 8

#include "floor.h"

//------------------------------------------------------------------------------
// Floorwide settings
//------------------------------------------------------------------------------

#define ID 99
#define DEFAULT_X 26
#define DEFAULT_Y 17

//------------------------------------------------------------------------------
// Maps
//------------------------------------------------------------------------------

static const Map maps[] = {
  // id, bank, data, width, height
  { MAP_A, BANK_16, floor_three_data, 32, 32 },
  { END },
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
  // {
  //   CHEST_1,
  //   MAP_A, 15, 12, true, true,
  //   str_chest_item_2pot_1eth,
  //   chest_item_2pot_1eth,
  // },
  // {
  //   CHEST_2,
  //   MAP_A, 18, 13, false, false,
  //   str_chest_item_1pots,
  //   chest_item_1pot,
  // },
  // {
  //   CHEST_3,
  //   MAP_A, 3, 12, false, false,
  //   NULL, NULL,
  //   chest_add_magic_key,
  // },
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

  { MAP_A, 26, 14, MAP_A, 4, 17, UP, EXIT_STAIRS },
  { MAP_A, 4, 17, MAP_A, 26, 14, DOWN, EXIT_STAIRS },

  { MAP_A, 24, 14, MAP_A, 19, 29, DOWN, EXIT_STAIRS },
  { MAP_A, 19, 29, MAP_A, 24, 14, DOWN, EXIT_STAIRS },

  { MAP_A, 28, 14, MAP_A, 12, 6, DOWN, EXIT_STAIRS },
  { MAP_A, 12, 6, MAP_A, 28, 14, DOWN, EXIT_STAIRS },

  { MAP_A, 14, 29, MAP_A, 27, 28, UP, EXIT_STAIRS },
  { MAP_A, 27, 28, MAP_A, 14, 29, DOWN, EXIT_STAIRS },

  { MAP_A, 17, 6, MAP_A, 3, 5, UP, EXIT_STAIRS },
  { MAP_A, 3, 5, MAP_A, 17, 6, DOWN, EXIT_STAIRS },

  { MAP_A, 4, 12, MAP_A, DEFAULT_X, DEFAULT_Y, UP, EXIT_STAIRS, &bank_floor3},

  {END},
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
  // { MAP_A, 13, 6, UP, str_floor_common_tbd },
  // { MAP_A, 24, 9, UP, str_floor_three_lever_puzzle },
  // { MAP_A, 23, 13, UP, str_floor_three_lever_one },
  // { MAP_A, 27, 13, UP, str_floor_three_lever_two },
  // { MAP_A, 16, 28, UP, str_floor_common_steve_jobs },

  { END },
};

//------------------------------------------------------------------------------
// Levers
//------------------------------------------------------------------------------

static void on_lever_pull(const Lever *lever) {
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
  // { LEVER_1, MAP_A,  4, 28, true, false, on_lever_pull },
  { END },
};

//------------------------------------------------------------------------------
// Doors
//------------------------------------------------------------------------------

static const Door doors[] = {
  /*
  {
    DOOR_1,           // Use DOOR_* constants for ids.
    MAP_A,            // Map for the door
    0, 0              // (x, y) tile for the door
    DOOR_STAIRS_UP    // Kind of door
    true              // Magic key required to unlock
    false,            // Does the door start opened?
  }
  */
  // { DOOR_1, MAP_A,  6, 26, DOOR_NORMAL, false },
  { END }
};

//------------------------------------------------------------------------------
// Sconces
//------------------------------------------------------------------------------

static void on_lit(const Sconce* sconce) {
}

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
  // { SCONCE_STATIC, MAP_A, 12, 26, true, FLAME_RED },
  { END }
};

//------------------------------------------------------------------------------
// NPCs (IMPLS YET)
//------------------------------------------------------------------------------

static void on_boss_victory(void) NONBANKED {
}

static void on_elite_victory(void) NONBANKED {
}

static bool on_boss_encouter(void) {
  // Monster *monster = encounter.monsters;
  // reset_encounter(MONSTER_LAYOUT_1);
  // kobold_generator(monster, player.level, B_TIER);
  // monster->id = 'A';
  // set_on_victory(on_boss_victory);
  // start_battle();
  return true;
}

static bool on_elite_encouter(void) {
  // Monster *monster = encounter.monsters;
  // reset_encounter(MONSTER_LAYOUT_1);
  // kobold_generator(monster, player.level, B_TIER);
  // monster->id = 'A';
  // set_on_victory(on_elite_victory);
  // start_battle();
  return true;
}

static bool on_npc_action(const NPC *npc) {
  // if (npc->id == NPC_2){
  //   map_textbox_with_action(str_floor_common_fight_me, on_boss_encouter);
  // } else {
  //   map_textbox_with_action(str_floor_common_love, on_elite_encouter);
  // }
  return true;
}

static const NPC npcs[] = {
  /*
  {
    NPC_1,            // Use NPC_* constants for ids.
    MAP_A,            // Map for the npc
    0, 0              // (x, y) tile for the npc
    MONSTER_KOBOLD,   // Monster graphic to use for the NPC
    B_TIER,           // Tier for the monster (determines palette)
    action_callback,  // Action callback to execute when the player interacts
  }
  */
  // { NPC_1, MAP_A, 15, 20, MONSTER_KOBOLD, A_TIER, on_npc_action },
  // { NPC_2, MAP_A, 23, 22, MONSTER_KOBOLD, S_TIER, on_npc_action },
  { END }
};

//------------------------------------------------------------------------------
// Scripting Callbacks
//------------------------------------------------------------------------------

static const EncounterTable random_encounters[] = {
  {
    ODDS_25P, MONSTER_LAYOUT_2,
    MONSTER_ZOMBIE, 6, C_TIER,
    MONSTER_KOBOLD, 5, C_TIER,
  },
  {
    ODDS_25P, MONSTER_LAYOUT_1,
    MONSTER_GOBLIN, 7, C_TIER,
  },
  {
    ODDS_25P, MONSTER_LAYOUT_1,
    MONSTER_KOBOLD, 7, C_TIER,
  },
  {
    ODDS_25P, MONSTER_LAYOUT_1,
    MONSTER_KOBOLD, 5, C_TIER,
  },
  { END }
};


static bool on_init(void) {
  // config_random_encounter(600, 1, 1, true);
  return false;
}

static bool on_special(void) {
  // if (player_at(20, 15) &&
  //     (is_lever_on(LEVER_8) ||
  //      is_lever_on(LEVER_7) ||
  //      is_lever_on(LEVER_6) ||
  //      !is_lever_on(LEVER_5))){
  //   teleport(MAP_A, 25, 15, LEFT);
  //   return true;
  // }
  return false;
}

static bool on_move(void) {
  if (check_random_encounter()) {
    generate_encounter(random_encounters);
    start_battle();
    return true;
  }
  return false;
}

static bool on_action(void) {
  return false;
}

//------------------------------------------------------------------------------
// Palette Colors
//------------------------------------------------------------------------------

static const palette_color_t palettes[] = {
  // Palette 1 - Core background tiles
  RGB8(197, 244, 135),
  RGB8(85, 166, 57),
  RGB8(74, 45, 100),
  RGB8(37, 20, 0),
  // Palette 2 - Treasure chests
  RGB8(224, 173, 18),
  RGB8(85, 166, 57),
  RGB8(74, 45, 100),
  RGB8(37, 20, 0),
  // Palette 3 - Treasure chest "special"
  RGB8(86, 221, 146),
  RGB8(85, 166, 57),
  RGB8(74, 45, 100),
  RGB8(37, 20, 0),
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
// Area Definition (shouldn't have to touch this)
//------------------------------------------------------------------------------
const Floor floor3 = {
  ID, DEFAULT_X, DEFAULT_Y, palettes,
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
  on_action,
};
