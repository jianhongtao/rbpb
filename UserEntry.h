#ifndef USERENTRY_H
#define USERENTRY_H

#include <QString>
#include <QStringList>
#include <QSet>

// 用户信息
class UserEntry
{
public:
    UserEntry();

public:
    // 构造数据
    bool makeData(const QString& str);
    
public:
    QString name;
    QString pass;
    QString mnpt;
    QSet<QString> auth;
};

#endif // USERENTRY_H
