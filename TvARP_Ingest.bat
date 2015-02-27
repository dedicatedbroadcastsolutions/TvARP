ECHO OFF

TITLE Tv_Automation_Recording_and_Playback Prompt

IF NOT EXIST release\TvARP_Ingest.exe (
  CLS
  ECHO release\TvARP_Ingest.exe could not be found.
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

start TvARP_Ingest.exe
exit


GOTO:EOF

:error
  ECHO.
  ECHO Press any key to exit.
  PAUSE >nul
  GOTO:EOF

