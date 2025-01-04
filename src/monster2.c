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

static void beholder_take_turn(Monster *monster) {
  sprintf(battle_pre_message, str_monster2_does_nothing,
    monster->name, monster->id);
  skip_post_message = true;
}

void beholder_generator(Monster *m, uint8_t level, PowerTier tier) BANKED {
  monster_init_instance(
    m, MONSTER_BEHOLDER, str_misc_beholder, &beholder_tileset, level, tier);

  m->palette = beholder_palettes;
  m->bank = BANK_7;
  m->take_turn = beholder_take_turn;

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

