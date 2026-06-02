#include <Arduino.h>
const uint8_t redpin = 4;
const uint8_t yellowpin = 3;
const uint8_t greenpin = 2;
const uint8_t switchpin = 11;
uint8_t state = 0;  // 0=red, 1=yellow, 2=green
bool switchmode;
bool previous_switchmode = HIGH;
bool pedestrian_requested = false;
unsigned long interval = 10000;
unsigned long statestart = 0;

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(switchpin, INPUT_PULLUP);
  digitalWrite(redpin, HIGH);
}

void loop() {
 unsigned long now = millis();
 switchmode = digitalRead(switchpin);
if(switchmode != previous_switchmode && switchmode == LOW){
    pedestrian_requested = true;
}
previous_switchmode = switchmode;
 if(state == 0 && now - statestart >= 2000){
  if(pedestrian_requested){
    // flash red 5 times for pedestrians
    for(int i = 0; i < 5; i++){
        digitalWrite(redpin, LOW);
        delay(500);
        digitalWrite(redpin, HIGH);
        delay(500);
    }
    pedestrian_requested = false;
}
 else{ 
  digitalWrite(redpin, LOW);
  digitalWrite(yellowpin, HIGH);
  state = 1;
  statestart = now;
 }
 }
 else  if(state == 1 && now - statestart >= 1000){
  if(pedestrian_requested){
    // flash red 5 times for pedestrians
    digitalWrite(yellowpin, LOW);
    for(int i = 0; i < 5; i++){
        digitalWrite(redpin, LOW);
        delay(500);
        digitalWrite(redpin, HIGH);
        delay(500);
    }
    digitalWrite(redpin, LOW);
    pedestrian_requested = false;
}
  else{
  digitalWrite(yellowpin, LOW);
  digitalWrite(greenpin, HIGH);
  state = 2;
  statestart = now;
  }
 }
 else  if(state == 2 && now - statestart >= 2000){
  if(pedestrian_requested){
    // flash red 5 times for pedestrians
    digitalWrite(greenpin, LOW);
    for(int i = 0; i < 5; i++){
        digitalWrite(redpin, LOW);
        delay(500);
        digitalWrite(redpin, HIGH);
        delay(500);
    }
    pedestrian_requested = false;
}
 else{ digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, LOW);
  state = 0;
  statestart = now;
 }
}
}