#include <Servo.h>
#include <Math.h>
int servoPinA = 9; // The servo in the back
int servoPinB = 10; // The next servo clockwise
int servoPinC = 11; // The last servo
Servo servoA;
Servo servoB;
Servo servoC;

int qACur; int qBCur; int qCCur; // Current servo angle for servos A, B, C
int qADes; int qBDes; int qCDes; // Desired servo angle for servos A, B, C
float xCur; float yCur; float zCur; // Current end-effector position
float xDes; float yDes; float zDes; // Desired end-effector position

void setup()
{
  servoA.attach(servoPinA);
  servoB.attach(servoPinB);
  servoC.attach(servoPinC);
  // Setup by aiming all servos to point outward
  servoA.write(45);
  delay(1000);
  servoB.write(45);
  delay(1000);
  servoC.write(45);
  delay(1000);
  servoA.write(90);
  delay(1000);
  servoB.write(90);
  delay(1000);
  servoC.write(90);
  delay(1000);
  // Define current coordinate as {0.0, 0.0, zMax} or something
  xCur = 0; yCur = 0; zCur = -130;
  // Go through waypoints:
  int i;
  for(i=0; i<getArrayLength(); i++)
  {
    xDes = getWaypt(i, 0);
    yDes = getWaypt(i, 1);
    zDes = getWaypt(i, 2);
    moveTo(xDes, yDes, zDes);
    delay(500);
  }
}

void loop()
{  
}
