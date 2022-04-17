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
    htab_t *tab = calloc(1, sizeof(htab_t));
    if (tab == NULL) {
        error_exit("Neuspěsná alokace tabulky v htab_init",0);
    }
    tab->arr_size = n;
    tab->arr_ptr = calloc(n, sizeof(htab_item_t*));
    if (tab->arr_ptr == NULL) {
        free(tab);
        error_exit("Neuspěsná alokace arr_ptr v htab_init",0);
    }   
    return tab;
}