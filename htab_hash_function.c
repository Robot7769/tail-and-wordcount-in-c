/**
 * @file htab_hash_function.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Tabulka
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab.h"

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}   