#ifndef COMBAT_H
#define COMBAT_H
#include "entity.h"

double calculate_damage(entity_t attacker, entity_t defender);
double heal(entity_t hero, int potion_strength);

#endif
