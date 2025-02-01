#include <SoftwareSerial.h>
#include "IBT.h"

#define LED_PIN 13
#define BT_RX 3
#define BT_TX 2

#define E1 4
#define E2 7
#define E3 8
#define E4 11
#define E5 12
#define E6 13
// #define E7 4
// #define E8 4



//Defining motors
IBT left(5,6);
IBT right(9,10);

int speed = 50;

SoftwareSerial mySerial(BT_RX, BT_TX); // Bluetooth module HC-05 on pins 3 (RX) & 2 (TX)

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    pinMode(LED_PIN, OUTPUT);
    
    pinMode(E1,OUTPUT);
    pinMode(E2,OUTPUT);
    pinMode(E3,OUTPUT);
    pinMode(E4,OUTPUT);
    pinMode(E5,OUTPUT);
    pinMode(E6,OUTPUT);
    


    Serial.println("Initializing...");
    Serial.println("Bluetooth ready for pairing.");
}



void loop() {
  digitalWrite(E1,HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
  digitalWrite(E5,HIGH);
  digitalWrite(E6,HIGH);
  
    if (mySerial.available()) {

        char command = mySerial.read();
        if(command!='S'){
          Serial.print("Received");
          
            Serial.println(command); // Print received byte in HEX format
        }
        if(command>=48&&command<=57){
          int rawInt = command;
          speed = map(rawInt,48,57,10,255);
          Serial.println(speed);
        }

        switch(command){
          case 'F':
            forward();
            break;
          case 'S':
            stop();
            break;
          case 'B':
            backward();
            break;
          case 'L':
            leftward();
            break;
          case 'R':
            rightward();
            break;
          
        }
        // else if(command==70){
        //   forward();
        // }
        // else if(command=66){
        //   // backward();
        // }
        // else if(command==76){
        //   leftward();
        // }
        // else if(command==82){
        //   rightward();
        // }
        
          
        
        
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

void stop(){
  left.setRawSpeed(0);
  right.setRawSpeed(0);
}
