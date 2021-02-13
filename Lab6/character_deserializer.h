#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define MINION_LIMIT (3)

typedef struct {
    char name[50];
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
    char name[50];
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

int get_character(const char* filename, character_v3_t* out_character);

char* get_stat(char* stat, char* stat_tokenized[], int version);

void remove_whitespace(char* character_stat);

#endif /* CHARACTER_DESERIALIZER_H */
