//Project 15 - digital tube display 
#include <IRremote.h>

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;
int n[8] = {1,1,1,1,1,1,1,1};
bool state = 0;
int num = 10;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); //start receiver
  
for(int pin = 2 ; pin <=9 ; pin++){       
//define digital pin 2-9 as output 
       pinMode(pin, OUTPUT);
       digitalWrite(pin, HIGH);
  }
  dispNumber(num);
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
          //loadArray(0,0,0,1,0,0,0,1);
          num = 0;
          break;
        case 16582903: 
          //loadArray(0,1,1,1,1,1,0,1);
          num = 1;
          break;
        case 16615543: 
          //loadArray(0,0,1,0,0,0,1,1);
          num = 2;
          break;
        case 16599223: 
          //loadArray(0,0,1,0,1,0,0,1);
          num = 3;
          break;
        case 16591063: 
          //loadArray(0,1,0,0,1,1,0,1);
          num = 4;
          break;
        case 16623703: 
          //loadArray(1,0,0,0,1,0,0,1);
          num = 5;
          break;
        case 16607383: 
          //loadArray(1,0,0,0,0,0,0,1);
          num = 6;
          break;
        case 16586983: 
          //loadArray(0,0,1,1,1,1,0,1);
          num = 7;
          break;
        case 16619623: 
          //loadArray(0,0,0,0,0,0,0,1);
          num = 8;
          break;
        case 16603303: 
          //loadArray(0,0,0,0,1,1,0,1);
          num = 9;
          break;
        case 16613503:
          if(num < 9) num++;
          else num = 9;
          break;
        case 16617583:
          if(num > 0) num--;
          else num = 0;
          break;
        case 4294967295:
          break;
        default:
          Serial.println("invalid code");
          //loadArray(1,1,1,1,1,1,1,1);
      }
    }
    Serial.println(num);
    dispNumber(num);
  }
  
  else{
    Serial.print("display unchanged - ");
    dispArray();
    dispNumber(num);
  }
}

void power(){
  state = !state;
  if(state == 1){
     loadArray(0,0,0,1,0,0,0,1);
     num = 0;
  }
  else{
     loadArray(1,1,1,1,1,1,1,1);
     num = 10;
  }
  delay(200);
  dispNumber(num);
}

void dispArray(){
  for(int i = 0; i < 8; i++){
    Serial.print(n[i]);
  }
  Serial.println(n[8]);
}

void loadArray(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h){
  n[0] = a;
  n[1] = b;
  n[2] = c;
  n[3] = d;
  n[4] = e;
  n[5] = f;
  n[6] = g;
  n[7] = h;
}

// display number
void dispNumber(int num){
    switch(num){
      case 0: 
        loadArray(0,0,0,1,0,0,0,1);
        break;
      case 1:
        loadArray(0,1,1,1,1,1,0,1);
        break;
      case 2:
        loadArray(0,0,1,0,0,0,1,1);
        break;
      case 3:
        loadArray(0,0,1,0,1,0,0,1);
        break;
      case 4:
        loadArray(0,1,0,0,1,1,0,1);
        break;
      case 5:
        loadArray(1,0,0,0,1,0,0,1);
        break;
      case 6:
        loadArray(1,0,0,0,0,0,0,1);
        break;
      case 7:
        loadArray(0,0,1,1,1,1,0,1);
        break;
      case 8:
        loadArray(0,0,0,0,0,0,0,1);
        break;
      case 9: 
        loadArray(0,0,0,0,1,1,0,1);
        break;
      case 10:
        loadArray(1,1,1,1,1,1,1,1);
        break;
      default:
        Serial.println(num);
    }
    //display the array of n[8] in digital pin 2-9
    for(int pin = 2; pin <= 9 ; pin++){ 
       digitalWrite(pin,n[pin-2]);
    }
}
