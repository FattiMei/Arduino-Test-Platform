#include <stdio.h>
#include <malloc.h>

int stringLen(char *s);
char *stringScan();
char *stringScanfromFile(FILE *fp);
char *stringCopy(char *s, char *t);
char *stringConcat(char *s, char *t);
int stringCompare(char *s, char *t);
int stringIsNumber(char *s);
void stringReverse(char *s);
int stringToNumber(char *s);