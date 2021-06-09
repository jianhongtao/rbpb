#ifndef USERTABLE_H
#define USERTABLE_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QVariant>
#include <QHash>
#include "Log.h"
#include "UserEntry.h"

// 用户信息表
class UserTable
{
private:
    UserTable(void);
    UserTable(const UserTable&);
    UserTable& operator=(const UserTable&);
    ~UserTable();

public:
    // 获取实例
    static UserTable* getInstance();

    // 读取用户信息
    bool init(const QString& fileName);
    
    // 验证用户身份和权限
    bool verify(const QString& name, const QString& pass, const QString& mountPoint) const;
    
    // 显示用户信息
    void print() const;
    
private:
    // 清空用户信息
    void clear();

private:
    static UserTable* instance;
    QHash<QString, UserEntry*> hashUser;
};

#endif // USERTABLE_H
