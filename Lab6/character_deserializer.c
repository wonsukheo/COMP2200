#include <stdio.h>
#include <string.h>

#include "character_deserializer.h"

#define FILE_LENGTH (1024)

char* get_stat(char* stat_name, char* character_stat[], int version)
{ 
    size_t i = 0;

    switch (version) {
    case 1:
        while (strcmp(stat_name, character_stat[i++]) != 0) {
        }
        return character_stat[i];
    break;

    case 2:
        while (strcmp(stat_name, character_stat[i++]) != 0) {
        }
        return character_stat[i + 9];
    break;

    default:
        return NULL;
    break;
    }
}

void remove_whitespace(char* string)
{
    size_t length = strlen(string);
    char* whitespace_start = string;
    char* whitespace_end = string;
    size_t i;
    size_t j;
    for (i = 0; i < length; ++i) {
        if (string[i] == ' ') {
            whitespace_start = &string[i];
            j = i;
            while (string[j] == ' ') {
                j++;
                if (j == length - 1) {
                    break;
                }
            }
            whitespace_end = &string[j];
            string[i] = string[j];
            string[j] = ' ';
        }
    }
}

int get_character(const char* filename, character_v3_t* out_character)
{  
    FILE* stream;
    size_t filelength;
    int version;
    size_t i;
    char character_info[FILE_LENGTH];
    char* character_info_ptr;
    char* character_stat[100];
    char* stat_info;

    character_info_ptr = character_info; 
    stream = fopen(filename, "r");
    while (fgets(character_info_ptr, FILE_LENGTH, stream) != NULL) {
        character_info_ptr += strlen(character_info_ptr);
    }
    fclose(stream);
    
    /* file version check */ 
    filelength = strlen(filename);
    if (filename[filelength - 5] == '1') {
        version = 1;
    } else if (filename[filelength - 5] == '2') {
        version = 2;
    } else {
        version = 3;
    }
    
    i = 0;


    switch (version) {
    case 1: {
        
        char delims[] = ",:";

        character_stat[i] = strtok(character_info, delims);
        while (character_stat[i] != NULL) {
            character_stat[++i] = strtok(NULL, delims);
        }

        stat_info = get_stat("id", character_stat, version);
        sscanf("player_", "%s", &(out_character->name));
        strcat(out_character->name, stat_info);
        
        stat_info = get_stat("lvl", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->level));
        
        stat_info = get_stat("hp", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->health));

        stat_info = get_stat("mp", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->mana));

        stat_info = get_stat("str", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->strength));

        stat_info = get_stat("dex", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->dexterity));

        stat_info = get_stat("intel", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->intelligence));

        stat_info = get_stat("def", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->armour));

        out_character->evasion = out_character->dexterity / 2;
        out_character->elemental_resistance.fire = out_character->armour / 12;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        out_character->leadership = out_character->level / 10;
        out_character->minion_count = 0;
        }
        break;
    case 2: {
        
        char delims[] = ",\n";

        character_stat[i] = strtok(character_info, delims);
        while (character_stat[i] != NULL) {
            character_stat[++i] = strtok(NULL, delims);
        }

        stat_info = get_stat("name", character_stat, version);
        sscanf(stat_info, "%s", &(out_character->name));

        stat_info = get_stat("level", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->level));
        
        stat_info = get_stat("health", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->health));

        stat_info = get_stat("mana", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->mana));

        stat_info = get_stat("strength", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->strength));

        stat_info = get_stat("dexterity", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->dexterity));

        stat_info = get_stat("intelligence", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->intelligence));

        stat_info = get_stat("armour", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->armour));

        stat_info = get_stat("evasion", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->evasion));
        
        stat_info = get_stat("magic_resistance", character_stat, version);
        sscanf(stat_info, "%d", &(out_character->elemental_resistance.fire));
       
        out_character->elemental_resistance.fire /= 3;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        out_character->leadership = out_character->level / 10;
        out_character->minion_count = 0;
        }
        break;
    case 3: {
        
        char delims[] = "|\n";

        remove_whitespace(character_info);       
        character_stat[i] = strtok(character_info, delims);
        
        while (character_stat[i] != NULL) {
            character_stat[++i] = strtok(NULL, delims);
        }

        sscanf(character_stat[14], "%s", &(out_character->name));
        sscanf(character_stat[15], "%d", &(out_character->level));
        sscanf(character_stat[16], "%d", &(out_character->health));
        sscanf(character_stat[17], "%d", &(out_character->mana));
        sscanf(character_stat[18], "%d", &(out_character->strength));
        sscanf(character_stat[19], "%d", &(out_character->dexterity));
        sscanf(character_stat[20], "%d", &(out_character->intelligence));
        sscanf(character_stat[21], "%d", &(out_character->armour));
        sscanf(character_stat[22], "%d", &(out_character->evasion));
        sscanf(character_stat[23], "%d", &(out_character->elemental_resistance.fire));
        sscanf(character_stat[24], "%d", &(out_character->elemental_resistance.cold));
        sscanf(character_stat[25], "%d", &(out_character->elemental_resistance.lightning));
        sscanf(character_stat[26], "%d", &(out_character->leadership));
        sscanf(character_stat[27], "%d", &(out_character->minion_count));

        if (*character_stat[27] != 0) {
            size_t j = 32;
            for (i = 0; i < out_character->minion_count; ++i) {
                sscanf(character_stat[j++], "%s", &(out_character->minions[i].name));
                sscanf(character_stat[j++], "%d", &(out_character->minions[i].health));
                sscanf(character_stat[j++], "%d", &(out_character->minions[i].strength));
                sscanf(character_stat[j++], "%d", &(out_character->minions[i].defence));
            }
        }
        }
        break;
    
    default:
        break;
    }
    return version;
}
