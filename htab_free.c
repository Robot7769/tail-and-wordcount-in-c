/**
 * @file htab_free.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 destruktor tabulky
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include <stdlib.h>

void htab_free(htab_t * t) {
    if (t != NULL) {
        htab_clear(t);
        free(t);
    }
}