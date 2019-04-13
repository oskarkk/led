#define tab() Serial.print("\t")

bool stateR[2], stateG[2], stateB[2] = {0};
unsigned short phase1 = 0;
unsigned short phase2 = 0;

// dzialanie oswietlenia zmienia sie poprzez dodawanie funkcji do pinow ponizej
byte compute(){
  //fadeFajny();
  //dimPokaz();
  //stateG[0] = fade(4096*2+7,64,1);
  //stateG[0] = fade(4096*2,64,1);
  stateG[0] = fade2(1024*8,6,0,&phase1);
  //stateG[0] = dim(1,50);
  //stateB[0] = dim2(1,5,&phase2);
  //stateG[0] = 1;
  //stateB[0] = 1;
  //stateB[0] = stateG[0] = fade(SECOND*2,30,0);
  
  byte bits[8] = {stateR[0],stateG[0],stateB[0],0,0,0,0,0};
  return toByte(bits);
}

bool fade(int duration, int period, bool direction) {
  // zmienne zależne od parametrów funkcji
  int periodCount = duration / period;
  // ile jest 1/10mikrosekund w okresie podzielone przez ilość okresów
  int step100 = 100*period/(periodCount-1);

  // zmienne zależne od czasu
  int phaseOld = lastTime%duration;
  int periodNumber = phaseOld / period; 

  // czy znajdujemy się w momencie przed punktem zmiany w obecnym okresie?
  // lub na końcu fade'a?
  if(100*(phaseOld%period) < step100*periodNumber || phaseOld==duration-1) {
    // jeżeli tak to zwracamy direction
    return direction; 
  } else {
    // jeżeli nie to zwracamy odwrotnosc
    return !direction;
  }
}

bool fade2(int duration, int period, bool direction, unsigned short* time) {
  int waves = duration >> period; // how many full waves are in duration
  // how many 100ths of INTERVAL are in a period - divided by number of full waves in duration of fade
  int step100 = (100 << period) / (waves-1);    // << period = * 2^period = (in specific case) *64

  (*time)++;
  if (*time == duration) *time = 0; // at the end of the fade set time to 0

  // which wave are we in
  int currentWave = *time >> period;
  byte shift = sizeof(*time)*8 - period;  // number of bits 
  short phase = *time << shift >> shift;  // like modulo - we're throwing away some most significant bits
  /*
  Serial.print(*time); tab();
  Serial.print(currentWave); tab();
  Serial.print(step100); tab();
  Serial.println(phase);
  String debugInfo = String(*time + currentWave*10000);
  Serial.println(debugInfo);
*/
  // czy znajdujemy się w momencie przed punktem zmiany w obecnym okresie?
  // lub na końcu fade'a?
  if(100*phase < step100*currentWave || *time==duration-1) {
    return direction; 
  } else {
    return !direction;
  }
}

bool dim(int brightness, int period) {
  int phase = lastTime % period;
  return (phase < brightness);
}

bool dim2(int brightness, int period, unsigned short* phase) {
  (*phase)++;
  if (*phase == period) *phase = 0;
  return (*phase < brightness);
}

void fadeFajny(){
  int loopLength = SECOND;
  int phase = lastTime % (loopLength*4);
  
  if(phase < loopLength) {
    stateG[0] = fade(loopLength,32,1);
  } else if(phase < loopLength*2) {
    stateB[0] = fade(loopLength,32,1);
  } else if(phase < loopLength*3) {
    stateG[0] = fade(loopLength,32,0);
  } else {
    stateB[0] = fade(loopLength,32,0);
  }
}

void dimPokaz(){
  if(lastTime<10000){
    stateG[0] = dim(1,20);
  } else if(lastTime<20000){
    stateG[0] = dim(1,50);
  } else if(lastTime<30000){
    stateG[0] = dim(1,10);
  } else if(lastTime<40000){
    stateG[0] = dim(1,5);
  } else if(lastTime<48000){
    stateG[0] = 1;
  } else {
    stateG[0] = 0;
    fadeFajny();
  }
}

//void fadeInOut(*output
