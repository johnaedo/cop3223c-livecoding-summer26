#ifndef COMBAT_H
#define COMBAT_H

double calculate_damage(const char *name, int bravery, int attack, int defense);
void heal(double *health, int *potions, int potion_strength);

#endif