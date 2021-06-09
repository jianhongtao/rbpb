#ifndef LJEPHDATA_H
#define LJEPHDATA_H

#include <QtCore>

typedef struct _stEphData_
{
    uint        type;   // data type;
    uint        satID;    //
    uint        sn;     // serial number
    QByteArray  data;   // data
}EphData;

typedef QPair<uint, uint> DataKey;

class LjEphData : public QObject
{
    Q_OBJECT
public:
    LjEphData(QObject *parent = nullptr);

    bool                parsePackage(const QByteArray& data);

    EphData             getNewEph();
    QVector<EphData>    getAllEph();

private:
    bool        parse_1019(QByteArray data);
    bool        parse_1020(QByteArray data);
    bool        parse_1042(QByteArray data);
    bool        parse_1044(QByteArray data);
    bool        parse_1045(QByteArray data);
    bool        parse_1046(QByteArray data);

    quint64     toUInt(QBitArray& bitArray, int start, int occupied);
    qint64      toInt(QBitArray& bitArray, int start, int occupied);

    QBitArray   byteArray2bitArray(QByteArray data);

    bool        isNewEph(uint type, uint satID, uint sn, QByteArray data);

private:
    QByteArray              m_dataArray;

    QMap<DataKey, EphData>  m_allEphData;
    QQueue<EphData>         m_newEphData;

    QMutex                  m_mutex;
};

class LjEphDataFactory : public QObject
{
    Q_OBJECT

public:
    static LjEphDataFactory*    instance();

    QMap<QString, LjEphData*>   getEphData();
    LjEphData*                  getEphData(const QString& mnpt);

public slots:
    void    parseData(const QString& mnpt, const QByteArray& data) ;

signals:
    void    ephDataChanged(const QString& mnpt, const EphData& data);

private:
    LjEphDataFactory(QObject *parent = nullptr);

    static  LjEphDataFactory*   m_instance;

    QMap<QString, LjEphData*>   m_map;
    QMutex                      m_mutex;
};

Q_DECLARE_METATYPE(EphData)
#endif // LJEPHDATA_H
