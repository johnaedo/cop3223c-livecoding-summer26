/* ============================================================
   entity.c — Hero and Enemy implementations
   Legally Distinct from Zelda - the Sequel | Week 5a

   CHECKPOINT A — enemy_type_name()
     Short, demonstrates enum-to-string mapping
     via switch.
     What should default return? What does an
     unknown EnemyType value mean in our game?

   CHECKPOINT B — create_enemy() and create_hero()
     Constructor pattern: function returns struct by value.
       - Designated initializers make intent clear
       - strncpy + manual null termination for the name fields
       - create_hero zeros the inventory (zero-init via .inv_count=0)
     Why not return Enemy*? What would be wrong with
     returning a pointer to the local `e`?"

   CHECKPOINT C — print_hero() and print_enemy()
     First use of const Hero * and const Enemy *.
     Draw the -> chain: h->inv_count, h->name, etc.
     This format is nicer than the Week 3 loose params.
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "entity.h"
#include "inventory.h"

/* ── enemy_type_name ───────────────────────────────────────── */
/* CHECKPOINT A */
const char *enemy_type_name(EnemyType t) {
    switch (t) {
        case DECEPTICON_MINION: return "Minion";
        case DECEPTICON_SEEKER:    return "Seeker";
        case DECEPTICON_LIEUTENANT:  return "Soundwave";
        case DECEPTICON_LEADER: return "Megatron";
        case DECEPTICON_UNICRON:   return "Unicron";
        default:           return "Unknown";
    }
}

/* ── create_hero ───────────────────────────────────────────── */
/* CHECKPOINT B */
Hero create_hero(const char *name, int hp, int attack, int defense) {
    Hero h = {
        .hp         = hp,
        .max_hp     = hp,
        .attack     = attack,
        .defense    = defense,
        .level      = 1,
        .experience = 0,
        .inv_count  = 0
    };
    strncpy(h.name, name, sizeof(h.name) - 1);
    h.name[sizeof(h.name) - 1] = '\0';
    /* inventory array is zero-initialized by the designated initializer above */
    return h;
}

/* ── create_enemy ──────────────────────────────────────────── */
/* CHECKPOINT B (continued) */
Enemy create_enemy(const char *name, int hp, int attack,
                   int defense, EnemyType type, const char *loot) {
    Enemy e = {
        .hp      = hp,
        .max_hp  = hp,
        .attack  = attack,
        .defense = defense,
        .type    = type
    };
    strncpy(e.name, name, sizeof(e.name) - 1);
    e.name[sizeof(e.name) - 1] = '\0';
    strncpy(e.loot, loot, ITEM_NAME_LEN - 1);
    e.loot[ITEM_NAME_LEN - 1] = '\0';
    return e;
}

/* ── print_hero ────────────────────────────────────────────── */
/* CHECKPOINT C */
void print_hero(const Hero *h) {
    printf("┌────────────────────────────────────┐\n");
    printf("│ %-35s│\n", h->name);
    printf("│ Level %-3d  XP: %-6d              │\n", h->level, h->experience);
    printf("│ HP:  %3d / %-3d                     │\n", h->hp, h->max_hp);
    printf("│ ATK: %-3d   DEF: %-3d               │\n", h->attack, h->defense);
    printf("│ Items: %-3d / %-3d                   │\n", h->inv_count, MAX_ITEMS);
    printf("└────────────────────────────────────┘\n");
}

/* ── print_enemy ───────────────────────────────────────────── */
/* CHECKPOINT C (continued) */
void print_enemy(const Enemy *e) {
    printf("┌────────────────────────────────────┐\n");
    printf("│ %-20s [%s]%*s│\n",
           e->name, enemy_type_name(e->type),
           (int)(12 - strlen(enemy_type_name(e->type))), "");
    printf("│ HP:  %3d / %-3d                     │\n", e->hp, e->max_hp);
    printf("│ ATK: %-3d   DEF: %-3d               │\n", e->attack, e->defense);
    printf("└────────────────────────────────────┘\n");
}
