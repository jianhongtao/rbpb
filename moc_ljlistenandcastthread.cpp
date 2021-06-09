/****************************************************************************
** Meta object code from reading C++ file 'ljlistenandcastthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ljlistenandcastthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ljlistenandcastthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LjListenAndCastThread_t {
    QByteArrayData data[15];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LjListenAndCastThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LjListenAndCastThread_t qt_meta_stringdata_LjListenAndCastThread = {
    {
QT_MOC_LITERAL(0, 0, 21), // "LjListenAndCastThread"
QT_MOC_LITERAL(1, 22, 18), // "clientStateChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 13), // "CLIENT_INFO_S"
QT_MOC_LITERAL(4, 56, 11), // "authRequest"
QT_MOC_LITERAL(5, 68, 8), // "userName"
QT_MOC_LITERAL(6, 77, 8), // "password"
QT_MOC_LITERAL(7, 86, 10), // "mountPoint"
QT_MOC_LITERAL(8, 97, 13), // "offlineNotify"
QT_MOC_LITERAL(9, 111, 16), // "onEphDataChanged"
QT_MOC_LITERAL(10, 128, 9), // "mnptconst"
QT_MOC_LITERAL(11, 138, 7), // "EphData"
QT_MOC_LITERAL(12, 146, 4), // "data"
QT_MOC_LITERAL(13, 151, 11), // "onAuthReply"
QT_MOC_LITERAL(14, 163, 5) // "reply"

    },
    "LjListenAndCastThread\0clientStateChanged\0"
    "\0CLIENT_INFO_S\0authRequest\0userName\0"
    "password\0mountPoint\0offlineNotify\0"
    "onEphDataChanged\0mnptconst\0EphData\0"
    "data\0onAuthReply\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LjListenAndCastThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    3,   42,    2, 0x06 /* Public */,
       8,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   52,    2, 0x0a /* Public */,
      13,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,   10,   12,
    QMetaType::Void, 0x80000000 | 3,   14,

       0        // eod
};

void LjListenAndCastThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LjListenAndCastThread *_t = static_cast<LjListenAndCastThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clientStateChanged((*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[1]))); break;
        case 1: _t->authRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: _t->offlineNotify((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onEphDataChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const EphData(*)>(_a[2]))); break;
        case 4: _t->onAuthReply((*reinterpret_cast< const CLIENT_INFO_S(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EphData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LjListenAndCastThread::*_t)(const CLIENT_INFO_S & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjListenAndCastThread::clientStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LjListenAndCastThread::*_t)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjListenAndCastThread::authRequest)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LjListenAndCastThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjListenAndCastThread::offlineNotify)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject LjListenAndCastThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LjListenAndCastThread.data,
      qt_meta_data_LjListenAndCastThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LjListenAndCastThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LjListenAndCastThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LjListenAndCastThread.stringdata0))
        return static_cast<void*>(const_cast< LjListenAndCastThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LjListenAndCastThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LjListenAndCastThread::clientStateChanged(const CLIENT_INFO_S & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LjListenAndCastThread::authRequest(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LjListenAndCastThread::offlineNotify(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
