#ifndef COMMON_H
#define COMMON_H

#include "stdafx.h"

#include <QHash>
#include <QString>

//#define __SEND_EMPTY_IONO_PKT__

#define __LOG__

#ifdef  __LOG__
    #define LOG printf
#else
    #define LOG
#endif


#define  atomic_inc(x)   __sync_fetch_and_add(&x,1)
#define  atomic_dec(x)   __sync_sub_and_fetch(&x, 1)
#define  atomic_add(x,y)  __sync_add_and_fetch((x),(y))
#define  atomic_sub(x,y)  __sync_sub_and_fetch((x),(y))

#define NtripServer             "Server: NTRIP BDStarCaster/1.0"
#define NtripVersion            "Ntrip-Version: Ntrip/2.0"
#define NtripFlags              "Ntrip-Falgs: st-fileter, st_auth, st_match, st_strict"
#define NtripCacheControl       "Cache-Control: no-store, no-cache, max-age=0"
#define NtripPragma             "Pragma: no-cache"
#define NtripConnection         "Connection: close"
#define NtripEncoding           "Transfer-Encoding: chunked"

#define SERVER_IP               ("10.212.130.6")
#define CASTER_ID               ("CASTER_v1.0_BJ_01")
#define CASTER_ID_LEN           (32)

#define REQ_CAST_MSG_HEAD       ("BDXT_RBPB\r\n")
#define REQ_CAST_MSG_HEAD_LEN   (11)

#define TIMEOUT                 (15)

#define TCP_PORT_STAT           (8000)
#define TCP_PORT_NTRIP          (2101)
#define TCP_PORT_NTRIP_TEST     (10000)

#define MAX_RECV_DATA_LEN       (2048)

#define THD_NUM                 (3)
#define EVENT_BASE_NUM          (THD_NUM)

typedef unsigned int        UINT32;
typedef unsigned char       UCHAR;
typedef unsigned long long  UINT64;

typedef  void*(*ThdFuc)(void*);

#define CHECK_VALUE_LENGHT(v, min, max, who)\
{\
    int len = v.length();\
    if (len < min || len > max)\
    {\
        char buf[128];sprintf(buf, "%s %s", who, "is error!");\
        Log::send('E', buf);\
        return false;\
    }\
}

#define CHECK_VALUE_BOOL(v, who)\
{\
    int nValue = v.toInt(); \
    if (nValue !=0 || nValue != 1) \
    {\
        char buf[128];sprintf(buf, "%s %s", who, "is error!");\
        Log::send('E', buf);\
        return false;\
    }\
}

#define CHECK_VALUE_INT(v, min, max, who)\
{\
  int nValue = v.toInt();\
  if (nValue < min || nValue > max)\
  {\
       char buf[128];sprintf(buf, "%s %s", who, "is error!");\
       Log::send('E', buf);\
       return false;\
  }\
}

#define CHECK_VALUE_DOUBLE(v, min, max, who)\
{\
   double nValue = v.toDouble();\
   if (nValue < min || nValue > max)\
    {\
       char buf[128];sprintf(buf, "%s %s", who, "is error!");\
       Log::send('E', buf);\
       return false;\
    }\
}

#define CHECK_VALUE_IP(v, who)\
{\
    QHostAddress ip;\
    if (!ip.setAddress(v))\
    {\
        char buf[128];sprintf(buf, "%s %s", who, "is error!");\
        Log::send('E', buf);\
        return false;\
    }\
}

enum ntrip_ver
{
    ntrip_v1 = 1,
    ntrip_v2 ,
};

enum req_type
{
    req_sour_table,
    req_diff_data
};

enum user_type
{
    usr_unknown,
    ntrip_client,
    bdxt_rbpb,
};

enum recv_pkt_status
{
    recv_pkt_req_line,
    recv_pkt_header,
    recv_pkt_payload,
    recv_pkt_complete,
};

enum enum_fd
{
    fd_get_cast_data = 0,
    fd_send_stat,
    fd_cast_data,
};

enum auth_type
{
    auth_unknown,
    auth_basic,
    auth_digest
};

enum status_code
{
    status_200 = 200,
    status_401 = 401,
    status_301 = 310,
    status_404 = 404
};

enum http_method
{
    method_get = 10,
    method_post = 11,
};

enum base_thd
{
    base_quit=0,
    base_CastData= 0,
    base_GetCastData,
    base_SendStat,
};

enum msg_type
{
    msg_cmd_quit,
    msg_data_eph,
    msg_data_client_info,
    msg_data_log,
};

typedef struct tag_one_client_stat
{
    UINT64  ulTotalSendCnt;
    char    BeginTime[32];
    char    EndTime[32];
    bool    IsDisConnected;
    char    ip[32];
    tag_one_client_stat()
    {
        IsDisConnected = false;
        ulTotalSendCnt = 0;
        memset(BeginTime, 0, 32);
        memset(EndTime,   0, 32);
        memset(ip,   0, 32);
    }

}ONE_CLIENT_STAT_S;

typedef struct tag_caster_stat
{
    UINT64  ulConcurrent;
    QHash<void*, ONE_CLIENT_STAT_S*> *clnStats;

    tag_caster_stat()
    {
        ulConcurrent = 0;
        clnStats = new QHash<void*, ONE_CLIENT_STAT_S*>();
    }
    ~tag_caster_stat()
    {
        delete clnStats;
    }

}STAT_S;

typedef struct tag_connection_arg
{
    struct event_base  *base;
    struct bufferevent *conn;
    struct sockaddr    *addr;
    int  addrSize;
    int  recvPktState;
    int  pktLen;
    char mnpt[24];
    bool bConnected;

    tag_connection_arg()
    {
        bConnected = false;
        recvPktState = recv_pkt_header;
        pktLen = 0;
        memset(mnpt, 0, 24);
    }
}CONNARG_S;

typedef struct tag_fds
{
    int rfd;
    int wfd;
}FDS_S;

/////// wxj add
typedef struct _st_Eph_Data_
{
    uint        type;           // data type;
    uint        satID;          //
    uint        sn;             // serial number
    char        mountPoint[24];
    uint        dataLen;
    char        data[2048];     // data
}EPH_DATA_S;

#define DATATIME_LEN 24

typedef struct  _st_ClientInfo_
{
    int     authState;
    int     port;
    int     flowCount;
    char    ip[32];
    char    mountPoint[24];
    char    authMessage[256];
    char    userName[32];
    char    loginTime[DATATIME_LEN];
    char    logoutTime[DATATIME_LEN];
    char    expireTime[DATATIME_LEN];
}CLIENT_INFO_S;

typedef struct  _st_LogInfo_
{
    char    content[512];
}LOG_INFO_S;

/////////////////

typedef struct tag_msg_info
{
    int     type;

    union
    {
        EPH_DATA_S      ephData;
        CLIENT_INFO_S   clientInfo;
        LOG_INFO_S      logInfo;
    };
}MSG_INFO_S;

#define MSG_INFO_LEN       (sizeof(MSG_INFO_S))

Q_DECLARE_METATYPE(MSG_INFO_S)
#endif // COMMON_H
