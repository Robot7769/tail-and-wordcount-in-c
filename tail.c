/**
 * @file tail.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Program tail tiskne posleních n řádků souboru
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

int main(int argc, char const *argv[]) {
    
    char const *soubor = NULL;
    int n_line = 10;

    printf("%d\n", argc);//!test
    if (argc >= 2) { // není zadý přepínač pouze soubor
        printf("%s %s\n", argv[0], argv[1]);//!test
        for (int i = 1; i < argc; i++) {
            
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
                if (i >= argc-1) {
                    i = argc;
                }
                
            } else {
                for (size_t j = 0; j < strlen(argv[i]); j++) {
                    if (argv[i][j] == '.') {
                        printf("nalezen soubor\n");//!test
                        soubor = argv[i];
                        break;
                    }
                }
            }
        }
    }
    printf("vypis:");
    if (soubor == NULL){
        soubor = "stdin";
    }
    
    printf("%s\n", soubor);
    printf("%d\n",n_line);
    
    return 0;
}
