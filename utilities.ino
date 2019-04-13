void timeBenchmark(byte delayLoop) {
  delayMicroseconds(delayLoop);
  // co sekundę
  if(lastTime%SECOND == 0){
      Serial.println(sumForAvg);
      Serial.println(lastTime);
      Serial.println(sumForAvg/lastTime);
      Serial.println();
  }
}

void sendToRegister(byte byteToSend) {
  //digitalWrite(latchPin, LOW);
  PORTB &= ~latchPinPort;
  //bitClear(PORTB,0);
  shiftFast(dataPinPort, clockPinPort, LSBFIRST, byteToSend);
  //digitalWrite(latchPin, HIGH);
  PORTB |= latchPinPort;
}

/*void sendToRegisterOld(byte byteToSend) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, byteToSend);
  digitalWrite(latchPin, HIGH);
}*/

byte toByte(byte *bits) {
  byte temp = 0;
  for(byte i=0; i<8; i++) temp += (temp << 1) + bits[i];
  return temp;
}

// zoptymalizowany shiftOut() (manipulacja bitami portów)
void shiftFast(uint8_t data, uint8_t clock, uint8_t bitOrder, uint8_t val) {
  uint8_t i;

  for (i = 0; i < 8; i++) {
    if (bitOrder == LSBFIRST) {
      //digitalWrite(data, !!(val & (1 << i)));
      !!(val & (1 << i)) ? PORTB |= data : PORTB &= ~data;
    } else { 
      //digitalWrite(data, !!(val & (1 << (7 - i))));
      !!(val & (1 << (7 - i))) ? PORTB |= data : PORTB &= ~data;
    }
    //digitalWrite(clock, HIGH);
    //digitalWrite(clock, LOW);    
    PORTB |= clock;
    PORTB &= ~clock;
  }
}

unsigned int bitwiseModulo() {
  
}