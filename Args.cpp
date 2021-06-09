#include "Args.h"
#include "Common.h"

Args* Args::instance = 0;

Args::Args()
{
    hostName = QHostInfo::localHostName();
    procName = "RBPB";
}

// 获取实例
Args* Args::getInstance()
{
    if(!instance)
    {
        instance = new Args();
    }

    return instance;
}

// 读取参数
bool Args::init(const QString& fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
    {
        Log::send('E', QString("Open file %1 error").arg(fileName));
        return false;
    }

    QStringList keys = settings.allKeys();
    if (keys.length()==0)
    {
        return false;
    }
    foreach(QString key, keys)
    {
        hashArgs[key] = settings.value(key);
    }

    if (!CheckArgs())
        return false;

    return true;
}

bool Args::CheckArgs()
{
    QString value;

    value = hashArgs["casterId"].toString();
    CHECK_VALUE_LENGHT(value, 1, 64, "rbpb casterId");

    value = hashArgs["castPort"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb castPort");

    value = hashArgs["getDataPort"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb getDataPort");

    value = hashArgs["statPort"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb getDataPort");

    value = hashArgs["tcpTimeout"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb reportInt");

    value = hashArgs["reConnTime"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb reportInt");

    value = hashArgs["upLoadFileIntv"].toString();
    CHECK_VALUE_INT(value, 1, 0xFFFF, "rbpb reportInt");

#ifdef __SEND_EMPTY_IONO_PKT__
    value = hashArgs["emptyIonoMsgIntv"].toString();
    CHECK_VALUE_INT(value, 0, 0xFFFF, "rbpb emptyIonoMsgIntv");
#endif

    value = hashArgs["remoteIp"].toString();
    if (value.length()==0 || value.length()>256)
    {
        Log::send('E', "rbpb remoteIp is error");
        return false;
    }
    else
    {
       QStringList strList = value.split(',', QString::SkipEmptyParts);
       for (int i=0; i<strList.length(); i++)
       {
          CHECK_VALUE_LENGHT(value, 1, 64, "rbpb remoteIp");
       }
    }
    return true;
}

// 显示参数
void Args::print() const
{
    QHash<QString, QVariant>::const_iterator it;
    for(it = hashArgs.begin(); it != hashArgs.end(); it++)
    {
        printf("%s=%s\n",
               qPrintable(it.key()),
               qPrintable(it.value().toString()));
    }
}

// 获取参数
QVariant Args::value(const QString& key, const QVariant& defaultValue) const
{
    return hashArgs.value(key, defaultValue);
}
