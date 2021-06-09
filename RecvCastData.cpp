#include "RecvCastData.h"


Queue<QueueItemRcvMsg> RecvCastData::queue;


RecvCastData::RecvCastData()
{

}

RecvCastData::~RecvCastData()
{

}

// 获取队列长度
int RecvCastData::length()
{
    return queue.length();
}

// 数据出队列
bool RecvCastData::get(QString* msgID, QByteArray* msgData)
{
    QueueItemRcvMsg item;
    if(queue.get(item, false))
    {
        *msgID = item.id;
        *msgData = item.data;
        return true;
    }
    return false;
}

