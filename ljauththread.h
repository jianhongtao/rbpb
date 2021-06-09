#ifndef LJAUTHTHREAD_H
#define LJAUTHTHREAD_H

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

class LjAuthThread : public QThread
{
    Q_OBJECT
public:
    ~LjAuthThread();

    static LjAuthThread*    instance();

public slots:
    void    onAuthRequest(const QString& userName, const QString& password, const QString& mountPoint);
    void    onOfflineNotify(const QString& userName);
    void    onHeartBeatNotify();

private slots:
    void    replyFinished(QNetworkReply *reply);

signals:
    void    errorString(const QString&);
    void    authReply(const CLIENT_INFO_S& info);

private:
    LjAuthThread(QObject *parent = nullptr);

    static LjAuthThread*        m_instance;
    QNetworkAccessManager*      m_networkManager;

    QTimer*                     m_heartBeatTimer;
    QString                     m_authServerIP;
    int                         m_authServerPort;
};

#endif // LJAUTHTHREAD_H
