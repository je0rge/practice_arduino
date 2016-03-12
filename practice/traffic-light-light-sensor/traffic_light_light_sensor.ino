#include "Lib_Utility.h"
DigitalOutput carRed, carYellow, carGreen, pedRed, pedGreen;
AnalogInput pedCross;
const int pedTime = 5000;
const int pedTimeEnd = 2000;

void setup(){
  pedGreen.Init(2);
  pedRed.Init(3);
  carGreen.Init(4);
  carYellow.Init(5);
  carRed.Init(6);
  pedCross.Init(A0);
  Serial.begin(115200);
}

void loop(){
  Serial.println(pedCross.RawValue());
  if(pedCross.RawValue() < 1000){
    delay(2000);
    pedTurn();
    }
  else{
    carTurn();
  }
}

void carTurn(){
    carGreen.On();
    carRed.Off();
    carYellow.Off();
    pedGreen.Off();
    pedRed.On();
  }

void pedTurn(){
  unsigned long startTime;
  unsigned long endTime;
  
  carGreen.Off();
  carYellow.On();
  carRed.Off();
  delay(2000);
  carGreen.Off();
  carYellow.Off();
  carRed.On();
  
  pedGreen.On();
  pedRed.Off();

  startTime = millis();
  while((millis() - startTime) < pedTime){
    endTime = millis();
    }
  while((millis() - endTime) < pedTimeEnd){
    pedGreen.Toggle();
    delay(200);
  }
  pedRed.On();
  delay(500);
  carTurn();
  }
