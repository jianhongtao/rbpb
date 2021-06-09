#ifndef SOURCETABLE_H
#define SOURCETABLE_H

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QVariant>
#include <QList>
#include <QHash>
#include "Log.h"
#include "CasterEntry.h"
#include "NetworkEntry.h"
#include "SourceEntry.h"

// 数据源表
class SourceTable
{
private:
    SourceTable(void);
    SourceTable(const SourceTable&);
    SourceTable& operator=(const SourceTable&);
    ~SourceTable();
    
public:
    // 获取实例
    static SourceTable* getInstance();
    
    // 读取数据源表
    bool init(const QString& fileName);
    
    // 获取数据源表
    QByteArray get() const;
    
    // 查找数据源
    bool find(const QString& mountPoint, bool* auth) const;
    
private:
    bool readCaster(const QString& fileName);
    bool readNetwork(const QString& fileName);
    bool readSource(const QString& fileName);
    
    // 清空数据源表
    void clear();
    
private:
    static SourceTable* instance;
    QList<CasterEntry> listCaster;
    QList<NetworkEntry> listNetwork;
    QHash<QString, SourceEntry*> hashSource;
    QByteArray sourceTable;
};

#endif // SOURCETABLE_H
