float waypoints[][3] = {{0, 0, -110},
{-95, 0, -110},
{-95, 0, -150},
{-95, 0, -110},
{-95, 45, -110},
{-95, 45, -150},
{-95, 45, -110},
{0, 45, -110},
{0, 45, -150},
{0, 45, -110},
{85, 45, -110},
{85, 45, -150},
{85, 45, -110},
{85, 0, -110},
{85, 0, -150},
{85, 0, -110},
{0, 0, -110},
{0, 0, -150},
{0, 0, -110},
{-95, -0, -110},
{-95, -0, -150},
{-95, -0, -110},
{-95, -43, -110},
{-95, -43, -150},
{-95, -43, -110},
{0, -43, -110},
{0, -43, -150},
{0, -43, -110},
{85, -43, -110},
{85, -43, -150},
{85, -43, -110},
{85, 0, -110},
{85, 0, -150},
{85, 0, -110},
{0, 0, -110},
{0, 0, -150},
{0, 0, -110},
{-95, 0, -110},
{-95, 0, -150},
{-95, 0, -110},
{-95, 45, -110},
{-95, 45, -150},
{-95, 45, -110},
{0, 45, -110},
{0, 45, -150},
{0, 45, -110},
{85, 45, -110},
{85, 45, -150},
{85, 45, -110},
{85, 0, -110},
{85, 0, -150},
{85, 0, -110},
{0, 0, -110},
{0, 0, -150},
{0, 0, -110},
{-95, -0, -110},
{-95, -0, -150},
{-95, -0, -110},
{-95, -43, -110},
{-95, -43, -150},
{-95, -43, -110},
{0, -43, -110},
{0, -43, -150},
{0, -43, -110},
{85, -43, -110},
{85, -43, -150},
{85, -43, -110},
{85, 0, -110},
{85, 0, -150},
{85, 0, -110},
{0, 0, -110},
{0, 0, -150},
{0, 0, -110}};

int arrayLength = 73;

float getWaypt(int m, int n)
{
  return waypoints[m][n];
}

int getArrayLength()
{
  return arrayLength;
}
