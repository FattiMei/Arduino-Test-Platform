#include <stdio.h>
#include <stdlib.h>

int stringLen(char *s){
	int size = 0;

	if(s == NULL) return -1;
	else while(s[size++] != '\0');

	return size;
}

char *stringScan(){
	char *s = NULL, c;
	int size = 0, allocato = 0;

	do{
		c = getchar();

		if(size >= allocato){
			allocato += 8;
			s = realloc(s, sizeof(char) * allocato);
		}

		if(c != 10) s[size] = c;
		else s[size] = '\0';

		size++;
	}while(c != 10);

	s = realloc(s, sizeof(char) * size);

	return s;
}

char *stringScanfromFile(FILE *fp){
	char *s = NULL, c;
	int size = 0, allocato = 0, err;

	//il file deve essere aperto con successo in modalità read
	if(fp == NULL) return NULL;
	else{
		do{
			err = fread(&c, sizeof(char), 1, fp);

			if(size >= allocato){
				allocato += 8;
				s = realloc(s, sizeof(char) * allocato);
			}
			if(c == '\n' || err != 1) s[size] = '\0';
			else s[size] = c;

			size++;
		}while(c != '\n' && err == 1);

		s = realloc(s, sizeof(char) * size);
		return s;
	}
}

char *stringCopy(char *s, char *t){
	char *nuovo;
	int size = stringLen(t), i = 0;

	if(size != -1){
		free(s);
		nuovo = malloc(sizeof(char) * size);

		for(i = 0; i < size; i++) nuovo[i] = t[i];
	}

	return nuovo;
}

char *stringConcat(char *s, char *t){
	int s_size, t_size, i = 0, size = 0;
	char *nuovo = NULL;

	s_size = stringLen(s);
	t_size = stringLen(t);

	if(s_size != -1){
		nuovo = realloc(nuovo, sizeof(char) * s_size);
		for(i = 0; i < s_size; i++) nuovo[i] = s[i];

		size += s_size - 1;
		//viene copiato anche il carattere '\0'
	}
	if(t_size != -1){
		nuovo = realloc(nuovo, sizeof(char) * (size + t_size));
		for(i = 0; i < t_size; i++) nuovo[size + i] = t[i];
	}

	return nuovo;
}

int stringCompare(char *s, char *t){
}

int stringIsNumber(char *s){
	int i = 0;
	while(*s != '\0'){
		if(*s < '0' || *s > '9') return 0;
		i++;
		s++;
	}

	if(i > 0) return 1;
	else return 0;
}

void stringReverse(char *s){
	int size = stringLen(s);
	char temp;

	for(int i = 0; i < (size - 1) / 2; i++){
		temp = s[i];
		s[i] = s[size - 2 - i];
		s[size - 2 - i] = temp;
	}
}

char *add(char *s, char *t){
	char *risultato;
	int parziale, carry = 0, flag_s = 1, flag_t = 1, i, size = 0, allocato = 0;

	if(stringIsNumber(s) && stringIsNumber(t)){
		stringReverse(s);
		stringReverse(t);

		i = 0;
		while(flag_s || flag_t){
			//controllo flag
			if(s[i] == '\0') flag_s = 0;
			if(t[i] == '\0') flag_t = 0;
			//somma
			parziale = carry;
			if(flag_s) parziale += s[i] - '0';
			if(flag_t) parziale += t[i] - '0';

			carry = parziale / 10;

			if(size >= allocato){
				allocato += 8;
				risultato = realloc(risultato, sizeof(char) * allocato);
			}

			risultato[size++] = parziale - carry * 10 + '0';
			i++;
		}

		//resize e aggiungi la coda
		risultato = realloc(risultato, sizeof(char) * (size + 1));
		risultato[size] = '\0';

		stringReverse(risultato);
		return risultato;
	}

	return NULL;
}

int stringToNumber(char *s){
	int result = 0, len, mask = 1;

	if(stringIsNumber(s) == 0) return -1;
	else{
		len = stringLen(s);
		for(int i = len - 2; i >= 0; i--){
			result += ((s[i] - '0') * mask);
			mask *= 10;
		}
	}

	return result;
}
