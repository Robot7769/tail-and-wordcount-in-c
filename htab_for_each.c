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
#include "error.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_for_each",0);
        return;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return;
    }
    size_t j = 0;
    for (size_t i = 0; i < t->arr_size; i++) { //! potřeba opravit, pomocí klíče nemusím procházet celou strukturu
        htab_item_t *tmp = t->arr_ptr[i];
        if (t->arr_ptr[i] != NULL) {
            for (; j < t->size; j++) {
                if (tmp->data != NULL) {
                    f(tmp->data);
                }
                if (tmp->next != NULL) {
                    tmp = tmp->next;
                } else {
                    break;
                }
            }
        }
    }
    return;
}
