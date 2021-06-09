#ifndef CASTERENTRY_H
#define CASTERENTRY_H

#include <QString>
#include <QStringList>

// 播发者信息
class CasterEntry
{
public:
    CasterEntry();
    
public:
    QString type;
    QString host;
    int port;
    QString identifier;
    QString opName;
    bool nmea;
    QString country;
    double latitude;
    double longitude;
    QString fallbackHost;
    int fallbackPort;
    QString misc;
};

#endif // CASTERENTRY_H
