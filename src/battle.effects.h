#ifndef _MONSTER_SFX_H
#define _MONSTER_SFX_H

#include "battle.h"
#include "sound.h"
#include "strings.h"

/**
 * Sets the "miss" sound effect to play during battle.
 */
#define SFX_MISS battle_sfx = sfx_miss

/**
 * Sets the monster melee attack sound to play during battle.
 */
#define SFX_MELEE battle_sfx = sfx_monster_attack1

/**
 * Sets the monster magic attack sound to play during battle.
 */
#define SFX_MAGIC battle_sfx = sfx_monster_attack2

/**
 * Sets the monster "action failed" sound effect to play during battle.
 */
#define SFX_FAIL battle_sfx = sfx_monster_fail

/**
 * Sets the "critical hit" sound effect to play during battle.
 */
#define SFX_CRIT battle_sfx = sfx_monster_critical

/**
 * Sets the flag to skip the post action message in the battle system.
 */
#define SKIP_POST_MSG skip_post_message = true

/**
 * Sets the message and sound effect for when a player misses with an attack.
 */
#define PLAYER_MISS do { \
  sprintf(battle_post_message, str_player_miss); \
  SFX_MISS; \
  } while(0)

/**
 * Sets the message and sound effect for when a player misses all monsters with
 * a multi-target attack.
 */
#define PLAYER_MISS_ALL do { \
  sprintf(battle_post_message, str_player_miss_all); \
  SFX_MISS; \
  } while(0)

/**
 * Sets the message and sound effect for when the player is healed.
 */
#define PLAYER_HEAL(hp) do { \
  sprintf(battle_post_message, str_player_heal_hp, (hp)); \
  } while (0)

#endif
