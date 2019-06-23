#include <stdio.h>
#include <malloc.h>

#include "string-mei.h"

#define VERSION "0.0"

void Init(){
    printf("Welcome to the Arduino test platform!\nVersion %s\n", VERSION);
}

char *keywords[] = {"clear", "exit", "version"};

char *shrink(char *s){
    char *shorter = NULL;

    int i;                          //contatore
    int size = 0, allocato = 0;     //variabili per gestire la stringa dinamica
    int first_char = 0, blank = 0;  //flag per la gestione

    for(i = 0; *(s + i) != '\0'; i++){
        if(first_char == 0){
            if(*(s + i) != ' ') first_char = 1;
        }
        else{
            if(*(s + i) == ' ') blank++;
            else blank = 0;
        }


        //se ha superato tutti i controlli scrivi
        if(first_char){
            if(*(s + i) == ' ' && blank != 1);
            else{
                if(size >= allocato){
                    allocato += 8;
                    shorter = realloc(shorter, sizeof(char) * allocato);
                }

                *(shorter + size) = *(s + i);
                size++;
            }
        }
    }
    if(*(shorter + size - 1) == ' ') size--;
    *(shorter + size) = '\0';

    shorter = realloc(shorter, sizeof(char) * size);

    free(s);
    return shorter;
}

int wc(char *s){
    int words;

    for(words = 1; *s != '\0'; s++){
        if(*s == ' ') words++;
    }

    return words;
}

int main(){
    //initializations, prints the actual version
    Init();

    char *command_raw = NULL;

    //get a raw string from the terminal
    command_raw = stringScan();

    //eliminate superfluous blanks, in head middle and tail
    command_raw = shrink(command_raw);

    //each blank divide a part of the command
    //find the number of parts of the command

    return 0;
}
