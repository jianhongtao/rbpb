/****************************************************************************
** Meta object code from reading C++ file 'ljstatisticsendthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ljstatisticsendthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ljstatisticsendthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MonitorArg_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MonitorArg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MonitorArg_t qt_meta_stringdata_MonitorArg = {
    {
QT_MOC_LITERAL(0, 0, 10) // "MonitorArg"

    },
    "MonitorArg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MonitorArg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MonitorArg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject MonitorArg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MonitorArg.data,
      qt_meta_data_MonitorArg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MonitorArg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MonitorArg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MonitorArg.stringdata0))
        return static_cast<void*>(const_cast< MonitorArg*>(this));
    return QObject::qt_metacast(_clname);
}

int MonitorArg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_LjStatisticSendThread_t {
    QByteArrayData data[16];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LjStatisticSendThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LjStatisticSendThread_t qt_meta_stringdata_LjStatisticSendThread = {
    {
QT_MOC_LITERAL(0, 0, 21), // "LjStatisticSendThread"
QT_MOC_LITERAL(1, 22, 11), // "sendEphData"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "EPH_DATA_S"
QT_MOC_LITERAL(4, 46, 4), // "data"
QT_MOC_LITERAL(5, 51, 11), // "MonitorArg*"
QT_MOC_LITERAL(6, 63, 7), // "monitor"
QT_MOC_LITERAL(7, 71, 4), // "mnpt"
QT_MOC_LITERAL(8, 76, 7), // "EphData"
QT_MOC_LITERAL(9, 84, 14), // "sendClientData"
QT_MOC_LITERAL(10, 99, 13), // "CLIENT_INFO_S"
QT_MOC_LITERAL(11, 113, 11), // "sendLogInfo"
QT_MOC_LITERAL(12, 125, 10), // "LOG_INFO_S"
QT_MOC_LITERAL(13, 136, 3), // "log"
QT_MOC_LITERAL(14, 140, 20), // "onClientStateChanged"
QT_MOC_LITERAL(15, 161, 16) // "onEphDataChanged"

    },
    "LjStatisticSendThread\0sendEphData\0\0"
    "EPH_DATA_S\0data\0MonitorArg*\0monitor\0"
    "mnpt\0EphData\0sendClientData\0CLIENT_INFO_S\0"
    "sendLogInfo\0LOG_INFO_S\0log\0"
    "onClientStateChanged\0onEphDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LjStatisticSendThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       1,    3,   57,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
       9,    2,   67,    2, 0x0a /* Public */,
      11,    1,   72,    2, 0x0a /* Public */,
      11,    2,   75,    2, 0x0a /* Public */,
      14,    1,   80,    2, 0x0a /* Public */,
      15,    2,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, 0x80000000 | 8,    6,    7,    4,
    QMetaType::Void, 0x80000000 | 10,    4,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,    6,    4,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 12,    6,   13,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    4,

       0        // eod
};

void LjStatisticSendThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LjStatisticSendThread *_t = static_cast<LjStatisticSendThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEphData((*reinterpret_cast< const EPH_DATA_S(*)>(_a[1]))); break;
        case 1: _t->sendEphData((*reinterpret_cast< MonitorArg*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const EphData(*)>(_a[3]))); break;
        case 2: _t->sendClientData((*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[1]))); break;
        case 3: _t->sendClientData((*reinterpret_cast< MonitorArg*(*)>(_a[1])),(*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[2]))); break;
        case 4: _t->sendLogInfo((*reinterpret_cast< const LOG_INFO_S(*)>(_a[1]))); break;
        case 5: _t->sendLogInfo((*reinterpret_cast< MonitorArg*(*)>(_a[1])),(*reinterpret_cast< const LOG_INFO_S(*)>(_a[2]))); break;
        case 6: _t->onClientStateChanged((*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[1]))); break;
        case 7: _t->onEphDataChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const EphData(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EphData >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MonitorArg* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MonitorArg* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MonitorArg* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EphData >(); break;
            }
            break;
        }
    }
}

const QMetaObject LjStatisticSendThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LjStatisticSendThread.data,
      qt_meta_data_LjStatisticSendThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LjStatisticSendThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LjStatisticSendThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LjStatisticSendThread.stringdata0))
        return static_cast<void*>(const_cast< LjStatisticSendThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LjStatisticSendThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
