#pragma bank 7

#include <stdio.h>

#include "battle.h"
#include "data.h"
#include "monster.h"
#include "stats.h"
#include "strings.h"

// -----------------------------------------------------------------------------
// Monster 10 - Mind Flayer
// -----------------------------------------------------------------------------

#define MIND_FLAYER_EXTRACT_BRAIN FLAG(6)
#define MIND_FLAYER_MIND_BLAST FLAG(7)

static void mindflayer_take_turn(Monster *monster) {
  const uint8_t tier = monster->exp_tier;
  const uint16_t base_damage = get_monster_dmg(monster->level, tier);

  if (
    d8() < 3 &&
    !(monster->parameter & MIND_FLAYER_MIND_BLAST)
  ) {
    // Mind blast
    sprintf(battle_pre_message, str_monster2_mindflayer_mind_blast, monster->id);
    if (player.debuff_immune & DEBUFF_CONFUSED) {
      monster->parameter |= MIND_FLAYER_MIND_BLAST;
      sprintf(battle_post_message, str_monster2_mindflayer_mind_blast_miss);
    }

    if (roll_attack(monster->matk, player.mdef)) {
      monster->parameter |= MIND_FLAYER_MIND_BLAST;
      uint16_t damage = damage_player(base_damage / 2, DAMAGE_MAGICAL);
      sprintf(
        battle_post_message, str_monster2_mindflayer_mind_blast_hit, damage);
      apply_confused(
        encounter.player_status_effects, tier, 3, player.debuff_immune);
    } else {
      sprintf(battle_post_message, str_monster2_mindflayer_mind_blast_miss);
    }

    return;
  }

  if (
    !(monster->parameter & MIND_FLAYER_EXTRACT_BRAIN) &&
    (player.debuffs & FLAG_DEBUFF_CONFUSED)
  ) {
    // Extract brain
    monster->parameter |= MIND_FLAYER_EXTRACT_BRAIN;
    sprintf(
      battle_pre_message, str_monster2_mindflayer_extract_brain, monster->id);

    if (roll_attack(level_offset(monster->level, -15), player.def)) {
      sprintf(battle_post_message,  str_monster2_mindflayer_extract_brain_hit);
      player.hp = 0;
    } else {
      sprintf(battle_post_message, str_monster_miss);
    }

    return;
  }

  // Tentacle attack
  sprintf(battle_pre_message, str_monster2_mindflayer_tentacle, monster->id);
  if (roll_attack(monster->atk, player.def))
    damage_player(base_damage, DAMAGE_PHYSICAL);
  else
    sprintf(battle_post_message, str_monster_miss);
}

void mindflayer_generator(Monster *m, uint8_t level, PowerTier tier) BANKED {
  monster_init_instance(
    m, MONSTER_MINDFLAYER, str_misc_mind_flayer, &mindflayer_tileset,
    level, tier);

  m->max_hp = get_monster_hp(level_offset(level, 10), S_TIER);
  m->atk = get_monster_atk(level_offset(level, 5), tier);
  m->mdef = get_monster_def(level_offset(level, 5), tier);
  m->aspect_resist |= DAMAGE_MAGICAL;

  m->palette = mindflayer_palettes;
  m->bank = BANK_7;
  m->take_turn = mindflayer_take_turn;

  monster_reset_stats(m);
}

// -----------------------------------------------------------------------------
// Monster 11 - Beholder
// -----------------------------------------------------------------------------

#define BEHOLDER_PARALYZE 0
#define BEHOLDER_FEAR 1
#define BEHOLDER_SLOW 2
#define BEHOLDER_NECRO 3
#define BEHOLDER_ICE 4
#define BEHOLDER_TRIP 5
#define BEHOLDER_FIRE 6
#define BEHOLDER_DEATH 7

static void beholder_take_turn(Monster *monster) {
  const uint8_t ray_chance[4] = { 2, 3, 4, 5 };
  const uint8_t debuff_turns[4] = { 1, 2, 3, 4 };
  const PowerTier debuff_tiers[4] = { C_TIER, B_TIER, B_TIER, A_TIER };
  const PowerTier exp_tier = monster->exp_tier;

  if (d16() < ray_chance[monster->exp_tier] && monster->parameter > 0) {
    // Random Eyestalk Ray
    const bool hit = roll_attack(monster->matk, player.mdef);
    const uint8_t turns = debuff_turns[exp_tier];
    const PowerTier debuff_tier = debuff_tiers[exp_tier];

    sprintf(battle_pre_message, str_monster2_beholder_shoot_ray, monster->id);
    if (!hit) {
      sprintf(battle_post_message, str_monster2_beholder_ray_miss);
      return;
    }

    monster->parameter--;

    const uint8_t ray_type = d8();

    const PowerTier ray_tiers[4] = { B_TIER, A_TIER, A_TIER, S_TIER };
    const uint16_t base_damage = get_monster_dmg(
      monster->level, ray_tiers[exp_tier]);

    switch (ray_type) {
    case BEHOLDER_ICE:
      damage_player(base_damage, DAMAGE_WATER);
      return;
    case BEHOLDER_FIRE:
      damage_player(base_damage, DAMAGE_FIRE);
      return;
    }

    uint16_t damage = damage_player(base_damage, DAMAGE_MAGICAL);
    StatusEffectResult debuff_result = STATUS_RESULT_FAILED;

    switch (ray_type) {
    case BEHOLDER_PARALYZE:
      debuff_result = apply_paralyzed(
        encounter.player_status_effects,
        debuff_tier,
        turns,
        player.debuff_immune
      );
      if (debuff_result == STATUS_RESULT_SUCCESS)
        sprintf(battle_post_message, str_monster2_beholder_ray_paralyze, damage);
      return;
    case BEHOLDER_FEAR:
      debuff_result = apply_scared(
        encounter.player_status_effects,
        debuff_tier,
        turns,
        player.debuff_immune
      );
      if (debuff_result == STATUS_RESULT_SUCCESS)
        sprintf(battle_post_message, str_monster2_beholder_ray_fear, damage);
      return;
    case BEHOLDER_SLOW:
      debuff_result = apply_agl_down(
        encounter.player_status_effects,
        debuff_tier,
        turns,
        player.debuff_immune
      );
      if (debuff_result == STATUS_RESULT_SUCCESS)
        sprintf(battle_post_message, str_monster2_beholder_ray_slow, damage);
      return;
    case BEHOLDER_NECRO:
      debuff_result = apply_poison(
        encounter.player_status_effects,
        debuff_tier,
        turns,
        player.debuff_immune
      );
      if (debuff_result == STATUS_RESULT_SUCCESS)
        sprintf(battle_post_message, str_monster2_beholder_ray_necro, damage);
      return;
    case BEHOLDER_TRIP:
      player.trip_turns = turns;
      sprintf(battle_post_message, str_monster2_beholder_ray_trip, damage);
      return;
    default:
      bool player_died = d256() < 3;
      if (player_died) {
        player.hp = 0;
        sprintf(battle_post_message, str_monster2_beholder_ray_death);
      }
      return;
    }
  }

  // Bite
  sprintf(battle_pre_message, str_monster2_beholder_bite, monster->id);
  if (roll_attack(monster->atk, player.def)) {
    damage_player(get_monster_dmg(monster->level, exp_tier), DAMAGE_PHYSICAL);
  } else {
    sprintf(battle_post_message, str_monster2_beholder_bit_miss);
  }
}

void beholder_generator(Monster *m, uint8_t level, PowerTier tier) BANKED {
  monster_init_instance(
    m, MONSTER_BEHOLDER, str_misc_beholder, &beholder_tileset, level, tier);

  m->palette = beholder_palettes;
  m->bank = BANK_7;
  m->take_turn = beholder_take_turn;

  m->max_hp = get_monster_hp(level_offset(level, 10), tier);
  m->atk = get_monster_atk(level_offset(level, 5), tier);
  m->matk = get_monster_atk(level_offset(level, 7), tier);
  m->agl = get_agl(level_offset(level, -4), tier);

  const uint8_t eye_ray_tries[4] = { 1, 2, 3, 4 };
  m->parameter = eye_ray_tries[m->exp_tier];

  monster_reset_stats(m);
}

// -----------------------------------------------------------------------------
// Monster 12 - Dragon
// -----------------------------------------------------------------------------

static void dragon_take_turn(Monster *monster) {
  sprintf(battle_pre_message, str_monster2_does_nothing,
    monster->name, monster->id);
  skip_post_message = true;
}

void dragon_generator(Monster *m, uint8_t level, PowerTier tier) BANKED {
  monster_init_instance(
    m, MONSTER_DRAGON, str_misc_dragon, &dragon_tileset, level, tier);

  m->palette = dragon_palettes;
  m->bank = BANK_7;
  m->take_turn = dragon_take_turn;

  monster_reset_stats(m);
}

