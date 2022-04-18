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

void htab_clear(htab_t * t) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_clear",0);
        return;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return;
    }

    size_t j = 0;
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *tmp = t->arr_ptr[i];
        htab_item_t *tmp_prev = tmp;
        if (tmp->next != NULL) {
            tmp = tmp->next;
            for (; j < t->size; j++) {
                //free(tmp_prev->data->key);
                free(tmp_prev->data);
                free(tmp_prev);
                tmp_prev = tmp;
                if (tmp->next != NULL) {
                    tmp = tmp->next;
                } else {
                    break;
                }
            }
        } 
        //free(tmp->data->key);
        free(tmp->data);
        free(tmp);
    }
    free(t->arr_ptr);
    t->size = 0;
    t->arr_size = 0;
    return;
}