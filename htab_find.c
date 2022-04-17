/**
 * @file htab_find.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Funkce hledání key v htab_t
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include "error.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    if (t == NULL) {
        error_exit("htab_t * t je NULL, modul htab_find",0);
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *tmp = t->arr_ptr[i];
        for (size_t j = 0; j < t->size; j++) {
            if (tmp->data->key == key) {
                return tmp->data;
            }
            if (tmp->next != NULL) {
                tmp = tmp->next;
            }
        }
    }
    return NULL;
}