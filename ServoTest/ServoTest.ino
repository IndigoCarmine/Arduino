#include <Servo.h>
#include <SD.h>

int Selecter = 1;
int Number = 0;

Servo servo1;
Servo servo2;
const int DegreeOfFreedom  = 2;
const int MovePerSecond = 20;

File dataFile;

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(4);

  
  if (!SD.begin(7)) {
    Serial.println(F("Card failed, or not present"));
    while(true);
  }
  dataFile = SD.open("TEST.CSV");
}

void ServoWork(int Degree){

  
  switch(Selecter){
    case 1:
      servo1.write(Degree);
      Serial.write("Servo1:");
      Serial.println(Degree);
      break;
    case 2:
      servo2.write(Degree);
      Serial.write("Servo2:");
      Serial.println(Degree);
      break;
  }
}



void loop() {

  dataFile.seek(0);
  while (dataFile.available()) {
    delay(1000/MovePerSecond);
    int inChar = dataFile.read();
    
    if (isDigit(inChar)) {
      Number = Number*10 + inChar - '0';
    }
    if(inChar == ','){      
      ServoWork(Number);
      Number = 0;
      
      Selecter++;
      }

    if (inChar == '\n') {
      ServoWork(Number);
      Number = 0;
      Selecter = 1;
      }    
  }

}

