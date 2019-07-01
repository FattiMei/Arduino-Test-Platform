#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

#include "string-mei.h"
#include "serial.h"
#include "terminal-mei.h"

#define VERSION "0.0"
#define REGISTERS 29
#define NUMBER 4

/**define a command structure
    It has a label, for associate the commands to the functions
    It has a function pointer to a generic function that takes an array of pointers
**/

struct Function{
    char* label;
    void(*func)(int, char**);
};

struct Register{
	char* label;
	unsigned char address, normal, mask;
};

struct Register R[] = {
	{"pinb",   0x03, 0, 0},
	{"ddrb",   0x04, 0, 0xC0},
	{"portb",  0x05, 0, 0},
	{"pinc",   0x06, 0, 0},
	{"ddrc",   0x07, 0, 0},
	{"portc",  0x08, 0, 0},
	{"pind",   0x09, 0, 0},
	{"ddrd",   0x0A, 0, 0x03},
	{"portd",  0x0B, 0, 0x03},
	{"tccr0a", 0x24, 0, 0},
	{"tccr0b", 0x25, 0, 0},
	{"tcnt0",  0x26, 0, 0},
	{"ocr0a",  0x27, 0, 0},
	{"ocr0b",  0x28, 0, 0},
	{"sreg",   0x3F, 0, 0},
	{"timsk0", 0x6E, 0, 0},
	{"timsk1", 0x6F, 0, 0},
	{"timsk2", 0x70, 0, 0},
	{"tccr1a", 0x80, 0, 0},
	{"tccr1b", 0x81, 0, 0},
	{"tccr1c", 0x82, 0, 0},
	{"ocr1al", 0x88, 0, 0},
	{"ocr1ah", 0x89, 0, 0},
	{"ocr1bl", 0x8A, 0, 0},
	{"ocr1bh", 0x8B, 0, 0},
	{"tccr2a", 0xB0, 0, 0},
	{"tccr2b", 0xB1, 0, 0},
	{"ocr2a",  0xB3, 0, 0},
	{"ocr2b",  0xB4, 0, 0}
};

void set_reg(int args, char** argv){
	int i;

	if(args != 3) printf("Invalid arguments\n");
	else{
		for(i = 0; i < REGISTERS && strcmp(argv[1], R[i].label) != 0; i++);

		if(i == REGISTERS) printf("Invalid argument\n");
		else{
			//get the last argument, is a string that needs to be converted in binary
			int value = 0;
			if(stringIsNumber(argv[2]) == 0) printf("Invalid argument: string is not a number\n");
			else{
				//conversion
				value = stringToNumber(argv[2]);
				//value = (value & ~(R[i].mask)) | (R[i].normal & R[i].mask);

				//riempio un buffer di 6 byte, lo standard che uso per le comunicazioni con Arduino
				char *registro, *valore, *parziale, *completo;
				registro = HexToAscii(R[i].address);
				valore = HexToAscii(value);

				parziale = stringConcat(registro, " ");
				completo = stringConcat(parziale, valore);

				sendBuffer((unsigned char*)completo, 6);

				free(registro);
				free(valore);
				free(parziale);
				free(completo);
			}
		}
	}
}

void clear(int args, char** argv){
	system("cls");
}

void version(int args, char** argv){
	printf("System version %s\n", VERSION);
}

void help(int args, char** argv){

}

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
        printf("Arduino-test-platform> ");
		int args;
		char **argv;
		char *command_raw = NULL, *command = NULL;

		command_raw = stringScan();
		command = shrink(command_raw);

		args = wc(command);
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
		free(command_raw);
		free(command);
		free(argv);
	}while(exit_flag == 0);

    closeSerial();

	return 0;
}
