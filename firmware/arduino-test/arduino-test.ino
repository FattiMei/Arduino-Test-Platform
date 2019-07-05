#define FOSC 16000000
#define BUFFER_LENGTH 128
#define USER_BUFFER_LENGTH 128

#define BIN 2
#define OCT 8
#define DEC 10
#define HEX 16

struct SFR{
  char *label;
  unsigned char address, value;
};

struct SFR accessible_registers[29] = {
  {"pinb",   0x03, 0},
  {"ddrb",   0x04, 0},
  {"portb",  0x05, 0},
  {"pinc",   0x06, 0},
  {"ddrc",   0x07, 0},
  {"portc",  0x08, 0},
  {"pind",   0x09, 0},
  {"ddrd",   0x0A, 0},
  {"portd",  0x0B, 0},
  {"tccr0a", 0x24, 0},
  {"tccr0b", 0x25, 0},
  {"tcnt0",  0x26, 0},
  {"ocr0a",  0x27, 0},
  {"ocr0b",  0x28, 0},
  {"sreg",   0x3F, 0},
  {"timsk0", 0x6E, 0},
  {"timsk1", 0x6F, 0},
  {"timsk2", 0x70, 0},
  {"tccr1a", 0x80, 0},
  {"tccr1b", 0x81, 0},
  {"tccr1c", 0x82, 0},
  {"ocr1al", 0x88, 0},
  {"ocr1ah", 0x89, 0},
  {"ocr1bl", 0x8A, 0},
  {"ocr1bh", 0x8B, 0},
  {"tccr2a", 0xB0, 0},
  {"tccr2b", 0xB1, 0},
  {"ocr2a",  0xB3, 0},
  {"ocr2b",  0xB4, 0}
};

char input_buffer[BUFFER_LENGTH], output_buffer[BUFFER_LENGTH], user_buffer[USER_BUFFER_LENGTH];

int args, i, valore;
char **argv = NULL, *comando = NULL, *lettura = NULL;

void setup(){
  USART_init(9600);
}

void loop(){
  USART_read_input_buffer(input_buffer);
  shrink(input_buffer, user_buffer);

  comando = stringCopy(comando, user_buffer);

  args = wc(comando);
  argv = getArgumentsValue(comando, args);

  if(stringCompare(argv[0], "set") == 0){
    if(args != 3) string_println("Invalid number of arguments");
    else{
      for(i = 0; i < 29; i++) if(stringCompare(accessible_registers[i].label, argv[1]) == 0) break;
      if(i != 29){
        valore = string_to_unsigned(argv[2], BIN);
        if(valore == -1) string_println("Invalid argument for function set");
        else{
          if(accessible_registers[i].address <= 0x3F) _SFR_IO8(accessible_registers[i].address) = valore;
          else _SFR_MEM8(accessible_registers[i].address) = valore;
        }
      }
      else string_println("Invalid argument");
    }
  }
  else if(stringCompare(argv[0], "read") == 0){
    if(args != 2) string_println("Invalid number of arguments");
    else{
      for(i = 0; i < 29; i++) if(stringCompare(accessible_registers[i].label, argv[1]) == 0) break;
      if(i != 29){
        if(accessible_registers[i].address <= 0x3F) valore = _SFR_IO8(accessible_registers[i].address);
        else valore = _SFR_MEM8(accessible_registers[i].address);

        lettura = unsigned_to_string((unsigned int) valore, BIN, user_buffer);
        string_println(lettura);

        free(lettura);
      }
    }
  }

  free(argv);
}

int stringLen(char *s){
  int len = 0;
  for(int i = 0; s[i] != '\0'; i++) len++;
  len++;

  return len;
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

int stringCompare(char *s, char *t){
  while(*s == *t){
    s++;
    t++;

    if(*s == '\0' || *t == '\0') break;
  }

  return *s - *t;
}

char *stringCopy(char *s, char *t){
  char *nuovo;
  int size = stringLen(t), i = 0;

  if(size != -1){
    free(s);
    nuovo = (char*) malloc(sizeof(char) * size);

    for(i = 0; i < size; i++) nuovo[i] = t[i];
  }

  return nuovo;
}

void shrink(char *s, char *user_buffer){
  int i, blank = 0, first_char_flag = 0, len;

  for(i = 0, len = 0; s[i] != '\0'; i++){
    if(first_char_flag == 0){
      if(s[i] != ' ') first_char_flag = 1;
    }
    else{
      if(s[i] == ' ') blank++;
      else blank = 0;
    }
    
    if(first_char_flag == 1 && blank <= 1) user_buffer[len++] = s[i];
  }
  if(user_buffer[len] == ' ') len--;

  user_buffer[len] = '\0';
}

int string_to_unsigned(char *s, int formato){
  const char set[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  int risultato = 0, mask = 1, cifra, len, i;

  if(formato < 2 || formato > 16) return -1;
  else{
    len = stringLen(s);
    if(len < 2) return -1;
    else{
      for(i = 0; i < len - 1; i++){
        for(cifra = 0; cifra < formato && s[i] != set[cifra]; cifra++);
        if(cifra == formato) return -1;
      }

      //ha superato tutti i controlli procedi con la conversione
      for(i = len - 2; i >= 0; i--){
        for(cifra = 0; s[i] != set[cifra]; cifra++);
        risultato += (cifra * mask);
        mask *= formato;
      }
    }
  }

  return risultato;
}

char *unsigned_to_string(unsigned int numero, int formato, char *user_buffer){
  int len = 0, cont = 0, resto;
  char *nuovo = NULL;
  const char set[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  if(formato < 2 || formato > 16) return NULL;
  else{
    if(numero == 0) user_buffer[len++] = '0';
    while(numero >= 1){
      resto = numero % formato;
      numero /= formato;

      user_buffer[len++] = set[resto];
    }
    if(formato == BIN){
      while(len < 9) user_buffer[len++] = '0';
    }
    user_buffer[len++] = '\0';
    nuovo = (char*) malloc(sizeof(char) * len);

    for(int i = len - 2; i >= 0; i--) nuovo[cont++] = user_buffer[i];
    nuovo[cont] = '\0';

    return nuovo;
  }
  
}

//sarebbe veramente interessante implementare una vera e propria printf, però forse ci sono troppi problemi
void string_println(char *s){
  int i, len = 0;
  for(i = 0; s[i] != '\0'; i++) output_buffer[len++] = s[i];

  output_buffer[len++] = '\n';
  output_buffer[len] = '\0';

  USART_write_output_buffer(output_buffer);
}

void string_print(char *s){
  int i, len = 0;
  for(i = 0; s[i] != '\0'; i++) output_buffer[len++] = s[i];

  output_buffer[len] = '\0';
  USART_write_output_buffer(output_buffer);
}

int wc(char *s){
  int words = 1;

  for(;*s != '\0'; s++){
    if(*s == ' ') words++;
  }

  return words;
}

char** getArgumentsValue(char *command, int args){
    char** argv;
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

    return argv;
}

int USART_read_input_buffer(char *input_buffer){
  int pos = 0, exit_flag = 0;
  while(exit_flag == 0){
    input_buffer[pos] = USART_read();

    if(input_buffer[pos] == '\n'){
      input_buffer[pos] = '\0';
      exit_flag = 1;
    }

    pos++;
  }

  return pos;
}

void USART_write_output_buffer(char *output_buffer){
  while(*output_buffer != '\0'){
    while (!(UCSR0A & (1<<5)));
    UDR0 = *output_buffer;

    output_buffer++;
  }
  
}

void USART_init(unsigned int baud_rate){
  unsigned int ubrr = FOSC / 16 / baud_rate - 1;
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0A = 0B00000000;
  UCSR0B = 0B00011000;
  UCSR0C = 0B00000110;

}

unsigned char USART_read(){
  while(!(UCSR0A & (1 << 7)));
  unsigned char byte_ = UDR0;

  return byte_;
}
