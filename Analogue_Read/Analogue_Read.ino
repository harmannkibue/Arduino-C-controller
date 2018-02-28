const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;
int gas=8;
int brake=9;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(gas,INPUT_PULLUP);
pinMode(brake,INPUT_PULLUP);

 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}


void brake_steer(){
  int gasp=0;
  int brakep=0;
    if(digitalRead(gas) == LOW){
      gasp=1;
      }
       if(digitalRead(brake) == LOW){
      brakep=1;
      }
      Serial.print("GAS:");
      Serial.print(gasp);
      Serial.print(" Brake:");
      Serial.println(brakep);
  }
void loop() {
  brake_steer();
//  int value=analogRead(A0);
//  int mappedvalue=map(value,0,1023,0,1023);
//  Serial.print("Value:");
//  Serial.print(value);
//  Serial.print("   MappedValue :");
//  Serial.println(mappedvalue);
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

  //delay(1);
  // put your main code here, to run repeatedly:

}


