#ifndef RECVCASTDATA_H
#define RECVCASTDATA_H

#include <QString>
#include <QThread>
#include <QByteArray>
#include <string>
#include <vector>

#include "Queue.h"
#include "Common.h"

using std::string;
using std::vector;


class SecCastServer;

class RecvCastData
{
private:
     RecvCastData();
     ~RecvCastData();

     friend class SecCastServer;
public:

     // 获取队列长度
     int length();

     // 数据出队列
    static bool get(QString* msgID, QByteArray* msgData);

 private:

     static Queue<QueueItemRcvMsg> queue;

};


#endif // RECVCASTDATA_H
