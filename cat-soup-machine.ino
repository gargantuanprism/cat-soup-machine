#include <Arduino.h>

const uint32_t RUN_TIME = 35e3;
uint32_t lastMillis = 0;
uint32_t now = 0;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  Serial.println("start");
}

void loop(){
  now = millis();

  if (digitalRead(2) == HIGH){
    lastMillis = now;
    Serial.println("running");

    digitalWrite(LED_BUILTIN, HIGH); 
    delay(RUN_TIME);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.println("done");
    Serial.println(millis());
  }
}

