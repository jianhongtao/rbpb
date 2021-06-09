/****************************************************************************
** Meta object code from reading C++ file 'ljcastdatathreadpool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ljcastdatathreadpool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ljcastdatathreadpool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LjCastDataThreadPool_t {
    QByteArrayData data[21];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LjCastDataThreadPool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LjCastDataThreadPool_t qt_meta_stringdata_LjCastDataThreadPool = {
    {
QT_MOC_LITERAL(0, 0, 20), // "LjCastDataThreadPool"
QT_MOC_LITERAL(1, 21, 18), // "clientStateChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "threadID"
QT_MOC_LITERAL(4, 50, 10), // "ClientInfo"
QT_MOC_LITERAL(5, 61, 10), // "clientInfo"
QT_MOC_LITERAL(6, 72, 5), // "start"
QT_MOC_LITERAL(7, 78, 17), // "QThread::Priority"
QT_MOC_LITERAL(8, 96, 8), // "priority"
QT_MOC_LITERAL(9, 105, 4), // "init"
QT_MOC_LITERAL(10, 110, 11), // "threadCount"
QT_MOC_LITERAL(11, 122, 14), // "sendNewEphData"
QT_MOC_LITERAL(12, 137, 4), // "mnpt"
QT_MOC_LITERAL(13, 142, 7), // "EphData"
QT_MOC_LITERAL(14, 150, 4), // "data"
QT_MOC_LITERAL(15, 155, 10), // "processMsg"
QT_MOC_LITERAL(16, 166, 10), // "MSG_INFO_S"
QT_MOC_LITERAL(17, 177, 3), // "msg"
QT_MOC_LITERAL(18, 181, 17), // "slotNewConnection"
QT_MOC_LITERAL(19, 199, 4), // "sock"
QT_MOC_LITERAL(20, 204, 4) // "addr"

    },
    "LjCastDataThreadPool\0clientStateChanged\0"
    "\0threadID\0ClientInfo\0clientInfo\0start\0"
    "QThread::Priority\0priority\0init\0"
    "threadCount\0sendNewEphData\0mnpt\0EphData\0"
    "data\0processMsg\0MSG_INFO_S\0msg\0"
    "slotNewConnection\0sock\0addr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LjCastDataThreadPool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       6,    0,   62,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   63,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x2a /* Public | MethodCloned */,
      11,    2,   67,    2, 0x0a /* Public */,
      15,    1,   72,    2, 0x0a /* Public */,
      18,    2,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   12,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::VoidStar,   19,   20,

       0        // eod
};

void LjCastDataThreadPool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LjCastDataThreadPool *_t = static_cast<LjCastDataThreadPool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clientStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const ClientInfo(*)>(_a[2]))); break;
        case 1: _t->start((*reinterpret_cast< QThread::Priority(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->init((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->init(); break;
        case 5: _t->sendNewEphData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const EphData(*)>(_a[2]))); break;
        case 6: _t->processMsg((*reinterpret_cast< MSG_INFO_S(*)>(_a[1]))); break;
        case 7: _t->slotNewConnection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ClientInfo >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EphData >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MSG_INFO_S >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LjCastDataThreadPool::*_t)(const QString & , const ClientInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjCastDataThreadPool::clientStateChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LjCastDataThreadPool::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LjCastDataThreadPool.data,
      qt_meta_data_LjCastDataThreadPool,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LjCastDataThreadPool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LjCastDataThreadPool::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LjCastDataThreadPool.stringdata0))
        return static_cast<void*>(const_cast< LjCastDataThreadPool*>(this));
    return QObject::qt_metacast(_clname);
}

int LjCastDataThreadPool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void LjCastDataThreadPool::clientStateChanged(const QString & _t1, const ClientInfo & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
