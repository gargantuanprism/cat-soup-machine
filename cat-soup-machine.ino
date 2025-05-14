#include <Arduino.h>
#include <stdio.h>

#define BUTTON_PIN 2
#define PUMP_TIME_FACTOR 5
#define LONG_PRESS_TIME 500
#define SERIAL_BAUD 9600

uint32_t startMillis = 0;
uint32_t now = 0;
uint8_t state[] = {0, 0};
char buf[64];

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(SERIAL_BAUD);
  Serial.println("start");
}

void loop(){
  now = millis();
  state[0] = digitalRead(BUTTON_PIN);

  if (state[0] != state[1]){

    // pressed, start timer
    if (state[0] == LOW){
      startMillis = millis();
      sprintf(buf, "pressed: %lu", startMillis);
      Serial.println(buf);
    }

    // released, stop timer
    else if (state[0] == HIGH && now - startMillis > LONG_PRESS_TIME){
      uint32_t pressTime = now - startMillis;
      uint32_t runTime = pressTime * PUMP_TIME_FACTOR;

      sprintf(buf, "press time: %lu, run: %lu", pressTime, runTime);
      Serial.println(buf);

      digitalWrite(LED_BUILTIN, HIGH);
      delay(runTime);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  state[1] = state[0];
}

