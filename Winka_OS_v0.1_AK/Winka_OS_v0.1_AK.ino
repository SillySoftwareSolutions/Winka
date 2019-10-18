/* Winka OS v0.1_AK
 by SillySoftwareSolutions

 v0.1_AK  * nur zum Testen
*/

#include <Servo.h>

// feste Variablen
#define SERVO 9  // D9 am nano
#define BUTTON 12 // D12

// Variablen, die über die Konsole verändert werden können:
byte POSA = 20; // muss kleiner als B sein!
byte POSB = 90;
int DELAY = 15*1000;
byte STEP = 40;

Servo s; 

boolean toPosA = false;
boolean toPosB = false;
long nextWink;
long nextStep;
byte pos = POSA;    


void setup() {
  // Serial setup
  Serial.begin(9600);
  
  // Servo setup
  s.attach(SERVO);
  s.write(pos);

  // Button setup
  pinMode(BUTTON, INPUT); 

  // erster Wink nach 2s
  delay(2000);
  wink();
}

void loop() {
  if(millis() >= nextStep){
    nextStep = millis() + STEP;
    if(toPosB){
      if(POSB > pos){
        pos += 1;
        s.write(pos);
      }else{
        toPosA = true;
        toPosB = false;
      }
    }else if(toPosA){
      if(POSA < pos){
        pos -= 1;
        s.write(pos);
      }
      else{
        nextStep = 0;
        toPosA = false;
        nextWink = millis() + DELAY;
      }
    }
    
  }else if(nextWink != 0 && millis() >= nextWink){
    wink();
  }

  if((byte)digitalRead(BUTTON) == 0){
    //Serial.println(toPosA);  Serial.print(" ");  Serial.print(toPosB);  Serial.print(" ");  Serial.print(nextStep);  Serial.print(" ");  Serial.print(nextWink);  Serial.print(" ");  Serial.print(millis());
    wink();
  }
  

 
}

void wink(){
  if(toPosA == false && toPosB == false){
      toPosB = true;
      toPosA = true;
      nextStep = millis() + STEP;
      nextWink = millis() + DELAY + STEP*100;
  }
}
