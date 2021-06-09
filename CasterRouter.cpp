#include "CasterRouter.h"

CasterRouter* CasterRouter::instance = 0;

CasterRouter::CasterRouter()
{

}

// 获取实例
CasterRouter* CasterRouter::getInstance()
{
    if(!instance)
    {
        instance = new CasterRouter();
    }

    return instance;
}

void CasterRouter::regCln(const QString& mp, void* ev, void* arg)
{
    QHash<QString, QHash<void*, void*> >::iterator it = hashCln.find(mp);
    if(it == hashCln.end())
    {
        QHash<void*, void*> entry;
        entry[ev] = arg;
        hashCln[mp] = entry;
    }
    else
    {
        QHash<void*, void*>& entry = it.value();
        QHash<void*, void*>::iterator itt = entry.find(ev);
        if(itt == entry.end())
        {
            entry[ev] = arg;
        }
    }
}

void CasterRouter::deregCln(const QString& mp, void* ev)
{
    QHash<QString, QHash<void*, void*> >::iterator it = hashCln.find(mp);
    if(it != hashCln.end())
    {
        QHash<void*, void*>& entry = it.value();
        entry.remove(ev);
        if(entry.isEmpty())
        {
            hashCln.remove(mp);
        }
    }
}

// 获取路由
QHash<void*, void*> CasterRouter::getCln(const QString& mp) const
{
    QHash<QString, QHash<void*, void*> >::const_iterator it = hashCln.find(mp);
    if(it != hashCln.end())
    {
        return it.value();
    }
    else
    {
        return QHash<void*, void*>();
    }
}

// 获取路由
QHash<void*, void*> CasterRouter::getCln() const
{
    QHash<void*, void*> ret;

    QHash<QString, QHash<void*, void*> >::const_iterator it = hashCln.begin();
    for(it = hashCln.begin(); it != hashCln.end(); ++it)
    {
        QHash<void*, void*>::const_iterator itt;
        for(itt = it.value().begin(); itt != it.value().end(); ++itt)
        {
            ret[itt.key()] = itt.value();
        }
    }

    return ret;
}

// 显示路由项
void CasterRouter::print() const
{
    printf("client table length = %d\n", hashCln.size());
    QHash<QString, QHash<void*, void*> >::const_iterator it;
    for(it = hashCln.begin(); it != hashCln.end(); it++)
    {
        printf("  %s = %d\n", it.key().toLocal8Bit().data(), it.value().size());
    }
    printf("\n");
}
