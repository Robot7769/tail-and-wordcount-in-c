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

#define HTAB_SIZE 10

void print_htab(htab_pair_t *data) {
    fprintf(stdout, "%s\t%d\n",data->key,data->value);
}

int main() {
    //fprintf(stdout,"START\n");
    htab_t *tab = htab_init(HTAB_SIZE);
    if (tab == NULL) {
        error_exit("Nastla chyba při vytváření tabulky\n");
    }
    //fprintf(stdout,"Htab init\n");
    FILE *file = stdin;
    char word[127];  
    //fprintf(stdout,"read_word\n");
    int size;

    while (EOF != (size = read_word(word,127,file))) {
        //printf("dostal jsem slovo: %s\n", word);
        //fprintf(stdout,"čtení\n");
        htab_pair_t *data = htab_lookup_add(tab,word);
        if (data == NULL) {
            htab_free(tab);
            error_exit("Nastla chyba Alokace\n");
        }
        //printf("ptr: %p -data\n", (void *) data);
        //printf("\n%s slovo\n", data->key);
        data->value += 1;
        //printf("%d val\n", data->value);
        
        //fprintf(stdout,"data val ++\n");
        for (int i = 0; i < size; i++){
            word[i] = '\0';
        }
        
        
    }
    //fprintf(stdout,"size: %ld, arr_size: %ld\n",htab_size(tab),htab_bucket_count(tab) );
    //fprintf(stdout,"write\n");
    htab_for_each(tab, &print_htab);
    //fprintf(stdout,"KONEC\n");
    htab_free(tab);
    return 0;
}
