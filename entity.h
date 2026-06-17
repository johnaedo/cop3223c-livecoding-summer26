#ifndef ENTITY_H
#define ENTITY_H

/* ============================================================
   entity.h — Hero and Enemy type definitions
   Legally Distinct from Zelda - the Sequel | Week 5a

   
   ============================================================ */

#include "inventory.h"   /* brings in char inventory[][], MAX_ITEMS */

/* ── Enemy type enum ───────────────────────────────────────── */
typedef enum {
    DECEPTICON_MINION,
    DECEPTICON_SEEKER,
    DECEPTICON_LIEUTENANT,
    DECEPTICON_LEADER,
    DECEPTICON_UNICRON
} EnemyType;

/* ── Hero struct ───────────────────────────────────────────── */
typedef struct {
    char name[64];
    int  hp;
    int  max_hp;
    int  attack;
    int  defense;
    int  level;
    int  experience;
    char inventory[MAX_ITEMS][ITEM_NAME_LEN];
    int  inv_count;
} Hero;

/* ── Enemy struct ──────────────────────────────────────────── */
typedef struct {
    char      name[32];
    int       hp;
    int       max_hp;
    int       attack;
    int       defense;
    EnemyType type;
    char      loot[ITEM_NAME_LEN];   /* item dropped on defeat */
} Enemy;

/* ── Construction functions ────────────────────────────────── */
Hero  create_hero(const char *name, int hp, int attack, int defense);
Enemy create_enemy(const char *name, int hp, int attack,
                   int defense, EnemyType type, const char *loot);

/* ── Display ───────────────────────────────────────────────── */
void print_hero(const Hero *h);
void print_enemy(const Enemy *e);

/* ── Type name helper ──────────────────────────────────────── */
const char *enemy_type_name(EnemyType t);

#endif /* ENTITY_H */
