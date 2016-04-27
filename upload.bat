:: Batch script: convert plaintext coordinates into arduino-usable .ino file

@ECHO off
SETLOCAL enabledelayedexpansion

(
  :: Create a line counter
  SET /a line=0
  :: Opening of the .ino file (with no CR)
  <nul set /p foo=float waypoints[][3] = {
  :: Load file line-by-line, commas as delimiters
  FOR /f "tokens=1,2,3 delims=," %%a IN (path.txt) DO (
    :: Increment line count
    SET /a line+=1

    SET x=%%a
    :: Remove any spaces
    SET x=!x: =!
	
    SET y=%%b
    :: Remove any spaces
    SET y=!y: =!
	
	SET z=%%c
    :: Remove any spaces
    SET z=!z: =!
    ECHO.{!x!, !y!, !z!},
  )
  :: Close the .ino file
  ECHO.};
  ECHO.
  ECHO.int arrayLength = !line!;
  ECHO.
  ECHO.float getWaypt(int m, int n^)
  ECHO.{
  ECHO.  return waypoints[m][n];
  ECHO.}
  ECHO.
  ECHO.int getArrayLength(^)
  ECHO.{
  ECHO.  return arrayLength;
  ECHO.}
)>path.ino

ENDLOCAL

"C:\Program Files (x86)\Arduino\arduino_debug.exe" --board arduino:avr:uno --upload birobot.ino