// Calibration details: Pick nine points and identify the approximate z-deviation at each point

// X limits
float xMin = -95.0;
float xMax = 85.0;

// Y limits
float yMin = -43.0;
float yMax = 45.0;

// By running a calibration script, figure out roughly how high Z is above where it's expected to be:
float zNW = 5; // "northwest," i.e. upper-left corner
float zN = 10; // top center
float zNE = 4;
float zW = 5;
float zC = 15; // center center
float zE = 1;
float zSW = 5;
float zS = 3;
float zSE = 0;

float Q11; float Q12; float Q21; float Q22;
float x1; float x2; float y1; float y2;

float zDev(float x, float y) {
  // Identify quadrant:
  if (x >= 0 & y >= 0) {
    x1 = 0;
    x2 = xMax;
    y1 = 0;
    y2 = yMax;
    Q11 = zC;
    Q12 = zN;
    Q21 = zE;
    Q22 = zNE;
  }
  if (x < 0 & y >= 0) {
    x1 = xMin;
    x2 = 0;
    y1 = 0;
    y2 = yMax;
    Q11 = zW;
    Q12 = zNW;
    Q21 = zC;
    Q22 = zN;
  }
  if (x < 0 & y < 0) {
    x1 = xMin;
    x2 = 0;
    y1 = yMin;
    y2 = 0;
    Q11 = zSW;
    Q12 = zW;
    Q21 = zS;
    Q22 = zC;
  }
  else {
    x1 = 0;
    x2 = xMax;
    y1 = yMin;
    y2 = 0;
    Q11 = zS;
    Q12 = zC;
    Q21 = zSE;
    Q22 = zE;
  }
  // Standard bilinear interpolation terms:
  float zD = (((Q11*(y2-y) + Q12*(y-y1))*(x2-x)) + ((Q21*(y2-y) + Q22*(y-y1))*(x-x1)))/((x2-x1)*(y2-y1));
  return zD;
}

