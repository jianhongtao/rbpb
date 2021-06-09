#include <QCoreApplication>
#include <QTextCodec>
#include <QDateTime>
#include <QLocale>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include "Common.h"
#include "Log.h"
#include "NtripArg.h"
#include "Rbpb.h"
#include "Args.h"
#include "SourceTable.h"
#include "UserTable.h"

bool InitProc()
{
    //init rbpb configuration.
    if(!Args::getInstance()->init("../cfg/rbpb/rbpb.conf"))
    {
        Log::send('E', "initialize rbpb.conf failed");
        return false;
    }
    Args::getInstance()->print();

    //init source table
    if(!SourceTable::getInstance()->init("../cfg/rbpb/castSource.conf"))
    {
        Log::send('E', "initialize castSource.conf failed");
        return false;
    }

    //init user info.
    if(!UserTable::getInstance()->init("../cfg/rbpb/castUser.conf"))
    {
        Log::send('E', "initialize castUser.conf failed");
        return false;
    }
    UserTable::getInstance()->print();

    return true;
}

void StartNripCaster()
{
    Rbpb *pRbPb = new Rbpb();
    pRbPb->StartCaster();

    //when rbpb exit, will come here.
    delete pRbPb;
    pRbPb = NULL;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!InitProc())
    {
        sleep(2);
        return 1;
    }

#define __SEND_HEART_PKT___


    StartNripCaster();

    a.exec();

    Log::send('R', "rbpb exit successfully");

    return 0;
}
