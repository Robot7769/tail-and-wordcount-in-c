/**
 * @file htab_resize.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Tabulka
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include "error.h"

htab_pair_t * lookup_or_add(htab_t * t, htab_key_t key);

void htab_resize(htab_t *t, size_t newn) {
    //return;
    //printf("--byla zavolána resize\n");
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_resize",0);
        return;
    }
    if (t->arr_size == 0 || t->arr_ptr == NULL) {
        return;
    }
    htab_t *new = htab_init(newn);
    size_t j = 0;
    for (size_t i = 0; i < t->arr_size; i++) { //! potřeba opravit, pomocí klíče nemusím procházet celou strukturu
        htab_item_t *tmp = t->arr_ptr[i];
        //printf("each-1\n");
        if (t->arr_ptr[i] != NULL) {
            //printf(" --each-- ");
            for (; j < t->size; j++) {
                //printf("each00\n");
                if (tmp->data != NULL) {
                    //printf("each01\n");
                    htab_pair_t *new_data = htab_lookup_add(new,tmp->data->key);
                    if (new_data == NULL) {
                        htab_free(t);
                        htab_free(new);
                        error_exit("Nepodařilo se přesunot prvek při resize");
                    }
                    
                    htab_pair_t *old_data = htab_find(t, new_data->key);
                    if (old_data == NULL) {
                        htab_free(t);
                        htab_free(new);
                        error_exit("Nepodařilo se přesunot prvek při resize");
                    }
                    new_data->value = old_data->value;                      //okopíruje hodnotu klíče ze staré tabulky
                }
                if (tmp->next != NULL) {
                    tmp = tmp->next;
                } else {
                    break;
                }
            }
        }
    }
    htab_clear(t);
    t->size = new->size;
    t->arr_size = new->arr_size;
    if (t->arr_ptr != NULL) {
        free(t->arr_ptr);
    }
    t->arr_ptr = new->arr_ptr;
    free(new);
    //zavolta clear 
    //smazat **na arr_ptr
    return;
}