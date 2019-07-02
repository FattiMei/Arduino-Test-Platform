#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2

int stringLen(char *s);
char *stringScan();
char *stringScanfromFile(FILE *fp);
char *stringCopy(char *s, char *t);
char *stringConcat(char *s, char *t);
int stringCompare(char *s, char *t);
int stringIsNumber(char *s);
void stringReverse(char *s);
int stringToNumber(char *s);
int stringToInt(char *s, int format);
