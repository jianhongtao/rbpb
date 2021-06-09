/****************************************************************************
** Meta object code from reading C++ file 'ljauththread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ljauththread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ljauththread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LjAuthThread_t {
    QByteArrayData data[15];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LjAuthThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LjAuthThread_t qt_meta_stringdata_LjAuthThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LjAuthThread"
QT_MOC_LITERAL(1, 13, 11), // "errorString"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "authReply"
QT_MOC_LITERAL(4, 36, 13), // "CLIENT_INFO_S"
QT_MOC_LITERAL(5, 50, 4), // "info"
QT_MOC_LITERAL(6, 55, 13), // "onAuthRequest"
QT_MOC_LITERAL(7, 69, 8), // "userName"
QT_MOC_LITERAL(8, 78, 8), // "password"
QT_MOC_LITERAL(9, 87, 10), // "mountPoint"
QT_MOC_LITERAL(10, 98, 15), // "onOfflineNotify"
QT_MOC_LITERAL(11, 114, 17), // "onHeartBeatNotify"
QT_MOC_LITERAL(12, 132, 13), // "replyFinished"
QT_MOC_LITERAL(13, 146, 14), // "QNetworkReply*"
QT_MOC_LITERAL(14, 161, 5) // "reply"

    },
    "LjAuthThread\0errorString\0\0authReply\0"
    "CLIENT_INFO_S\0info\0onAuthRequest\0"
    "userName\0password\0mountPoint\0"
    "onOfflineNotify\0onHeartBeatNotify\0"
    "replyFinished\0QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LjAuthThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   50,    2, 0x0a /* Public */,
      10,    1,   57,    2, 0x0a /* Public */,
      11,    0,   60,    2, 0x0a /* Public */,
      12,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void LjAuthThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LjAuthThread *_t = static_cast<LjAuthThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errorString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->authReply((*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[1]))); break;
        case 2: _t->onAuthRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->onOfflineNotify((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onHeartBeatNotify(); break;
        case 5: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LjAuthThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjAuthThread::errorString)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LjAuthThread::*_t)(const CLIENT_INFO_S & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjAuthThread::authReply)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LjAuthThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LjAuthThread.data,
      qt_meta_data_LjAuthThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LjAuthThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LjAuthThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LjAuthThread.stringdata0))
        return static_cast<void*>(const_cast< LjAuthThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LjAuthThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void LjAuthThread::errorString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LjAuthThread::authReply(const CLIENT_INFO_S & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
