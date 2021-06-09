#ifndef NTRIPARG_H
#define NTRIPARG_H

#include <QtCore>
#include "stdafx.h"

class NtripArg : public QObject
{
    Q_OBJECT
public:
    NtripArg(QObject* parent=nullptr);

public:
    int             port;
    int             recvPktState;
    int             pktLen;
    int             userType;
    int             ver;
    int             reqType;
    int             flowCount;
    QString         ip;
    QString         mountPoint;
    QString         username;
    QString         password;
    QString         loginTime;
    QString         logoutTime;
    QString         expireTime;
    bufferevent*    bev;
    int             authState;
};

#endif // NTRIPARG_H
