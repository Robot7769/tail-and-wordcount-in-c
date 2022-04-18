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

bool htab_erase(htab_t * t, htab_key_t key) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_erase",0);
        return false;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return false;
    }
    size_t j = 1;
    for (size_t i = 0; i < t->arr_size; i++) { //! potřeba opravit, pomocí klíče nemusím procházet celou strukturu
        htab_item_t *tmp = t->arr_ptr[i];
        if (tmp->data->key == key) {
            t->arr_ptr[i] = tmp->next;
            //free(tmp->data->key);
            free(tmp->data);
            free(tmp);
            if (--(t->size) / t->arr_size < AVG_LEN_MIN) {
                htab_resize(t,(size_t) (t->size/2) + (t->size%2));
            } else {
                (t->size)--;
            }
            return true;
        }
        htab_item_t *tmp_prev = tmp;
        if (tmp->next != NULL) {
            tmp = tmp->next;
            for (; j < t->size; j++) {
                if (tmp->data->key == key) {
                    tmp_prev = tmp->next;
                    //free(tmp->data->key);
                    free(tmp->data);
                    free(tmp);
                    if (--(t->size) / t->arr_size < AVG_LEN_MIN) {
                        htab_resize(t,(size_t) (t->size/2) + (t->size%2));
                    } else {
                        (t->size)--;
                    }
                    return true;
                }
                if (tmp->next != NULL) {
                    tmp = tmp->next;
                } else {
                    break;
                }
            }
        }
    }
    return false;
}