//Definimos las funciones propias
float calcula_Rpot(uint8_t max_pulsos, uint8_t pulsos, float Rmax) {
  float Rpot;

  Rpot = (Rmax * pulsos) / max_pulsos;
  return Rpot;
}
//-------------------------------------------------------------

void incremento(uint8_t inc_pin, uint8_t ud_pin, float cs_pin) {
  digitalWrite(cs_pin, LOW);
  digitalWrite(ud_pin, HIGH);
  digitalWrite(inc_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(inc_pin, LOW);

  digitalWrite(inc_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(cs_pin, HIGH);
  delay(50);
  digitalWrite(cs_pin, LOW);
}
//-------------------------------------------------------------

void decremento(uint8_t inc_pin, uint8_t ud_pin, float cs_pin) {
  digitalWrite(cs_pin, LOW);
  digitalWrite(ud_pin, LOW);
  digitalWrite(inc_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(inc_pin, LOW);

  digitalWrite(inc_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(cs_pin, HIGH);
  delay(50);
  digitalWrite(cs_pin, LOW);
}
//-------------------------------------------------------------

void almacenar(uint8_t inc_pin, uint8_t ud_pin, float cs_pin) {
  int pos = 100;
  int i;

  for (i = 0; i < pos; i++) {
    digitalWrite(cs_pin, LOW);
    digitalWrite(ud_pin, LOW);
    digitalWrite(inc_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(inc_pin, LOW);
  }

  digitalWrite(inc_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(cs_pin, HIGH);
  delay(50);
  digitalWrite(cs_pin, LOW);
}
//-------------------------------------------------------------

void sel_controlador(uint8_t valor){
  if(valor == 0){
    digitalWrite(KP,HIGH);
    digitalWrite(KI,LOW);
    digitalWrite(KD,LOW);
  }
  else if(valor == 1){
    digitalWrite(KP,HIGH);
    digitalWrite(KI,HIGH);
    digitalWrite(KD,LOW);
  }
  else if(valor == 2){
    digitalWrite(KP,HIGH);
    digitalWrite(KI,LOW);
    digitalWrite(KD,HIGH);
  }
  else if(valor == 3){
    digitalWrite(KP,HIGH);
    digitalWrite(KI,HIGH);
    digitalWrite(KD,HIGH);
  }
}

