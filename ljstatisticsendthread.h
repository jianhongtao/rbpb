#ifndef LJSTATISTICSENDTHREAD_H
#define LJSTATISTICSENDTHREAD_H


#include <QtCore>
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
#include "ljlistenandcastthread.h"

class MonitorArg : public QObject
{
    Q_OBJECT
public:
    MonitorArg(QObject* parent=nullptr);

public:
    int                 port;
    QString             ip;
    struct bufferevent* bev;
};

class LjStatisticSendThread : public QThread
{
    Q_OBJECT
public:
    static LjStatisticSendThread* instance();
    ~LjStatisticSendThread();

    void    addMonitor(bufferevent* bev, MonitorArg* monitor);
    void    removeMonitor(bufferevent* bev);

    FDS_S   cmdChannel() { return mChannel;}

public slots:
    void    sendEphData(const EPH_DATA_S& data);
    void    sendEphData(MonitorArg* monitor, const QString& mnpt, const EphData& data);

    void    sendClientData(const CLIENT_INFO_S& data);
    void    sendClientData(MonitorArg* monitor, const CLIENT_INFO_S& data);

    void    sendLogInfo(const LOG_INFO_S& log);
    void    sendLogInfo(MonitorArg* monitor, const LOG_INFO_S& log);

    void    onClientStateChanged(const CLIENT_INFO_S&);
    void    onEphDataChanged(const QString& mnpt, const EphData& data);

protected:
    virtual void run();

private:
    static LjStatisticSendThread* m_instance;

    LjStatisticSendThread(QObject *parent = nullptr);

    QMap<bufferevent*, MonitorArg*> m_monitors;
    struct event_base*              eventBase;
    struct evconnlistener*          listener;
    struct event*                   evNewDataNotify;

    FDS_S                           mChannel;
};

#endif // LJSTATISTICSENDTHREAD_H
