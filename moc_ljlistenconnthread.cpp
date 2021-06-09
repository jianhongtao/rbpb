/****************************************************************************
** Meta object code from reading C++ file 'ljlistenconnthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ljlistenconnthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ljlistenconnthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LjListenConnThread_t {
    QByteArrayData data[10];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LjListenConnThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LjListenConnThread_t qt_meta_stringdata_LjListenConnThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "LjListenConnThread"
QT_MOC_LITERAL(1, 19, 18), // "clientStateChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 8), // "threadID"
QT_MOC_LITERAL(4, 48, 10), // "ClientInfo"
QT_MOC_LITERAL(5, 59, 10), // "clientInfo"
QT_MOC_LITERAL(6, 70, 14), // "sendNewEphData"
QT_MOC_LITERAL(7, 85, 9), // "mnptconst"
QT_MOC_LITERAL(8, 95, 7), // "EphData"
QT_MOC_LITERAL(9, 103, 4) // "data"

    },
    "LjListenConnThread\0clientStateChanged\0"
    "\0threadID\0ClientInfo\0clientInfo\0"
    "sendNewEphData\0mnptconst\0EphData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LjListenConnThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,

       0        // eod
};

void LjListenConnThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LjListenConnThread *_t = static_cast<LjListenConnThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clientStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const ClientInfo(*)>(_a[2]))); break;
        case 1: _t->sendNewEphData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const EphData(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            typedef void (LjListenConnThread::*_t)(const QString & , const ClientInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LjListenConnThread::clientStateChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LjListenConnThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LjListenConnThread.data,
      qt_meta_data_LjListenConnThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LjListenConnThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LjListenConnThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LjListenConnThread.stringdata0))
        return static_cast<void*>(const_cast< LjListenConnThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LjListenConnThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LjListenConnThread::clientStateChanged(const QString & _t1, const ClientInfo & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
