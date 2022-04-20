/**
 * @file htab_clear.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 ruší všechny záznamy
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include "error.h"
#include <stdlib.h>

void htab_clear(htab_t * t) { //! nemá mazet celou arr_ptr ale jen smazat slova
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_clear",0);
        return;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        while (t->arr_ptr[i] != NULL) {
            if (t->arr_ptr[i]->data->key != NULL) {
                free((void *)t->arr_ptr[i]->data->key);
            }
            if (t->arr_ptr[i]->data != NULL) {
                free(t->arr_ptr[i]->data);
            }
            htab_item_t *tmp_prev = t->arr_ptr[i];
            t->arr_ptr[i]  = t->arr_ptr[i]->next;
            if (tmp_prev != NULL) {
                free(tmp_prev);
            }
        }
        if (t->arr_ptr[i] != NULL) {
            free(t->arr_ptr[i]);
        }
    }
    return;
} 
