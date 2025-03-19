#include <Arduino.h>

const uint32_t RUN_TIME = 20e3;
const uint32_t INTERVAL = 60e3;
uint32_t lastMillis = 0;
uint32_t now = 0;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop(){
  now = millis();

  // overflow
  if (now < lastMillis){
    lastMillis = now;
  }

  // if (digitalRead(2) == HIGH){
  if (Serial.available() > 0 
      && Serial.read() == 'x'
      && (now - lastMillis > INTERVAL || lastMillis == 0)){
    lastMillis = now;
    Serial.println("running");
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(RUN_TIME);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("done");
    Serial.println(millis());
  }
}

