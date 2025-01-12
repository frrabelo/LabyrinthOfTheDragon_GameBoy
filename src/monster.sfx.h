#ifndef _MONSTER_SFX_H
#define _MONSTER_SFX_H

#include "battle.h"
#include "sound.h"

#define SFX_MISS battle_sfx = sfx_miss
#define SFX_MELEE battle_sfx = sfx_monster_attack1
#define SFX_MAGIC battle_sfx = sfx_monster_attack2
#define SFX_FAIL battle_sfx = sfx_monster_fail
#define SFX_CRIT battle_sfx = sfx_monster_critical

#endif
