/**
 * @file io.c
 * @author Jan Škrabal (xskrab12)-FIT
 * @brief IJC-DU2 Modul který čte slovo ze souboru 
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include "error.h"

bool err_long_word = false;

int read_word(char *s, int max, FILE *f) {
    //printf("čtení slova start\n");
    //char word[max];
    for (int i = 0; i < max-1; i++) {
        //printf("for\n");
        int znak = fgetc(f);
        //printf("znak_cislo: %d\n",znak);
        if ((char)znak == '\0' || (char)znak == ' ' || (char)znak == '\n' || (char)znak == '\t') {
            //s[i+1] = '\0';
            //printf("vracím slovo-konec: %s\n", s);
            //s = word;
            return i+1;
        }
        if (znak == EOF) {
            //s = word;
            //s[i] = '\0';
            //printf("vracím slovo-EOF: %s\n", s);
            return EOF;
        }
        
        s[i] = (char)znak;
        
    }
    //s[max] = '\0';
    printf("vracím slovo-chyba: %s\n", s);
    if (!err_long_word) {
        err_long_word = true;
        warning_msg("slovo je moc dlouhé\n",0);
    }

    //s = word;
    //!error delší slovo
    return max; //? EOF


    //TODO
}
