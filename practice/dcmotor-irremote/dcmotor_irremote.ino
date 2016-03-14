#include <IRremote.h>

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;

int relayPin =  3;                          
bool relayState = 1;                                          
 
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); //start receiver
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);  

  pinMode(8, OUTPUT); //making pin 8 as 5v power supply
  digitalWrite(8, 1); //5v power of ir receiver
}
void loop() {
  if(irrecv.decode(&results)){
    Serial.print("code received - ");
    Serial.println(results.value, DEC);
    
    if(results.value == 16580863){
        relayState = !relayState;
        Serial.println(relayState);
        delay(200);
        digitalWrite(relayPin, relayState);
    }
    else if(results.value == 4294967295){
      Serial.println("code long press");
    }
    else{
      Serial.println("invalid code");
    }
  irrecv.resume();
  }
  else{
    Serial.println("waiting for code");
  }
  
}
