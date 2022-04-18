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

void print_htab(htab_pair_t *data) {
    printf("%s\t%d\n",data->key,data->value);
}

int main() {
    printf("START\n");
    htab_t *tab = htab_init(150);
    printf("Htab init\n");
    FILE *file = stdin;
    char word[127];  
    printf("read_word\n");
    while (read_word(word,127,file) != EOF) {
        htab_pair_t *data = htab_lookup_add(tab,word);
        (data->value)++;
        printf("data val ++\n");
    }
    printf("write\n");
    htab_for_each(tab, &print_htab);
    printf("KONEC\n");
    return 0;
}
