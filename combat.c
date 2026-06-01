#include <stdio.h>
#include <stdlib.h>
#include "combat.h"

double calculate_damage(const char *name, int bravery, int attack, int defense) {
    float defense_modifier = 0.0;
    srand(0);
    defense_modifier = 1 + rand()%20;


    double adjusted_attack = attack * (1 + (double) bravery/100);
    printf("adjusted attack: %lf\n", adjusted_attack);
    double damage = adjusted_attack - defense;
    printf("damage: %lf\n", damage);
    return (damage < 0) ? 0 : damage;

}

void heal(double *health, int *potions, const int potion_strength) {
    *health += potion_strength;
    (*potions)--;
}