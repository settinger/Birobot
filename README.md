# Birobot
(as in _Biro_ + _Robot_...the name is not finalized, let me know if you have a catchy suggestion)

Birobot is a delta-configuration pen plotter designed to be easy to build and easy to program. It can be programmed like a standard Arduino project, or you can control it by giving it a series of coordinates in an easy-to-read plain text format.

This project is developed and maintained by Sam Ettinger, an associate at Robot Sapience, Ltd., Hong Kong. This documentation is, like the project, in its infancy. Please report any questions or problems you encounter!

## Setting up the software
The Arduino code can be uploaded to Birobot from any computer with the Arduino IDE. To use the plaintext-coordinate uploader, some additional files are required.

### Arduino Installation
- [Install the Arduino IDE](https://www.arduino.cc/en/Main/Software).
- Create an Arduino project called "Birobot." Copy the files `Birobot.ino`, `helperfxn.ino`, `constants.ino`, and `path.ino`. Make sure the capitalization of the folder matches the capitalization of `Birobot.ino` (the rest don't matter).
- The file `constants.ino` contains a list of variables that correspond to physical dimensions of Birobot. These should be as accurate as possible for smooth, linear motion of the end effector.
- The file `path.ino` contains a list of waypoints that Birobot will visit in succession. These can be edited by hand, or by using `upload.bat` (see below).

### Uploading plaintext coordinates (Windows)
- Ensure you have the Arduino IDE version 1.5.6 or newer.
- Copy the file `upload.bat` to the same folder as the Arduino project.
- Create a text file named `path.txt` in the same folder as `upload.bat`. Fill it with coordinates (one coordinate per line). Take a look at the demo files for examples.
- Run `upload.bat`. This will look for a file called `path.txt`, convert the plaintext coordinates to something Arduino-readable, and upload it to the Arduino controlling Birobot.
- _TODO: write the rest of this_

### Simulator Installation
- Install Python, numpy, and matplotlib.
- _TODO: write the rest of this_

## Setting up the hardware
The Birobot design is still in progress. You can take a look at the CAD folder for a sense of how it's put together. A small shield for the Arduino UNO is included in the KiCad folder.

_TODO: write the rest of this_