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
  // Setup by pegging all servos to 0 degrees, then let them move to 90 deg
  servoA.write(0);
  delay(1000);
  servoB.write(0);
  delay(1000);
  servoC.write(0);
  delay(2000);
  // Define current coordinate as {0.0, 0.0, zMax} or something
}

// Goofy demo: wobble in a circle
int i;
void loop()
{  
  for(i=0; i<360; i++)
  {
    xDes = 25.0*cos(i*0.01745);
    yDes = 25.0*sin(i*0.01745);
    zDes = 10.0 + 10.0*sin(3.0*i*0.01745);
    moveTo(xDes, yDes, zDes);
    delay(50);
  }
}
