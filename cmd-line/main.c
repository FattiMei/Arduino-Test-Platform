#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "string-mei.h"

#define VERSION "0.0"

#define NUMBER 2

/**define a command structure
    It has a label, for associate the commands to the functions
    It has a function pointer to a generic function that takes an array of pointers
**/

struct Command{
    char* label;
    void(*func)(char**);
};

void clear(char** args){
    system("cls");
}
void version(char** args){
    printf("System version %s\n", VERSION);
}

void help(char** args){
    //stampa
}

//the commands are defined globally
struct Command list[] = {
    {"clear", &clear},
    {"version", &version},
    {"help", &help};
};

void Init(){
    printf("Welcome to the Arduino test platform!\nVersion %s\n", VERSION);
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

    char **words;
    do{
        char *command_raw = NULL, *command = NULL;

        //get a raw string from the terminal
        command_raw = stringScan();
        command = shrink(command_raw);

        //we have to use an array of pointers to access directly each member of the command

        int parts = wc(command);

        words = (char **) malloc(sizeof(char**) * parts);

        for(int i = 0, flag = 1, count = 0; command[i] != '\0'; i++){
            if(flag == 1){
                flag = 0;
                words[count++] = &(command[i]);
            }
            else{
                if(command[i] == ' '){
                    flag = 1;
                    command[i] = '\0';
                }
            }
        }

        //compare the first word with a list of commands defined above
        for(int i = 0; i < NUMBER; i++){
            if(strcmp(words[0], list[i].label) == 0) list[i].func(NULL);
        }
    }while(strcmp(words[0], "exit") != 0);


    return 0;
}
