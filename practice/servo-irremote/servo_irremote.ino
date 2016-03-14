//Project 15 - digital tube display 
#include <IRremote.h>
#include <Servo.h>

Servo s;
int sPin = 3;
int ledPin = 4;

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;

bool state = 0;
int num = 1;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); //start receiver

  s.attach(sPin);
  moveServo(num);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, state);
}

void loop() {  
  if(irrecv.decode(&results)){
    irrecv.resume();
    Serial.print("code received - ");
    Serial.println(results.value, DEC);
    if(results.value == 16580863){
      power();
      results.value = 4294967295;
    }
    if(state == 1){
      switch(results.value){
        case 16593103: 
          num = 1;
          moveServo(num);
          break;
        case 16582903: 
          num = 20;
          moveServo(num);
          break;
        case 16615543: 
          num = 40;
          moveServo(num);
          break;
        case 16599223: 
          num = 60;
          moveServo(num);
          break;
        case 16591063: 
          num = 80;
          moveServo(num);
          break;
        case 16623703: 
          num = 100;
          moveServo(num);
          break;
        case 16607383: 
          num = 120;
          moveServo(num);
          break;
        case 16586983: 
          num = 140;
          moveServo(num);
          break;
        case 16619623: 
          num = 160;
          moveServo(num);
          break;
        case 16603303: 
          num = 180;
          moveServo(num);
          break;
        case 16613503:
          if(num < 160) num+= 20;
          else num = 180;
          moveServo(num);
          break;
        case 16617583:
          if(num > 20) num-= 20;
          else num = 1;
          moveServo(num);
          break;
        case 4294967295:
          break;
        default:
          Serial.println("invalid code");
      }
    }
    Serial.println(num);
  }
  
  else{
    Serial.print("servo postion unchanged - ");
    Serial.println(num);
  }
}

void power(){
  state = !state;
  if(state == 1){
     num = 1;
  }
  else{
     num = 180;
  }
  delay(200);
  digitalWrite(ledPin, state);
  moveServo(num);
}

void moveServo(int num){
      s.write(num);
}

