#include <Keyboard.h>
void setup() {
  // put your setup code here, to run once:
Keyboard.begin();
pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

int state=digitalRead(2);
if(state==LOW){
  Keyboard.press(193);
}
else{
  Keyboard.release(193);
  }

delay(10);
}
