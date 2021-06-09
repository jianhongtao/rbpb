#include "NtripArg.h"
#include "Common.h"

NtripArg::NtripArg(QObject* parent)
    :QObject(parent)
{
    recvPktState = recv_pkt_req_line;
    pktLen       = 0;
    reqType      = usr_unknown;
    ver          = ntrip_v1;
    bev          = nullptr;
    authState    = -1;  // unknown state
    flowCount    = 0;
}
