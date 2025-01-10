#ifndef _SOUND_H
#define _SOUND_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

/**
 * Initializes the sound system.
 */
void sound_init(void) NONBANKED;

/**
 * Timer ISR that handles sound updates.
 */
void update_sound(void) NONBANKED;

/**
 * Plays the given sound.
 * @param sound Sound function to execute.
 */
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
