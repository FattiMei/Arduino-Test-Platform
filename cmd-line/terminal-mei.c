#include <stdio.h>
#include <stdlib.h>
#include "string-mei.h"

int wc(char *s){
	int words = 1;

	for(;*s != '\0'; s++){
		if(*s == ' ') words++;
	}

	return words;
}

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
    return shorter;
}

char* HexToAscii(unsigned char byte){
    char *s;
    s = (char*) malloc(sizeof(char) * 3);

    const char character_set[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    s[2] = '\0';
    for(int i = 1; i >= 0; i--){
        s[i] = character_set[byte & 0xF];
        byte = byte >> 4;
    }

    return s;
}

char** getArgumentsValue(char *command, int args){
    char** argv;
    argv = (char**) malloc(sizeof(char**) * args);

    for(int j = 0, flag = 1, count = 0; command[j] != '\0'; j++){
        if(flag == 1){
            flag = 0;
            argv[count++] = &(command[j]);
        }
        else if(command[j] == ' '){
            flag = 1;
            command[j] = '\0';
        }
    }

    return argv;
}
