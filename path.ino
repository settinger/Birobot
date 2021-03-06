float waypoints[][3] = {{0, 0, -180},
{-20, 41, -180},
{-20, 41, -230},
{-85, 38, -230},
{-85, 38, -180},
{-95, 22, -180},
{-95, 22, -230},
{-10, 22, -230},
{-10, 22, -180},
{-51, 39, -180},
{-51, 39, -230},
{-51, 2, -230},
{-51, 2, -180},
{-57, 20, -180},
{-57, 20, -230},
{-70, 8, -230},
{-94, -3, -230},
{-94, -3, -180},
{-45, 20, -180},
{-45, 20, -230},
{-30, 8, -230},
{-10, -3, -230},
{-10, -3, -180},
{-80, -43, -180},
{-80, -43, -230},
{-80, -3, -230},
{-80, -3, -180},
{-80, -3, -180},
{-80, -3, -230},
{-24, -3, -230},
{-24, -43, -230},
{-24, -43, -180},
{-80, -20, -180},
{-80, -20, -230},
{-24, -20, -230},
{-24, -20, -180},
{-80, -38, -180},
{-80, -38, -230},
{-24, -38, -230},
{-24, -38, -180},
{5, 41, -180},
{5, 41, -230},
{15, 33, -230},
{15, 33, -180},
{1, 18, -180},
{1, 18, -230},
{12, 9, -230},
{12, 9, -180},
{3, -41, -180},
{3, -41, -230},
{10, -8, -230},
{10, -8, -180},
{25, 33, -180},
{25, 33, -230},
{82, 33, -230},
{82, 33, -180},
{40, 45, -180},
{40, 45, -230},
{40, 14, -230},
{40, 14, -180},
{66, 45, -180},
{66, 45, -230},
{66, 14, -230},
{66, 14, -180},
{20, 13, -180},
{20, 13, -230},
{85, 13, -230},
{85, 13, -180},
{40, 11, -180},
{40, 11, -230},
{32, 0, -230},
{19, -11, -230},
{19, -11, -180},
{66, 11, -180},
{66, 11, -230},
{85, -12, -230},
{85, -12, -180},
{34, -3, -180},
{34, -3, -230},
{68, -3, -230},
{68, -22, -230},
{68, -22, -180},
{34, -20, -180},
{34, -20, -230},
{68, -20, -230},
{68, -20, -180},
{34, -3, -180},
{34, -3, -230},
{34, -31, -230},
{40, -40, -230},
{72, -40, -230},
{80, -30, -230},
{81, -25, -230},
{81, -25, -180},
};

int arrayLength = 94;

float getWaypt(int m, int n)
{
  return waypoints[m][n];
}

int getArrayLength()
{
  return arrayLength;
}
