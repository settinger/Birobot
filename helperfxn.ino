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
  // Choose the angle q that buckles out more
  if (qOne < qTwo)
  {
    q = (int) (qOne+0.5); // Add 0.5 to ensure proper rounding
  }
  else
  {
    q = (int) (qTwo+0.5); // Add 0.5 to ensure proper rounding
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
    // if the distance betwen current and desired points is greater than some threshold, set an interim point
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
    qADes = coord2servo(xCur, yCur, zCur, 'a', qACur);
    qBDes = coord2servo(xCur, yCur, zCur, 'b', qBCur);
    qCDes = coord2servo(xCur, yCur, zCur, 'c', qCCur);
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

int coord2servo(float x, float y, float z, char servo, int qCur)
{
  // Compute servo geometry given desired cartesian coordinate
  // Equations taken from ''The Delta Parallel Robot: Kinematics Solutions'' by Robert L. Williams II, PhD; Ohio Univ.

  // I don't know how pointers work, sorry (planning to fix this later)
  if(servo == 'a')
  {
    float E = 2*L*(y+a);
    float F = 2*L*z;
    float G = x*x + y*y + z*z + a*a + L*L + 2*y*a - l*l;
    if (((E*E + F*F - G*G) > 0) && E != G) // Ensure a solution exists
    {
      int q = quadraticSolve(E, F, G);
      q += 90; // the function quadraticSolve uses a different servo orientation; this line compensates
      return q;
    }
    else
    {
      return qCur;
    }
  }
  if(servo == 'b')
  {
    float E = -L*((sqrt(3)*(x+b)) + y + c);
    float F = 2*L*z;
    float G = x*x + y*y + z*z + b*b + c*c + L*L + 2*(b*x + c*y) - l*l;
    if (((E*E + F*F - G*G) > 0) && E != G) // Ensure a solution exists
    {
      int q = quadraticSolve(E, F, G);
      q += 90; // the function quadraticSolve uses a different servo orientation; this line compensates
      return q;
    }
    else
    {
      return qCur;
    }
  }
  else
  {
    float E = L*((sqrt(3)*(x-b)) - y - c);
    float F = 2*L*z;
    float G = x*x + y*y + z*z + b*b + c*c + L*L + 2*(c*y - b*x) - l*l;
    if (((E*E + F*F - G*G) > 0) && E != G) // Ensure a solution exists
    {
      int q = quadraticSolve(E, F, G);
      q += 90; // the function quadraticSolve uses a different servo orientation; this line compensates
      return q;
    }
    else
    {
      return qCur;
    }
  }
}
