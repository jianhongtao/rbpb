#include "ljlistenandcastthread.h"
#include "ljauththread.h"

#define RTCM3PREAMB     0xD3

static const unsigned int CRC24Q[]={
    0x000000,0x864CFB,0x8AD50D,0x0C99F6,0x93E6E1,0x15AA1A,0x1933EC,0x9F7F17,
    0xA18139,0x27CDC2,0x2B5434,0xAD18CF,0x3267D8,0xB42B23,0xB8B2D5,0x3EFE2E,
    0xC54E89,0x430272,0x4F9B84,0xC9D77F,0x56A868,0xD0E493,0xDC7D65,0x5A319E,
    0x64CFB0,0xE2834B,0xEE1ABD,0x685646,0xF72951,0x7165AA,0x7DFC5C,0xFBB0A7,
    0x0CD1E9,0x8A9D12,0x8604E4,0x00481F,0x9F3708,0x197BF3,0x15E205,0x93AEFE,
    0xAD50D0,0x2B1C2B,0x2785DD,0xA1C926,0x3EB631,0xB8FACA,0xB4633C,0x322FC7,
    0xC99F60,0x4FD39B,0x434A6D,0xC50696,0x5A7981,0xDC357A,0xD0AC8C,0x56E077,
    0x681E59,0xEE52A2,0xE2CB54,0x6487AF,0xFBF8B8,0x7DB443,0x712DB5,0xF7614E,
    0x19A3D2,0x9FEF29,0x9376DF,0x153A24,0x8A4533,0x0C09C8,0x00903E,0x86DCC5,
    0xB822EB,0x3E6E10,0x32F7E6,0xB4BB1D,0x2BC40A,0xAD88F1,0xA11107,0x275DFC,
    0xDCED5B,0x5AA1A0,0x563856,0xD074AD,0x4F0BBA,0xC94741,0xC5DEB7,0x43924C,
    0x7D6C62,0xFB2099,0xF7B96F,0x71F594,0xEE8A83,0x68C678,0x645F8E,0xE21375,
    0x15723B,0x933EC0,0x9FA736,0x19EBCD,0x8694DA,0x00D821,0x0C41D7,0x8A0D2C,
    0xB4F302,0x32BFF9,0x3E260F,0xB86AF4,0x2715E3,0xA15918,0xADC0EE,0x2B8C15,
    0xD03CB2,0x567049,0x5AE9BF,0xDCA544,0x43DA53,0xC596A8,0xC90F5E,0x4F43A5,
    0x71BD8B,0xF7F170,0xFB6886,0x7D247D,0xE25B6A,0x641791,0x688E67,0xEEC29C,
    0x3347A4,0xB50B5F,0xB992A9,0x3FDE52,0xA0A145,0x26EDBE,0x2A7448,0xAC38B3,
    0x92C69D,0x148A66,0x181390,0x9E5F6B,0x01207C,0x876C87,0x8BF571,0x0DB98A,
    0xF6092D,0x7045D6,0x7CDC20,0xFA90DB,0x65EFCC,0xE3A337,0xEF3AC1,0x69763A,
    0x578814,0xD1C4EF,0xDD5D19,0x5B11E2,0xC46EF5,0x42220E,0x4EBBF8,0xC8F703,
    0x3F964D,0xB9DAB6,0xB54340,0x330FBB,0xAC70AC,0x2A3C57,0x26A5A1,0xA0E95A,
    0x9E1774,0x185B8F,0x14C279,0x928E82,0x0DF195,0x8BBD6E,0x872498,0x016863,
    0xFAD8C4,0x7C943F,0x700DC9,0xF64132,0x693E25,0xEF72DE,0xE3EB28,0x65A7D3,
    0x5B59FD,0xDD1506,0xD18CF0,0x57C00B,0xC8BF1C,0x4EF3E7,0x426A11,0xC426EA,
    0x2AE476,0xACA88D,0xA0317B,0x267D80,0xB90297,0x3F4E6C,0x33D79A,0xB59B61,
    0x8B654F,0x0D29B4,0x01B042,0x87FCB9,0x1883AE,0x9ECF55,0x9256A3,0x141A58,
    0xEFAAFF,0x69E604,0x657FF2,0xE33309,0x7C4C1E,0xFA00E5,0xF69913,0x70D5E8,
    0x4E2BC6,0xC8673D,0xC4FECB,0x42B230,0xDDCD27,0x5B81DC,0x57182A,0xD154D1,
    0x26359F,0xA07964,0xACE092,0x2AAC69,0xB5D37E,0x339F85,0x3F0673,0xB94A88,
    0x87B4A6,0x01F85D,0x0D61AB,0x8B2D50,0x145247,0x921EBC,0x9E874A,0x18CBB1,
    0xE37B16,0x6537ED,0x69AE1B,0xEFE2E0,0x709DF7,0xF6D10C,0xFA48FA,0x7C0401,
    0x42FA2F,0xC4B6D4,0xC82F22,0x4E63D9,0xD11CCE,0x575035,0x5BC9C3,0xDD8538
};

unsigned int crc24q(const unsigned char *buff, int len)
{
    unsigned int crc=0;
    int i;

    for (i=0;i<len;i++) crc=((crc<<8)&0xFFFFFF)^CRC24Q[(crc>>16)^buff[i]];
    return crc;
}

void setbitu(unsigned char *buff, int pos, int len, unsigned int data)
{
    unsigned int mask=1u<<(len-1);
    int i;
    if (len<=0||32<len) return;
    for (i=pos;i<pos+len;i++,mask>>=1) {
        if (data&mask) buff[i/8]|=1u<<(7-i%8); else buff[i/8]&=~(1u<<(7-i%8));
    }
}

/*
*   RTCM3 data format:
*
*   +----------+--------+-----------+--------------------+----------+
*   | preamble | 000000 |  length   |    data message    |  parity  |
*   +----------+--------+-----------+--------------------+----------+
*   |<-- 8 --->|<- 6 -->|<-- 10 --->|<--- length x 8 --->|<-- 24 -->|
*/

/* ionospheric data, message NO. : 1264 */
int Make1264EmptyMsg(unsigned char *buf)
{
    int i=0;
    setbitu(buf,i, 8,RTCM3PREAMB); i+= 8;
    setbitu(buf,i, 6,0          ); i+= 6;
    setbitu(buf,i,10,0          ); i+=10;   //message length

    unsigned int crc;
    crc=crc24q(buf, 3);              //crc-24q
    setbitu(buf,i,24,crc);

    return 6;                   //total=48bits
}


void onHeartBeat(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;
    //Rbpb::GetStat()->IncTotalSendMsg(bev);
}

void handleNtripClientEvent(struct bufferevent* bev, short what, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;

    char type;
    char buf[256]={0};
    if(what & BEV_EVENT_EOF)
    {
        type = 'R';
        sprintf(buf, "LjListenAndCastThread:: tcp connect %s:%d has closed",
                qPrintable(ntripArg->ip), ntripArg->port);

        //printf("ntrip client closed\n");
    }
    else if(what & BEV_EVENT_ERROR)
    {
        type = 'W';
        sprintf(buf, "LjListenAndCastThread:: tcp connect %s:%d has error",
                qPrintable(ntripArg->ip), ntripArg->port);
    }
    else if(what & (BEV_EVENT_TIMEOUT | BEV_EVENT_READING))
    {
        type = 'W';
        sprintf(buf, "LjListenAndCastThread:: tcp connect %s:%d reading timeout",
                qPrintable(ntripArg->ip), ntripArg->port);
    }
    else if(what & (BEV_EVENT_TIMEOUT | BEV_EVENT_WRITING))
    {
        type = 'W';
        sprintf(buf, "LjListenAndCastThread:: tcp connect %s:%d writing timeout",
                qPrintable(ntripArg->ip), ntripArg->port);
    }
    else
    {
        type = 'W';
        sprintf(buf, "LjListenAndCastThread:: tcp connect %s:%d unknown error",
                qPrintable(ntripArg->ip), ntripArg->port);
    }
    Log::send(type, buf);

    //after send source table,close connection, or ntrip requstion can not build connection.
    //bufferevent_free(bev);

    LjListenAndCastThread::instance()->deregCln(ntripArg->mountPoint, ntripArg);
    //delete ntripArg;
}

void onNtripClientWrite(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;
    //Rbpb::GetStat()->IncTotalSendMsg(bev);
}


CLIENT_INFO_S   arg2info(NtripArg* arg)
{
    CLIENT_INFO_S   info;

    info.authState  = arg->authState;
    info.port       = arg->port;
    info.flowCount  = arg->flowCount;
    strcpy(info.ip, qPrintable(arg->ip));
    strcpy(info.userName, qPrintable(arg->username));
    strcpy(info.loginTime, qPrintable(arg->loginTime));
    strcpy(info.logoutTime, qPrintable(arg->logoutTime));
    strcpy(info.expireTime, qPrintable(arg->expireTime));
    strcpy(info.mountPoint, qPrintable(arg->mountPoint));

    return info;
}


void sendData(NtripArg *ntripArg, QByteArray data)
{
    if(ntripArg->authState != 0)
        return;

    bufferevent* bev = ntripArg->bev;

    if(ntripArg->ver == ntrip_v2)
    {
        char head[32];
        int  headLen = sprintf(head, "%X\r\n", data.length());

        bufferevent_write(bev, head, headLen);
        bufferevent_write(bev, data.data(), data.length());
        bufferevent_write(bev, "\r\n", 2);
    }
    else
    {
        bufferevent_write(bev, data.data(), data.length());
    }

    ntripArg->flowCount += data.length();

    emit LjListenAndCastThread::instance()->clientStateChanged(arg2info(ntripArg));

    bufferevent_setcb(ntripArg->bev, 0, onNtripClientWrite, handleNtripClientEvent, ntripArg);

    struct timeval tv;
    tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
    tv.tv_usec = 0;
    bufferevent_set_timeouts(ntripArg->bev, 0, &tv);
}

/*  1264 ionospheric message */
void sendHeartBeatMsg(evutil_socket_t sock, short what, void* arg)
{
    char unsigned data[256];

    int len = Make1264EmptyMsg(data);

    QList<NtripArg*> clients = LjListenAndCastThread::instance()->getCln();

    foreach(NtripArg *ntripArg, clients)
    {
        sendData(ntripArg, QByteArray((char*)data, len));

        //bufferevent_setcb(ntripArg->bev, 0, onHeartBeat, handleNtripClientEvent, ntripArg);
    }
}

void closeNtripClientAfterWrite(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;

    char buf[256];
    sprintf(buf, "LjListenAndCastThread:: Close tcp connect %s:%d",
            qPrintable(ntripArg->ip), ntripArg->port);
    Log::send('R', buf);

    bufferevent_free(bev);
    delete ntripArg;
}

void sendSourceTable(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;
    QByteArray sour = SourceTable::getInstance()->get();

    QLocale lo = QLocale::English;
    QString date = lo.toString(QDateTime::currentDateTimeUtc(), "ddd, dd MMM yyyy hh:mm:ss");

    char buf[1024];
    if (ntripArg->ver == ntrip_v2)
    {
        sprintf(buf,
                "HTTP/1.1 200 OK\r\n"
                "%s\r\n"
                "Date: %s GMT\r\n"
                "%s\r\n"
                "%s\r\n"
                "%s\r\n"
                "%s\r\n"
                "%s\r\n"
                "Content-Type: gnss/sourcetable\r\n"
                "Content-Length: %d\r\n"
                "\r\n",
                NtripServer,
                date.toLocal8Bit().data(),
                NtripVersion,
                NtripFlags,
                NtripCacheControl,
                NtripPragma,
                NtripConnection,
                sour.length());
    }
    else
    {
        sprintf(buf,
                "SOURCETABLE 200 OK\r\n"
                "%s\r\n"
                "Date: %s GMT\r\n"
                "%s\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: %d\r\n"
                "\r\n",
                NtripServer,
                date.toLocal8Bit().data(),
                NtripConnection,
                sour.length());
    }

    QByteArray rsp(buf);
    rsp.append(sour);
    printf("%s\n", rsp.data());

    struct evbuffer* evb = bufferevent_get_output(bev);
    evbuffer_add(evb, rsp.data(), rsp.size());

    bufferevent_setcb(bev, 0, closeNtripClientAfterWrite, handleNtripClientEvent, arg);

    struct timeval tv;
    tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
    tv.tv_usec = 0;
    bufferevent_set_timeouts(bev, 0, &tv);
}

//
void onAfterAuthReply(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;

    if(ntripArg->authState == 0)
    {
        Log::send('R', QString("LjListenAndCastThread:: Send all eph data to client %1:%2")
            .arg(ntripArg->ip).arg(ntripArg->port));

        LjEphData* ephData = LjEphDataFactory::instance()->getEphData(ntripArg->mountPoint);
        foreach(EphData msgData, ephData->getAllEph())
        {
            sendData(ntripArg, msgData.data);
        }

//        bufferevent_setcb(ntripArg->bev, 0, onNtripClientWrite, handleNtripClientEvent, ntripArg);

//        struct timeval tv;
//        tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
//        tv.tv_usec = 0;
//        bufferevent_set_timeouts(bev, 0, &tv);
    }
    else
    {
        LjListenAndCastThread::instance()->deregCln(ntripArg->mountPoint, ntripArg);
    }

}

#define _TEST_

// Try to open ntrip client
void openNtripClient(struct bufferevent* bev, void* arg)
{
    NtripArg* ntripArg = (NtripArg*)arg;

#ifdef _TEST_
    ntripArg->mountPoint = QString("ZDNE01");
#endif

    char buf[1204];
    int len;

    //find mountpoint
    bool needAuth = false;
    SourceTable* sourTbl = SourceTable::getInstance();
    if(!sourTbl->find(ntripArg->mountPoint, &needAuth))
    {
        Log::send('W', "LjListenAndCastThread:: Not found mount-point -- " + ntripArg->mountPoint);

        if(ntripArg->ver == ntrip_v2)
        {
            len = sprintf(buf, "HTTP/1.1 404 Not found\r\n\r\n");
            struct evbuffer* evb = bufferevent_get_output(bev);
            evbuffer_add(evb, buf, len);

            bufferevent_setcb(bev, 0, closeNtripClientAfterWrite, handleNtripClientEvent, arg);

            struct timeval tv;
            tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
            tv.tv_usec = 0;
            bufferevent_set_timeouts(bev, 0, &tv);
        }
        else
        {
            sendSourceTable(bev, arg);
        }
        return;
    }

    // Register first
    LjListenAndCastThread* pThread = LjListenAndCastThread::instance();
    ntripArg->loginTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");

    //Need authorize
    if(needAuth)
    {
        pThread->regCln(ntripArg->mountPoint, ntripArg);

        // Send authorization request
        emit pThread->authRequest(ntripArg->username,
                                  ntripArg->password,
                                  ntripArg->mountPoint);
    }
    else
    {
        ntripArg->authState = 0;
        pThread->regCln(ntripArg->mountPoint, ntripArg);
    }
}

// Call this after handshake,process ntrip protocol
void onNtripClientConnected(struct bufferevent* bev, void* arg)
{
    NtripArg*   ntripArg = (NtripArg*)arg;

    evbuffer    *evb = bufferevent_get_input(bev);
    int         totalLen = evbuffer_get_length(evb);

    size_t      len = 0;
    char*       line = nullptr;

    do
    {
        switch (ntripArg->recvPktState)
        {
         case recv_pkt_req_line:
            {
                line = evbuffer_readln(evb, &len, EVBUFFER_EOL_CRLF);
                if (!line) return;

                // LOG("%s\n", line);
                totalLen -= len+2;

                // Line should be like 'GET /AUTO HTTP/1.0' etc...
                QString ReqLine(line);
                ReqLine = ReqLine.simplified();
                QStringList ReqLineList = ReqLine.split(" ", QString::KeepEmptyParts);
                if (ReqLineList.length() != 3)
                {
                    Log::send('W', QString("LjListenAndCastThread:: ntrip client request line is error(%1)").arg(ReqLine));
                    bufferevent_free(bev);
                    free(line);
                    return;
                }
                QString method = ReqLineList[0].toUpper();
                QUrl url(ReqLineList[1]);
                if (!url.isValid())
                {
                    Log::send('W', QString("LjListenAndCastThread:: ntrip client request url is error(%1)").arg(method));
                    bufferevent_free(bev);
                    free(line);
                    return;
                }
                QString urlPath = url.path();
                ntripArg->mountPoint = url.fileName();

                if (method == "GET")
                {
                    if (urlPath == "/")
                        ntripArg->reqType = req_sour_table;
                    else
                        ntripArg->reqType = req_diff_data;
                }
                else
                {
                    Log::send('W', "LjListenAndCastThread:: ntrip client request method is abnormal, NOT GET method");
                    bufferevent_free(bev);
                    free(line);
                    return;
                }
                free(line);
                ntripArg->recvPktState = recv_pkt_header;
            }
            break;
        case recv_pkt_header:
            {
               do
               {
                   // Process what we care, now only ntrip-version and authorization
                   line = evbuffer_readln(evb, &len, EVBUFFER_EOL_CRLF);
                   if (line)
                   {
                     //  LOG("%s\n", line);
                       QString strLine(line);
                       //header end
                       if (len==0)
                       {
                           free(line);
                           totalLen -= 2;
                           break;
                       }
                       totalLen -= len+2;

                       if (strLine.contains("ntrip-version", Qt::CaseInsensitive))
                       {
                           QStringList VerList = strLine.split(":", QString::SkipEmptyParts);
                           if (VerList[1].contains("ntrip/2.0", Qt::CaseInsensitive))
                               ntripArg->ver = ntrip_v2;
                           else
                               ntripArg->ver = ntrip_v1;
                       }
                       else if (strLine.contains("authorization", Qt::CaseInsensitive))
                       {
                           QStringList AuthList = strLine.split(":", QString::SkipEmptyParts);
                           if (AuthList[1].contains("basic", Qt::CaseInsensitive))
                           {
                               AuthList[1].remove(0,6);
                               QString Auth = QByteArray::fromBase64(AuthList[1].toLocal8Bit());
                               AuthList.clear();

                               AuthList = Auth.split(":", QString::SkipEmptyParts);
                               if(AuthList.size() == 2)
                               {
                                   ntripArg->username = AuthList[0];
                                   ntripArg->password = AuthList[1];

                                   LOG("username: %s, passwd: %s\n",
                                       ntripArg->username.toLocal8Bit().data(),
                                       ntripArg->password.toLocal8Bit().data());
                               }
                           }
                       }
                       free(line);
                       if (totalLen <=0) return;
                   }
                   else
                       return;
               }while (true);

               ntripArg->recvPktState = recv_pkt_complete;
            }
            break;
        case recv_pkt_complete:
            {
                ntripArg->recvPktState = recv_pkt_req_line;
                goto send_response;
            }
            break;

        default:
            Log::send('W', "LjListenAndCastThread:: ntrip client request packet is abnormal");
            bufferevent_free(bev);
            return;
        }
    }while (totalLen>0);

send_response:
    if(ntripArg->reqType == req_diff_data)
    {
        openNtripClient(bev, arg);
    }
    else
    {
        sendSourceTable(bev, arg);
    }
}

// Process listener errors
void processListenError(struct evconnlistener* listener, void* arg)
{
    // report error
    int err = EVUTIL_SOCKET_ERROR();
    char buf[64];
    sprintf(buf, "LjListenAndCastThread:: Error occurs on the listener: %s", evutil_socket_error_to_string(err));
    Log::send('E', buf);

    // exit event loop
    struct event_base *base = evconnlistener_get_base(listener);
    event_base_loopexit(base, 0);
}

// Call this function when new connections comes
void processNewConnection(struct evconnlistener* listener,
             evutil_socket_t fd,
             struct sockaddr* addr,
             int len,
             void* arg)

{
    char buf[256];
    sprintf(buf, "LjListenAndCastThread:: Accept tcp connect from %s:%d",
            inet_ntoa(((struct sockaddr_in*)addr)->sin_addr),
            ntohs(((struct sockaddr_in*)addr)->sin_port));
    Log::send('R', buf);

    struct event_base* base = evconnlistener_get_base(listener);
    struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev)
    {
        Log::send('W', "LjListenAndCastThread:: thread cant create new connection");
        return;
    }

    NtripArg* ntripArg = new NtripArg();
    ntripArg->ip    = inet_ntoa(((struct sockaddr_in*)addr)->sin_addr);
    ntripArg->port  = ntohs(((struct sockaddr_in*)addr)->sin_port);
    ntripArg->bev   = bev;

    bufferevent_setcb(bev, onNtripClientConnected, 0, handleNtripClientEvent, ntripArg);

    struct timeval tv;
    tv.tv_sec  = Args::getInstance()->value("tcpTimeout").toInt();
    tv.tv_usec = 0;
    bufferevent_set_timeouts(bev, &tv, 0);

    bufferevent_enable(bev, EV_READ|EV_WRITE);
}

void castDataToClients(const QByteArray& msgData, const QString& mnpt)
{
    LjListenAndCastThread::instance()->castDataToClients(msgData, mnpt);
}

void    onClientAuthReply(const CLIENT_INFO_S& reply)
{
    NtripArg *ntripArg = LjListenAndCastThread::instance()->getCln(reply.mountPoint, reply.userName);
    if(!ntripArg)
        return;

    ntripArg->authState = reply.authState;

    emit LjListenAndCastThread::instance()->clientStateChanged(arg2info(ntripArg));

    char    buf[1204];
    int     len;

    QLocale lo = QLocale::English;
    QString date = lo.toString(QDateTime::currentDateTimeUtc(), "ddd, dd MMM yyyy hh:mm:ss");

    // generate response
    if(ntripArg->authState == 0)
    {
        if(ntripArg->ver == ntrip_v2)
        {
            len = sprintf(buf,
                          "HTTP/1.1 200 OK\r\n"
                          "%s\r\n"
                          "Date: %s GMT\r\n"
                          "%s\r\n"
                          "%s\r\n"
                          "%s\r\n"
                          "%s\r\n"
                          "%s\r\n"
                          "%s\r\n"
                          "Content-Type: gnss/data\r\n"
                          "\r\n",
                          NtripServer,
                          date.toLocal8Bit().data(),
                          NtripVersion,
                          NtripFlags,
                          NtripCacheControl,
                          NtripPragma,
                          NtripConnection,
                          NtripEncoding);
        }
        else
        {
            len = sprintf(buf,
                          "ICY 200 OK\r\n"
                          "%s\r\n"
                          "Date: %s GMT\r\n"
                          "%s\r\n"
                          "\r\n",
                          NtripServer,
                          date.toLocal8Bit().data(),
                          NtripConnection);
        }
    }
    else if(ntripArg->authState == 1001)
    {
        len = sprintf(buf,"Already Connected, [%s]-%s\r\n\r\n", reply.userName, reply.authMessage);
    }
    else if(ntripArg->authState == 1002)
    {
        len = sprintf(buf,"Unauthorized, [%s]-%s\r\n\r\n", reply.userName, reply.authMessage);
    }
    else if(ntripArg->authState == 1003)
    {
        len = sprintf(buf,"Unauthorized, [%s]-%s\r\n\r\n", reply.userName, reply.authMessage);
    }
    else
    {
        len = sprintf(buf,"[%s]-%s\r\n\r\n", reply.userName, reply.authMessage);
    }

    if(ntripArg->authState != 0)
    {
        Log::send('R', QString("LjListenAndCastThread:: %1 -- %2:%3")
            .arg(buf).arg(ntripArg->ip).arg(ntripArg->port));
    }

    struct evbuffer* evb = bufferevent_get_output(ntripArg->bev);
    evbuffer_add(evb, buf, len);

    bufferevent_setcb(ntripArg->bev, 0, onAfterAuthReply, handleNtripClientEvent, ntripArg);

    struct timeval tv;
    tv.tv_sec = Args::getInstance()->value("tcpTimeout").toInt();
    tv.tv_usec = 0;
    bufferevent_set_timeouts(ntripArg->bev, 0, &tv);
}

// Process pipe message
void onMsgNotify(evutil_socket_t sock, short event, void *arg)
{
    MSG_INFO_S msgInfo;
    read(sock, &msgInfo, MSG_INFO_LEN);

    switch (msgInfo.type)
    {
        case msg_data_eph:
        {
            QString mnpt(msgInfo.ephData.mountPoint);

            QByteArray data(msgInfo.ephData.data, msgInfo.ephData.dataLen);

            castDataToClients(data, mnpt);
        }
        break;

        case msg_data_client_info:
        {
            onClientAuthReply(msgInfo.clientInfo);
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

LjListenAndCastThread* LjListenAndCastThread::m_instance=nullptr;

LjListenAndCastThread::LjListenAndCastThread(QObject *parent)
    : QThread(parent)
{
    eventBase       = nullptr;
    listener        = nullptr;
    evNewDataNotify = nullptr;
    evHeartTimer    = nullptr;
}

LjListenAndCastThread::~LjListenAndCastThread()
{    
    if(evHeartTimer)
        event_free(evHeartTimer);
    if(evNewDataNotify)
        event_free(evNewDataNotify);
    if(listener)
        evconnlistener_free(listener);
    if(eventBase)
        event_base_free(eventBase);
}

LjListenAndCastThread* LjListenAndCastThread::instance()
{
    if(!m_instance)
        m_instance = new LjListenAndCastThread();

    return m_instance;
}

void LjListenAndCastThread::run()
{
    eventBase = event_base_new();
    if (!eventBase)
    {
        Log::send('E', "LjListenAndCastThread:: Cast data thread create event loop object error");
        return;
    }

    int fds[2];
    if (pipe(fds))
    {
        Log::send('E', "LjListenAndCastThread:: pipe open error------");
        return;
    }

    mChannel.rfd = fds[0];
    mChannel.wfd = fds[1];

    // QString host  =   Args::getInstance()->value("bind").toString();
    QString host  = "0.0.0.0";
    int  port     = Args::getInstance()->value("castPort").toInt();

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family       = AF_INET;
    addr.sin_addr.s_addr  = inet_addr(host.toLocal8Bit().data());
    addr.sin_port         = htons(port);

    listener = evconnlistener_new_bind(eventBase,
                                       processNewConnection,
                                       this,
                                       LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
                                       -1,
                                       (struct sockaddr*)&addr, sizeof(addr));

    if (!listener)
    {
        int err = EVUTIL_SOCKET_ERROR();
        char buf[64];
        sprintf(buf, "LjListenAndCastThread:: Create listener error: %s", evutil_socket_error_to_string(err));
        Log::send('E', buf);
        return;
    }

    evconnlistener_set_error_cb(listener, processListenError);

    evNewDataNotify = event_new(eventBase,
                                mChannel.rfd,
                                EV_READ | EV_PERSIST,
                                onMsgNotify,
                                (void*)eventBase);

    event_add(evNewDataNotify, NULL);

    int emptyIonoMsgIntv =  Args::getInstance()->value("emptyIonoMsgIntv").toInt();
    if (emptyIonoMsgIntv > 0)
    {
        /* create timer event ,to send  heartbeat packet for sending ionospheric data to RX. */
        struct timeval tv;
        evHeartTimer = event_new(eventBase, -1, EV_TIMEOUT|EV_PERSIST, sendHeartBeatMsg, NULL);
        tv.tv_sec  = emptyIonoMsgIntv;
        tv.tv_usec = 0;
        event_add(evHeartTimer, &tv);
    }

    event_base_dispatch(eventBase);
}

void LjListenAndCastThread::onEphDataChanged(const QString& mnpt, const EphData& ephData)
{
    MSG_INFO_S msgInfo;

    msgInfo.type = msg_data_eph;
    strcpy(msgInfo.ephData.mountPoint, mnpt.toLocal8Bit().data());
    memset(msgInfo.ephData.data, 0, 2048);
    msgInfo.ephData.dataLen = ephData.data.length();
    memcpy(msgInfo.ephData.data, ephData.data.data(), ephData.data.length());

    write(mChannel.wfd, (void*)(&msgInfo), sizeof(msgInfo));
}

void LjListenAndCastThread::regCln(const QString& mp, NtripArg* arg)
{
    ClientHash*  entry;

    if(!hashCln.contains(mp))
    {
        entry = new ClientHash();
        hashCln.insert(mp, entry);
    }
    else
    {
        entry = hashCln.value(mp);
    }

    if(!entry->contains(arg->username))
    {
        entry->insert(arg->username, arg);

        emit clientStateChanged(arg2info(arg));
    }
}

void LjListenAndCastThread::deregCln(const QString& mp, NtripArg* arg)
{
    if(hashCln.contains(mp))
    {
        ClientHash* entry = hashCln.value(mp);

        if(entry->contains(arg->username))
        {
            arg->logoutTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");

            entry->remove(arg->username);

            emit clientStateChanged(arg2info(arg));

            emit offlineNotify(arg->username);

            bufferevent_free(arg->bev);
            delete arg;
        }
    }
}

// 获取路由
QList<NtripArg*> LjListenAndCastThread::getCln(const QString& mp)
{
    QList<NtripArg*>    argList;

    if(!mp.isEmpty() && hashCln.contains(mp))
    {
        argList = hashCln.value(mp)->values();
    }
    else
    {
        QHashIterator<QString, ClientHash*> i(hashCln);
        while (i.hasNext())
        {
            i.next();
            argList.append(i.value()->values());
        }
    }

    return argList;
}

NtripArg*  LjListenAndCastThread::getCln(const QString& mp, const QString& username)
{
    NtripArg* arg = nullptr;

    if(hashCln.contains(mp))
    {
        ClientHash* clients;

        clients = hashCln.value(mp);

        if(clients->contains(username))
        {
            arg = clients->value(username);
        }
    }

    return arg;
}

int  LjListenAndCastThread::clientCount(QString mnpt)
{
    //QMutexLocker locker(&clientMutex);
    int count = 0;

    if(!mnpt.isEmpty())
    {
        count = this->getCln(mnpt).count();
    }
    else
    {
        count = this->getCln().count();
    }

    return count;
}

QList<CLIENT_INFO_S>  LjListenAndCastThread::clientsInfo()
{
    QMutexLocker locker(&mClientMutex);

    QList<CLIENT_INFO_S>   clientsStat;

    QList<NtripArg*>    args = this->getCln();

    foreach(NtripArg* arg, args)
    {
        CLIENT_INFO_S clientInfo = arg2info(arg);

        clientsStat.append(clientInfo);
    }

    return clientsStat;
}

void LjListenAndCastThread::castDataToClients(const QByteArray& msgData, const QString& mnpt)
{
    QList<NtripArg*> clients = getCln(mnpt.toLocal8Bit().data());

    Log::send('R',QString("MNTP: %1----------> DataLen: %2 ===== ClientsCount: %3")
        .arg(mnpt).arg(msgData.length()).arg(clients.size()));

    foreach(NtripArg *ntripArg, clients)
    {
        sendData(ntripArg, msgData);
    }
}

void LjListenAndCastThread::onAuthReply(const CLIENT_INFO_S& info)
{
    MSG_INFO_S msgInfo;

    msgInfo.type = msg_data_client_info;
    msgInfo.clientInfo = info;

    write(mChannel.wfd, (void*)(&msgInfo), sizeof(msgInfo));
}

