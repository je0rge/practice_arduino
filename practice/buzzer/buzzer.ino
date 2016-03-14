float sinVal;
int toneVal;
void setup(){
     pinMode(10, OUTPUT);
}
void loop(){
  /*
     for(int x=0; x<180; x++){
//convert angle of sinusoidal to radian measure 
            sinVal = (sin(x*(3.1412/180)));
//generate sound of different frequencies by sinusoidal value
            toneVal = 2000+(int(sinVal*1000));
//Set a frequency for Pin-out 10
            tone(10, toneVal, 10);
            delay(20); 
     }  */

 //convert angle of sinusoidal to radian measure 
            sinVal = (sin(0*(3.1412/180)));
//generate sound of different frequencies by sinusoidal value
            toneVal = 2000+(int(sinVal*1000));
//Set a frequency for Pin-out 10
            tone(10, toneVal,20);
            delay(1000); 
                 
}
