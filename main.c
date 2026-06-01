#include <stdio.h>
#include <stdlib.h>
#include "combat.h"

void print_hero_stats(void);
void print_monster_stats(void);
void print_stats(char * name, int bravery, double health, int attack, int defense);



int main(void) {

    int hero_bravery = 10;
    int hero_attack = 10;
    int hero_defense = 10;
    double hero_health = 10;
    char hero_name[50];

    int monster_bravery = 0;
    int monster_attack = 12;
    int monster_defense = 10;
    double monster_health = 10;
    char monster_name[50] = "Decepticon";


    printf("===================================\n");
    printf("|   Legally Distinct from Zelda   |\n");
    printf("|            the sequel           |\n");
    printf("|=================================|\n");
    
    printf("Enter your hero's name> ");
    fscanf(stdin, "%s", hero_name);

    do {
        printf("%s Attacks!\n", hero_name);
        monster_health -= calculate_damage(hero_bravery, hero_attack, monster_defense);
        if (monster_health < 0) monster_health = 0;
        printf("%s Counter-Attacks!\n", monster_name);
        hero_health -= calculate_damage(0, monster_attack, hero_defense);
        if (hero_health < 0) hero_health = 0;

        print_stats(hero_name, hero_bravery, hero_health, hero_attack, hero_defense);
        print_stats(monster_name, 0, monster_health, monster_attack, monster_defense);
        printf("Enter 'd' to continue");
        char enter;
        fscanf(stdin, "%c", &enter);

    } while (hero_health > 0 && monster_health > 0);
    
    if (hero_health == 0 && monster_health == 0) {
        printf("DRAW!\n");
    } else if (hero_health == 0 && monster_health > 0) {
        printf("%s WINS!\n", monster_name);
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



