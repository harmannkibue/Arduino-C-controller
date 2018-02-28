
 #define outputA 3
 #define outputB 2
  
 int aState;
 int aLastState;  
 int now=0;
 int prev=0;
 int ppr=3000;
 int counter = ppr/2; 
 
void setup() {
  // put your setup code here, to run once:
  pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
    digitalWrite (outputA, HIGH);   // enable pull-up
  digitalWrite (outputB, HIGH);   // enable pull-up
  
   Serial.begin(9600);
    aLastState = digitalRead(outputA);
  

}

void loop() {
    int v=rotar();
//   delay(10);
  if (now-prev >10){
  Serial.println(v);
  prev=millis();
  }
  now=millis();

}

int rotar(){
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState < aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
      if (counter <ppr){
        counter ++;
        }
       
     } else {
      if (counter >0){
        counter --;
        }
       
     }
    // Serial.print("Position: ");
     //Serial.println(counter);
    // Serial.print("X Value: ");
   //  Serial.println(map(counter,0,2000,0,1023));
     
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
   return map(counter,0,2000,0,1023);
  }
