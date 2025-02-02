/*
* W.J. Hoogervorst - January 2025
* Light switch stock room based on IR sensor AM312 to detect motion or door opening
*/


#define PIRPIN 2
#define RELAYPIN 3

uint32_t switchdelay = 20000;  // the time the relay stays on when switched
uint32_t switchtime;          // the time the relay was switched on

boolean Motion = false;  // is motion present?

void setup() {
  pinMode(PIRPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, HIGH);
  delay(switchdelay);  //if the module is switched on, the delay should be on, gives also time to bootup the AM312
  switchtime = millis();
  //Serial.begin(9600);
}

void loop() {

  if (digitalRead(PIRPIN) == HIGH) {
    Motion = true;
    //Serial.println("motion");
    switchtime = millis();
  } else {
    Motion = false;
    //Serial.println("\t\t No motion");
  }
  if (Motion && digitalRead(RELAYPIN) == LOW) {
    switchtime = millis();
    digitalWrite(RELAYPIN, HIGH);
    //Serial.println("relay on");
  }
  if (millis() > switchtime + switchdelay && digitalRead(RELAYPIN) == HIGH) {
    digitalWrite(RELAYPIN, LOW);
    //Serial.println("relay off");
  }
  delay(100);
}
