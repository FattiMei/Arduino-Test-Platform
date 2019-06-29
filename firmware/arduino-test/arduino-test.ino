byte comando[3];

void setup(){
  Serial.begin(9600);
}

void loop(){
  
  if(Serial.available() > 0){
    Serial.readBytes(comando, 3);

    if(comando[0] == 1){
      if(comando[1] > 0x3F) _SFR_IO8(comando[1]) = comando[2];
      else _SFR_MEM8(comando[1]) = comando[2];
    }
  }
}
