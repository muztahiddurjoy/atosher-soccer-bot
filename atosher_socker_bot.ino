#include <SoftwareSerial.h>
#include "IBT.h"

#define LED_PIN 13
#define BT_RX 3
#define BT_TX 2


//Defining motors
IBT left(4,5);
IBT right(6,7);

int speed = 50;

SoftwareSerial mySerial(BT_RX, BT_TX); // Bluetooth module HC-05 on pins 3 (RX) & 2 (TX)

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    pinMode(LED_PIN, OUTPUT);
    
    Serial.println("Initializing...");
    Serial.println("Bluetooth ready for pairing.");
}



void loop() {
    if (mySerial.available()) {

        int command = mySerial.read();
        
        if(command>=48&&command<=57){
          int rawInt = command;
          speed = map(rawInt,48,57,10,200);
          Serial.println(speed);
        }
        else if(command==70){
          forward();
        }
        else if(command=66){
          backward();
        }
        else if(command==76){
          leftward();
        }
        else if(command==82){
          rightward();
        }
        if(command!=83){
          Serial.print("Received");
          int comInt = command;
            Serial.println(comInt); // Print received byte in HEX format
        }
        
    }

}

void forward(){
  left.setRawSpeed(speed);
  right.setRawSpeed(speed);
  Serial.println("going forward");
}


void backward(){
  left.setRawSpeed(-speed);
  right.setRawSpeed(-speed);
  Serial.println("going backward");
}

void leftward(){
  left.setRawSpeed(-speed/5);
  right.setRawSpeed(speed/5);
  Serial.println("going left");
}

void rightward(){
  left.setRawSpeed(speed/5);
  right.setRawSpeed(-speed/5);
  Serial.println("going right");
}
