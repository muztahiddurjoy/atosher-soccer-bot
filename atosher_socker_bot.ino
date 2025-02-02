#include <SoftwareSerial.h>
#include "IBT.h"

#define LED_PIN 13
#define BT_RX 3
#define BT_TX 2

#define E1 4
#define E2 7
#define E3 8
#define E4 11
// #define E7 4
// #define E8 4



//Defining motors
IBT left(5,6);  
IBT right(9,10);

int speed = 150;

SoftwareSerial mySerial(BT_RX, BT_TX); // Bluetooth module HC-05 on pins 3 (RX) & 2 (TX)

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    pinMode(LED_PIN, OUTPUT);
    
    pinMode(E1,OUTPUT);
    pinMode(E2,OUTPUT);
    pinMode(E3,OUTPUT);
    pinMode(E4,OUTPUT);
    
    Serial.println("Initializing...");
    Serial.println("Bluetooth ready for pairing.");

  digitalWrite(E1,HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
}



void loop() {
    if (mySerial.available()) {
        char command = mySerial.read();
        if(command!='S'){
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
          case 'I':
            frontRight();
            break;
          case 'G':
            frontLeft();
            break;
          
        }
        

        command = '\0';  // Reset after processing        
    }
     

}

void forward(){
  left.setRawSpeed(speed);
  right.setRawSpeed(speed);
}


void backward(){
  left.setRawSpeed(-speed);
  right.setRawSpeed(-speed);
}

void leftward(){
  left.setRawSpeed(-speed);
  right.setRawSpeed(speed);
}

void frontLeft(){
  left.setRawSpeed(speed/2);
  right.setRawSpeed(speed);
}

void rightward(){
  left.setRawSpeed(speed);
  right.setRawSpeed(-speed);
}

void frontRight(){
  left.setRawSpeed(speed);
  right.setRawSpeed(speed/2);
}

void stop(){
  left.setRawSpeed(0);
  right.setRawSpeed(0);
}
