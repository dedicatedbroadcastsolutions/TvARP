ECHO OFF

TITLE Tv_Automation_Recording_and_Playback Prompt

IF NOT EXIST Windows_Binaries\TvARP_Sample_Build_Directory\release\TvARP_EAS_beta.exe (
  CLS
  ECHO Windows_Binaries\TvARP_Sample_Build_Directory\release\TvARP_EAS_beta.exe could not be found.
  GOTO:error
)

CD Windows_Binaries\TvARP_Sample_Build_Directory\release || GOTO:error
PROMPT $G
CLS
SET PATH=%CD%;%PATH%
ECHO.
ECHO Current directory is now: "%CD%"
ECHO The bin directory has been added to PATH
ECHO.

start TvARP_EAS_beta.exe
exit


GOTO:EOF

:error
  ECHO.
  ECHO Press any key to exit.
  PAUSE >nul
  GOTO:EOF

