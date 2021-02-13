#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define NAME_LENGTH (50)
#define MINION_LIMIT (3)

typedef struct {
    char name[NAME_LENGTH];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    char name[NAME_LENGTH];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    size_t minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[MINION_LIMIT];
} character_v3_t;

int get_character(const char*, character_v3_t*);

char* get_stat(char*, char*[], int);

void remove_whitespace(char*);

#endif /* CHARACTER_DESERIALIZER_H */
