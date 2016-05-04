:: Batch script: convert plaintext coordinates into arduino-usable .ino file
:: Sam Ettinger, 27 April 2016
:: Error handling and advice from user "thefeduke," DOStips forum


@ECHO off
SETLOCAL enabledelayedexpansion

(
  :: Create a line counter
  SET /a line=0
  SET   "BadLines= "
  :: Opening of the .ino file (with no CR)
  <nul set /p foo=float waypoints[][3] = {
  :: Load file line-by-line, commas or spaces as delimiters
  FOR /f "tokens=1,2,3* delims=, " %%a IN (path.txt) DO (
    :: Increment line count 
    SET /a line+=1
    IF .%%d NEQ . (
      Set "Errline[!line!]=Line '!line!' has extra information '%%d'"
      Set "BadLines=!BadLines! !Line!"
    )
    IF .%%c EQU . (
      Set "Errline[!line!]=Line '!line!' is missing third number."
      Set "BadLines=!BadLines! !Line!"
    )
    for /f "delims=-0.123456789" %%V in ("%%c") do (
      Set "Errline[!line!]=Line '!line!' has invalid character '%%V'."
      Set "BadLines=!BadLines! !Line!"
    )
    IF .%%b EQU . (
      Set "Errline[!line!]=Line '!line!' has only one number."
      Set "BadLines=!BadLines! !Line!"
    )
    for /f "delims=-0.123456789" %%V in ("%%b") do (
      Set "Errline[!line!]=Line '!line!' has invalid character '%%V'."
      Set "BadLines=!BadLines! !Line!"
    )
    for /f "delims=-0.123456789" %%V in ("%%a") do (
      Set "Errline[!line!]=Line '!line!' has invalid character '%%V'."
      Set "BadLines=!BadLines! !Line!"
    )
  ECHO.{%%a, %%b, %%c},
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
)>%Temp%\%~n0_out.txt

IF "%BadLines%" EQU " " (
  ECHO.Creating .ino file.
  Copy /Y %Temp%\%~n0_out.txt path.ino
) Else (
  ECHO.Error messages:
  :: These variables can be used for error display 
  Set "BadLines"
  Set Err
  Exit /B 1
)

ENDLOCAL

"C:\Program Files (x86)\Arduino\arduino_debug.exe" --board arduino:avr:uno --upload birobot.ino

Exit /b