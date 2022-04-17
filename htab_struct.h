/**
 * @file htab_struct.h
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Hlavičkový soubor htab_struct
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab.h"

#ifndef __HTAB_STRUCT_H__
#define __HTAB_STRUCT_H__

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

struct htab_item {
    htab_pair_t data;
    struct htab_item *next;
};

#endif