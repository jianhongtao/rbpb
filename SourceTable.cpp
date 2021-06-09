#include "SourceTable.h"

SourceTable* SourceTable::instance = 0;

SourceTable::SourceTable()
{

}

// 获取实例
SourceTable* SourceTable::getInstance()
{
    if(!instance)
    {
        instance = new SourceTable();
    }

    return instance;
}

// 读取数据源表
bool SourceTable::init(const QString& fileName)
{
    clear();

    if(!readCaster(fileName))
    {
        return false;
    }
    
    if(!readNetwork(fileName))
    {
        return false;
    }

    if(!readSource(fileName))
    {
        return false;
    }

    sourceTable.append("ENDSOURCETABLE\r\n");
    
    return true;
}

// 获取数据源表
QByteArray SourceTable::get() const
{
    return sourceTable;
}

// 查找数据源
bool SourceTable::find(const QString& mountPoint, bool* auth) const
{
    QHash<QString, SourceEntry*>::const_iterator it = hashSource.find(mountPoint);
    if(it != hashSource.end())
    {
        *auth = it.value()->authentication;
        return true;
    }

    return false;
}

bool SourceTable::readCaster(const QString& fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
    {
        Log::send('W', QString("Open file %1 error").arg(fileName));
        return false;
    }

    int num = settings.beginReadArray("Casters");
    if (num==0)
        return false;
    bool ok = false;

    for(int i = 0; i < num; i++)
    {
        settings.setArrayIndex(i);

        CasterEntry entry;
        QVariant val;
        QStringList strList;

        strList.append("CAS");

        val = settings.value("host");
        entry.host = val.toString();
        if (entry.host > 128)
        {
            Log::send('E', "Casters host is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("port");
        entry.port = val.toInt();
        if (entry.port > 65535 || entry.port < 0)
        {
            Log::send('E', "Casters port is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("identifier");
        entry.identifier = val.toString();
        if (entry.identifier > 256)
        {
            Log::send('E', "Casters identifier is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("opName");
        entry.opName = val.toString();
        if (entry.opName > 256)
        {
            Log::send('E', "Casters opName is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("nmea");
        entry.nmea = val.toBool();
        if (val.toString() !="1" && val.toString() !="0" )
        {
            Log::send('E', "Casters nmea is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("country");
        entry.country = val.toString();
        if (entry.country > 256)
        {
            Log::send('E', "Casters country is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("latitude");
        entry.latitude = val.toDouble(&ok);
        if (!ok)
        {
            Log::send('E', "Casters latitude is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("longitude");
        entry.longitude = val.toDouble(&ok);
        if (!ok)
        {
            Log::send('E', "Casters longitude is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("fallbackHost");
        entry.fallbackHost = val.toString();

        if (entry.fallbackHost.length() > 256)
        {
            Log::send('E', "Casters fallbackHost is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("fallbackPort");
        entry.fallbackPort = val.toInt(&ok);
        if (!ok ||  entry.fallbackPort > 65535 || entry.fallbackPort < 0)
        {
            Log::send('E', "Casters fallbackPort is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("misc");
        entry.misc = val.toString();
        if (entry.misc.length() > 256)
        {
            Log::send('E', "Casters misc is error");
            return false;
        }
        strList.append(val.toString());

        listCaster.append(entry);

        sourceTable.append(strList.join(";"));
        sourceTable.append("\r\n");
    }
    settings.endArray();

    return true;
}

bool SourceTable::readNetwork(const QString& fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
    {
        Log::send('W', QString("Open file %1 error").arg(fileName));
        return false;
    }

    int num = settings.beginReadArray("Networks");
    if (num==0)
        return false;

    for(int i = 0; i < num; i++)
    {
        settings.setArrayIndex(i);

        NetworkEntry entry;
        QVariant val;
        QStringList strList;

        strList.append("NET");

        val = settings.value("identifier");
        entry.identifier = val.toString();

        if (entry.identifier.length() > 256)
        {
            Log::send('E', "Networks identifier is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("opName");
        entry.opName = val.toString();
        if (entry.opName.length() > 256)
        {
            Log::send('E', "Networks opName is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("authentication");

        entry.authentication = val.toString();
        if (entry.authentication.length() > 256)
        {
            Log::send('E', "Networks authentication is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("fee");
        entry.fee = val.toString();
        if (entry.fee.length() > 256)
        {
            Log::send('E', "Networks fee is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("webNet");
        entry.webNet = val.toString();
        if (entry.webNet.length() > 256)
        {
            Log::send('E', "Networks webNet is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("webStr");
        entry.webStr = val.toString();
        if (entry.webStr.length() > 256)
        {
            Log::send('E', "Networks webStr is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("webReg");
        entry.webReg = val.toString();
        if (entry.webReg.length() > 256)
        {
            Log::send('E', "Networks webReg is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("misc");
        entry.misc = val.toString();
        if (entry.misc.length() > 256)
        {
            Log::send('E', "Networks misc is error");
            return false;
        }
        strList.append(val.toString());

        listNetwork.append(entry);

        sourceTable.append(strList.join(";"));
        sourceTable.append("\r\n");
    }
    settings.endArray();

    return true;
}

bool SourceTable::readSource(const QString& fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
    {
        Log::send('W', QString("Open file %1 error").arg(fileName));
        return false;
    }

    int num = settings.beginReadArray("Sources");
    if (num==0)
        return false;
   bool ok;
    for(int i = 0; i < num; i++)
    {
        settings.setArrayIndex(i);

        SourceEntry entry;
        QVariant val;
        QStringList strList;

        strList.append("STR");

        val = settings.value("mountPoint");
        entry.mountPoint = val.toString();
        if (entry.mountPoint.length() > 256)
        {
            Log::send('E', "Sources mountPoint is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("identifier");
        entry.identifier = val.toString();
        if (entry.identifier.length() > 256)
        {
            Log::send('E', "Sources identifier is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("format");
        entry.format = val.toString();
        if (entry.format.length() > 256)
        {
            Log::send('E', "Sources format is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("formatDetails");
        entry.formatDetails = val.toString();
        if (entry.formatDetails.length() > 256)
        {
            Log::send('E', "Sources formatDetails is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("carrier");
        entry.carrier = val.toInt(&ok);
        if ( !ok)
        {
            Log::send('E', "Sources carrier is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("navSystem");
        entry.navSystem = val.toString();
        if (entry.navSystem.length() > 256)
        {
            Log::send('E', "Sources navSystem is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("network");
        entry.network = val.toString();
        if (entry.network.length() > 256)
        {
            Log::send('E', "Sources network is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("country");
        entry.country = val.toString();
        if (entry.network.length() > 256)
        {
            Log::send('E', "Sources country is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("latitude");
        entry.latitude = val.toDouble(&ok);
        if (!ok)
        {
            Log::send('E', "Sources latitude is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("longitude");
        entry.longitude = val.toDouble(&ok);
        if (!ok)
        {
            Log::send('E', "Sources longitude is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("nmea");
        entry.nmea = val.toBool();
        if (val.toString() != "1" && val.toString() != "0")
        {
            Log::send('E', "Sources nmea is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("solution");
        entry.solution = val.toBool();
        if (val.toString() != "1" && val.toString() != "0")
        {
            Log::send('E', "Sources solution is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("generator");
        entry.generator = val.toString();
        if (entry.generator .length() > 256)
        {
            Log::send('E', "Sources generator is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("comprEncryp");
        entry.comprEncryp = val.toString();
        if (entry.comprEncryp .length() > 256)
        {
            Log::send('E', "Sources comprEncryp is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("authentication");
        if (val.toString() != "N" && val.toString() !="Y")
        {
            Log::send('E', "Sources authentication is error");
            return false;
        }
        if(val.toString()=="N")
        {
            entry.authentication = false;
        }
        else
        {
            entry.authentication = true;
        }
        strList.append(val.toString());

        val = settings.value("fee");
        if (val.toString() != "N" && val.toString() !="Y")
        {
            Log::send('E', "Sources fee is error");
            return false;
        }
        if(val.toString()=="N")
        {
            entry.fee = false;
        }
        else
        {
            entry.fee = true;
        }
        strList.append(val.toString());

        val = settings.value("bitrate");
        entry.bitrate = val.toInt(&ok);
        if (!ok)
        {
            Log::send('E', "Sources bitrate is error");
            return false;
        }
        strList.append(val.toString());

        val = settings.value("misc");
        entry.misc = val.toString();
        if (entry.misc.length() > 1024)
        {
            Log::send('E', "Sources misc is error");
            return false;
        }
        strList.append(val.toString());

        hashSource[entry.mountPoint] = new SourceEntry(entry);

        sourceTable.append(strList.join(";"));
        sourceTable.append("\r\n");
    }
    settings.endArray();

    return true;
}

// 清空数据源表
void SourceTable::clear()
{
    listCaster.clear();

    listNetwork.clear();

    QHash<QString, SourceEntry*>::iterator it;
    for(it = hashSource.begin(); it != hashSource.end(); it++)
    {
        delete it.value();
    }
    hashSource.clear();

    sourceTable.clear();
}
