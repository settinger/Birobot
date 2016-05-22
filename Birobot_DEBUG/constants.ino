// Construction properties
boolean servosToTheLeft = false; // looking from above, with arm A pointing at you, is servo A to the left of arm A?

// Geometric constants (in mm):
float L = 123; // This assumes all upper links are the same length
float l = 175; // This assumes all parallelograms are the same length
float h = 25; // Parallelogram width (UNUSED)
float sB = 70; // Length of side of base triangle
float sP = 70; // Length of side of actuator triangle

// Personal preference constants:
float distThresh = 0.5; // If a move travels more mm than this, break it up into segments
float rotvel = 0.3; // servo rotational velocity (in deg/ms)
float zMax = -20.0;   // farthest up (in mm) that the end effector will go (UNUSED)
float zMin; float xMax; float xMin; float yMax; float yMin; // eventually i should figure these out too

// Do-not-touch constants:
float wB = sB/(2*sqrt(3)); // Assumes equilateral triangle
float uB = 2*wB;
float wP = sP/(2*sqrt(3)); // Assumes equilateral triangle
float uP = 2*wP;
float a = wB - uP;
float b = sP/2 - (wB*sqrt(3)/2);
float c = wP - wB/2;
