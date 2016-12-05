#include <Servo.h>
#include <MultiServo.h>

//Create a chain of 9 Servos
MultiServo MServo(4);

void setup() {  

  //Initialise the chain with the pin numbers
  int pins[4] = {50,51,52,53};
  MServo.init(pins);

  //Set all to 90° for initialise all the positions
  MServo.setBrutPosAll(90.0);  
     
}

void loop() {

  //Define new position to reach
  double pos[] = {20.0,20.0,20.0,20.0};
  MServo.setPos(pos);   

  //For get a double array of the servo position
  double currentPos[MServo.size()];
  MServo.getPos(currentPos);  

  //Aproche of 0.5° to the new position
  //Servo realy start moving at this line
  MServo.updateOnce(0.5);

  //Wait 10ms
  delay(10);  
}


