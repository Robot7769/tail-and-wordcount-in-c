/**
 * @file htab_bucket_count.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Funkce vrací velikost pole
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include "error.h"

size_t htab_bucket_count(const htab_t * t) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modulu htab_bucket_count",0);
        return 0;
    }
    return t->arr_size;
}