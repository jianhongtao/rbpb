#include "ljephdata.h"
#include "Log.h"

//#define SEND_ALL

#define CRC24_INIT 0x000000 //b704ce
#define CRC24_POLY 0x864cfb

unsigned long crc24_calc(unsigned char *octets, unsigned int len)
{
    unsigned long crc = CRC24_INIT;
    int i;
    while (len--)
    {
        crc^= (*octets++)<<16;
        for (i=0;i<8;i++)
        {
            crc <<= 1;
            if (crc&0x1000000)
                crc^= CRC24_POLY;
        }
    }
    return crc& 0xffffffL;
}

//----------------------------------------------
LjEphDataFactory*  LjEphDataFactory::m_instance=nullptr;

LjEphDataFactory::LjEphDataFactory(QObject *parent)
    : QObject(parent)
{

}

LjEphDataFactory*    LjEphDataFactory::instance()
{
    if(!m_instance)
        m_instance = new LjEphDataFactory();

    return m_instance;
}

QMap<QString, LjEphData*>  LjEphDataFactory::getEphData()
{
    QMutexLocker locker(&m_mutex);

    return m_map;
}

LjEphData* LjEphDataFactory::getEphData(const QString& mnpt)
{
    QMutexLocker locker(&m_mutex);

    LjEphData* pEphData;
    if(!m_map.contains(mnpt))
    {
       pEphData = new LjEphData(this);
       m_map.insert(mnpt, pEphData);
    }
    else
    {
        pEphData = m_map.value(mnpt);
    }

    return pEphData;
}

void   LjEphDataFactory::parseData(const QString& mnpt, const QByteArray& data)
{
    if(getEphData(mnpt)->parsePackage(data))
    {
        EphData          newData;

        while(!(newData=getEphData(mnpt)->getNewEph()).data.isEmpty())
        {
            emit ephDataChanged(mnpt, newData);
        }
    }
    else
    {
        //Log::send('R', "Receive data, but not new eph");
    }
}

//-----------------------------------------------
LjEphData::LjEphData(QObject *parent)
    : QObject(parent)
{

}

//LjEphData* LjEphData::getInstance()
//{
//    if(!m_instance)
//        m_instance = new LjEphData();

//    return m_instance;
//}


QBitArray   LjEphData::byteArray2bitArray(QByteArray data)
{
    QBitArray bitArray;

    bitArray.resize(data.size()*8);

    for(int i=0; i<data.size(); i++)
    {
        uchar ch = data.at(i);

        for(int j=0; j<8; j++)
        {
            bool b = ch>>j & 0x1;
            bitArray.setBit(i*8+7-j, b);
        }
    }

    return bitArray;
}

bool  LjEphData::isNewEph(uint type, uint satID, uint sn, QByteArray data)
{
    bool isNew = false;

    DataKey key=qMakePair(type, satID);

    EphData ephData;
    if(m_allEphData.contains(key))
    {
        ephData = m_allEphData.value(key);
        if(ephData.sn != sn)
        {
            ephData.sn   = sn;
            ephData.data = data;

            isNew = true;
        }
    }
    else
    {
        ephData.type = type;
        ephData.satID= satID;
        ephData.sn   = sn;
        ephData.data = data;

        isNew = true;
    }

#ifdef SEND_ALL
    isNew = true;
#endif

    if(isNew)
    {
        m_allEphData.insert(key, ephData);

        m_newEphData.enqueue(ephData);
        if(m_newEphData.count()>50)
            m_newEphData.dequeue();
    }

    return isNew;
}

// GPS 星历
bool    LjEphData::parse_1019(QByteArray data)
{
    uint    type = 1019;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 6);   // GPS Satellite ID
    sn    = toUInt(bitArray, 48, 8);   // GPS IODE

    return  isNewEph(type, satID, sn, data);
}

// GLONASS 星历
bool    LjEphData::parse_1020(QByteArray data)
{
    uint    type = 1020;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 6);   // GLONASS Satellite ID (Satellite Slot Number)
    sn    = toUInt(bitArray, 41, 7);   // GLONASS tb

    return  isNewEph(type, satID, sn, data);
}

// BDS 星历
bool    LjEphData::parse_1042(QByteArray data)
{
    uint    type = 1042;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 6);       // BDS Satellite ID DF488 uint6 6
    sn    = toUInt(bitArray, 299, 17);     // BDS toe

    return  isNewEph(type, satID, sn, data);
}

// QZSS 星历
bool    LjEphData::parse_1044(QByteArray data)
{
    uint    type = 1044;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 4);       // QZSS Satellite ID
    sn    = toUInt(bitArray, 78, 8);       // QZSS IODE

    return  isNewEph(type, satID, sn, data);
}

// Galileo F/NAV 星历
bool    LjEphData::parse_1045(QByteArray data)
{
    uint    type = 1045;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 6);       // Galileo Satellite ID
    sn    = toUInt(bitArray, 30, 10);      // Galileo IODnav

    return  isNewEph(type, satID, sn, data);
}

// Galileo I/NAV 星历
bool    LjEphData::parse_1046(QByteArray data)
{
    uint    type = 1046;
    uint    satID;
    uint    sn;

    QByteArray content = data.mid(3, data.length()-6);

    QBitArray bitArray = byteArray2bitArray(content);

    satID = toUInt(bitArray, 12, 6);       // Galileo Satellite ID
    sn    = toUInt(bitArray, 30, 10);      // Galileo IODnav

    return  isNewEph(type, satID, sn, data);
}

quint64 LjEphData::toUInt(QBitArray& bitArray, int start, int occupied)
{
    quint64 value = 0;

    if(bitArray.count()<start+occupied)
        return value;

    for(int i=start; i<start+occupied; i++)
    {
        value <<= 1;
        value += (int)bitArray.at(i);
    }

    return value;
}

qint64  LjEphData::toInt(QBitArray& bitArray, int start, int occupied)
{
    qint64 value = 0;

    if(bitArray.count()<start+occupied)
        return value;

    bool negtive = bitArray.at(start);

    for(int i=start+1; i<start+occupied; i++)
    {
        value <<= 1;
        if(!negtive)
            value += bitArray.at(i)?1:0;
        else
            value += bitArray.at(i)?0:1;
    }

    if(negtive)
        value = -(value+1);

    return value;
}


// 解析数据包, 如果有新的星历数据返回true否则false, 数据接收线程调用此函数
bool    LjEphData::parsePackage(const QByteArray& data)
{
    QMutexLocker locker(&m_mutex);

    bool    ret = false;

    m_dataArray.append(data);

    while(m_dataArray.length()>=5)
    {
        bool    b;
        quint32 header = m_dataArray.left(3).toHex().toUInt(&b, 16);

        if((header>>16&0xFF) == 0xD3)
        {
            quint32 type;
            quint32 len = header&0x3FF;

            type = m_dataArray.mid(3, 2).toHex().toUInt(&b, 16);
            type = type>>4;

            // not enough data
            if(m_dataArray.length() < len+6)
            {
                break;
            }

            quint32     crc24 = m_dataArray.mid(3+len, 3).toHex().toUInt(&b, 16);

            quint32 temp = crc24_calc((unsigned char*)m_dataArray.data(), len+3);

            if(crc24 == temp)
            {
                QByteArray  frame = m_dataArray.mid(0, len+6);
                switch(type)
                {
                case 1019:
                    ret = ret?ret:parse_1019(frame);
                break;
                case 1020:
                    ret = ret?ret:parse_1020(frame);
                break;
                case 1042:
                    ret = ret?ret:parse_1042(frame);
                break;
                case 1044:
                    ret = ret?ret:parse_1044(frame);
                break;
                case 1045:
                    ret = ret?ret:parse_1045(frame);
                break;
                case 1046:
                    ret = ret?ret:parse_1046(frame);
                break;
                default:
                break;
                }
            }

            m_dataArray = m_dataArray.right(m_dataArray.length()-len-6);
        }
        else
        {
            m_dataArray.clear();
        }
    }

    return ret;
}

// 获取最新星历数据，数据播发线程调用此函数
EphData          LjEphData::getNewEph()
{
    QMutexLocker locker(&m_mutex);

    EphData  newEph;

    if(!m_newEphData.isEmpty())
        newEph = m_newEphData.dequeue();

    return newEph;
}

// 获取完整的星历数据，数据播发线程调用此函数
QVector<EphData>   LjEphData::getAllEph()
{
    QMutexLocker locker(&m_mutex);

    QVector<EphData>   allEph;

    foreach(EphData eph, m_allEphData.values())
    {
        allEph.append(eph);
    }

    return allEph;
}
