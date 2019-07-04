#define BUFFER_LENGTH 128

char dato[BUFFER_LENGTH];
volatile int pos = 0, receive_flag = 0;

void setup(){
  USART_init(16000000 / 16 / 9600 - 1);
  DDRB |= 0B00100000;
}

void loop(){
  //decido di acquisire l'input completo e poi di stamparlo tutto i una volta
  dato[pos] = USART_read();
  if(dato[pos] == '\n'){
    //stampa tutto
    USART_Transmit(dato, pos + 1);
    pos = 0;
  }
  else pos++;
}

void USART_init(unsigned int ubrr){
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

void USART_write(unsigned char byte_){
  UDR0 = byte_;
}

void USART_Transmit(unsigned char *data, int length){
  for(int i = 0; i < length; i++){
    while (!(UCSR0A & (1<<5)));
    UDR0 = data[i];
  }
}
