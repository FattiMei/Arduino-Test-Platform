#include <stdio.h>

#define VERSION "0.0"

void Init(){
    printf("Welcome to the Arduino test platform!\nVersion %s\n", VERSION);
}

char *keywords[] = {"clear", "exit", "version"};

int main(){
    //initializations, prints the actual version
    Init();

    char *command_raw = NULL;

    //get a raw string from the terminal


    return 0;
}
