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
    
    char const *soubor = NULL; //? free????
    int n_line = 10;

    printf("%d\n", argc);//!test
    if (argc >= 2) { // není zadý přepínač pouze soubor
        printf("%s %s\n", argv[0], argv[1]);//!test
        for (int i = 1; i < argc; i++) {
            bool valid_arg = false;
            if (argv[i][0] == '-' && argv[i][1] == 'n') {
                printf("hledám %d \n",i);
                if (argv[i][2] != '\0' || i >= argc) {
                    error_exit("přepínač -n je správně zadaný\n",0);
                }
                printf("nalezen přepínač\n");//!test
                if (i < argc-1) {
                    i++;
                } else {
                    error_exit("u přepínač -n nebyl zadan parametr\n",0);
                }
                printf("%s \n",argv[i]);//!test
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
                for (size_t j = 0; j < strlen(argv[i]); j++) {
                    if (argv[i][j] == '.') {
                        printf("nalezen soubor\n");//!test
                        soubor = argv[i];
                        valid_arg = true;
                        break;
                    }
                }
            }
            if (!valid_arg) {
                error_exit("Argument číslo %d (\"%s\") je nevalidní\n",i+1, argv[i]);
            }
        }
    }
    FILE* f;
    printf("vypis:\n");//!tetst
    if (soubor == NULL){
        f = stdin;
    } else {
        f = fopen(soubor,"r");
        if (f == NULL) {
            error_exit("Soubor \"%s\"se nepodařilo otevřít",soubor);
        }
    }
    char *radek = NULL;
    size_t delka = 0;
    char **vypis = (char **) malloc((n_line+1) * sizeof(char *));
    if (vypis == NULL) {
        fclose(f);
        error_exit("Nrpodařilase alokace",0);
    }

    int pos = 0;
    while (EOF != getline(&radek, &delka, f)) {
        vypis[pos] = radek;
        //printf("%d- %s",pos+1, vypis[pos+1]);//!tetst
        //printf("L: %ld\n",delka);//!tetst
        printf("%s", radek);//!tetst
        printf("%d- %s",pos, vypis[pos]);//!tetst
        if (pos < n_line-1) {
            pos++;
        } else {
            pos = 0;
        }
    }
    printf("pos: %d\n",pos);
    printf("-%s", vypis[0]);
    printf("-%s", vypis[1]);
    printf("-%s", vypis[2]);
    for (int i = 0; i < n_line; i++) {
        printf("%d-%s",i, vypis[((pos + i)%10)]);
    }
    
    //n_radek = getline(&radek, &delka, f);
    //printf("%s", radek);//!tetst
    //printf("L: %ld\n",delka);//!tetst
    
    
    //printf("%s\n", soubor);//!tetst
    //printf("%d\n",n_line);//!tetst
    
    
    fclose(f);
    free(radek);
    free(vypis);
    //? free(soubor); // bacha může být NULL
    return 0;
}
