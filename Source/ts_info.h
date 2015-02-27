#ifndef TS_Info_H
#define TS_Info_H

#include <QObject>
#include "QString"
#include <QStringList>
struct PCR {
    quint64 base;
    quint64 remainder;
    quint64 composite;
};
struct Elementry_Stream {
    int type;
    int pid;
};

struct Program {
    QString program_name;
    int program_number;
    int pcr_pid;
    int pmt_pid;
    QList<Elementry_Stream> stream;
};

struct Transport_Stream {
    bool failed;
    int kbitrate;   // Mux Bitrate in kbps
    quint64 pcr_period_ms;      //  ms between PCR
    QList<Program> program_list;         //  PIDs contained in Mux
    QStringList info;
};

class TS_Info : public QObject
{
    Q_OBJECT
public:
    explicit TS_Info(QObject *parent = 0);
    ~TS_Info();
    Transport_Stream ts_properties;
    bool kill;
signals:
    void status( QString );
public slots:
    Transport_Stream process_file(QString source_filename) ;
    PCR getPCR(QByteArray packet);

private slots:

private:
    unsigned char  ts_packet[188];

    long long pcr;
};

#endif // TS_Info_H

