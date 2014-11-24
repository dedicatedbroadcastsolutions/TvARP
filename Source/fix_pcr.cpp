#include "fix_pcr.h"
#include "windows.h"
fix_pcr::fix_pcr(QObject *parent) :
    QObject(parent)
{
    newFile     = fopen (NEW_FILE,     "wb");           // VlC Fixed Output File
    deltaPcrPerPkt = (CONSTANT/K_BIT_RATE);              // CONSTANT = 8*PKT_SIZE*27000;  PKT_SIZE = 188; 27000 is Clock/1000
    lastCalcPcrPkt = 0;
    lastVidPcrPkt  = 1;
    lastAudPcrPkt  = 1;
    gNewFilePkt  = 0;
    gStop        = false;
    buildNullPkt ();
    buildVidPktZeros();
    QHostAddress stream_addr;
    stream_addr.setAddress("239.0.0.220");
    qint16 stream_port = 1234;
    //#define K_BIT_RATE         4000           // 5000  4400 In kbps    //2875
    stream_vid = new stream(stream_addr , stream_port , K_BIT_RATE , PKTS_PER_DGRAM , PKT_SIZE , this );
    connect(stream_vid,SIGNAL(done_with_stream()),this,SIGNAL(kill_me()));
}

fix_pcr::~fix_pcr()
{
    qDebug("closing fix_pcr");
    fclose (origFile);
    fclose(newFile);
}

void fix_pcr::vlcFix_Send (char *vlcOutputFile)  // playStopSec in Seconds since Epoch
{
    qDebug()<< "vlcFix_Send = " << QThread::currentThreadId();
    gStop = false;
    qDebug("vlcFix_Send");
    origFile  = fopen (vlcOutputFile, "rb");

    int nullsNeeded;    int nonNulls;                                   // Total Nulls Needed; Total Non Nulls Needed
    int nullLoop_Ratio; int nonNullLoop_Ratio; int nulls_nonNullsLoop;  // Ratios of Null and NonNull Spacing

 // read file and output packets until first pcr is found.
    findFirstPcrLoc (origFile);

    while (!gStop)
    {
        getNulls_Pkts_Ratios_CalcPcr_LookaheadToNextOldPcr (origFile,
                            nullsNeeded,    nonNulls,   nulls_nonNullsLoop,   // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                            nullLoop_Ratio, nonNullLoop_Ratio);               // Ratios of Null and NonNull(Pkt) Spacing

        long long filePcr = getPcr();

        outputNulls_Pkts_ByRatio_CalcPcr (origFile,
                            nullsNeeded,    nonNulls,    nulls_nonNullsLoop,   // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                            nullLoop_Ratio, nonNullLoop_Ratio);                // Ratios of Null and NonNull(Pkt) Spacing
    }
    stream_vid->send_udp_packet();
}

void fix_pcr::findFirstPcrLoc (FILE* origFile)
{
    int  pktsRead               = 0;
    int  pid                    = 0;
    int  adaptFlag              = 0;
    int  adaptLength            = 0;
    int  pcrFlag                = 0;

    while(!gStop)                                              // Loop reading pkts looking for first PCR
    {
        pktsRead = fread(buffer, PKT_SIZE, 1, origFile);   // End File when no more data (pktsRead <= 0) in origFile

        if (pktsRead <= 0) {                                 // Check for End of VLC Output when Reading Pkts (188 bytes) from File
            printf ("1-First Read Dry \r");
            Sleep(2000);                                    // Try Again to Read Pkts after 1000 ms wait for VLC to write more
            pktsRead = fread(buffer, PKT_SIZE, 1, origFile);     // End File when no more data (pktsRead <= 0) in origFile
            if (pktsRead <= 0) {                             // Check Again for End of VLC Output File
                progEnd = "1-VLC Output File Ended";         // VLC Output File Ended by "End of File" at Location 1
                gStop = true;
                break;                                       // Stop Reading Orig File (VLC Output File)
            }
        }

        writeOutput (buffer);                                   // Write Pkt as it is read

        //===== Find Next PCR
        // Check for Video PID
        pid  = (buffer[1] & 0x1F) << 8;                // 0x1F = 0001 1111;  TEI, Pusi, Transport Priority, PID Hi 5 bits
        pid |=  buffer[2];                             // OR in Low 8 bits

        if (pid != VLC_VID_PID)
        {
            continue;                                  // Not Video PID, so loop ahead to next Pkt
        }
        // Check if Adapt Flag is present
        adaptFlag = buffer[3] & 0x20;	     // 0x20 = 0010 0000 = Scramble 00;  Adapt 10, Payload 01;  Continuity Count

        if (adaptFlag != 0x20)
        {
            continue;                                 // Adaptation Field is Not present, so loop ahead to next Pkt
        }
        // Check that Adaptation Field is large enough to hold PCR Flag and PCR
        adaptLength = buffer[4];

        if (adaptLength < 7)
        {
            continue;
        }
        // Check if Pcr Flag is present
        pcrFlag = buffer[5] & 0x10;			          // 0x10 = 0001 0000   3 Flags, PCR Flag, 4 Flags

        if (pcrFlag != 0x10)
        {
            continue;                                 // Pcr Flag is Not present, so loop ahead to next Pkt
        }
        break;                                        // Vid PID, Adaptatation Flag, Pcr Flag has all been found in this packet
    }
    // Next PCR has been fouind

    //===== Pcr Found, so Read Pcr and Continuity Count from File to global pcr value
    pcr   = getPcr();							      // Set first PCR (Get PCR from Global buffer[] )
    vidCc = buffer[3] & 0x0F;                        // Get first Continuity Count from Global buffer[]
}

void fix_pcr::getNulls_Pkts_Ratios_CalcPcr_LookaheadToNextOldPcr (FILE* origFile,
                            int &nullsNeeded,    int &nonNulls,   int &nulls_nonNullsLoop,       // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                            int &nullLoop_Ratio, int &nonNullLoop_Ratio)                         // Ratios of Null and NonNull(Pkt) Spacing
{
    int  pktsRead               = 0;
    int  pid                    = 0;
    int  adaptFlag              = 0;
    int  adaptLength            = 0;
    int  pcrFlag                = 0;
    long currPktLocInFile       = 0;
    long long calcLookAheadPcr  = 0;

    // Look ahead is from last PCR Pkt which is "lastCalcPcrPkt" (Gl;obal)

    int  pktCountToLookAheadPcr = 0;                       // Start counting Pkt distance (in lookahead) since last Pcr Pkt

    //===== Save current Packet Location
    currPktLocInFile = ftell (origFile);               // Save current file location to come back to after this Look-Ahead

    while(!gStop)                                              // Loop reading pkts looking for next (lookahead) PCR
    {
        //----- Get next Packet (Look-ahead
        pktsRead = fread(buffer, PKT_SIZE, 1, origFile);   // End File when no more data (pktsRead <= 0) in origFile

        //----- End File when no more data (pktsRead <= 0) in origFile
        if (pktsRead <= 0)
        {
            // VLC Output File Ended by "End of File" at Location 1b.
            progEnd = "1b-VLC Output File Ended in \"get Nulls Lookahead\" ";
            gStop = true;
            fseek (origFile, currPktLocInFile, SEEK_SET);           // Restore from beginning (SEEK_SET) of File to position before this Look-ahead
            return;                                       // Stop Reading Orig File (VLC Output File)
        }
        pktCountToLookAheadPcr++;
        //===== Find Next PCR
        // Check for Video PID
        pid  = (buffer[1] & 0x1F) << 8;                // 0x1F = 0001 1111;  TEI, Pusi, Transport Priority, PID Hi 5 bits
        pid |=  buffer[2];                             // OR in Low 8 bits
        if (pid != VLC_VID_PID)
        {
            continue;                                  // Not Video PID, so loop ahead to next Pkt
        }
        // Check if Adapt Flag is present
        adaptFlag = buffer[3] & 0x20;	     // 0x20 = 0010 0000 = Scramble 00;  Adapt 10, Payload 01;  Continuity Count
        if (adaptFlag != 0x20)
        {
            continue;                                 // Adaptation Field is Not present, so loop ahead to next Pkt
        }
        // Check that Adaptation Field is large enough to hold PCR Flag and PCR
        adaptLength = buffer[4];
        if (adaptLength < 7)
        {
            continue;
        }
        // Check if Pcr Flag is present
        pcrFlag = buffer[5] & 0x10;			          // 0x10 = 0001 0000   3 Flags, PCR Flag, 4 Flags

        if (pcrFlag != 0x10)
        {
            continue;                                 // Pcr Flag is Not present, so loop ahead to next Pkt
        }
        break;                                        // Vid PID, Adaptatation Flag, Pcr Flag has all been found in this packet
    }// End of Search Loop (while (1))
    // Next PCR has been fouind

    //===== Pcr Found, now read it from File
    long long lookAheadPcrInFile = getPcr();	  // Get PCR from Global buffer[]

    //===== Calculate look-ahead Pcr
    calcLookAheadPcr = pcr + (long long)(deltaPcrPerPkt * pktCountToLookAheadPcr); // Calc lookAhead (trial) Pcr

    //===== Calculate pcrDelta  (Amount that calculated Pcr will be off, for which Nulls are required
    long long pcrDelta = (calcLookAheadPcr - lookAheadPcrInFile);

    //===== Calculate Nulls Needed, Non Nulls, and Loop Ratios
    nullsNeeded       = (int) (((10 * (-pcrDelta) / deltaPcrPerPkt) + 5) /10);  // Round Up using integer arithmetic
    // nullsNeeded       = (int)  ((-pcrDelta / (long long) deltaPcrPerPkt));
    if (nullsNeeded <= 0)
    {
        nullsNeeded  = 1;
    }
    nonNulls          = pktCountToLookAheadPcr;

    nullLoop_Ratio    = 10 * nullsNeeded / (nullsNeeded + nonNulls);             // Values will be between 0..9 (or 10 is one is 0)
    nonNullLoop_Ratio = 10 * nonNulls    / (nullsNeeded + nonNulls);             // Values will be between 0..9 (or 10 is one is 0) (Sum is always 9 or 10)

    nulls_nonNullsLoop = (nullsNeeded + nonNulls) / (nullLoop_Ratio + nonNullLoop_Ratio) ;
    if (nulls_nonNullsLoop >= 1)
    {
        nulls_nonNullsLoop -= 1;                                                 // Leave Loop 1 short to insure full Null count is output
    }
    //===== Restore previous current Packet Location (Before this Look-ahead)
    fseek (origFile, currPktLocInFile, SEEK_SET);           // Restore from beginning (SEEK_SET) of File to position before this Look-ahead
}

void fix_pcr::outputNulls_Pkts_ByRatio_CalcPcr (FILE* origFile,
                            int &nullsNeeded,    int &nonNulls,   int &nulls_nonNullsLoop,       // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                            int &nullLoop_Ratio, int &nonNullLoop_Ratio)                         // Ratios of Null and NonNull(Pkt) Spacing
{
    int nullsOut    = 0;                    // Null Pkt Count in Group
    int nonNullsOut = 0;                    // Non Null Pkt Count in Group

    // Output Group of Nulls and Non Nulls in Ratio to each other, such as 4/5, 7/2, 8/1, 9/0, etc.
    for (int i = 0; i < nulls_nonNullsLoop; i++)
    {                                       // ... Some Null Pkts, and Some Non Null Pkts
        for (int i = 0; i < nullLoop_Ratio; i++)
        {                  // Output Nulls in Ratio to Non Nulls
            if (nullsOut >= nullsNeeded)
            {
                break;                      // Break current "for loop"
            }
            nullsOut++;                     // Count Null Pkts Output in Group
            gNewFilePkt++;                  // Count Pkts (of any kind) Before Output for PCR Calc
            writeOutput (nullPkt);          // Write 1 Null Packet to Output
        }
        for (int i = 0; i < nonNullLoop_Ratio; i++)
        {               // Output Nulls in Ratio to Non Nulls
            if (nonNullsOut >= nonNulls)
            {
                break;                      // Break current "for loop"
            }
            nonNullsOut++;                  // Count Non Null Pkts Output in Group
            gNewFilePkt++;                  // Count Pkts (of any kind) Before Output for PCR Calc
            outputPkt (origFile);           // Write 1 Non Null Packet to Output
            if (gStop == true)
            {
                return;
            }
            //TEST printf ("nonNullsOut = %d \n", nonNullsOut);
        }
        if ( (nullsOut >= nullsNeeded) && (nonNullsOut >= nonNulls) )
        {
            break;                          // Break outer "for loop"
        }
    }

    // Output Remainder Nulls from Group; (Diff between Nulls Needed and nullPkt Count)
    for (int i = nullsOut; i < nullsNeeded; ++i)
    {
        nullsOut++;
        gNewFilePkt++;                                     // Count Pkts (of any kind) Before Output for PCR Calc
        writeOutput (nullPkt);							   // Write 1 Null Packet to Output
    }

    // Output Remainder Non Nulls from Group; (Diff between Non Nulls Expected and nonNullPkt Count)
    for (int i = nonNullsOut; i < nonNulls; ++i)
    {
        nonNullsOut++;
        gNewFilePkt++;                                     // Count Pkts (of any kind) Before Output for PCR Calc
        outputPkt (origFile);                              // Write 1 Non Null Packet to Output
        if (gStop == true)
        {
            return;
        }
    }
}

void fix_pcr::outputPkt(FILE* origFile)
{
    int pid       = 0;
    int bytesRead = 0;

    while ( (bytesRead = readPktIntoBuffer(origFile)) > 0)          // Buffer is Global
    {                                                            // Read untill Time, EOF, Stopped by Keypress
        //  gOrigFilePkt++;
        pid  = (buffer[1] & 0x1F) << 8;                 // 0x1F = 0001 1111;  TEI, Pusi, Transport Priority, PID Hi 5 bits
        pid |=  buffer[2];                              // OR in Low 8 bits

        if (pid == 0x1FFF)
        {                            // Any Null PIDs in Output of VLC (Normally there aren't any)
            // No Continuity Count in Null
            break;
        }
        if (pid == 0x00)
        {                             // PAT
            break;
        }
        if (pid == VLC_PMT_PID)
        {                       // PMT
            break;
        }
        if (pid == VLC_VID_PID)
        {
            processVidPkt ();                   // Also checks for "Stop"; Adds new PCR whenever it can (approx 40 ms)
            break;
        }
        if (pid == VLC_AUD_PID)
        {
            processAudPkt ();                   // Also sets DialNorm;  Adds new PCR whenever it can (approx 40 ms)
            break;
        }
    }

    if (bytesRead > 0)
    {
        // Do not Output Pkt if No Pkt has been read (bytesRead <= 0)
        writeOutput (buffer);
    }
    else
    {
        progEnd = "1c-VLC Output File Ended in \"output Pkt()\" of \"outputNulls_Pkts_ByRatio...\" ";
    }
    return;                                             // One Pkt from VLC Output File has been Output
}

int fix_pcr::readPktIntoBuffer(FILE * origFile)
{
    int  pktsRead    = 0;
    //----- Get next Packet
    pktsRead = fread(buffer, PKT_SIZE, 1, origFile); // End File when no more data (pktsRead <= 0) in origFile
    if (pktsRead <= 0)
    {
        progEnd = "1-VLC Output File Ended";         // VLC Output File Ended by "End of File" at Location 1
        return (pktsRead);
    }
    return (pktsRead);
}

void fix_pcr::buildNullPkt (void)
{
   nullPkt[0] = 0x47;
   nullPkt[1] = 0x1f;
   nullPkt[2] = 0xff;
   nullPkt[3] = 0x10;
   for (int i=4; i <= 187; i++)  {
       nullPkt[i] = 0xff;					    // Fill nullPkt[ ]; 0..187
   }
   return;
}

void fix_pcr::buildVidPktZeros (void)
{
   vidPktZeros[0] = 0x47;
   vidPktZeros[1] = (VLC_VID_PID >> 8) & 0x1F;       // Set 0001 1111	TEI, Pusi, Transport Priority; PID hi 5 bits
   vidPktZeros[2] =  VLC_VID_PID & 0xFF;             // Set PID lo bits
   vidPktZeros[3] = 0x10;                        // Set Payload Flag 0001 0000;  Scramble 00, Adapt 10, Payload 01; Continuity Count
   for (int i=4; i <= 187; i++)  {
       vidPktZeros[i] = 0x00;					 // Fill Vid Zeros Pkt[ ]; 0..187
   }
   return;
   // Note for adding Continuity Count to vidPktZeros[3]
   // int cc = 0 &0x0F; Countinuity Count (limit to 0...15)
   // buffer[3] |= cc &0x0F;
}

long long fix_pcr::getPcr(void)							 // Get PCR from Global "buffer[]"
{
  long long basePcr;
  long long extnPcr;

  basePcr =                   buffer[6];	     // base PCR bits 33..26
  basePcr = (basePcr << 8) +  buffer[7];         // base PCR bits 25..18
  basePcr = (basePcr << 8) +  buffer[8];         // base PCR bits 17..10
  basePcr = (basePcr << 8) +  buffer[9];         // base PCR bits  9.. 2
  basePcr = (basePcr << 1) + (buffer[10]>>7);    // base PCR bit   1  is in hi bit of "Padding Byte"  1000 0000

  extnPcr =                   buffer[10] & 0x01; // 9th ext bit in low bit of "Padding Byte"  0000 0001
  extnPcr = (extnPcr << 8) +  buffer[11] ;       // 8 ext bits in last PCR byte

  return ((300*basePcr) + extnPcr);
}

void fix_pcr::stampPcr (long long pcrValue, int jitter, unsigned char pkt[] )
{
    pcrValue += jitter;                    // may be +1, -1  Or  0 if D=0 in #defines

    long long basePcr = pcrValue / 300;    // Base PCR (90 kHz Tick-rate -- Same rate as PTS/DTS)
    long long extnPcr = pcrValue % 300;	   // Extended (Extn) PCR  (27 MHz Tick-rate)

    pkt [6]  = (basePcr >> 25) & 0xff;	   // base PCR bits 33..26
    pkt [7]  = (basePcr >> 17) & 0xff;     // base PCR bits 25..18
    pkt [8]  = (basePcr >>  9) & 0xff;     // base PCR bits 17..10
    pkt [9]  = (basePcr >>  1) & 0xff;     // base PCR bits  9.. 2

    pkt [10]  = (basePcr <<  7) & 0x80;    // base PCR bit  1  into hi bit of "Padding Byte"  1000 0000
    pkt [10] |=  0x7e;					   // 0x7e = 0111 1110; Set Padding to 0111 1110
    pkt [10] |= (extnPcr >>  8) & 0x01;    // 9th ext bit in low bit or "Padding Byte"

    pkt [11] =   extnPcr & 0xff;		   // 8 ext bits in last PCR byte
}

void fix_pcr::removePcr(unsigned char pkt[])
{
    pkt [5] &= 0xef;       // 0xef = 1110 1111 Set PCR Flag to 0 in Adapt Fld Flags; (3 Flags, PCR Flag;  4 Flags)

    pkt [6]  = 0x00;	   // base PCR bits 33..26
    pkt [7]  = 0x00;       // base PCR bits 25..18
    pkt [8]  = 0x00;       // base PCR bits 17..10
    pkt [9]  = 0x00;       // base PCR bits  9.. 2

    pkt [10] = 0x00;       // base PCR bit  1  into hi bit of "Padding Byte"  1000 0000
                           // 0x7e = 0111 1110; Set Padding to 0111 1110
                           // 9th ext bit in low bit or "Padding Byte"

    pkt [11] =  0x00;	   // 8 ext bits in last PCR byt
}

bool fix_pcr::processVidPkt()
{
    int adaptFlag   = 0;
    int adaptLength = 0;
    int pcrFlag     = 0;
    int pusiFlag    = 0;
    int skip        = 0;

    //===== Pkt is VIDEO PID, Process it to: Restamp or Remove PCR depending on current Pcr Interval,

    // Check this Pkt for beginning of Vid Frame to Show PTS Delay
    pusiFlag = buffer[1] & 0x40;                   // 0x40 = 0100 0000	TEI, Pusi, Transport Priority; PID hi 5 bits
    if (pusiFlag == 0x40)
    {                        // First TS Packet of Video Frame
        skip = 0;
        adaptFlag = buffer[3] & 0x20;	           // 0x20 = 0010 0000;  Scramble 00, Adapt 10, Payload 01,
        if (adaptFlag == 0x20)
        {
            adaptLength = buffer[4];
            skip = 1 + adaptLength;                // Adaptation Field Present
        } else
        {                                   // PES location is just past Adaptation Field
            skip = 0;
        }
        showPtsDelay(skip, "Vid");
    }
    //----- Restamp or Remove PCR, if PCR Flag

    // Check if Adapt Flag is present
    adaptFlag = buffer[3] & 0x20;	     // 0x20 = 0010 0000 = Scramble 00, Adapt 10, Payload 01;  Continuity Count
    //TEST  printf ("Adapt Flag Byte = %2.2X; Adapt Flag = %x \n", buffer[3], adaptFlag);
    if (adaptFlag != 0x20)
    {
        return (false);                  // Not adaptation Field Pkt, so nothing to process
    }

    // Check if Adaptation Length is big enough to hold PCR Flag and PCR
    adaptLength = buffer[4];

    if (adaptLength < 7)
    {
        return (false);
    }

    // Check if Pcr Flag is present
    pcrFlag   = buffer[5] & 0x10;		 // 0x10 = 0001 0000   3 Flags, PCR Flag, 4 Flags
    //TEST  printf ("PCR Flag Byte = %2.2x; PCR Flag = %x \n", buffer[5], pcrFlag);
    if (pcrFlag != 0x10)
    {
        return (false);                  // No Pcr Flag, so nothing to process
    }

    //----- VLC_VID_PID with Adapt Field Contains PCR, so Remove or Re-stamp the PCR; (File Pkt Contains PCR)
    pcr += ( deltaPcrPerPkt * (gNewFilePkt - lastCalcPcrPkt) );  // Update PCR Value

    if ((gNewFilePkt - lastVidPcrPkt) < VID_PCR_PKT_INTVL)
    {   // Interval Too Soon, So Remove PCR from Pkt
        //TEST printf ("---> (Remove) Delta PCR Pkt = %d \n", (gNewFilePkt - lastVidPcrPkt) );
        //TEST printf ("Pkt: %d; Remove PCR;  Vid Pcr Pkt Intvl: %d \n", gNewFilePkt, (gNewFilePkt - lastVidPcrPkt) );
        removePcr(buffer);
    }else
    {                                                   // Interval OK, so Re-Stamp PCR in Pkt
        lastVidPcrPkt = gNewFilePkt;                   // to calculate Vid PID PCR Interval
        dVid *= (-1);                                       // dVid (+/-) = intentional Video PCR jitter to check analyzer;  dVid is Global
        stampPcr (pcr, dVid, buffer);
    } // End: ((gNewFilePkt - lastVidPcrPkt) < VID_PCR_PKT_INTVL)

    lastCalcPcrPkt = gNewFilePkt;                       // to calculate PCR Value

    //----- Check if PCR can be added to VLC_VID_PID Pkt; (Pkt Has Adapt Field that does Not contain PCR)
    if (adaptFlag == 0x20 && pcrFlag != 0x10)
    {
        if (buffer[4] >= 7)
        {                                          // Check that there room in this Adaption Field for PCR
            if ((gNewFilePkt - lastVidPcrPkt) >= VID_PCR_PKT_INTVL)
            {      // Check that PCR Interval > 25 ms)
                    bool valueOkFlag = true;
                for (int i=6; i<=11; i++)
                {
                    if (! (buffer[i] == 0x00 || buffer[i] == 0xff) )
                    { // Check that orig values are 0x00 or 0xFF before stamping PCR
                        valueOkFlag = false; 						   // Signal when Value not 0x00 or 0xFF
                    }
                } // End: for (int i=6; i<=11; i++)
                if (valueOkFlag  == true)
                {
                    // OK to Add PCR to this Video Pkt; (There is no PCR in this File Pkt)
                    buffer[5] |= 0x10;                                      // Set PCR Flag; Adapt Field Flags = 0x10 = 0001 0000; PCR Flag = 0001 0000

                    pcr += ( deltaPcrPerPkt * (gNewFilePkt - lastCalcPcrPkt) ); // Update PCR Value

                    lastCalcPcrPkt = gNewFilePkt;               // to calculate PCR Value
                    lastVidPcrPkt  = gNewFilePkt;               // to calculate Vid PID PCR Interval
                    dVid *= (-1);                           // dVid (+/-) = intentional Video PCR jitter to check analyzer

                    stampPcr (pcr, dVid, buffer);
                }
            }
        }
    }  // End: if (adaptFlag == 0x20 && pcrFlag != 0x10)

    if ((gNewFilePkt - lastVidPcrPkt) > (4 * VID_PCR_PKT_INTVL))
    {
        //Print Info if Pcr is late
        //TEST  printf ("--> Pkt = %d,  Delta PCR Pkt = %d \n", gNewFilePkt, gNewFilePkt - lastVidPcrPkt);
    }

    //----- Write buffer after "return" for this (VLC_VID_PID) Pkt
    //		after...
    //      ...Re-stamping PCR, Or
    //		...Removing PCR (PCR Interval Too Soon), Or
    //      ...Adding   PCR (PCR Interval Long enough)

    return (false);
}

//---------------------------------------------------- End of Process Video Pkt -------------------------------------------

//====================================================== Process Audio Pkt ===============================================
bool fix_pcr::processAudPkt ()
{
    int adaptFlag  = 0;
    int pusiFlag   = 0;
    int adaptLength = 0;
    int skip        = 0;

    //===== Pkt is AUDIO PID, Process it to: Set DialNorm. Add PCRs to Aud Pkts

    //----- Check this Pkt for beginning of Aud Frame to Show PTS Delay
    pusiFlag = buffer[1] & 0x40;                     // 0x40 = 0100 0000	TEI, Pusi, Transport Priority; PID hi 5 bits
    if (pusiFlag == 0x40)
    {                          // First TS Packet of VLC Audio Frame
        skip = 0;
        adaptFlag = buffer[3] & 0x20;	               // 0x20 = 0010 0000;  Scramble 00, Adapt 10, Payload 01,
        if (adaptFlag == 0x20)
        {
            adaptLength = buffer[4];
            skip = 1 + adaptLength;                  // Adaptation Field Present, get Adaptation Field Length; Add in AF Length Byte
        } else
        {
            skip = 0;
        }
        showPtsDelay(skip, "Aud");

    }  // End:  if (pusiFlag == 0x40)

    //----- Add PCR to this VLC_AUD_PID when Possible,
    // Check Adapt Fld Flag, Adpt Fld Size, Time since last Aud PCR, Pkt Values [6...11] Ready for PCR (0x00 or 0xFF)
    adaptFlag = buffer[3] & 0x20;	                      // 0x20 = 0010 0000 = Scramble 00, Adapt 10, Payload 01;  Continuity Count
    if (adaptFlag == 0x20)
    {                              // Check that there is Adapt Field (Place for PCR)
        if (buffer[4] >= 7)
        {	                          // Check that there is room in this VLC Pkt for PCR
            if ( (gNewFilePkt - lastAudPcrPkt) > AUD_PCR_PKT_INTVL)
            {   //Check that PCR Interval > ~25ms at 6000 kbps
                bool valueOkFlag = true;
                for (int i=6; i<=11; i++)
                {                           // buffer[6] ... buffer[11]
                    if ( !(buffer[i] == 0x00 || buffer[i] == 0xff) )
                    { // Check that Orig values in Pkt PCR area are 0x00 or 0xFF
                        valueOkFlag = false; 					   // Signal when Value not 0x00 or 0xFF
                    }
                } // End: for(int i=6; i<=11; i++)
                if (valueOkFlag == true)
                {
                    // OK to Add PCR to this Audio Pkt
                    pcr += ( deltaPcrPerPkt * (gNewFilePkt - lastCalcPcrPkt) ); // Update PCR Value
                    lastCalcPcrPkt = gNewFilePkt;
                    lastAudPcrPkt  = gNewFilePkt;

                    buffer[5] |= 0x10;                                 // Set PCR Flag; Adapt Field Flags = 0x10 = 0001 0000; PCR Flag = 1
                    dAud *= (-1);                                      // dAud (+/-) = intentional Audio PCR jitter to check analyzer
                    stampPcr (pcr, dAud, buffer);
                }
            }
        }
    }  // End: if (adaptFlag == 0x20)

    // Write VLC_AUD_PID after "return" after...
    // ...Setting DialNorm, And
    // ...Adding PCR
    return (false);
}

void fix_pcr::showPtsDelay (int offset, char* av)
{
    long long pts      = 0;
    long long ptsDelay = 0;

    pcr += ( deltaPcrPerPkt * (gNewFilePkt - lastCalcPcrPkt) );    // Update PCR Value
    lastCalcPcrPkt = gNewFilePkt;                                  // Update last Calc Pcr Pkt
    pts = getPts(offset);
    ptsDelay = pts - (pcr/300);                                    // offset = (0) or (AdaptFieldLength + 1)
}

long long fix_pcr::getPts(int offset)              // offset = (0) or (AdaptFieldLength + 1)
{
     long long ptsFound;

     ptsFound =                   ((buffer[offset + 13] & 0x0e) >> 1);      // bits 33..31
     ptsFound = (ptsFound << 8) +  (buffer[offset + 14] & 0xff)      ;      // bits 30..24
     ptsFound = (ptsFound << 7) + ((buffer[offset + 15] & 0xfe) >> 1);      // bits 23..16
     ptsFound = (ptsFound << 8) +  (buffer[offset + 16] & 0xff)      ;      // bits 15..9
     ptsFound = (ptsFound << 7) + ((buffer[offset + 17] & 0xfe) >> 1);      // bits  8..1
     return (ptsFound);
}

void fix_pcr::writeOutput (unsigned char pkt[] )
{
    int pktsWritten = 0;
    stream_vid->make_udp_packet( QByteArray((char*)pkt,PKT_SIZE) );
    pktsWritten = fwrite(pkt, PKT_SIZE, 1, newFile);		// Write pkt to newFile
    return;
}
