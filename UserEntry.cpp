#include "UserEntry.h"

UserEntry::UserEntry()
{

}

// 构造数据
bool UserEntry::makeData(const QString& str)
{
    QStringList data = str.split(";", QString::KeepEmptyParts);
    if(data.length() != 3)
    {
        return false;
    }
    for(int i = 0; i < data.length(); i++)
    {
        if(data[i].isEmpty())
        {
            return false;
        }
    }

    name = data[0];
    pass = data[1];

    data = data[2].split(",", QString::SkipEmptyParts);
    foreach(QString s, data)
    {
        auth.insert(s);
    }

    return true;
}
