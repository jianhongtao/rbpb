#ifndef NETWORKENTRY_H
#define NETWORKENTRY_H

#include <QString>
#include <QStringList>

// 网络服务信息
class NetworkEntry
{
public:
    NetworkEntry();
    
public:
    QString type;
    QString identifier;
    QString opName;
    QString authentication;
    QString fee;
    QString webNet;
    QString webStr;
    QString webReg;
    QString misc;
};

#endif // NETWORKENTRY_H
