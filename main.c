#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"

void print_hero_stats(void);
void print_monster_stats(void);
void print_stats(char * name, int bravery, double health, int attack, int defense);



int main(void) {

    const int potion_strength = 3;

    int hero_bravery = 10;
    int hero_attack = 10;
    int hero_defense = 10;
    double hero_health = 10;
    char hero_name[50];
    int hero_potions = 3;
    int magic_skill = 70;

    int monster_bravery[] = {0,0};
    int monster_attack[] = {7, 12};
    int monster_defense[] = {5, 10};
    double monster_health[] = {7.0, 10.0};
    char monster_name[2][50] = {
        "Megatron",
        "Starscream"
    };


    printf("===================================\n");
    printf("|   Legally Distinct from Zelda   |\n");
    printf("|            the sequel           |\n");
    printf("|=================================|\n");
    
    printf("Enter your hero's name> ");
    fscanf(stdin, "%s", hero_name);

    do {
        for (int i=0; i<2; i++) { 
            printf("%s Attacks!\n", hero_name);
            monster_health[i] -= calculate_damage(hero_name, hero_bravery, hero_attack, monster_defense[i]);
            if (monster_health[i] < 0) monster_health[i] = 0;
            printf("%s Counter-Attacks!\n", monster_name[i]);
            hero_health -= calculate_damage(monster_name[i], 0, monster_attack[i], hero_defense);
            printf("current hero health: %f\n", hero_health);
            if (hero_health < 0) hero_health = 0;
            if (hero_health) {
                srand(time(NULL));
                int dice_roll = rand() % 100;
                if (dice_roll < magic_skill) {
                    heal(&hero_health, &hero_potions, potion_strength);
                }
            }
        print_stats(hero_name, hero_bravery, hero_health, hero_attack, hero_defense);
        print_stats(monster_name[i], 0, monster_health[i], monster_attack[i], monster_defense[i]);
        printf("Enter 'd' to continue");
        char enter;
        fscanf(stdin, "%c", &enter);
        }

    } while (hero_health > 0 && (monster_health[0] > 0 || monster_health[1] > 0));
    
    if (hero_health == 0 && monster_health[0] == 0 && monster_health[1] == 0) {
        printf("DRAW!\n");
    } else if (monster_health[0] > 0 && monster_health[1] > 0) {
        printf("%s and %s WIN!\n", monster_name[0], monster_name[1]);
    } else if (monster_health[0] > 0 || monster_health[1] > 0) {
        printf("%s WINS!\n", monster_health[1] ? monster_name[1] : monster_name[0]);
    } else {
        printf("%s WINS!\n", hero_name);
    };


    
}

void print_stats(char *name, int bravery, double health, int attack, int defense) {
    printf("====================\n");
    printf("| %-18s|\n", name);
    printf("| HP: %lf           |\n", health);
    printf("| ATTACK: %d DEF: %d|\n", attack, defense);
    if (bravery) printf("| BRAVERY: %d.      |\n", bravery);
    printf("====================|\n");

}



