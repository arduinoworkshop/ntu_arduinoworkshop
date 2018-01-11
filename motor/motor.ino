// This program runs a single motor using the ardafruit motor driver shield

#define MOTOR_1   1

#include <AFMotor.h>

AF_DCMotor motor1(MOTOR_1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor1.setSpeed(200);
 
  motor1.run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  
  motor1.run(FORWARD);
  for (i=0; i<255; i++) {
    motor1.setSpeed(255);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor1.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("tock");

  motor1.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor1.setSpeed(255);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor1.setSpeed(i);  
    delay(10);
 }
  

  Serial.print("tech");
  motor1.run(RELEASE);
  delay(1000);
}
