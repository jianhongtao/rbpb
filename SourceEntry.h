#ifndef SOURCEENTRY_H
#define SOURCEENTRY_H

#include <QString>
#include <QStringList>

// 数据源信息
class SourceEntry
{
public:
    SourceEntry();
    
public:
    QString type;
    QString mountPoint;
    QString identifier;
    QString format;
    QString formatDetails;
    int carrier;
    QString navSystem;
    QString network;
    QString country;
    double latitude;
    double longitude;
    bool nmea;
    bool solution;
    QString generator;
    QString comprEncryp;
    bool authentication;
    bool fee;
    int bitrate;
    QString misc;
};

#endif // SOURCEENTRY_H
