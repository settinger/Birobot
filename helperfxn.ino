int quadraticSolve(float E, float F, float G)
{
  // Two angle solutions
  float tOne = (-F + sqrt(E*E + F*F - G*G))/(G - E);
  float tTwo = (-F - sqrt(E*E + F*F - G*G))/(G - E);
  float qOne = 2*atan(tOne)*180/M_PI;
  float qTwo = 2*atan(tTwo)*180/M_PI;
  int q;
  // Shift values so they are between 0 and 180 degrees
  if (qOne < 0) {qOne += 180;}
  if (qTwo < 0) {qTwo += 180;}
  // Choose the angle q that exists or buckles out more
  if ((qOne < qTwo) || (isnan(qTwo) && !isnan(qOne)))
  {
    q = (int) (qOne+0.5); // Add 0.5 to ensure proper rounding
  }
  if ((qTwo < qOne) || (isnan(qOne) && !isnan(qTwo)))
  {
    q = (int) (qTwo+0.5); // Add 0.5 to ensure proper rounding
  }
  else // zero solutions, this shouldn't happen
  {
    q = 90;
  }
  return q;
}

void moveTo(float xDes, float yDes, float zDes)
{
  boolean doneMoving = false;
  float divFactor;
  float dist;
  int allotTime;
  while(!doneMoving)
  {
    // if the distance betwen current and desired points is greater than 2mm, set an interim point
    dist = sqrt(sq(xDes-xCur) + sq(yDes-yCur) + sq(zDes-zCur));
    if(dist > distThresh)
    {
      divFactor = dist/distThresh;
      xCur = xCur + (xDes-xCur)/divFactor;
      yCur = yCur + (yDes-yCur)/divFactor;
      zCur = zCur + (zDes-zCur)/divFactor;
    }
    else
    {
      xCur = xDes;
      yCur = yDes;
      zCur = zDes;
      doneMoving = true;
    }
    // Compute servo angles
    qADes = coord2servo(xCur, yCur, zCur, 'a');
    qBDes = coord2servo(xCur, yCur, zCur, 'b');
    qCDes = coord2servo(xCur, yCur, zCur, 'c');
    // write servo angles
    servoA.write(qADes);
    allotTime = (int) abs(qACur - qADes)*rotvel; // How long it takes to move
    delay(allotTime);
    qACur = qADes;
    servoB.write(qBDes);
    allotTime = (int) abs(qBCur - qBDes)*rotvel; // How long it takes to move
    delay(allotTime);
    qBCur = qBDes;
    servoC.write(qCDes);
    allotTime = (int) abs(qCCur - qCDes)*rotvel; // How long it takes to move
    delay(allotTime);
    qCCur = qCDes;
  }
}

int coord2servo(float x, float y, float z, char servo)
{
  // Compute servo geometry given desired cartesian coordinate
  // Equations taken from ''The Delta Parallel Robot: Kinematics Solutions'' by Robert L. Williams II, PhD; Ohio Univ.
  float EA = 2*L*(y+a);
  float EB = -L*((sqrt(3)*(x+b)) + y + c);
  float EC = L*((sqrt(3)*(x-b)) - y - c);
  
  float F = 2*L*z;
  
  float GA = x*x + y*y + z*z + a*a + L*L + 2*y*a - l*l;
  float GB = x*x + y*y + z*z + b*b + c*c + L*L + 2*(b*x + c*y) - l*l;
  float GC = x*x + y*y + z*z + b*b + c*c + L*L + 2*(c*y - b*x) - l*l;
  
  int qA = quadraticSolve(EA, F, GA);
  int qB = quadraticSolve(EB, F, GB);
  int qC = quadraticSolve(EC, F, GC);
  // I don't know how pointers work, sorry
  if(servo == 'a') {return qA;}
  if(servo == 'b') {return qB;}
  else {return qC;}
}
