/**
 * @file htab_for_each.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Projde všechny záznamy a zavolá na ně funkci f
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    if (t == NULL) {
        error_exit("htab_t * t je NULL, modul htab_find",0);
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *tmp = t->arr_ptr[i];
        for (size_t j = 0; j < t->size; j++) {
            f(tmp->data);
            tmp = tmp->next;
        }
    }
    return;
}