// adresy czujnikow uzyskane za pomoca oddzielnego programu
// kazda linijka to inny czujnik
const byte address[NUMBER_SENSORS][8] PROGMEM={0x28, 0xFF, 0xE5, 0x7F, 0x70, 0x17, 0x3, 0xFD, // niebieski
                                         0x28, 0xFF, 0x4E, 0xD7, 0x70, 0x17, 0x3, 0xB, // bialy
                                         0x28, 0xFF, 0xCD, 0xD8, 0x70, 0x17, 0x3, 0x14}; // czerwony


void temperature() {
  if (sensors.available()) {
    for (byte i=0; i<NUMBER_SENSORS; i++) {
      float temp = sensors.readTemperature(FA(address[i]));
      if (temp > 60.0) {
        Serial.print("  >....");
      } else if(temp < 0) {
        Serial.print("  <....");
      } else {
        Serial.print("  ");
        Serial.print(temp);
      }
    }
    // float average = (sensors.readTemperature(FA(address[0]))+sensors.readTemperature(FA(address[1]))+sensors.readTemperature(FA(address[2])))/3;
    // Serial.println("Srednia temp: ");
    // Serial.println(average);
    Serial.println();
    sensors.request();
    delay(1000);
  }
}
