/* ============================================================
   main.c — Legally Distinct from Zelda - the Sequel | Week 5a
   "The Great Refactor"

   Compile:
     gcc -Wall -Wextra -std=c17 -o dungeon \
         main.c entity.c combat.c inventory.c

   Week 5a changes vs. Week 3:
     ✓ Hero and Enemy are now structs — all stats in one place
     ✓ run_combat takes Hero* and Enemy* — 2 params not 10
     ✓ EnemyType enum replaces magic-number enemy categories
     ✓ create_hero / create_enemy constructor pattern
     ✓ XP tracking and loot are fields, not loose variables
     ✓ Dungeon is an array of Enemy structs

   INSTRUCTOR:
   Session 5a is primarily the refactor demonstration. Build
   entity.h/entity.c first (25 min), then show how combat.c
   and main.c simplify. The "before and after" of run_combat's
   parameter list is the headline moment.
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "entity.h"
#include "combat.h"
#include "inventory.h"
#include "utils.h"

int main(void) {

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      Legally Distinct from Zelda - the Sequel  ║\n");
    printf("║      Week 5a — The Great Refactor              ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    /* ── Hero creation ──────────────────────────────────────── */
    char hero_name[64];
    strcpy(hero_name, input("Enter your hero's name", 63));

    Hero hero = create_hero(hero_name, 100, 15, 5);

    /* Start with a couple of items */
    inventory_add(hero.inventory, &hero.inv_count, "Health Potion");
    inventory_add(hero.inventory, &hero.inv_count, "Torch");

    printf("\n");
    print_hero(&hero);
    printf("\n");

    /* ── Dungeon: array of Enemy structs ────────────────────── */
    /* INSTRUCTOR: "This is the payoff. We define an entire dungeon
       as an array of Enemy structs. No parallel arrays of names,
       HPs, attacks. One array, one type, clean iteration." */
    Enemy dungeon[] = {
        create_enemy("Rumble",  30,  7, 1, DECEPTICON_MINION, "Gold Coin"),
        create_enemy("Thundercracker",   70, 14, 6, DECEPTICON_SEEKER,    "Health Potion"),
        create_enemy("Soundwave",   120, 18, 9, DECEPTICON_LIEUTENANT,  "Iron Shield"),
    };
    int dungeon_size = sizeof(dungeon) / sizeof(dungeon[0]);

    /* ── Combat sequence ────────────────────────────────────── */
    for (int i = 0; i < dungeon_size; i++) {
        printf("\nA %s [%s] appears!\n\n",
               dungeon[i].name, enemy_type_name(dungeon[i].type));

        int won = run_combat(&hero, &dungeon[i]);

        if (!won) {
            printf("\nGame over.\n");
            return 0;
        }

        printf("\nCurrent status:\n");
        print_hero(&hero);

        if (i < dungeon_size - 1) {
            printf("\nPress Enter to continue...\n");
            fscanf(stdin, "%*[^\n]"); fscanf(stdin, "%*c");
        }
    }

    /* ── Victory ────────────────────────────────────────────── */
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║         DUNGEON CLEARED!             ║\n");
    printf("╚══════════════════════════════════════╝\n");
    print_hero(&hero);
    printf("\nFinal inventory:\n");
    inventory_print(hero.inventory, hero.inv_count);
    printf("\n(File I/O next week — save that hard-won progress!)\n");

    return 0;
}
