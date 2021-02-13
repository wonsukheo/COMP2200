#include <stdio.h>
#include <string.h>

#include "character_deserializer.h"

#define FILE_LENGTH (1024)

char* get_stat(char* stat_name, char* character_stat[], int version)
{ 
    size_t i = 0;

    while (strcmp(stat_name, character_stat[i++]) != 0) {
    
    }
    
    if (version == 1) {
        return character_stat[i]; 
    } else if (version == 2) {
        return character_stat[i + 9];
    } else {
        return NULL;
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
            j = i + 1;
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
    int version;
    size_t i;
    char character_stat[FILE_LENGTH];
    char* character_stat_ptr;
    char* stat_tokenized[200];
    char* stat_info;

    character_stat_ptr = character_stat; 
    stream = fopen(filename, "r");
    while (fgets(character_stat_ptr, FILE_LENGTH, stream) != NULL) {
        character_stat_ptr += strlen(character_stat_ptr);
    }
    fclose(stream);
    /*check version*/
    if (strstr(character_stat, "id") != NULL) {
        version = 1;
    } else if (strstr(character_stat, "magic_resistance") != NULL) {
        version = 2;
    } else {
        version = 3;
    }
     
    /* insert character stat */
    switch (version) {
    case 1: {
        char delims[] = ",:";
        i = 0;
        
        stat_tokenized[i] = strtok(character_stat, delims);
        while (stat_tokenized[i] != NULL) {
            stat_tokenized[++i] = strtok(NULL, delims);
        }
        
        sscanf("player_", "%s", out_character->name);
        stat_info = get_stat("id", stat_tokenized, version);
        strncpy(&(out_character->name[7]), stat_info, 42);
        out_character->name[50] = '\0';
        
        stat_info = get_stat("lvl", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->level));
        
        stat_info = get_stat("hp", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->health));

        stat_info = get_stat("mp", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->mana));

        stat_info = get_stat("str", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->strength));

        stat_info = get_stat("dex", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->dexterity));

        stat_info = get_stat("intel", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->intelligence));

        stat_info = get_stat("def", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->armour));

        out_character->evasion = out_character->dexterity / 2;
        out_character->elemental_resistance.fire = out_character->armour / 12;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        out_character->leadership = out_character->level / 10;
        out_character->minion_count = 0;
    } break;
    case 2: {
        char delims[] = ",\n";
        i = 0;
        stat_tokenized[i] = strtok(character_stat, delims);
        while (stat_tokenized[i] != NULL) {
            stat_tokenized[++i] = strtok(NULL, delims);
        }
        
        stat_info = get_stat("name", stat_tokenized, version);
        strncpy(out_character->name, stat_info, 50);
        out_character->name[50] = '\0';

        stat_info = get_stat("level", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->level));
        
        stat_info = get_stat("health", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->health));

        stat_info = get_stat("mana", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->mana));

        stat_info = get_stat("strength", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->strength));

        stat_info = get_stat("dexterity", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->dexterity));

        stat_info = get_stat("intelligence", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->intelligence));

        stat_info = get_stat("armour", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->armour));

        stat_info = get_stat("evasion", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->evasion));
        
        stat_info = get_stat("magic_resistance", stat_tokenized, version);
        sscanf(stat_info, "%d", &(out_character->elemental_resistance.fire));
       
        out_character->elemental_resistance.fire /= 3;
        out_character->elemental_resistance.cold = out_character->elemental_resistance.fire;
        out_character->elemental_resistance.lightning = out_character->elemental_resistance.fire;
        out_character->leadership = out_character->level / 10;
        out_character->minion_count = 0;
    } break;
    case 3: {
        size_t j = 32;
        char delims[] = "|\n";
        i = 0;
        remove_whitespace(character_stat);       
        
        stat_tokenized[i] = strtok(character_stat, delims);
        while (stat_tokenized[i] != NULL) {
            stat_tokenized[++i] = strtok(NULL, delims);
        }
        strncpy(out_character->name, stat_tokenized[14], 50);
        out_character->name[50] = '\0';
        sscanf(stat_tokenized[15], "%d", &(out_character->level));
        sscanf(stat_tokenized[16], "%d", &(out_character->health));
        sscanf(stat_tokenized[17], "%d", &(out_character->mana));
        sscanf(stat_tokenized[18], "%d", &(out_character->strength));
        sscanf(stat_tokenized[19], "%d", &(out_character->dexterity));
        sscanf(stat_tokenized[20], "%d", &(out_character->intelligence));
        sscanf(stat_tokenized[21], "%d", &(out_character->armour));
        sscanf(stat_tokenized[22], "%d", &(out_character->evasion));
        sscanf(stat_tokenized[23], "%d", &(out_character->elemental_resistance.fire));
        sscanf(stat_tokenized[24], "%d", &(out_character->elemental_resistance.cold));
        sscanf(stat_tokenized[25], "%d", &(out_character->elemental_resistance.lightning));
        sscanf(stat_tokenized[26], "%d", &(out_character->leadership));
        sscanf(stat_tokenized[27], "%d", &(out_character->minion_count));

        if (*stat_tokenized[27] != 0) {
            for (i = 0; i < out_character->minion_count; ++i) {
                
                strncpy(out_character->minions[i].name, stat_tokenized[j++], 50);
                out_character->minions[i].name[50] = '\0';
                
                sscanf(stat_tokenized[j++], "%d", &(out_character->minions[i].health));
                sscanf(stat_tokenized[j++], "%d", &(out_character->minions[i].strength));
                sscanf(stat_tokenized[j++], "%d", &(out_character->minions[i].defence));
            }
        }
    } break;
    
    default:
        break;
    }
    return version;
}
