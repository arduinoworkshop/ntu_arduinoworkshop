
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

int command = 0;
int distance;

int stage = 0;
/*
 * 0 - wait for detection
 * 1 - turn and search
 * 2 - follow
 */
int count = 0;
int countLimit = 50;
int interval = 200;
int limit = 25;

int tolerance = 3;

void loop() {

//  manual mode
  if ((Serial1.available() > 0) && (command < 10))
  {
    command = Serial1.read() - 48;

    if (command >= 10)
    {
      count = 0;
      stage = 0;
    }
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

  else if ((!Serial1.available() > 0) && (command < 10))
  {
    move_robot(0);
    
  }

  else if ((Serial1.available() > 0) || (command >= 10))
  {
    command = Serial1.read() - 48;
    distance = ultrasonic.MeasureInCentimeters();


  // update stage
    if ((stage == 0) && (distance+2*tolerance <= limit))  // stage 0 and no detection
    {
      stage = 2;
    }
    else if ((stage == 2) && (distance-2*tolerance > limit)) // lost detection while following
    {
      stage = 1;
    }
    else if ((stage == 1) && (distance-2*tolerance > limit) && (count < countLimit)) // turn and search
    {
      count += 1;
    }
    else if ((stage == 1) && (distance-2*tolerance > limit) && (count == countLimit)) // turn, search and still no detection
    {
      stage = 0;
      count = 0;
    }
    else if ((stage == 1) && (distance-2*tolerance+5 <= limit))  // turn, search and get detection
    {
      stage = 2;
      count = 0;
    }
  
    Serial.println(distance);
    Serial.println(stage);
  
  // carry out stage
    switch(stage)
    {
      case 0:
      move_robot(0);
        break;
  
      case 1:
        move_robot(3);
        break;
  
      case 2:
        if ((distance-tolerance < limit) && (distance+tolerance > limit))
        {
          move_robot(0);
        }
        else if (distance > limit)
        {
          move_robot(1);
        }
        else
        {
          move_robot(2);
        }
        break;
    }
  
    delay(interval);







    
  }

  
  
  
  
}
