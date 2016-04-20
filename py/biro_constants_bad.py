from math import sqrt
# Geometric constants (in mm):
L = 123.0; # This assumes all upper links are the same length
l = 175.0; # This assumes all parallelograms are the same length
h = 25.0; # Parallelogram width (UNUSED)
sB = 70.0; # Length of side of base triangle
sP = 70.0; # Length of side of actuator triangle

# Personal preference constants:
distThresh = 2.0; # If a move travels more mm than this, break it up into segments
rotvel = 0.3; # servo rotational velocity (in deg/ms)
zMax = 20.0;   # farthest up (in mm) that the end effector will go
# float zMin; float xMax; float xMin; float yMax; float yMin; # eventually i should figure these out too

# Do-not-touch constants:
wB = sB/(2*sqrt(3)); # Assumes equilateral triangle
uB = 2*wB;
wP = sP/(2*sqrt(3)); # Assumes equilateral triangle
uP = 2*wP;
a = wB - uP;
b = sP/2 - (wB*sqrt(3)/2);
c = wP - wB/2;
