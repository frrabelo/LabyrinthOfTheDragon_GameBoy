#ifndef _SOUND_H
#define _SOUND_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

void sound_init(void) NONBANKED;
void update_sound(void) NONBANKED;
void play_sound(void (*sound)(void)) NONBANKED;

void sfx_test(void);
void sfx_stairs(void);
void sfx_error(void);
void sfx_wall_hit(void);
void sfx_menu_move(void);
void sfx_next_round(void);
void sfx_no_no_square(void);
void sfx_melee_attack(void);
void sfx_monster_death(void);
void sfx_level_up(void);

#endif
