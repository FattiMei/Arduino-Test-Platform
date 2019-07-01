#include <stdio.h>

#include "serial.h"
#include "string-mei.h"

void serialInit(){
    arduino = fopen(COM, "r+");
    if(arduino == NULL) printf("Device non collegato\n");
}

int sendBuffer(unsigned char* buffer, int length){
    fwrite(buffer, sizeof(unsigned char), length, arduino);
    fflush(arduino);
}

void closeSerial(){
    fclose(arduino);
}
