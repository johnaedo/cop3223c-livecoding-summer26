#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"
#include "entity.h"

void print_hero_stats(void);
void print_monster_stats(void);
void print_stats(entity_t entity);



int main(void) {

    const int potion_strength = 3;

    entity_t hero = {
        .bravery = 10,
        .attack = 10,
        .defense = 10,
        .current_hp = 10,
        .max_hp = 10,
        .name = "Uncle Linus",
        .potions = 3,
        .magic_skill = 70,
        .type = HERO
    };
    
    entity_t enemy1 = {
        .bravery = 0,
        .attack = 10,
        .defense = 10,
        .current_hp = 10,
        .max_hp = 10,
        .name = "Starscream",
        .potions = 0,
        .magic_skill = 0,
        .type = ENEMY_SEEKER
    };
    
    entity_t enemy2 = {
        .bravery = 0,
        .attack = 10,
        .defense = 10,
        .current_hp = 10,
        .max_hp = 10,
        .name = "Frenzy",
        .potions = 0,
        .magic_skill = 0,
        .type = ENEMY_DECEPTICON
    };
    

    printf("===================================\n");
    printf("|   Legally Distinct from Zelda   |\n");
    printf("|            the sequel           |\n");
    printf("|=================================|\n");
    
    printf("Enter your hero's name> ");
    fscanf(stdin, "%s", hero.name);

    do {
            printf("%s Attacks!\n", hero.name);
            enemy1.current_hp -= calculate_damage(hero, enemy1);
            if (enemy1.current_hp < 0) enemy1.current_hp = 0;
            printf("%s Counter-Attacks!\n", enemy1.name);
            hero.current_hp -= calculate_damage(enemy1, hero);
            printf("current hero health: %f\n", hero.current_hp);
            if (hero.current_hp < 0) hero.current_hp = 0;
            if (hero.current_hp) {
                srand(time(NULL));
                int dice_roll = rand() % 100;
                if (dice_roll < hero.magic_skill) {
                    heal(hero, potion_strength);
                    hero.potions--;
                }
            }
        print_stats(hero);
        print_stats(enemy1);
        printf("Enter 'd' to continue");
        char enter;
        fscanf(stdin, "%c", &enter);

    } while (hero.current_hp > 0 && (enemy1.current_hp > 0));
    
    if (hero.current_hp == 0 && enemy1.current_hp == 0) {
        printf("DRAW!\n");
    } else if (enemy1.current_hp > 0) {
        printf("%s WINS!\n", enemy1.name);
    } else if (enemy1.current_hp > 0) {
        printf("%s WINS!\n", enemy1.current_hp);
    } else {
        printf("%s WINS!\n", hero.name);
    };


    
}

void print_stats(entity_t entity) {
    printf("====================\n");
    printf("| %-18s|\n", entity.name);
    printf("| HP: %lf           |\n", entity.current_hp);
    printf("| ATTACK: %d DEF: %d|\n", entity.attack, entity.defense);
    if (entity.bravery) printf("| BRAVERY: %d.      |\n", entity.bravery);
    printf("====================|\n");

}



