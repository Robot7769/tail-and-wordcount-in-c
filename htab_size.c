/**
 * @file htab_size.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Funkce vrací velikost tabulky
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"

size_t htab_size(const htab_t * t) {
    return t->size;
}