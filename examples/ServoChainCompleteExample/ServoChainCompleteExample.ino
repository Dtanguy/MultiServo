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
  //OR if special positions are nessesary
  double initPos[4] = {90.0,100.0,158.3,126.2};
  MServo.setBrutPos(initPos);

  //Connect serial port
  Serial.begin(9600);  

  //Print the connected servo
  Serial.print("Servo Connected to pin : ");
  for(int i=0; i<MServo.size(); i++){
    Serial.print(MServo.getServo(i).getPin());
    Serial.print(" ");
  }
  Serial.println("");
     
}

void loop() {

  //Print there position (the print are with a 100 coef for avoid parsing double
  //For example 153.56° will be print as 15356
  Serial.print("Servo actual position : ");
  Serial.println(MServo.getPosChar());

  //Define new position to reach
  double pos[] = {20.0,20.0,20.0,20.0};
  MServo.setPos(pos); 
  //Or change only one motor goal
  MServo.setPos(0, 90.0);
  //Or increase one motor goal
  MServo.setPosAdd(0, 90.0);
  //Or decrease one motor goal
  MServo.setPosAdd(0, -90.0);

  //For get a double array of the servo position
  double currentPos[MServo.size()];
  MServo.getPos(currentPos);  

  //Aproche of 0.5° to the new position
  //Servo realy start moving at this line
  MServo.updateOnce(0.5);

  //Wait 10ms
  delay(10);  
}


