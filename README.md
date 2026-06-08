# cop3223c-livecoding-summer2026
RPG Game we build throughout the Summer 2026 semester

# Week 4 - Hero, Potions, Two Monsters

## Game Loop:
    - Print welcome banner
    - Prompt for Hero name
    - Combat Do:
        Hero attacks Monster 0 => attack(hero, monster 0)
        Monster 0 attacks Hero => attack(monster 0, hero)
        Hero heals
        Monster 1 attacks Hero => attack(monster 1, hero)
        Hero heals
    While (Hero still lives or at least one monster is still alive)
    - Print results
    - Prompt to play again

## Attack(attacker, defender)
    - Modified Attack = Attack * (1 + Bravery/100)
    - Damage = Attack - Defense
    - Defender Health = Defender Health - Damage

## Heal (Hero Health, Magic Skill, Num Potions, Potion Strength)
    - If (! Num Potions):
        Print "Can't heal, no more potions"
        Return
    - If (! rand(100) \< Magic Skill):
        Print "Heal failed"
        Return
    - Hero Health += Potion Strength


        
