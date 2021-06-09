#include "ljrcvdatathread.h"
#include "Rbpb.h"

void handleConnectEvent(bufferevent *bev, short event, void *arg);


// Receive data from data server
void recvCastData(struct bufferevent* bev, void* arg)
{
    CONNARG_S *conn = (CONNARG_S*)arg;
    struct evbuffer *evb = bufferevent_get_input(bev);
    int totalLen = evbuffer_get_length(evb);
    size_t len=0;
    char buf[MAX_RECV_DATA_LEN];

    do
    {
        switch (conn->recvPktState)
        {
            case recv_pkt_header:
            {
                char *line = evbuffer_readln(evb, &len, EVBUFFER_EOL_CRLF);
                if (!line) return;

                totalLen -= len+2;
                QString header = line;
                QStringList hdList = header.split(":", QString::SkipEmptyParts);
                if (hdList.length() != 2)
                {
                    Log::send('W', " the data header received from data server is error");
                    LOG("%s %s\n", line);
                    free(line);
                    return;
                }

                strcpy(conn->mnpt, hdList[0].toLocal8Bit().data());
                conn->pktLen = hdList[1].toInt(0, 16);
                free(line);

                if (conn->pktLen <= 0)
                {
                    bufferevent_free(bev);
                    conn->bConnected = false;
                    Rbpb::ResetConnected();
                    Log::send('W', "the length of data received from data server is error");
                    return;
                }
                conn->recvPktState = recv_pkt_payload;
            }
            break;
            case recv_pkt_payload:
            {
                while (conn->pktLen > 0)
                {
                    if (conn->pktLen > MAX_RECV_DATA_LEN)
                        len = evbuffer_remove(evb, buf, MAX_RECV_DATA_LEN);
                    else
                        len = evbuffer_remove(evb, buf, conn->pktLen);

                    if (len > 0)
                    {
                        emit LjRcvDataThread::instance()->receivedNewData(conn->mnpt, QByteArray(buf, len));
                    }
                    else
                    {
                        bufferevent_free(bev);
                        conn->bConnected = false;
                        Rbpb::ResetConnected();
                        conn->pktLen = 0;
                        conn->recvPktState = recv_pkt_header;
                        Log::send('W', "receive cast data from data server is error");
                        return;
                    }
                    conn->pktLen -= len;
                    totalLen -= len;

                    if (totalLen <= 0) return;
                }
                conn->recvPktState = recv_pkt_header;
                conn->pktLen =0;
            }
            break;
            default:
            {
                bufferevent_free(bev);
                conn->bConnected = false;
                Rbpb::ResetConnected();
                conn->pktLen = 0;
                conn->recvPktState = recv_pkt_header;
                Log::send('W', "receive cast data from data server is error");
            }
            return;
        }
    }while (totalLen > 0);
}

//// Call this if data request is sent unsuccessfully
//void requestFail(bufferevent *bev, short event, void *arg)
//{
//    CONNARG_S *conn = (CONNARG_S*)arg;
//    if (event & BEV_EVENT_EOF)
//    {
//        Log::send('W', "Receive data connection is closed");
//    }
//    else if (event & BEV_EVENT_ERROR)
//    {
//        Log::send('W', "Receive data connection is error");
//    }
//    else if (event & BEV_EVENT_TIMEOUT)
//    {
//        Log::send('R', "Receive data connection is time out");
//    }
//    else
//    {
//        Log::send('R', "Receive data connection is unkown error");
//    }

//    conn->bConnected = false;
//    Rbpb::ResetConnected();
//    bufferevent_free(bev);
//}

//void recvCastDataEvent(bufferevent *bev, short event, void *arg)
//{
//    CONNARG_S *conn = (CONNARG_S*)arg;
//    if (event & BEV_EVENT_EOF)
//    {
//        Log::send('W', "Receive data connection is closed");
//    }
//    else if (event & BEV_EVENT_ERROR)
//    {
//        Log::send('W', "Receive data connection is error");
//    }
//    else if (event & BEV_EVENT_TIMEOUT)
//    {
//        Log::send('R', "Receive data connection is time out");
//    }
//    else
//    {
//        Log::send('R', "Receive data connection is unkown error");
//    }

//    conn->bConnected = false;
//    Rbpb::ResetConnected();
//    bufferevent_free(bev);
//}

// Call this if data request is sent successfully
void requestSuccess(struct bufferevent* bev, void* arg)
{
    struct timeval tv;
    tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
    tv.tv_usec = 0;
    bufferevent_set_timeouts(bev, &tv, NULL);
    //bufferevent_setcb(bev, recvCastData, NULL, recvCastDataEvent, arg);
    bufferevent_setcb(bev, recvCastData, NULL, handleConnectEvent, arg);
}

// Handle connect events
void handleConnectEvent(bufferevent *bev, short event, void *arg)
{
    CONNARG_S *conn = (CONNARG_S*)arg;
    char buf[128];
    char type;
    if (event & BEV_EVENT_EOF)
    {
        type = 'W';
        sprintf(buf, "Receive data  connection is closed, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));
    }
    else if (event & BEV_EVENT_ERROR)
    {
        type = 'W';
        sprintf(buf, "Receive data  connection is error, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));
    }
    else if (event & BEV_EVENT_READING)
    {
        type = 'W';
        sprintf(buf, "Receive data  connection error occurs while reading, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));
    }
    else if (event & BEV_EVENT_WRITING)
    {
        type = 'W';
        sprintf(buf, "Receive data  connection error occurs while writing,, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));
    }
    else if (event & BEV_EVENT_TIMEOUT)
    {
        type = 'W';
        sprintf(buf, "Receive data connection is time out, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));
    }
    else if (event & BEV_EVENT_CONNECTED)
    {
        Rbpb::SetConnected();
        conn->bConnected = true;

        //Send get broadcast data request.
        bufferevent_write(conn->conn, REQ_CAST_MSG_HEAD, REQ_CAST_MSG_HEAD_LEN);

        // set write timeout
        struct timeval tv;
        tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
        tv.tv_usec = 0;
        bufferevent_set_timeouts(conn->conn, NULL, &tv);

        //bufferevent_setcb(conn->conn, NULL, requestSuccess, requestFail, conn);
        bufferevent_setcb(conn->conn, NULL, requestSuccess, handleConnectEvent, conn);

        type = 'R';
        sprintf(buf, "Receive data connection connect successfully, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));

        Log::send(type, buf);
        return;
    }
    else
    {
        type = 'W';
        sprintf(buf, "Receive data connection is unknown erro, remote ip: %s",
                inet_ntoa(((struct sockaddr_in*)conn->addr)->sin_addr));

    }
    Log::send(type, buf);

    conn->bConnected = false;
    Rbpb::ResetConnected();
    bufferevent_free(bev);
}

// Connect to data server , of which parameters are contained in arg
void connectToDataServer(CONNARG_S *arg)
{
    struct bufferevent *conn = bufferevent_socket_new(arg->base, -1, BEV_OPT_CLOSE_ON_FREE);
    if (!conn)
    {
        Log::send('W', "Data receive thread cant create new connection");
        return;
    }

    arg->conn = conn;
    int ret = bufferevent_socket_connect(conn, arg->addr,arg->addrSize);
    if (ret)
        return;

    bufferevent_setcb(arg->conn,  NULL, NULL, handleConnectEvent, (void*)arg);
    bufferevent_enable(arg->conn, EV_READ | EV_WRITE);
}

// try to reconnect to data server if not connected
void tryToReconnectDataServer(evutil_socket_t sock, short what, void* arg)
{
    CONN_VECT *pConnVect = (CONN_VECT*)arg;

    if (Rbpb::IsConnected())
    {
        return;
    }

    connectToDataServer((*pConnVect)[Rbpb::GetConnPos()]);
    Rbpb::IncConnPos();

    if (Rbpb::GetConnPos() == pConnVect->size())
        Rbpb::RestConnPos();
}

//----------------------
LjRcvDataThread* LjRcvDataThread::m_instance=nullptr;

LjRcvDataThread::LjRcvDataThread(QObject *parent)
    : QThread(parent)
{
}

LjRcvDataThread* LjRcvDataThread::instance()
{
    if(!m_instance)
        m_instance = new LjRcvDataThread();

    return m_instance;
}


void LjRcvDataThread::run()
{
    struct event_base *base = event_base_new();
    if (!base)
    {
        Log::send('E', "Create event loop object error");
        return;
    }

    // Get args from configure
    QString Ip  =  Args::getInstance()->value("remoteIp").toString();
    QStringList IpList = Ip.split(";", QString::SkipEmptyParts);

    CONN_VECT *pConnVect = new CONN_VECT();
    CONNARG_S *conn = NULL;
    int  port ;

    // Create data server(s) vector
    for (int i=0; i<IpList.length(); i++)
    {
        conn  = new CONNARG_S();
        port  = Args::getInstance()->value("getDataPort").toInt();

        struct sockaddr_in *addr = new sockaddr_in();
        int adrSize = sizeof(struct sockaddr_in);
        memset(addr, 0, adrSize);

        addr->sin_family      = AF_INET;
        addr->sin_addr.s_addr = inet_addr(IpList[i].toLocal8Bit().data());
        addr->sin_port        = htons(port);

        conn->addr       = (struct sockaddr*)addr;
        conn->addrSize   = adrSize;
        conn->bConnected = false;
        conn->base       = base;
        pConnVect->push_back(conn);
    }

    // Try to connect to first data server
    connectToDataServer((*pConnVect)[0]);

    // Create timer event to determine whether or not reconnect to data server
    struct timeval tv;
    struct event* evTimer = event_new(base, -1, EV_TIMEOUT|EV_PERSIST,
                                      tryToReconnectDataServer,
                                      (void*)pConnVect);

    tv.tv_sec  = Args::getInstance()->value("reConnTime").toInt();
    tv.tv_usec = 0;
    event_add(evTimer, &tv);

    Log::send('R',"Get data thread start successfully\n");
    event_base_dispatch(base);

    event_free(evTimer);
    event_base_free(base);

    qDeleteAll(pConnVect->begin(), pConnVect->end());
    delete pConnVect;

    Log::send('R',"Get cast data thread exit successfully\n");
}
