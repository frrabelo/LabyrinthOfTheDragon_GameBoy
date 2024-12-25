#pragma bank 6

#include <stdio.h>

#include "battle.h"
#include "data.h"
#include "monster.h"
#include "stats.h"
#include "strings.h"

/**
 * Initializes a monster instance for a monster generator.
 * @param i Monster instance to reset.
 * @param m Base monster for the instance.
 */
void monster_init_instance(
  Monster *monster,
  MonsterType type,
  const char *name,
  const Tileset *ts
) {
  monster->type = type;
  monster->tileset = ts;
  monster->active = true;
  monster->name = name;
  monster->palette = NULL;
  monster->id = '\0';
  monster->exp_tier = C_TIER;
  monster->hp = 0;
  monster->max_hp = 0;
  monster->target_hp = 0;
  monster->atk_base = 0;
  monster->atk = 0;
  monster->def_base = 0;
  monster->def = 0;
  monster->matk_base = 0;
  monster->matk = 0;
  monster->mdef_base = 0;
  monster->mdef = 0;
  monster->agl_base = 0;
  monster->agl = 0;
  monster->aspect_immune = 0;
  monster->aspect_resist = 0;
  monster->aspect_vuln = 0;
  monster->debuff_immune = 0;
  monster->can_flee = true;
  monster->fled = false;
  monster->parameter = 0;
}

/**
 * Applies damage to the player.
 * @param base_damage Base damage for the attck.
 * @param type Type of damage dealt.
 */
void damage_player(uint16_t base_damage, DamageAspect type) BANKED {
  if (player.aspect_immune & type) {
    sprintf(battle_post_message, str_monster_hit_immune);
    return;
  }

  uint8_t roll = d16();
  uint16_t damage = calc_damage(roll, base_damage);
  bool critical = roll >= 12;

  if (critical) {
    sprintf(battle_post_message, str_monster_hit_crit, damage);
  } else  if (player.aspect_resist & type) {
    damage >>= 1;
    sprintf(battle_post_message, str_monster_hit_resist, damage);
  } else if (player.aspect_vuln & type) {
    damage <<= 1;
  } else if (type == DAMAGE_PHYSICAL) {
    sprintf(battle_post_message, str_monster_hit, damage);
  } else {
    const char *aspect = damage_aspect_name(type);
    sprintf(battle_post_message, str_monster_hit_aspect, damage, aspect);
  }

  if (player.hp < damage)
    player.hp = 0;
  else
    player.hp -= damage;
}

// -----------------------------------------------------------------------------
// Monster 255 - Test Dummy
// -----------------------------------------------------------------------------

inline void dummy_take_turn(Monster *dummy) {
  sprintf(battle_pre_message, str_monster_dummy_pre, dummy->id);

  switch (dummy->parameter) {
  case DUMMY_INVINCIBLE:
    dummy->target_hp = dummy->max_hp;
    sprintf(battle_post_message, str_monster_dummy_post_heal);
    break;
  case DUMMY_COWARD:
    monster_flee(dummy);
    break;
  case DUMMY_AGGRESSIVE:
    sprintf(battle_pre_message, str_monster_attack,
      dummy->name, dummy->id);
    if (roll_attack(dummy->atk, player.def)) {
      const uint16_t base = get_monster_dmg(dummy->level, dummy->exp_tier);
      damage_player(base, DAMAGE_PHYSICAL);
    } else {
      sprintf(battle_post_message, str_monster_miss);
    }
    break;
  default:
    skip_post_message = true;
    break;
  }
}

void dummy_generator(
  Monster *monster,
  uint8_t level,
  TestDummyType type
) BANKED {
  monster_init_instance(
    monster,
    MONSTER_DUMMY,
    str_misc_dummy,
    &test_dummy_tileset
  );

  PowerTier tier = C_TIER;

  monster->palette = DUMMY_COLORS;
  monster->exp_tier = tier;
  monster->level = level;

  monster->max_hp = get_monster_hp(level, tier);
  monster->hp = monster->max_hp;

  monster->atk_base = get_monster_atk(level, tier);
  monster->def_base = get_monster_def(level, tier);
  monster->matk_base = get_monster_atk(level, tier);
  monster->mdef_base = get_monster_def(level, tier);
  monster->agl_base = get_agl(1, C_TIER);

  monster->parameter = type;

  monster_reset_stats(monster);
}

// -----------------------------------------------------------------------------
// Monster 1 - Kobold
// -----------------------------------------------------------------------------

inline void kobold_take_turn(Monster *m) {
  const uint8_t move_roll = d16();

  // Dazed (silly kobolds being dazed 6.25% of the time)
  if (move_roll == 15) {
    sprintf(battle_pre_message, str_monster_kobold_dazed, m->id);
    sprintf(battle_post_message, str_monster_kobold_does_nothing);
    return;
  }

  uint8_t atk, def;
  DamageAspect type;

  if (move_roll < 4) {
    // Fire loogie
    atk = m->matk;
    def = player.mdef;
    type = DAMAGE_FIRE;
    sprintf(battle_pre_message, str_monster_kobold_fire, m->id);
  } else {
    // Axe attack
    atk = m->atk;
    def = player.def;
    type = DAMAGE_PHYSICAL;
    sprintf(battle_pre_message, str_monster_kobold_axe, m->id);
  }

  if (roll_attack(atk, def)) {
    damage_player(get_monster_dmg(m->level, m->exp_tier), type);
  } else if (!d16()) {
    // Silly kobolds falling over on their ass 6.25% of the time
    sprintf(battle_post_message, str_monster_kobold_miss);
  } else {
    sprintf(battle_post_message, str_monster_miss);
  }
}

void kobold_generator(Monster *m, uint8_t level, PowerTier tier) BANKED {
  monster_init_instance(m, MONSTER_KOBOLD, str_misc_kobold, &kobold_tileset);

  m->palette = MONSTER_KOBOLD_PALETTES + tier * 4;
  m->exp_tier = tier;
  m->level = level;

  m->max_hp = get_monster_hp(level_offset(level, 2), tier);
  m->hp = m->max_hp;

  m->atk_base = get_monster_atk(level_offset(level, 3), tier);
  m->def_base = get_monster_def(level_offset(level, -1), tier);
  m->matk_base = get_monster_atk(level_offset(level, -1), tier);
  m->mdef_base = get_monster_def(level_offset(level, -2), tier);
  m->agl_base = get_agl(level_offset(level, 2), tier == C_TIER ? B_TIER : tier);

  m->aspect_resist = DAMAGE_EARTH;
  m->aspect_vuln = DAMAGE_FIRE;

  monster_reset_stats(m);
}

void monster_flee(Monster *monster) BANKED {
  sprintf(
    battle_pre_message,
    str_monster_flee,
    monster->name,
    monster->id
  );

  if (roll_flee(monster->agl, player.agl)) {
    sprintf(battle_post_message, str_monster_flee_success);
    monster->fled = true;
  } else {
    sprintf(battle_post_message, str_monster_flee_failure);
    monster->fled = false;
  }
}

void monster_take_turn(Monster *monster) BANKED {
  switch (monster->type) {
  case MONSTER_KOBOLD:
    kobold_take_turn(monster);
    break;
  case MONSTER_DUMMY:
    dummy_take_turn(monster);
    break;
  }
}
