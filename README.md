# MultiServo

An arduino library for pilot group of servomotor synchronously

Still WIP /!\

The goal of this library is to fix the latence between two servo.write(angle) commande.

In fact when you do this :

servo1.write(angle1);<br>
servo2.write(angle2);

there is a delay between the first and the second move. 
It is insignificant for 2 servo but with a lot, this latence become problematic.
For solve that i use a control loop whitch move all the servo to they new position step by step.
You put all the new position in an array and the lib manages to move them from they previous position to the new at the speed you choice.

Go see the example file for see how to use it.