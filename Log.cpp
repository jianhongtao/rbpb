#include "Log.h"
#include "Args.h"
#include "ljstatisticsendthread.h"

void Log::send(char type, const QString& content)
{
    Args* args = Args::getInstance();
    QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
    QJsonObject msg;
    msg.insert("msgID", "IM_LOG");
    msg.insert("hostName", args->hostName);
    msg.insert("type", QString(type));
    msg.insert("time", curTime);
    msg.insert("proc", args->procName);
    msg.insert("content", content);
    //ThdSndMsg::put("IM_LOG", QJsonDocument(msg).toJson());

    QString log;
    if((type == 'R') || (type == 'r'))
    {
        log = QString("[RUN ");
    }
    else if((type == 'W') || (type == 'w'))
    {
        log = QString("[WRN ");
    }
    else
    {
        log = QString("[ERR ");
    }
    log += curTime + "] ";
    log += content;
    qDebug() << log;

    MSG_INFO_S  message;
    message.type = msg_data_log;
    strcpy(message.logInfo.content, QJsonDocument(msg).toJson().data());

    FDS_S pipe = LjStatisticSendThread::instance()->cmdChannel();
    write(pipe.wfd, &message, sizeof(MSG_INFO_S));
}
