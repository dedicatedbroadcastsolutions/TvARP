#ifndef FIX_PCR_H
#define FIX_PCR_H

#include <QUdpSocket>
#include <QObject>
#include "QString"
#include "stream.h"

class fix_pcr : public QObject
{
    Q_OBJECT
public:
    explicit fix_pcr(QObject *parent = 0);
    ~fix_pcr();
    stream *stream_vid;
signals:
    void kill_me();
public slots:
    void vlcFix_Send (char *vlcOutputFile);

private slots:
    int  readPktIntoBuffer(FILE* origFile);
    bool processVidPkt();
    bool processAudPkt();

    void outputPkt(FILE* origFile);
    void outputNulls_Pkts_ByRatio_CalcPcr (FILE*origFile,
                                int &nullsNeeded,    int &nonNulls,  int &nulls_nonNullsLoop,        // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                                int &nullLoop_Ratio, int &nonNullLoop_Ratio);                        // Ratios of Null and NonNull(Pkt) Spacing
    void stampPcr  (long long pcrValue, int jitter, unsigned char pkt[]);
    void removePcr (unsigned char pkt[]);
    void writeOutput (unsigned char pkt[]);
    void buildNullPkt     (void);
    void buildVidPktZeros (void);
    long long getPcr(void);
    void showPtsDelay (int offset, char* av);
    long long getPts(int offset);
    void findFirstPcrLoc (FILE* origFile);

    void getNulls_Pkts_Ratios_CalcPcr_LookaheadToNextOldPcr (FILE* origFile,
                                int &nullsNeeded,    int &nonNulls,   int &nulls_nonNullsLoop,       // Total Nulls Needed, Total Non Nulls (Pkts) Needed, Sum
                                int &nullLoop_Ratio, int &nonNullLoop_Ratio);                        // Ratios of Null and NonNull(Pkt) Spacing
private:
    #define D                  1		      // 0 Leave PCR accurate; 1 Add some Jitter  (Approx +/- 37 nSec)
    #define K_BIT_RATE         3000           // 5000  4400 In kbps    //2875

    #define VID_PCR_INTVL_MS   27 //27 //22 // 25       // mSec between Vid PCRs   Prior = 31 ms
    #define AUD_PCR_INTVL_MS   20 //22 // 25	   // mSec between Aud PCRs   prior = 29 ms

    #define NEW_FILE           "c:\\3abn\\Z_FixedVLC.ts"

    #define VLC_PMT_PID        0x40			  // 64 dec
    #define VLC_VID_PID        0x44			  // 68 dec
    #define VLC_AUD_PID        0x45			  // 69 dec

    #define PKT_SIZE           188
    #define PKTS_PER_DGRAM     7
    #define CONSTANT           8*PKT_SIZE*27000	 // 27 Meg Hz Clock/1000  (1504 * 27000)

    #define VID_PCR_PKT_INTVL  (VID_PCR_INTVL_MS * K_BIT_RATE/8/PKT_SIZE)
    #define AUD_PCR_PKT_INTVL  (AUD_PCR_INTVL_MS * K_BIT_RATE/8/PKT_SIZE)

    int gNewFilePkt   = 0;                              // To Calculate PCR Value (by counting packets of nulls and pkts)
    bool gStop        = false;

    unsigned char  buffer[PKT_SIZE];
    unsigned char  nullPkt[PKT_SIZE];
    unsigned char  vidPktZeros[PKT_SIZE];

    FILE  *newFile ;//,*testFileOut;
    int  lastCalcPcrPkt;                                    // To Calculate PCR Value (by counting packets of nulls and pkts)
    int  lastVidPcrPkt;                                     // To Calculate Vid PCR Interval
    int  lastAudPcrPkt;                                     // To Calculate Aud PCR Interval
    int  patCc			= 0;                                // Continuity Count for PAT Pkts
    int  pmtCc          = 0;                                // Continuity Count for PMT Pkts
    int  vidCc          = 0;                                // Continuity Count for Video Pkts
    int  audCc          = 0;                                // Continuity Count for Audio Pkts
    int	 dVid = D;                                          // Alter video PCR, +(up) and -(down) make Jitter
    int	 dAud = D;                                          // Alter audio PCR, +(up) and -(down) make Jitter
    int  deltaPcrPerPkt = 0;
    QString  progEnd    = "";
    int gFrames_CueToI = 0;
    long long pcr         = 0;
    long long gLastPcrVal = 0;
    FILE *origFile;
    //char *vlcOutputFile ;
    char *file;
};

#endif // FIX_PCR_H

