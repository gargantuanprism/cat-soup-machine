#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const uint32_t LONG_PRESS_TIME = 500;
const uint32_t PUMP_TIME_FACTOR = 5;
uint32_t startMillis = 0;
uint32_t now = 0;
uint8_t state = 0;
uint8_t prevState = 0;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("start");
}

void loop(){
  now = millis();
  state = digitalRead(BUTTON_PIN);

  if (state != prevState){

    // pressed, start timer
    if (state == LOW){
      Serial.println("pressed");
      startMillis = millis();
    }

    // released, stop timer
    else if (state == HIGH && now - startMillis > LONG_PRESS_TIME){
      uint32_t pressTime = now - startMillis;
      uint32_t runTime = pressTime * PUMP_TIME_FACTOR;

      Serial.print("pressed for: ");
      Serial.println(pressTime);
      Serial.print("run time: ");
      Serial.println(runTime);

      digitalWrite(LED_BUILTIN, HIGH);
      delay(runTime);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  prevState = state;
}

