#ifndef CASTERROUTER_H
#define CASTERROUTER_H

#include <QString>
#include <QHash>

// 管理播发路由
class CasterRouter
{
private:
    CasterRouter(void);
    CasterRouter(const CasterRouter&);
    CasterRouter& operator=(const CasterRouter&);
    ~CasterRouter();
    
public:
    // 获取实例
    static CasterRouter* getInstance();

    // 注册Client
    void regCln(const QString& mp, void* ev, void* arg);
    
    // 注销Client
    void deregCln(const QString& mp, void* ev);
    
    // 获取Client
    QHash<void*, void*> getCln(const QString& mp) const;
    QHash<void*, void*> getCln() const;

    // 显示路由项
    void print() const;
    
private:
    static CasterRouter* instance;
    QHash<QString, QHash<void*, void*> > hashCln;
};

#endif // CASTERROUTER_H
