/**************************************
 *** JamMate V1.0 *********************
 *** first release Sun Jul 19, 2020 ***
 *** Author: Mischahr *****************
**************************************/

//    Arduino Pin-Map
const int GreenKeyIn= 2;
const int PlayCMD =  12;
const int PageUpCMD= 11;
const int StopCMD =  10;
//______________________

int trigger=0;
long timestamp =0;
boolean keyDown=false;
boolean keyUp  =false;
    
void setup() {
pinMode(GreenKeyIn,  INPUT_PULLUP); 
pinMode(PlayCMD,     OUTPUT);
pinMode(StopCMD,     OUTPUT);
pinMode(PageUpCMD,   OUTPUT);
   
// initializing (Power-on)
digitalWrite(PlayCMD,   HIGH); // send +3.3V
digitalWrite(StopCMD,   HIGH); // send +3.3V
digitalWrite(PageUpCMD, HIGH); // send +3.3V
}

boolean onKeyDown() {
  if (digitalRead(GreenKeyIn)==LOW) {
     return true;
     }
  else return false;
}
  
boolean onKeyUp() {
  if (digitalRead(GreenKeyIn)==HIGH) {
    return true;
  }
  else return false;
}

boolean triggerPlay() {  
  if (onKeyDown()==true && trigger==0) {
      timestamp=millis();
      trigger++;
      digitalWrite(PlayCMD, LOW);
  }
  
  if (onKeyDown()==true && trigger==1 && (millis()-timestamp>1000)) {
      trigger++;
      digitalWrite(PlayCMD, HIGH);
      digitalWrite(StopCMD, LOW);
  }

  if (onKeyDown()==true && trigger==2 && (millis()-timestamp>1100)) {
      digitalWrite(StopCMD, HIGH);
  }
  
  if (onKeyDown()==true && trigger==2 && (millis()-timestamp>2000)) {
      trigger++;
      digitalWrite(PageUpCMD, LOW); 
  }  

  if (onKeyDown()==true && trigger==3 && (millis()-timestamp>2100)) {
      trigger++;
      digitalWrite(PageUpCMD,HIGH);
  }  
  
  if (onKeyUp()==true && trigger>0) {
      trigger=0;
      digitalWrite(PlayCMD,   HIGH);
      digitalWrite(StopCMD,   HIGH);
      digitalWrite(PageUpCMD, HIGH); 
  }
}

//____________________________________________________________________________________________________________  
void loop() {
  triggerPlay();
}
