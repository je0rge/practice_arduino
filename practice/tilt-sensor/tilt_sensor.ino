int SensorLED = 13; //define LED digital pin 13 
int SensorINPUT = 3; // connect tilt sensor to interrupt 1 in digital pin 3 
unsigned char state = 0;
float sinVal;
int toneVal;


void setup() { 
  pinMode(SensorLED, OUTPUT); //configure LED as output mode
  pinMode(SensorINPUT, INPUT_PULLUP); //configure tilt sensor as input mode 
  //when low voltage changes to high voltage, it triggers interrupt 1 and runs the blink function
  attachInterrupt(1, blink, RISING);   
 }
 
void loop(){
      if(state!=0){
        state = 0;  
        digitalWrite(SensorLED,HIGH); // turn on LED
        buzzer();
        delay(500);
      }  
      else{ 
        digitalWrite(SensorLED,LOW); // if not, turn off LED
        noTone(10);
     }
}

void blink(){                   
  //interrupt function blink()
  state++; //once trigger the interrupt, the state keeps increment
}

void buzzer(){
     for(int x=0; x<180; x++){
        //convert angle of sinusoidal to radian measure 
            sinVal = (sin(x*(3.1412/180)));
        //generate sound of different frequencies by sinusoidal value
            toneVal = 2000+(int(sinVal*1000));
        //Set a frequency for Pin-out 10
            tone(10, toneVal);
            delay(20); 
     }          
}
