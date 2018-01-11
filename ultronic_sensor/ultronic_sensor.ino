#include <Ultrasonic.h>

#define ULTRASONIC_SENSOR   8
#define DELAY_INTERVAL      10


Ultrasonic ultrasonic(ULTRASONIC_SENSOR);

void setup() {
  Serial.begin(9600);
 
}

int distance;

void loop() {


  distance = ultrasonic.MeasureInCentimeters(); 
  Serial.println(distance);
  delay(DELAY_INTERVAL);
}
