#ifndef RCVRAWDATATHREAD_H
#define RCVRAWDATATHREAD_H

#include <QtCore>
#include "Common.h"
#include "Log.h"
#include "NtripArg.h"
#include "Rbpb.h"
#include "NtripArg.h"
#include "CasterRouter.h"
#include "SourceTable.h"
#include "UserTable.h"
#include "Args.h"
#include "ljephdata.h"

class LjRcvDataThread : public QThread
{
    Q_OBJECT
public:
    static LjRcvDataThread* instance();

protected:
    virtual void run();

signals:
    void    receivedNewData(const QString& mnpt, const QByteArray& data);

private:
    static LjRcvDataThread* m_instance;

    LjRcvDataThread(QObject *parent = nullptr);
};

#endif // RCVRAWDATATHREAD_H
