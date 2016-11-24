#include <MultiServo.h>

//Create a chain of 9 Servos
MultiServo MServo(9);

void setup() {  

  //Initialise the chain with the pin numbers
  int pins[] = {0,1,2,3,4,5,6,7,8};
  MServo.init(pins);

  //Initialise the postion of earch servo
  double initPos[] = {90,90,90,90,90,90,90,90,90};
  MServo.setInstantPos(initPos);
  
}

void loop() {

  //Set a new position
  double posToGo[] = {0.4,10.8,20.3,30.7,40.2,50,60.6,70.1,80.5};
  MServo.setPos(posToGo);

  //Get the actual position
  double posNow[MServo.getNbServo()];
  MServo.getPos(posNow);

  //Go smooth and synchron to this position at the speed and precision pass in parameter 
  MServo.update(10,0.1);
  
}
