#ifndef COMBAT_H
#define COMBAT_H

/* ============================================================
   combat.h — Week 5a: struct-based interface
   Legally Distinct from Zelda - the Sequel

   COMPARE WITH WEEK 3:
   Week 3 run_combat signature:
     int run_combat(const char *hero_name,
                    int *hero_hp, int hero_max_hp,
                    int hero_atk, int hero_def,
                    const char *enemy_name,
                    int *enemy_hp, int enemy_max_hp,
                    int enemy_atk, int enemy_def);   ← 10 parameters

   Week 5 run_combat signature:
     int run_combat(Hero *hero, Enemy *enemy);        ← 2 parameters

   INSTRUCTOR: Put both signatures on the board side by side.
   The struct is doing the same work with far less noise.
   ============================================================ */

#include "entity.h"

int  run_combat(Hero *hero, Enemy *enemy);
void apply_damage_hero(Hero *h, int damage);
void apply_damage_enemy(Enemy *e, int damage);
void heal_hero(Hero *h, int amount);

#endif /* COMBAT_H */
