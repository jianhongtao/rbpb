#include "ljstatisticsendthread.h"


void onMonitorBevEvent(struct bufferevent* bev, short what, void* arg)
{
    MonitorArg* monitor = (MonitorArg*)arg;

    char type;
    char buf[256]={0};
    if(what & BEV_EVENT_EOF)
    {
        type = 'R';
        sprintf(buf, "LjStatisticSendThread:: tcp connect %s:%d has closed",
                qPrintable(monitor->ip), monitor->port);

        printf("ntrip client closed\n");
    }
    else if(what & BEV_EVENT_ERROR)
    {
        type = 'W';
        sprintf(buf, "LjStatisticSendThread:: tcp connect %s:%d has error",
                qPrintable(monitor->ip), monitor->port);
    }
    else if(what & (BEV_EVENT_TIMEOUT | BEV_EVENT_READING))
    {
        type = 'W';
        sprintf(buf, "LjStatisticSendThread:: tcp connect %s:%d reading timeout",
                qPrintable(monitor->ip), monitor->port);
    }
    else if(what & (BEV_EVENT_TIMEOUT | BEV_EVENT_WRITING))
    {
        type = 'W';
        sprintf(buf, "LjStatisticSendThread:: tcp connect %s:%d writing timeout",
                qPrintable(monitor->ip), monitor->port);
    }
    else
    {
        type = 'W';
        sprintf(buf, "LjStatisticSendThread:: tcp connect %s:%d unknown error",
                qPrintable(monitor->ip), monitor->port);
    }

    Log::send(type, buf);

    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    thread->removeMonitor(bev);

    bufferevent_free(bev);
    delete monitor;
}


void onMonitorWrite(struct bufferevent* bev, void* arg)
{
    MonitorArg* monitor = (MonitorArg*)arg;
}

void sendHistory(struct bufferevent* bev, void* arg)
{
    MonitorArg* monitor = (MonitorArg*)arg;
    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    ////
    QMap<QString, LjEphData*>  allEph = LjEphDataFactory::instance()->getEphData();
    foreach(QString mnpt, allEph.keys())
    {
        LjEphData* ljEphData = allEph.value(mnpt);

        QVector<EphData>    ephDataList = ljEphData->getAllEph();
        foreach(EphData ephData, ephDataList)
        {
            thread->sendEphData(monitor, mnpt, ephData);
        }
    }

    QList<CLIENT_INFO_S> clients = LjListenAndCastThread::instance()->clientsInfo();
    foreach(CLIENT_INFO_S info, clients)
    {
        thread->sendClientData(monitor, info);
    }

//    bufferevent_setcb(bev, 0, onMonitorWrite, onMonitorBevEvent, monitor);
}

void onMonitorRequest(struct bufferevent* bev, void* arg)
{
    MonitorArg* monitor = (MonitorArg*)arg;
    monitor->bev = bev;

    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    thread->addMonitor(bev, monitor);

    struct evbuffer* evb = bufferevent_get_input(bev);
    int  totalLen = evbuffer_get_length(evb);

    size_t len;
    while(totalLen>0)
    {
        char* line;
        line = evbuffer_readln(evb, &len, EVBUFFER_EOL_CRLF);

        free(line);

        totalLen -= len;

        if(len ==0)
            break;

        //Log::send('R', line);
    }

    char buf[512];
    len = sprintf(buf,"ICY 200 OK\r\n");

    evb = bufferevent_get_output(bev);
    evbuffer_add(evb, buf, len);

    bufferevent_setcb(bev, 0, sendHistory, onMonitorBevEvent, monitor);
}


// Call this function when new connections comes
void processNewMonitorConnection(struct evconnlistener* listener,
             evutil_socket_t fd,
             struct sockaddr* addr,
             int len,
             void* arg)

{
    char buf[256];
    sprintf(buf, "LjStatisticSendThread:: Accept tcp connect from %s:%d",
            inet_ntoa(((struct sockaddr_in*)addr)->sin_addr),
            ntohs(((struct sockaddr_in*)addr)->sin_port));
    Log::send('R', buf);

    struct event_base* base = evconnlistener_get_base(listener);
    struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev)
    {
        Log::send('W', "LjStatisticSendThread:: Statistic send thread cant create new connection");
        return;
    }

    MonitorArg* monitorArg = new MonitorArg();
    monitorArg->ip = inet_ntoa(((struct sockaddr_in*)addr)->sin_addr);
    monitorArg->port = ntohs(((struct sockaddr_in*)addr)->sin_port);

    bufferevent_setcb(bev, onMonitorRequest, 0, onMonitorBevEvent, monitorArg);

//    struct timeval tv;
//    tv.tv_sec  = Args::getInstance()->value("tcpTimeout").toInt();
//    tv.tv_usec = 0;
//    bufferevent_set_timeouts(bev, &tv, 0);

    bufferevent_enable(bev, EV_READ|EV_WRITE);
}

// process listener errors
void processMonitorListenError(struct evconnlistener* listener, void* arg)
{
    // report error
    int err = EVUTIL_SOCKET_ERROR();
    char buf[64];
    sprintf(buf, "Error occurs on the listener: %s", evutil_socket_error_to_string(err));
    Log::send('E', buf);

    // exit event loop
    struct event_base *base = evconnlistener_get_base(listener);
    event_base_loopexit(base, 0);
}

void castDataToMonitors(const EPH_DATA_S& data)
{
    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    thread->sendEphData(data);
}

void castLogToMonitors(const LOG_INFO_S& log)
{
    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    thread->sendLogInfo(log);
}

void castClientToMonitors(const CLIENT_INFO_S& data)
{
    LjStatisticSendThread* thread = LjStatisticSendThread::instance();

    thread->sendClientData(data);
}

void onMessageNotify(evutil_socket_t sock, short event, void *arg)
{
    MSG_INFO_S msgInfo;
    read(sock, &msgInfo, MSG_INFO_LEN);

    switch (msgInfo.type)
    {
        case msg_data_eph:
        {
            castDataToMonitors(msgInfo.ephData);
        }
        break;
        case msg_data_client_info:
        {
            castClientToMonitors(msgInfo.clientInfo);
        }
        break;
        case msg_data_log:
        {
            castLogToMonitors(msgInfo.logInfo);
        }
        break;

        case msg_cmd_quit:
            event_base_loopexit((struct event_base*)arg, NULL);
            break;

        default:
            Log::send('W', "broadcast data thd received unknown notify");
            break;
    }
}



MonitorArg::MonitorArg(QObject* parent)
    :QObject(parent)
{
    port = 0;
    ip   = QString();
    bev  = nullptr;
}



LjStatisticSendThread* LjStatisticSendThread::m_instance=nullptr;

LjStatisticSendThread::LjStatisticSendThread(QObject *parent)
    : QThread(parent)
{
    eventBase       = nullptr;
    listener        = nullptr;
    evNewDataNotify = nullptr;
}

LjStatisticSendThread::~LjStatisticSendThread()
{
    if(listener)
        evconnlistener_free(listener);
    if(evNewDataNotify)
        event_free(evNewDataNotify);
    if(eventBase)
        event_base_free(eventBase);
}


LjStatisticSendThread* LjStatisticSendThread::instance()
{
    if(!m_instance)
        m_instance = new LjStatisticSendThread();

    return m_instance;
}

void  LjStatisticSendThread::addMonitor(bufferevent* bev, MonitorArg* monitor)
{
    m_monitors.insert(bev, monitor);
}

void  LjStatisticSendThread::removeMonitor(bufferevent* bev)
{
    m_monitors.remove(bev);
}

void LjStatisticSendThread::run()
{
    eventBase = event_base_new();
    if (!eventBase)
    {
        Log::send('E', "cast data thread create event loop object error");
        return;
    }

    int fds[2];
    if (pipe(fds))
    {
        Log::send('E',"LjStatisticSendThread:: pipe open error------");
        return;
    }

    mChannel.rfd = fds[0];
    mChannel.wfd = fds[1];

    QString host  = "0.0.0.0";
    int  port     = Args::getInstance()->value("moniPort", 9000).toInt();

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family       = AF_INET;
    addr.sin_addr.s_addr  = inet_addr(host.toLocal8Bit().data());
    addr.sin_port         = htons(port);

    listener = evconnlistener_new_bind(eventBase,
                                       processNewMonitorConnection,
                                       NULL,
                                       LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
                                       -1,
                                       (struct sockaddr*)&addr, sizeof(addr));

    if (!listener)
    {
        int err = EVUTIL_SOCKET_ERROR();
        char buf[64];
        sprintf(buf, "Create listener error: %s", evutil_socket_error_to_string(err));
        Log::send('E', buf);
        return;
    }

    evconnlistener_set_error_cb(listener, processMonitorListenError);

    evNewDataNotify = event_new(eventBase,
                                mChannel.rfd,
                                EV_READ | EV_PERSIST,
                                onMessageNotify,
                                (void*)eventBase);

    event_add(evNewDataNotify, NULL);

    event_base_dispatch(eventBase);
}

void LjStatisticSendThread::sendEphData(const EPH_DATA_S& data)
{
    EphData ephData;
    ephData.type    = data.type;
    ephData.satID   = data.satID;
    ephData.sn      = data.sn;
    ephData.data    = QByteArray(data.data, data.dataLen);

    QString mnpt(data.mountPoint);

    foreach(MonitorArg* monitor, m_monitors.values())
    {
        this->sendEphData(monitor, mnpt, ephData);
    }
}

void LjStatisticSendThread::sendEphData(MonitorArg* monitor, const QString& mnpt, const EphData& data)
{
    QByteArray  msg;

    msg.append(0xD3);

    QJsonDocument   jsonDoc;
    QJsonObject     jsonData;

    jsonData.insert("moniType", 1000);
    jsonData.insert("mnpt", mnpt);
    jsonData.insert("type", QJsonValue::fromVariant(data.type));
    jsonData.insert("prn",  QJsonValue::fromVariant(data.satID));
    jsonData.insert("sn",   QJsonValue::fromVariant(data.sn));
    jsonData.insert("data", QJsonValue::fromVariant(data.data.toHex()));

    jsonDoc.setObject(jsonData);

    QByteArray  content = jsonDoc.toBinaryData();
    int len = content.length();

    msg.append((char*)(&len), 4);
    msg.append(content);

    struct evbuffer* evb = bufferevent_get_output(monitor->bev);
    evbuffer_add(evb, msg.data(), msg.length());

    bufferevent_setcb(monitor->bev, 0, onMonitorWrite, onMonitorBevEvent, monitor);
}

void LjStatisticSendThread::sendLogInfo(const LOG_INFO_S& log)
{
    foreach(MonitorArg* monitor, m_monitors.values())
    {
        this->sendLogInfo(monitor, log);
    }
}

void LjStatisticSendThread::sendLogInfo(MonitorArg* monitor, const LOG_INFO_S& log)
{
    QByteArray  msg;

    msg.append(0xD3);

    QJsonDocument   jsonDoc = QJsonDocument::fromJson(log.content);
    QJsonObject     jsonData= jsonDoc.object();

    jsonData.insert("moniType", 3000);

    jsonDoc.setObject(jsonData);

    QByteArray  content = jsonDoc.toBinaryData();
    int len = content.length();

    msg.append((char*)(&len), 4);
    msg.append(content);

    struct evbuffer* evb = bufferevent_get_output(monitor->bev);
    evbuffer_add(evb, msg.data(), msg.length());

    bufferevent_setcb(monitor->bev, 0, onMonitorWrite, onMonitorBevEvent, monitor);
}

void LjStatisticSendThread::sendClientData(const CLIENT_INFO_S& data)
{
   foreach(MonitorArg* monitor, m_monitors.values())
   {
       if(data.authState == 0)
            this->sendClientData(monitor, data);
   }
}

void LjStatisticSendThread::sendClientData(MonitorArg* monitor, const CLIENT_INFO_S& data)
{
    QByteArray  msg;

    msg.append(0xD3);

    QJsonDocument   jsonDoc;
    QJsonObject     jsonData;

    jsonData.insert("moniType", 2000);
    jsonData.insert("port", data.port);
    jsonData.insert("ip", data.ip);
    jsonData.insert("flowCount", (double)(data.flowCount*1.0/1024));
    jsonData.insert("mountPoint",  data.mountPoint);
    jsonData.insert("userName",   data.userName);
    jsonData.insert("loginTime", data.loginTime);
    jsonData.insert("logoutTime", data.logoutTime);

    jsonDoc.setObject(jsonData);

    QByteArray  content = jsonDoc.toBinaryData();
    int len = content.length();

    msg.append((char*)(&len), 4);
    msg.append(content);

    struct evbuffer* evb = bufferevent_get_output(monitor->bev);
    evbuffer_add(evb, msg.data(), msg.length());

    bufferevent_setcb(monitor->bev, 0, onMonitorWrite, onMonitorBevEvent, monitor);
}

void LjStatisticSendThread::onClientStateChanged(const CLIENT_INFO_S& clientInfo)
{
    MSG_INFO_S msgInfo;

    msgInfo.type        = msg_data_client_info;
    msgInfo.clientInfo  = clientInfo;

    write(mChannel.wfd, (void*)(&msgInfo), sizeof(msgInfo));
}

void LjStatisticSendThread::onEphDataChanged(const QString& mnpt, const EphData& ephData)
{
    MSG_INFO_S msgInfo;

    msgInfo.type = msg_data_eph;

    msgInfo.ephData.type    = ephData.type;
    msgInfo.ephData.satID   = ephData.satID;
    msgInfo.ephData.sn      = ephData.sn;

    memset(msgInfo.ephData.mountPoint, 0, 24);
    strcpy(msgInfo.ephData.mountPoint, mnpt.toLocal8Bit().data());

    memset(msgInfo.ephData.data, 0, 2048);
    msgInfo.ephData.dataLen = ephData.data.length();
    memcpy(msgInfo.ephData.data, ephData.data.data(), ephData.data.length());

    write(mChannel.wfd, (void*)(&msgInfo), sizeof(msgInfo));
}
