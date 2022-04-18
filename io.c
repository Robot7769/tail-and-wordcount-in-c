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

int read_word(char *s, int max, FILE *f) {
    char word[max];
    for (int i = 0; i < max-1; i++) {
        int znak = fgetc(f);
        if (znak == EOF) {
            s = word;
            return EOF;
        }
        if ((char)znak != ' ' || (char)znak != '\n' || (char)znak != '\t') {
            word[i] = (char)znak;
        }
        if ((char)znak == '\0') {
            s = word;
            return i+1;
        }
    }
    s = word;
    //!error delší slovo
    return -1;


    //TODO
}
