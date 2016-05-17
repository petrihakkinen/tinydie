// TinyDie
//
// 7 die leds can be controlled with only 4 bits using the following encoding:
//
//    A        B        C        D
//  _____    _____    _____    _____  
// |     |  |    *|  |*    |  |     |
// |  *  |  |     |  |     |  |*   *|
// |_____|  |*____|  |____*|  |_____|
//
// One:   A
// Two:   B
// Three: A+B
// Four:  B+C
// Five:  A+B+C
// Six:   B+C+D

byte diebits[] = { 0,1,2,3,6,7,14 };
byte result = 0;
int delayValue = 100;
boolean shuffle = false;

void setup() {                
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
}

void updateLeds(byte n) {
  byte bits = diebits[n];
  // pins D0 & D1 have been swapped for easier PCB layout
  digitalWrite(1, bits & 1);
  digitalWrite(0, bits & 2);
  digitalWrite(2, bits & 4);
  digitalWrite(3, bits & 8);
}

void loop() {
  updateLeds(result);

  delay(delayValue);

  if(digitalRead(4) == LOW) {
    // button is down
    shuffle = true;
    delayValue = 40;
  } else {
    // button is up
    delayValue = (delayValue * 3) >> 1;
    if(delayValue > 1000) {
      delayValue = 100;
      shuffle = false;
    }
  }
  
  // shuffle
  if(shuffle)
    result = random(1, 7); // upper bound is exclusive
}

