 class DigitalOutput{
  int _pin;
  bool _state; 
  public:
  void Init(int p){
  _pin = p;
  pinMode(_pin, OUTPUT);
  Set(LOW);
};
  void Set(bool s){
  digitalWrite(_pin, s);
  _state = s;   
};
  void On(){
  Set(HIGH);
};
  void Off(){
  Set(LOW);
};
  void Toggle(){
  Set(!_state);
};
  bool State(){
  return _state;
};
};

#include <IRremote.h>
#include <Servo.h>

Servo s;
DigitalOutput carRed, carYellow, carGreen, pedRed, pedGreen;

const int pedTime = 5000;
const int pedTimeEnd = 2000;

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;

void setup(){
  pedGreen.Init(2);
  pedRed.Init(3);
  carGreen.Init(4);
  carYellow.Init(5);
  carRed.Init(6);

  irrecv.enableIRIn(); //start receiver
  Serial.begin(9600);
}

void loop(){
  if(irrecv.decode(&results)){
    Serial.println(results.value, HEX);

    if(results.value == 16580863){
      Serial.println("Ped Turn");
      delay(2000);
      pedTurn();
      }
    irrecv.resume();
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
