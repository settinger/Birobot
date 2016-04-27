:: Batch script: convert plaintext waypoints into arduino-usable .ino file

@ECHO off
setlocal enabledelayedexpansion

:: Create a line counter
SET /a line=0

:: Load file line-by-line, commas as delimiters
(
FOR /f "tokens=1,2,3 delims=," %%a IN (path.txt) DO (
:: Check if first token exists; if not, throw error
  SET x=%%a
:: Remove any spaces
  SET x=!x: =!
:: Check if second token exists; if not, throw error
  SET y=%%b
  SET y=!y: =!
  SET z=0
  IF NOT "%%c"=="" (
    SET z=%%c
    SET z=!z: =! )
  ECHO.!x!
  ECHO.!y!
  ECHO.!z!
::  ECHO.%%a,%%b,%%c
)
)>newpath.txt