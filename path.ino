float waypoints[][3] = {{0, 0, -150},
{0, 20, -160},
{70, -20, -150},
{0, 0, -100},
{0, 0, -150},
{0, 0, -100},
{0, 0, -150},
{0, 0, -100},
{0, 0, MISSING_VALUE},
{0, 0, -100},
{0, 0, -150},
{0, 0, -100},
{0, 0, -150},
{0, 0, -100},
{0, 0, -150},
{0, 0, -100},
{0, 0, -150},
};

int arrayLength = 17;

float getWaypt(int m, int n)
{
  return waypoints[m][n];
}

int getArrayLength()
{
  return arrayLength;
}
