#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


// 发送日志信息
class Log
{
private:
    Log();
    ~Log();

public:
    // 发送日志
    static void send(char type, const QString& content);
};

#endif // LOG_H
