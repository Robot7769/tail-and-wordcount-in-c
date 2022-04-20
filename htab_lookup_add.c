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
#include "error.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h> //!smazat

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    if (t == NULL) {
        warning_msg("htab_t * t je NULL, modul htab_lookup_add",0);
        return NULL;
    }
    //printf("htab_lookup_add funkce\n");
    htab_pair_t *data = htab_find(t,key);
    //printf("find done\n");
    if (data != NULL) {
        return data; 
    }
    //printf("start hash\n");
    size_t index = (htab_hash_function(key) % t->arr_size);
    //printf("hash done, index: %ld\n", index);
    if (t->arr_ptr[index] == NULL) {
        t->arr_ptr[index]= malloc(sizeof(htab_item_t));
        if (t->arr_ptr[index] == NULL) {
            warning_msg("Neuspěsná alokace htab_item_t v htab_lookup_add",0);
            return NULL;
        }
        t->arr_ptr[index]->data = malloc(sizeof(htab_pair_t));
        if (t->arr_ptr[index]->data == NULL) {
            warning_msg("Neuspěsná alokace htab_pair_t v htab_lookup_add",0);
            return NULL;
        }
        t->arr_ptr[index]->data->key = malloc(strlen(key) * sizeof(char) +1);
        if (t->arr_ptr[index]->data->key == NULL) {
            warning_msg("Neuspěsná alokace klice v htab_lookup_add",0);
            return NULL;
        }
        strcpy((char *) t->arr_ptr[index]->data->key, key);
        //printf(">>ulozene s key: %s\n",t->arr_ptr[index]->data->key);
        t->arr_ptr[index]->data->value = 0;
        t->arr_ptr[index]->next = NULL;
        t->size += 1;
        return t->arr_ptr[index]->data;
    }
    htab_item_t *tmp = t->arr_ptr[index];
    for (size_t j = 0; j < t->size; j++) {  //! potřeba opravit, pomocí klíče nemusím procházet celou strukturu
        if (tmp->next != NULL) {
            tmp = tmp->next;
        }
    }
    //printf("for done\n");
    tmp->next = malloc(sizeof(htab_item_t));
    if (tmp->next == NULL) {
        warning_msg("Neuspěsná alokace nového itemu v htab_lookup_add",0);
        return NULL;
    }
    tmp->next->data = malloc(sizeof(htab_pair_t));
    if (tmp->next->data == NULL) {
        warning_msg("Neuspěsná alokace htab_pair_t v htab_lookup_add",0);
        free(tmp->next);
        return NULL;
    }
    tmp->next->data->key = malloc(strlen(key) * sizeof(char) +1);
    if (tmp->next->data->key == NULL) {
        warning_msg("Neuspěsná alokace klice v htab_lookup_add",0);
        free(tmp->next);
        free(tmp->next->data);
        return NULL;
    }
/*
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if (item == NULL) {
        warning_msg("Neuspěsná alokace htab_item_t v htab_lookup_add",0);
        return NULL;
    }
    item->data->key = malloc(strlen(key) * sizeof(char) +1);
    if (item->data->key == NULL) {
        warning_msg("Neuspěsná alokace klice v htab_lookup_add",0);
        return NULL;
    }
    */
    strcpy((char *) tmp->next->data->key, key);
    //printf(">>ulozene s key: %s\n",tmp->next->data->key);
    tmp->next->data->value = 0;
    tmp->next->next = NULL;
    /*
    htab_item_t *new_item = malloc(sizeof(htab_item_t));
    if (new_item == NULL) {
        warning_msg("Neuspěsná alokace nového itemu v htab_lookup_add",0);
        return NULL;
    }
    printf("ptr: %p -old\n", (void *) tmp);
    tmp = new_item;
    printf("ptr: %p -new\n", (void *) tmp->data);
    tmp = item;
    printf("ptr: %p -item\n", (void *) tmp->data);

    */

    t->size += 1;
    if (t->size / t->arr_size > AVG_LEN_MAX) {
        printf("call resize\n");
        htab_resize(t,(t->size)*2);
    }
    return htab_find(t,key);    //tmp->next->data;
}