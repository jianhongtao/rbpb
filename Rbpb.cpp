#include <QUrl>
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
#include "ljrcvdatathread.h"
#include "ljlistenandcastthread.h"
#include "ljephdata.h"
#include "ljstatisticsendthread.h"
#include "ljauththread.h"


bool                   Rbpb::bConnected = false;
int                    Rbpb::pos = 0;

Rbpb::Rbpb()
{
}

Rbpb::~Rbpb()
{
}

void Rbpb::StartCaster()
{
    qRegisterMetaType<MSG_INFO_S>("MSG_INFO_S");
    qRegisterMetaType<CLIENT_INFO_S>("CLIENT_INFO_S");

    m_ephDataFactory        = LjEphDataFactory::instance();
    m_rcvDataThread         = LjRcvDataThread::instance();
    m_listenAndCastThread   = LjListenAndCastThread::instance();
    m_statisticThread       = LjStatisticSendThread::instance();
    m_authThread            = LjAuthThread::instance();

    QObject::connect(m_rcvDataThread, &LjRcvDataThread::receivedNewData,
            m_ephDataFactory, &LjEphDataFactory::parseData);

    QObject::connect(m_ephDataFactory, &LjEphDataFactory::ephDataChanged,
            m_listenAndCastThread, &LjListenAndCastThread::onEphDataChanged);

    QObject::connect(m_ephDataFactory, &LjEphDataFactory::ephDataChanged,
            m_statisticThread, &LjStatisticSendThread::onEphDataChanged);

    QObject::connect(m_listenAndCastThread, &LjListenAndCastThread::authRequest,
            m_authThread, &LjAuthThread::onAuthRequest);

    QObject::connect(m_authThread, &LjAuthThread::authReply,
            m_listenAndCastThread, &LjListenAndCastThread::onAuthReply);

    QObject::connect(m_listenAndCastThread, &LjListenAndCastThread::offlineNotify,
            m_authThread, &LjAuthThread::onOfflineNotify);

    QObject::connect(m_listenAndCastThread, &LjListenAndCastThread::clientStateChanged,
            m_statisticThread, &LjStatisticSendThread::onClientStateChanged);

    m_listenAndCastThread->start();
    m_rcvDataThread->start();
    m_statisticThread->start();
    m_authThread->start();

    return;
}

