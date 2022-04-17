/**
 * @file htab_lookup_add.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 vyhledá záznam odpovídající řetězci key
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include <stdlib.h>

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    htab_pair_t *data = htab_find(t,key);
    if (data != NULL) {
        return data; 
    }
    size_t index = htab_hash_function(key);
    htab_item_t *tmp = t->arr_ptr[index];
    for (size_t j = 0; j < t->size; j++) {
        if (tmp->next != NULL) {
            tmp = tmp->next;
        }
    }
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if (item == NULL) {
        warning_msg("Neuspěsná alokace htab_item_t v htab_lookup_add",0);
        return NULL;
    }
    item->data->key = key;
    item->data->value = 1;
    item->next = NULL;
    tmp->next = item;
    if (++(t->size) / t->arr_size > AVG_LEN_MAX) {
        htab_resize(t,++(t->size));
    } else {
        (t->size)++;
    }
    return item;
}