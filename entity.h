#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
  HERO,
  ENEMY_DECEPTICON,
  ENEMY_SEEKER,
  ENEMY_QUINTESSON,
  ENEMY_UNICRON  
} EntityCategory;

typedef struct {
    char name[32];
    int max_hp;
    double current_hp;
    int attack;
    int defense;
    int bravery;
    int potions;
    int magic_skill;
    EntityCategory type;
} entity_t;



#endif