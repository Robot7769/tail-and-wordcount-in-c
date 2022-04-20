/**
 * @file tail.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Program tail tiskne posleních n řádků souboru
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"

int main(int argc, char const *argv[]) {
    
    char const *soubor = NULL;
    int n_line = 10;

    if (argc > 4) {
        error_exit("Příliš mnoho artumentů\n",0);
    }

    if (argc >= 2) { // není zadý přepínač pouze soubor
        for (int i = 1; i < argc; i++) {
            bool valid_arg = false;
            if (argv[i][0] == '-' && argv[i][1] == 'n') {
                if (argv[i][2] != '\0' || i >= argc) {
                    error_exit("přepínač -n je správně zadaný\n",0);
                }
                if (i < argc-1) {
                    i++;
                } else {
                    error_exit("u přepínač -n nebyl zadan parametr\n",0);
                }
                for (size_t y = 0; y < strlen(argv[i]); y++)
                {
                    if (!(argv[i][y] >= '0' && argv[i][y] <= '9')){
                        error_exit("argument obsahuje něco jiného než kladná čísla\n",0);
                    }
                }
                n_line = atoi(argv[i]);
                valid_arg = true;
                if (i >= argc-1) {
                    i = argc;
                }
            } else {
                if (argv[i][0] != '-') {
                    soubor = argv[i];
                    valid_arg = true;
                }
            }
            if (!valid_arg) {
                error_exit("Argument číslo %d (\"%s\") je nevalidní\n",i+1, argv[i]);
            }
        }
    }
    FILE* f;
    if (soubor == NULL){
        f = stdin;
    } else {
        f = fopen(soubor,"r");
        if (f == NULL) {
            error_exit("Soubor \"%s\" se nepodařilo otevřít\n",soubor);
        }
    }
    char *radek = NULL;
    size_t delka = 0;
    char **vypis = (char **) malloc((n_line) * sizeof(char *));
    if (vypis == NULL) {
        fclose(f);
        error_exit("Nrpodařila se alokace\n",0);
    }

    for (int i = 0; i < n_line; i++) {
        vypis[i] = NULL;
    }
    
    int pos = 0;
    
    while (EOF != getline(&radek, &delka, f)) {
        if (vypis[pos] != NULL) {
            free(vypis[pos]);
        } 
        vypis[pos] = radek;
        radek = NULL;
        pos = (pos +1) % n_line;
    }

    //!výpis
    for (int i = 0; i < n_line; i++) {
        if (vypis[((pos + i)%n_line)] != NULL) {
            printf("%s", vypis[((pos + i)%n_line)]);
        }
    }
    
    if (f != NULL) {
        fclose(f);
    }
    if (radek != NULL) {
        free(radek);
    }
    for (int i = 0; i < n_line; i++) {
        if (vypis[i] != NULL) {
            free(vypis[i]);
        }    
    }
    
    if (vypis != NULL) {
        free(vypis);
    }
    return 0;
}
