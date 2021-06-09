#ifndef ARGS_H
#define ARGS_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QVariant>
#include <QHash>
#include <QHostInfo>
#include "Log.h"

// 管理进程运行参数
class Args
{
private:
    Args(void);
    Args(const Args&);
    Args& operator=(const Args&);
    ~Args();

public:
    // 获取实例
    static Args* getInstance();

    // 读取参数
    bool init(const QString& fileName);

    // 显示参数
    void print() const;

    // 获取参数
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
    bool CheckArgs();

public:
    QString hostName;
    QString procName;

private:
    static Args* instance;
    QHash<QString, QVariant> hashArgs;
};

#endif // ARGS_H
