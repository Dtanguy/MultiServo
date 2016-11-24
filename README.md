# MultiServo

An arduino librarie for pilot group of servomotor synchronously

Still WIP /!\

I made this librarie for fix the latence between two servo.write(angle) commande.

In fact when you do this :

servo1.write(angle1);
servo2.write(angle2);

there is a delay between the first and the second move. 
It is insignificant for 2 servo but with a lot, this latence become problematic.
For solve that i use a control loop whitch move all the servo to they new position step by step.
You put all the new position in an array and the lib manages to move them from they previous position to the new at the speed you choice.

A simple example of how to use it :

//Just include the libraries
#include <MultiServo.h>

//Create a chain of 9 Servos
MultiServo MServo(9);

void setup() {  

  //Initialise the chain with the pin numbers of the servo
  int pins[] = {0,1,2,3,4,5,6,7,8};
  MServo.init(pins);

  //Initialise the postion of earch servo
  double initPos[] = {90,90,90,90,90,90,90,90,90};
  MServo.setInstantPos(initPos);
  
}

void loop() {

  //Set a new position 
  double posToGo[] = {0.4, 10.8, 20.3, 30.7, 40.2 ,50, 60.6, 70.1, 80.5};
  MServo.setPos(posToGo);

  //Get the actual position
  double posNow[MServo.getNbServo()];
  MServo.getPos(posNow);

  //Go smooth and synchron to the setted position at the speed and precision pass in parameter 
  MServo.update(10, 0.1);
  
}
