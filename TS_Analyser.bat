ECHO OFF

TITLE Tv_Automation_Recording_and_Playback Prompt

IF NOT EXIST release\TS_Analyser.exe (
  CLS
  ECHO release\TS_Analyser.exe could not be found.
  GOTO:error
)

CD release || GOTO:error
PROMPT $G
CLS
SET PATH=%CD%;%PATH%
ECHO.
ECHO Current directory is now: "%CD%"
ECHO The bin directory has been added to PATH
ECHO.

start TS_Analyser.exe
exit


GOTO:EOF

:error
  ECHO.
  ECHO Press any key to exit.
  PAUSE >nul
  GOTO:EOF

