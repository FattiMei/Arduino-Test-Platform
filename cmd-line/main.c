#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

#include "string-mei.h"
#include "serial.h"
#include "terminal-mei.h"
#include "functions.h"

#define VERSION "0.0"
#define NUMBER 4

/**define a command structure
    It has a label, for associate the commands to the functions
    It has a function pointer to a generic function that takes an array of pointers
**/

struct Function{
    char* label;
    void(*func)(int, char**);
};

//the commands are defined globally
struct Function list[] = {
    {"clear", &clear},
    {"version", &version},
    {"help", &help},
    {"set", &set_reg}
};

void Init(){
    printf("Welcome to Arduino-test-platform!\nVersion %s\n", VERSION);
    serialInit();
}

int main(){

	int exit_flag = 0, i;


    //initializations, prints the actual version
    Init();

	do{
		int args;
		char **argv;
		char *command_raw = NULL, *command = NULL;

        //get a string from input
		command_raw = stringScan();
		command = shrink(command_raw);

        //calculate number arguments and value
		args = wc(command);

        argv = getArgumentsValue(command, args);

        //parsing block, compare the first part of the command to a list of functions
		if(strcmp(argv[0], "exit") == 0) exit_flag = 1;
		else{
			for(i = 0; i < NUMBER; i++){
				if(strcmp(argv[0], list[i].label) == 0){
					list[i].func(args, argv);
					break;
				}
			}
			if(i == NUMBER) printf("Comando sconosciuto\n");
		}

        //free the memory allocated
		free(command_raw);
		free(command);
		free(argv);

	}while(exit_flag == 0);

    closeSerial();

	return 0;
}
