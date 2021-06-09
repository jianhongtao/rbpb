#ifndef RBPB_H
#define RBPB_H

#include <QString>
#include <QThread>
#include <QByteArray>
#include <string>
#include <QHash>
#include <QList>
#include <QVector>

#include "Queue.h"
#include "Common.h"

using std::string;

class LjRcvDataThread;
class LjListenAndCastThread;
class LjEphDataFactory;
class LjStatisticSendThread;
class LjAuthThread;

typedef QVector<CONNARG_S*> CONN_VECT;

class Rbpb
{
public:
    Rbpb();
    ~Rbpb();

public:
    void        StartCaster();

    static bool IsConnected() {return bConnected;}
    static void SetConnected() {bConnected = true;}
    static void ResetConnected() {bConnected = false;}

    static int  GetConnPos() {return pos;}
    static int  RestConnPos() {pos=0;}
    static int  IncConnPos() {++pos;}

private:

    //label connection to get data from rbpc
    static  bool                     bConnected;

    //lable connect to which rbpc , reserved in connection vector
    static int                       pos;

    LjRcvDataThread*        m_rcvDataThread;
    LjListenAndCastThread*  m_listenAndCastThread;
    LjEphDataFactory*       m_ephDataFactory;
    LjStatisticSendThread*  m_statisticThread;
    LjAuthThread*           m_authThread;
};

#endif // RBPB_H
