#define LENGTH 6

char s[9];
int count = 0;

unsigned char registro, valore;

void setup(){
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    s[count++] = Serial.read();
  }
  if(count == LENGTH){
    count = 0;
    s[LENGTH - 1] = '\0';
    
    //interpretazione del comando, quasi sicuramente non funziona
    for(int i = 0; s[i] != '\0'; i++){
      if(s[i] == ' ') s[i] = '\0';
    }
    
    registro = stringHexToNumber(&s[0]);
    valore = stringHexToNumber(&s[3]);
    
    if(registro < 0x3F) _SFR_IO8(registro) = valore;
    else _SFR_MEM8(registro) = valore;
  }
}

int stringCompare(char *s, char *t){
  while(*s == *t){
    if(*s == '\0') return 1;

    s++;
    t++;
  }
  return 0;
}

int stringIsHex(char *s){
  int i;
  
  for(i = 0; s[i] != '\0'; i++){
    if(s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9' && s[i] != 'A' && s[i] != 'B' && s[i] != 'C' && s[i] != 'D' && s[i] != 'E' && s[i] != 'F') return 0;
  }
  if(i != 0) return 1;
  else return 0;
}

unsigned char stringHexToNumber(char *s){
  int len, mask = 1, i, cifra;
  unsigned char risultato = 0;

  if(stringIsHex(s) == 1){
    //get the length of the string
    for(len = 0; s[len] != '\0'; len++);

    if(len != 0){
      for(i = len - 1; i >= 0; i--){
        switch(s[i]){
          case '0': cifra = 0; break;
          case '1': cifra = 1; break;
          case '2': cifra = 2; break;
          case '3': cifra = 3; break;
          case '4': cifra = 4; break;
          case '5': cifra = 5; break;
          case '6': cifra = 6; break;
          case '7': cifra = 7; break;
          case '8': cifra = 8; break;
          case '9': cifra = 9; break;
          case 'A': cifra = 10; break;
          case 'B': cifra = 11; break;
          case 'C': cifra = 12; break;
          case 'D': cifra = 13; break;
          case 'E': cifra = 14; break;
          case 'F': cifra = 15; break; 
        }
        risultato += (cifra * mask);
        mask *= 16;
      }
      return risultato;
    }
    else return -1;
  }
  else return -1;
}
