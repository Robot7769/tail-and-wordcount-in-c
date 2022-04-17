/**
 * @file htab.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Tabulka
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab.h"
#include "htab_struct.c"

size_t htab_size(const htab_t * t) {
    return t->size;
}