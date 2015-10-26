=========================================================================================================
TvARP - Television Automated Recording and Playback
---------------------------------------------------------------------------------------------------------
This project is designed to provide Tv automation for recording, playback, local insertion,EAS insertion,
and playlist management.  The target application is to use input streams from ASI or IP sources in to a 
D2Mux 5020 multiplexer to create an ATSC TV Channel.  

Now supports continuous back to back streaming of pre encoded files and ad insertion via the D2Mux based on a schedule file C:\Remote\Videos\insert.sch.  Mux debug and ring detect can happen either on seperate comports or the same port.  Other features will be added as possible.

To compile, open the .pro project file for the appropriate module with Qt Creator.  Make sure to set the
build directory to be the sample build directory, and set the working directory to the release subfolder.
These settings can be found in the projects tab under build and run respectively.
_________________________________________________________________________________________________________
