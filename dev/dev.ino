
#include <AFMotor.h>
#include <Ultrasonic.h>

// declare pins
#define MOTOR_L   3
#define MOTOR_R   4
#define ULTRASONIC_SENSOR   42

//  create objects
Ultrasonic ultrasonic(ULTRASONIC_SENSOR);
AF_DCMotor motorL(MOTOR_L);
AF_DCMotor motorR(MOTOR_R);

void setup() {
  
  // set up bluetooth TX RX
  Serial1.begin(9600);

//  set up serial monitor
  Serial.begin(9600);
  
}

void move_robot(int cmd)
{
  switch(cmd)
  {
//    stop
    case 0:
      motorL.setSpeed(0);
      motorR.setSpeed(0);
      break;

//    move forward
    case 1:
      motorL.run(FORWARD);
      motorR.run(FORWARD);
      motorL.setSpeed(255);
      motorR.setSpeed(255);
      break;

//    move backward
    case 2:
      motorL.run(BACKWARD);
      motorR.run(BACKWARD);
      motorL.setSpeed(255);
      motorR.setSpeed(255);
      break;

//  turn left
    case 3:
      motorL.run(BACKWARD);
      motorR.run(FORWARD);
      motorL.setSpeed(255);
      motorR.setSpeed(255);
      break;

//  turn right
    case 4:
      motorL.run(FORWARD);
      motorR.run(BACKWARD);
      motorL.setSpeed(255);
      motorR.setSpeed(255);
      break;    
  }
}

int command;
int distance;

void loop() {
  if (Serial1.available() > 0)
  {
    command = Serial1.read() - 48;
    distance = ultrasonic.MeasureInCentimeters();

//  stop when obstacle detected
//    if (distance < 20)
//    {
//      command = 0;
//    }
    
    
    Serial.println(command);
    Serial.println(distance);

    move_robot(command);
    
    delay(45);
  }

  else
  {
    move_robot(0);
    
  }
  
  
  
  
}
