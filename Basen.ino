#include <OneWire.h>
#include <DS18B20.h>

#define INTERVAL 200 // how much us is 1 lastTime
#define SECOND 5000  // 1,000,000/INTERVAL - how many intervals are in a second

// piny do kontrolowania rejestru
byte latchPin = 8;
byte clockPin = 12;
byte dataPin = 11;

byte latchPinPort = B00000001;
byte clockPinPort = B00010000;
byte dataPinPort =  B00001000;

// numer pinu do którego podlaczamy czujnik
#define ONEWIRE_PIN 2

// liczba czujnikow
#define NUMBER_SENSORS 3


unsigned long lastTime = 0;
unsigned long tempTime = 0;
unsigned long tempMicros = 0;
unsigned long sumForAvg = 0;

byte registerState;

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  while(!Serial);
  Serial.begin(9600);
  registerState = compute();
  
  sensors.begin();
  sensors.request();
}

void loop() {
  if( (tempTime = (tempMicros = micros())/INTERVAL) != lastTime) {
    lastTime = tempTime;
    //timeBenchmark(0);
    sendToRegister(registerState);
    // temperature();
    // Serial.println(sensors.readTemperature(FA(address[0])));
    // sensors.request();
    registerState = compute();
    sumForAvg += micros() - tempMicros;
  }
}


