/**
 * @file htab_init.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Inicializace htab
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab_struct.h"
#include <stdlib.h>
#include "error.h"

htab_t *htab_init(size_t n) {
    if (n < 1) {
        warning_msg("Moc malá tabulka v htab_init",0);
        return NULL;
    }
    htab_t *tab = (htab_t *) calloc(1, sizeof(htab_t));
    if (tab == NULL) {
        warning_msg("Neuspěsná alokace tabulky v htab_init",0);
        return NULL;
    }
    tab->arr_size = n;
    tab->arr_ptr = (htab_item_t **) calloc(n, sizeof(htab_item_t*));     //? co se stane když zavolám htab_init(0); ????!!!!
    if (tab->arr_ptr == NULL) {
        free(tab);
        warning_msg("Neuspěsná alokace arr_ptr v htab_init",0);
        return NULL;
    }   
    return tab;
}