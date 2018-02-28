// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>

 #define outputA 3
 #define outputB 2

//The rheostat variables
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;


//The rotary encoder variables
 int aState;
 int aLastState;
 int xvalue=512;
  int now=0;
 int prev=0;
 int revtimes=98;
 int counter = revtimes/2; 

 //Mousr buttons brake and accel
 int gas=8;
int brake=9;
 int lefti=6;
int righti=7;
 
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
//  pinMode(2, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
pinMode(A0,INPUT);
 pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
    digitalWrite (outputA, HIGH);   // enable pull-up
  digitalWrite (outputB, HIGH);   // enable pull-up
  pinMode(6, INPUT_PULLUP);
   pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
 Serial.begin(9600);
  // Initialize Joystick Library
  Joystick.begin();

  //The steering (rheostat config)
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

// Last state of the buttons
int lastButtonState[5] = {0,0,0,0,0};

void loop() {
// int16_t values=512;
//  int value=analogRead(A0);
//  int mappedvalue=map(value,90,950,0,1023);
//  Serial.print("Value:");
//  Serial.print(value);
//  Serial.print("   MappedValue :");
//  Serial.println(mappedvalue);
//  value=mappedvalue;
// if (digitalRead(2)==LOW){
//  value=0;
//  }
//  Joystick.setXAxis(value);
int value=rotar();

 if (now-prev >1){
 
  Serial.print("value :");
  Serial.print(value);
  Serial.print("  Xvalue :");
  Serial.println(xvalue);
  prev=millis();
   gamepad();
  }
  now=millis();
  xvalue=map(value,0,revtimes,0,1023);

}
void wipers(){
  int leftv=0;
  int rightv=0;
   if(digitalRead(lefti) == LOW){
      leftv=1;
    //  yvalue=1023;
      }
       if(digitalRead(righti) == LOW){
      rightv=1;
     // yvalue=0;
      }
       Joystick.setButton(2, leftv);
    Joystick.setButton(3, rightv);
  }
void brake_accel(){
  int gasp=0;
  int brakep=0;
  int yvalue=512;
    if(digitalRead(gas) == LOW){
      gasp=1;
    //  yvalue=1023;
      }
       if(digitalRead(brake) == LOW){
      brakep=1;
     // yvalue=0;
      }
    Joystick.setButton(0, gasp);
    Joystick.setButton(1, brakep);
     Joystick.setYAxis(yvalue);
      Serial.print("GAS:");
      Serial.print(gasp);
      Serial.print(" Brake:");
      Serial.println(brakep);
  }
  void steer(){
    //  int value=analogRead(A0);
    int value=steering();
    int mappedvalue=map(value,0,1023,0,1023);
    value=mappedvalue;
    Joystick.setXAxis(value);
//     Serial.println(value);
    }
    
void gamepad(){
 steer();
  brake_accel();
  wipers();
 
//  Joystick.setYAxis(value);
}

int steering(){
    total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
 return average;
  delay(1);
  // put your main code here, to run repeatedly:
  
  }

int rotar(){
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState < aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
   if (digitalRead(outputB) != aState) { 
      if (counter <revtimes){
        counter ++;
        }
       
     } else {
      if (counter >0){
        counter --;
        }
       
     }
     //Serial.print("Position: ");
//     Serial.println(counter);
//        Serial.print("OutputA: ");
//  Serial.println(digitalRead(outputA));
//   Serial.print("Outputb: ");
//  Serial.println(digitalRead(outputB));
   } 
 

//   Serial.print("OutputA: ");
//  Serial.println(digitalRead(outputA));
//   Serial.print("Outputb: ");
//  Serial.println(digitalRead(outputB));
   
   aLastState = aState;
   return counter;
  }

