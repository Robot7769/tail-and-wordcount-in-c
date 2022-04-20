/**
 * @file htab_erase.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Tabulka
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include "error.h"
#include <stdlib.h>

bool htab_erase(htab_t * t, htab_key_t key) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_erase",0);
        return false;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return false;
    }

    size_t index = (htab_hash_function(key) % t->arr_size);
    htab_item_t *tmp = t->arr_ptr[index];
    while (tmp != NULL) {
        if (!strcmp(tmp->data->key, key)) {
            htab_item_t *tmp_prev = tmp;
            if (tmp->data->key != NULL) {
                free((void *)tmp->data->key);
            }
            if (tmp->data != NULL) {
                free(tmp->data);
            }
            if (tmp_prev != NULL) {
                free(tmp_prev);
            }
            return true;
        }

        tmp  = tmp->next;

    }

    return false;
}
