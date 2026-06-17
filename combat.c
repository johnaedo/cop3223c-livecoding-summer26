/* ============================================================
   combat.c — Week 5a: struct-based combat
   Legally Distinct from Zelda - the Sequel

   The combat logic is identical to Week 3. What changed is
   the parameter types. Walk through apply_damage_hero() and
   ask students: "In Week 3, this took int *hp. Now it takes
   Hero *h. What's the difference in practice?"

   Answer: now the function has access to max_hp (for clamping),
   name (for print messages), and any other field — all through
   one pointer instead of passing each value separately.

   CHECKPOINT: After building run_combat, compare it side-by-side
   with the Week 3 version. Same loop, same choices, massively
   cleaner signature and field access.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"
#include "inventory.h"
#include "utils.h"

void apply_damage_hero(Hero *h, int damage) {
    h->hp -= damage;
    if (h->hp < 0) h->hp = 0;
}

void apply_damage_enemy(Enemy *e, int damage) {
    e->hp -= damage;
    if (e->hp < 0) e->hp = 0;
}

void heal_hero(Hero *h, int amount) {
    h->hp += amount;
    if (h->hp > h->max_hp) h->hp = h->max_hp;
}

static int calculate_damage(int attack, int defense) {
    int d = attack - defense;
    return d < 1 ? 1 : d;
}

static void print_separator(void) {
    printf("─────────────────────────────────────\n");
}

int run_combat(Hero *hero, Enemy *enemy) {
    int round = 1;

    while (hero->hp > 0 && enemy->hp > 0) {
        printf("\n");
        print_separator();
        printf("  Round %d\n", round);
        print_separator();
        print_hero(hero);
        printf("              VS\n");
        print_enemy(enemy);
        printf("\n");

        /* ── Player choice ─────────────────────────────── */
        int choice;
        char choice_input;
        do {
            printf("What will %s do?\n", hero->name);
            printf("  1) Attack\n");
            printf("  2) Defend (+3 DEF this round)\n");
            if (inventory_has(hero->inventory, hero->inv_count, "Health Potion")) {
                printf("  3) Use Health Potion (+25 HP)\n");
            }
            printf("  4) Flee\n");
            printf("Choice: ");
            strcpy(&choice_input, input("Choice", 1));
            printf("input: %s\n", &choice_input);
            choice = atoi(&choice_input);
            if (choice < 1 || choice > 4) printf("Invalid. Try again.\n");
        } while (choice < 1 || choice > 4);

        int effective_def = hero->defense;

        switch (choice) {
            case 1: {
                int dmg = calculate_damage(hero->attack, enemy->defense);
                apply_damage_enemy(enemy, dmg);
                printf("\n%s attacks %s for %d damage!\n",
                       hero->name, enemy->name, dmg);
                printf("%s HP: %d / %d\n",
                       enemy->name, enemy->hp, enemy->max_hp);
                break;
            }
            case 2:
                effective_def += 3;
                printf("\n%s braces for impact! DEF +3.\n", hero->name);
                break;
            case 3:
                if (inventory_has(hero->inventory, hero->inv_count, "Health Potion")) {
                    inventory_remove(hero->inventory, &hero->inv_count, "Health Potion");
                    int before = hero->hp;
                    heal_hero(hero, 25);
                    printf("\n%s uses a Health Potion! HP: %d → %d\n",
                           hero->name, before, hero->hp);
                } else {
                    printf("\nNo potions left!\n");
                }
                break;
            case 4:
                printf("\n%s flees!\n", hero->name);
                return 0;
        }

        /* ── Enemy counterattack ───────────────────────── */
        if (enemy->hp > 0) {
            int dmg = calculate_damage(enemy->attack, effective_def);
            apply_damage_hero(hero, dmg);
            printf("%s strikes back for %d damage!\n", enemy->name, dmg);
            printf("%s HP: %d / %d\n", hero->name, hero->hp, hero->max_hp);
        }

        round++;
    }

    printf("\n");
    print_separator();

    if (hero->hp > 0) {
        printf("  *** VICTORY! ***\n");
        printf("  %s defeated the %s!\n", hero->name, enemy->name);

        /* Award loot if the enemy drops something */
        if (strlen(enemy->loot) > 0) {
            printf("  %s drops: %s\n", enemy->name, enemy->loot);
            inventory_add(hero->inventory, &hero->inv_count, enemy->loot);
        }

        /* Award experience */
        hero->experience += enemy->max_hp;
        printf("  XP gained: %d  (Total: %d)\n",
               enemy->max_hp, hero->experience);

        print_separator();
        return 1;
    }

    printf("  *** DEFEAT... ***\n");
    printf("  %s was slain.\n", hero->name);
    print_separator();
    return 0;
}
