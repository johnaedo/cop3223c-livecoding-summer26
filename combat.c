#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "entity.h"

double calculate_damage(entity_t attacker, entity_t defender) {
    float defense_modifier = 0.0;
    srand(0);
    defense_modifier = 1 + rand()%20;


    double adjusted_attack = attacker.attack * (1 + (double) attacker.bravery/100);
    printf("adjusted attack: %lf\n", adjusted_attack);
    double damage = adjusted_attack - defender.defense;
    printf("damage: %lf\n", damage);
    return (damage < 0) ? 0 : damage;

};

double heal(entity_t hero, int potion_strength) {
    return hero.current_hp + potion_strength;
}
