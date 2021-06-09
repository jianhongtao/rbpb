#include "UserTable.h"
#include "Common.h"

UserTable* UserTable::instance = 0;

UserTable::UserTable()
{

}

// 获取实例
UserTable* UserTable::getInstance()
{
    if(!instance)
    {
        instance = new UserTable();
    }

    return instance;
}

// 读取用户信息
bool UserTable::init(const QString& fileName)
{
    clear();

    QSettings settings(fileName, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
    {
        Log::send('W', QString("Open file %1 error").arg(fileName));
        return false;
    }

    int num = settings.beginReadArray("Users");
    if (num==0)
    {
        return false;
    }
    char buf[32];
    for(int i = 0; i < num; i++)
    {
        settings.setArrayIndex(i);
        UserEntry entry;

        entry.mnpt = settings.value("mnpt").toString();
        sprintf(buf, "%d%s\n", i+1, "\mnpt");
        CHECK_VALUE_LENGHT(entry.mnpt , 1, 64, buf);
        QHash<QString, UserEntry*>::const_iterator it = hashUser.find(entry.mnpt);
        if (it!=hashUser.end())
        {
            char buf[128];
            sprintf(buf, "mnpt is error, already has a mnpt named '%s'", entry.mnpt.toLocal8Bit().data());
            Log::send('E', buf);
            return false;
        }

        entry.name = settings.value("name").toString();
        sprintf(buf, "%d%s\n", i+1, "\name");
        CHECK_VALUE_LENGHT(entry.name , 1, 64, buf);

        entry.pass = settings.value("passwd").toString();
        sprintf(buf, "%d%s\n", i+1, "\name");
        CHECK_VALUE_LENGHT(entry.pass  , 1, 64, buf);

        entry.auth.insert(entry.mnpt);

        hashUser[entry.mnpt] = new UserEntry(entry);
    }
    settings.endArray();
    return true;
}

bool UserTable::verify(const QString& name, const QString& pass, const QString& mountPoint) const
{
    QHash<QString, UserEntry*>::const_iterator it = hashUser.find(mountPoint);
    if(it == hashUser.end())
    {
        return false;
    }

    const UserEntry* entry = it.value();
    if(entry->pass != pass || entry->name != name)
    {
        return false;
    }
    return entry->auth.contains(mountPoint);
}

// 显示用户信息
void UserTable::print() const
{
    printf("user number = %d\n", hashUser.size());
    QHash<QString, UserEntry*>::const_iterator ith;
    for(ith = hashUser.begin(); ith != hashUser.end(); ith++)
    {
        UserEntry* entry = ith.value();
        printf("%s %s", qPrintable(entry->name), qPrintable(entry->pass));
        QSet<QString>::const_iterator its;
        for(its = entry->auth.begin(); its != entry->auth.end(); its++)
        {
            printf(" %s", its->toLocal8Bit().data());
        }
        printf("\n");
    }
    printf("\n");
}

// 清空用户信息
void UserTable::clear()
{
    QHash<QString, UserEntry*>::iterator it;
    for(it = hashUser.begin(); it != hashUser.end(); it++)
    {
        delete it.value();
    }
    hashUser.clear();
}
