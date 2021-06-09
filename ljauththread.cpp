#include "ljauththread.h"
#include "Args.h"

LjAuthThread* LjAuthThread::m_instance=nullptr;

LjAuthThread::LjAuthThread(QObject *parent)
    :QThread(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    m_authServerIP  = Args::getInstance()->value("authServerIp").toString();
    m_authServerPort= Args::getInstance()->value("authServerPort").toInt();

    m_heartBeatTimer = new QTimer(this);
    m_heartBeatTimer->setInterval(60*1000);
    connect(m_heartBeatTimer, SIGNAL(timeout()), this, SLOT(onHeartBeatNotify()));
    m_heartBeatTimer->start();
}

LjAuthThread::~LjAuthThread()
{

}

void  LjAuthThread::onAuthRequest(const QString& userName, const QString& password, const QString& mountPoint)
{
    QNetworkRequest request;
    QUrl            url = QUrl(QString("http://%1:%2/user/account/auth")
                               .arg(m_authServerIP).arg(m_authServerPort));

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject     content;
    content.insert("username", QJsonValue(userName));
    content.insert("password", QJsonValue(password));
    content.insert("mountpoint", QJsonValue(mountPoint));
    QString servID = QString("EphCaster-%1").arg(QHostInfo::localHostName());
    content.insert("servID", QJsonValue(servID));
    content.insert("type", QJsonValue(1));
    QJsonDocument   jsonDoc(content);
    QByteArray temp = jsonDoc.toJson();

    m_networkManager->post(request, temp);
}

void  LjAuthThread::onOfflineNotify(const QString& userName)
{
    QNetworkRequest request;
    QUrl            url = QUrl(QString("http://%1:%2/user/account/offline")
                               .arg(m_authServerIP).arg(m_authServerPort));

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject     content;
    content.insert("username", QJsonValue(userName));
    QString servID = QString("EphCaster-%1").arg(QHostInfo::localHostName());
    content.insert("servID", QJsonValue(servID));
    content.insert("type", QJsonValue(1));
    QJsonDocument   jsonDoc(content);
    QByteArray temp = jsonDoc.toJson();

    m_networkManager->post(request, temp);
}

void LjAuthThread::onHeartBeatNotify()
{
    QNetworkRequest request;
    QUrl            url = QUrl(QString("http://%1:%2/user/account/heartbeat")
                               .arg(m_authServerIP).arg(m_authServerPort));

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setRawHeader(QByteArray("Content-Type"), "application/json");

    QJsonObject     content;
    QString servID = QString("EphCaster-%1").arg(QHostInfo::localHostName());
    content.insert("servID", QJsonValue(servID));
    content.insert("type", QJsonValue(1));
    QJsonDocument   jsonDoc(content);
    QByteArray temp = jsonDoc.toJson();

    m_networkManager->post(request, temp);
}

LjAuthThread* LjAuthThread::instance()
{
    if(!m_instance)
        m_instance = new LjAuthThread();

    return m_instance;
}


void   LjAuthThread::replyFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        QString err = reply->errorString();
        emit errorString(err);
        Log::send('W', QString("LjAuthThread: %1").arg(err));
     }
    else
    {
        QByteArray content = reply->readAll();
        QJsonDocument   jsonDoc = QJsonDocument::fromJson(content);
        QJsonObject     jsonObj = jsonDoc.object();

        if(!jsonObj.contains("code"))
        {
            Log::send('W', QString("LjAuthThread: Unknown reply"));
        }
        else
        {
            int code = jsonObj.value("code").toInt();

            if(code != 200)
            {
                Log::send('W', QString("LjAuthThread: Bad reply, code != 200"));
            }
            else
            {
                QNetworkRequest request = reply->request();
                if(request.url().path().contains("/user/account/auth"))
                {
                    QJsonObject data = jsonObj.value("data").toObject();
                    if(!data.isEmpty())
                    {
                        CLIENT_INFO_S   clientInfo;

                        clientInfo.authState    = data.value("status").toInt();
                        strcpy(clientInfo.authMessage, qPrintable(data.value("message").toString()));
                        strcpy(clientInfo.expireTime,  qPrintable(data.value("expireTime").toString()));
                        strcpy(clientInfo.userName, qPrintable(data.value("username").toString()));
                        strcpy(clientInfo.mountPoint,  qPrintable(data.value("mountpoint").toString()));

                        emit authReply(clientInfo);
                    }
                }
                else
                {
                    int xxx = 123;
                }
            }
        }

        //Log::send('R', QString::fromLocal8Bit(content));
    }

    reply->deleteLater();
}
