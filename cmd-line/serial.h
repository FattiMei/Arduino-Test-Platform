#define COM "\\\\.\\COM3"

FILE *arduino;

void serialInit();
int sendBuffer(unsigned char* buffer, int length);
void closeSerial();
