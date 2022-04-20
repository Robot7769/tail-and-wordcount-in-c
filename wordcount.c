/**
 * @file wordcount.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Program počítá počet výskytů slov v souboru
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "htab.h"
#include "io.c"
#include <stdlib.h>
#include <stdio.h>

#define HTAB_SIZE 16384
//16384 je 2^14 je lepší obětovat kus paměti, než výpočetního výkonu.
//2^n je zdůvodu resize na 2-násobně menší/vetší, funkce htab_resize je ale i ošetřen na resize na liché číslo.
//Pro malé soubory je obtimální klidně in číslo 70.
//testovánáno tak, aby byl kód optimálně rychlý a nealokoval (realocoval) mockrát při standartně velkých souborech  

void print_htab(htab_pair_t *data) {
    fprintf(stdout, "%s\t%d\n",data->key,data->value);
}

int main() {
    htab_t *tab = htab_init(HTAB_SIZE);
    if (tab == NULL) {
        error_exit("Nastla chyba při vytváření tabulky\n");
    }
    FILE *file = stdin;
    char word[127];  
    int size;

    while (EOF != (size = read_word(word,127,file))) {
        htab_pair_t *data = htab_lookup_add(tab,word);
        if (data == NULL) {
            htab_free(tab);
            error_exit("Nastla chyba Alokace\n");
        }
        data->value += 1;

        for (int i = 0; i < size; i++){
            word[i] = '\0';
        }
    }
    htab_for_each(tab, &print_htab);
    htab_free(tab);
    return 0;
}
