#include "my_string.h"

static char* ptr = NULL;

size_t strlen(const char* str)
{
    const char* str = str;
    const char* p = str;
    
    while (*p != '\0') {
        p++;
    }
    
    return (size_t)(p - str);
}

char* strsubstr(const char* str, const char* substr)
{
    /* return * of string where substring found */

    size_t i;
    size_t j;
    size_t len_str = strlen(str);
    size_t len_sub = strlen(substr);

    if (len_sub > len_str) {
        return NULL;
    }
    
    for (i = 0; i <= len_str - len_sub; i++) {
        for (j = 0; j < len_sub; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
            if (j == len_sub - 1) {
                return (char*)&str[i];
            }
        }
    }    
    
    return NULL;
}

void reverse(char* str)
{
    /* flip char[], does not make array in function */
   
    size_t i;

    size_t len = strlen(str);
    char* temp = str + len - 1;
    
    for (i = 0; i < len / 2; ++i) {
        *(str + i) ^= *(temp - i);
        *(temp - i) ^= *(str + i);
        *(str + i) ^= *(temp - i);
    }
}

int index_of(const char* str, const char* word)
{
    /* return first index of word, -1 if not found */
    
    char* p = strsubstr(str, word);
    
    if (p == NULL) { 
        return -1;
    }
 
    return (int)(p - str);
}

void reverse_by_words(char* str)
{
    size_t i;
    size_t count = 0;
    char* p = str;
 
    for (i = 0; i <= strlen(str); i++) {
        count ++;
        
        if (*(str + i) == ' ') {
            *(str + i) = '\0';
            reverse(p);
            p += count;
            count = 0;
            *(str + i) = ' ';
        }
        
        if (*(str + i) == '\0') {
            reverse(p);
            p += count;
            count = 0;
        }
    }    
} 

char* tokenize(char* str_or_null, const char* delims) 
{
    size_t i;
    size_t j;

    size_t len_del = strlen(delims);
    size_t len_str;
    
    if (ptr == NULL && str_or_null == NULL) {
        return NULL;
    }
    if (str_or_null == NULL) {
        str_or_null = ptr;
    }
    
    ptr = str_or_null;
    len_str = strlen(str_or_null);
    
    for (i = 1; i <= len_str; i++) {
        for (j = 0; j < len_del; j++) {
            if (str_or_null[i] == delims[j]) {
                str_or_null[i] = '\0';
                ptr = ptr + i + 1;
                return str_or_null;
            }
          
            if (str_or_null[i] == '\0') {
                ptr = NULL;
                return str_or_null;
            }
        }    
    }
    return NULL;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    size_t i;
    size_t j;
    size_t len_del = strlen(delims);
    size_t len_str;
    
    if (ptr == NULL && str_or_null == NULL) {
        return NULL;
    }
    if (str_or_null == NULL) {
        str_or_null = ptr;
    }
    
    ptr = str_or_null;
    len_str = strlen(str_or_null);
    
    for (i = 1; i <= len_str; i++) {
        for (j = 0; j < len_del; j++) {
            if (str_or_null[i] == delims[j]) {
                str_or_null[i] = '\0';
                ptr = ptr + i + 1;
                reverse_by_words(str_or_null);
		return str_or_null;
            }
          
            if (str_or_null[i] == '\0') {
                ptr = NULL;
                reverse_by_words(str_or_null);
		return str_or_null;
            }
        }    
    }
    return NULL;
}
