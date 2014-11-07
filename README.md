=========================================================================================================
TvARP - Television Automated Recording and Playback
---------------------------------------------------------------------------------------------------------
This project is designed to provide Tv automation for recording, playback, local insertion,EAS insertion,
and playlist management.  The target application is to use input streams from ASI or IP sources in to a 
D2Mux 5020 multiplexer to create an ATSC TV Channel.  Initially the feature set is restricted to just EAS
relay and insertion in to the digital domain from a standard analog EAS system.  Other features will be 
added as possible.

Current known bugs: Jitter on EAS UDP stream can be greater then 200ms which causes problems with
insertion, and audio playback.

_________________________________________________________________________________________________________
