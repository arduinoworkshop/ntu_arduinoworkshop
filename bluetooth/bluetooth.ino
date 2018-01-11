/*  
 *   
 *   issues with string
 *   high latency
 *   
 *   use int for speedy data reading
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

//String incomingMsg;

//void loop() {
//  if (Serial1.available() > 0) {
//      // read the incoming byte:
//      incomingMsg = Serial1.readString();
//      Serial.println(incomingMsg);
//  }
//}


int incomingMsg;

void loop() {
  if (Serial1.available() > 0) {
      // read the incoming byte:
      incomingMsg = Serial1.read() - 48;
      Serial.println(incomingMsg);
  }
}
