#include <rand.h>
#include <stdint.h>
#include <stdio.h>

#include "battle.h"
#include "core.h"
#include "encounter.h"
#include "floor.h"
#include "item.h"
#include "map.h"
#include "sound.h"
#include "stats.h"

void init_test_player(PlayerClass c, uint8_t level) {
  init_player(c);
  set_player_level(level);
  sprintf(player.name, "Tester");
  player.message_speed = AUTO_PAGE_MED;
}

void test_battle_init(void) {
  encounter.is_test = true;
  toggle_sprites();
  init_battle();
}

void fill_inventory(uint8_t amt) {
  Item *item = inventory;
  for (uint8_t k = 0; k < INVENTORY_LEN; k++, item++)
    item->quantity = amt;
}

void test_big_map(void) {
  init_test_player(CLASS_FIGHTER, 45);

  player.has_torch = true;
  grant_ability(ABILITY_ALL);
  set_active_floor(&bank_floor1);
  init_world_map();
  game_state = GAME_STATE_WORLD_MAP;
}

#define SET_MAGIC_KEYS(n) do { \
    player.got_magic_key = true; \
    player.magic_keys = (n); \
  } while (0)

#define SET_HAS_TORCH player.has_torch = true

#define TEST_SEED(s) do {\
  init_random = false; \
  initarand(s); \
  } while(0)

void test_level(void) {
  init_test_player(CLASS_FIGHTER, 4);
  grant_ability(ABILITY_0);

  // SET_MAGIC_KEYS(9);
  // SET_HAS_TORCH;
  // disable_encounters = true;

  set_active_floor(&bank_floor1);
  init_world_map();

  // TEST_SEED(62);
}
