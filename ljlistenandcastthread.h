#ifndef LJLISTENCONNTHREAD_H
#define LJLISTENCONNTHREAD_H

#include <QtNetwork>
#include "Common.h"
#include "Log.h"
#include "NtripArg.h"
#include "Rbpb.h"
#include "NtripArg.h"
#include "CasterRouter.h"
#include "SourceTable.h"
#include "UserTable.h"
#include "Args.h"
#include "ljephdata.h"


typedef QHash<QString, NtripArg*> ClientHash;

class LjListenAndCastThread : public QThread
{
    Q_OBJECT
public:
    ~LjListenAndCastThread();

    static LjListenAndCastThread* instance();

    FDS_S                   cmdChannel() { return mChannel;}

    QList<CLIENT_INFO_S>    clientsInfo();

    void                    regCln(const QString& mp, NtripArg* arg);// 注册Client
    void                    deregCln(const QString& mp, NtripArg* arg);// 注销Client

    QList<NtripArg*>        getCln(const QString& mp=QString()) ;// 获取Client
    NtripArg*               getCln(const QString& mp, const QString& username);

    int                     clientCount(QString mnpt=QString());
    void                    castDataToClients(const QByteArray& msgData, const QString& mnpt);

public slots:
    void                    onEphDataChanged(const QString& mnptconst, const EphData& data);
    void                    onAuthReply(const CLIENT_INFO_S& reply);

protected:
    virtual void            run();

signals:
    void                    clientStateChanged(const CLIENT_INFO_S&);
    void                    authRequest(const QString& userName, const QString& password, const QString& mountPoint);
    void                    offlineNotify(const QString& userName);

private:
    LjListenAndCastThread(QObject *parent = nullptr);

    static LjListenAndCastThread*   m_instance;

    struct event_base*              eventBase;
    struct evconnlistener*          listener;
    struct event*                   evNewDataNotify;
    struct event*                   evHeartTimer;

    QHash<QString, ClientHash*>     hashCln;

    FDS_S                           mChannel;

    QMutex                          mClientMutex;

};
#endif // LJLISTENCONNTHREAD_H
