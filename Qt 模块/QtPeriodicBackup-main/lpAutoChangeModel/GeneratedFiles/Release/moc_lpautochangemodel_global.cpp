/****************************************************************************
** Meta object code from reading C++ file 'lpautochangemodel_global.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lpautochangemodel_global.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lpautochangemodel_global.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lpAutoChangeModelMgr_t {
    QByteArrayData data[24];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lpAutoChangeModelMgr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lpAutoChangeModelMgr_t qt_meta_stringdata_lpAutoChangeModelMgr = {
    {
QT_MOC_LITERAL(0, 0, 20), // "lpAutoChangeModelMgr"
QT_MOC_LITERAL(1, 21, 7), // "sgStart"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "isStart"
QT_MOC_LITERAL(4, 38, 8), // "sgNewJob"
QT_MOC_LITERAL(5, 47, 27), // "QSharedPointer<QJsonObject>"
QT_MOC_LITERAL(6, 75, 6), // "newJob"
QT_MOC_LITERAL(7, 82, 11), // "sgAskCurJob"
QT_MOC_LITERAL(8, 94, 10), // "sgReadData"
QT_MOC_LITERAL(9, 105, 3), // "cmd"
QT_MOC_LITERAL(10, 109, 7), // "bAppend"
QT_MOC_LITERAL(11, 117, 12), // "sgAlarmPLCEx"
QT_MOC_LITERAL(12, 130, 4), // "data"
QT_MOC_LITERAL(13, 135, 13), // "sgSendWarning"
QT_MOC_LITERAL(14, 149, 4), // "info"
QT_MOC_LITERAL(15, 154, 4), // "type"
QT_MOC_LITERAL(16, 159, 6), // "vparam"
QT_MOC_LITERAL(17, 166, 13), // "sgPartDbReady"
QT_MOC_LITERAL(18, 180, 12), // "onRecvCurJob"
QT_MOC_LITERAL(19, 193, 6), // "curJob"
QT_MOC_LITERAL(20, 200, 15), // "onRecvModelName"
QT_MOC_LITERAL(21, 216, 2), // "vm"
QT_MOC_LITERAL(22, 219, 7), // "onStart"
QT_MOC_LITERAL(23, 227, 12) // "onRecvResult"

    },
    "lpAutoChangeModelMgr\0sgStart\0\0isStart\0"
    "sgNewJob\0QSharedPointer<QJsonObject>\0"
    "newJob\0sgAskCurJob\0sgReadData\0cmd\0"
    "bAppend\0sgAlarmPLCEx\0data\0sgSendWarning\0"
    "info\0type\0vparam\0sgPartDbReady\0"
    "onRecvCurJob\0curJob\0onRecvModelName\0"
    "vm\0onStart\0onRecvResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lpAutoChangeModelMgr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       7,    0,   85,    2, 0x06 /* Public */,
       8,    2,   86,    2, 0x06 /* Public */,
       8,    1,   91,    2, 0x26 /* Public | MethodCloned */,
      11,    3,   94,    2, 0x06 /* Public */,
      11,    2,  101,    2, 0x26 /* Public | MethodCloned */,
      13,    3,  106,    2, 0x06 /* Public */,
      17,    0,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,  114,    2, 0x0a /* Public */,
      20,    2,  117,    2, 0x0a /* Public */,
      22,    1,  122,    2, 0x0a /* Public */,
      23,    0,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    9,   12,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QVariant,   14,   15,   16,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    9,   21,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void lpAutoChangeModelMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lpAutoChangeModelMgr *_t = static_cast<lpAutoChangeModelMgr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sgNewJob((*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[1]))); break;
        case 2: _t->sgAskCurJob(); break;
        case 3: _t->sgReadData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->sgReadData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sgAlarmPLCEx((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: _t->sgAlarmPLCEx((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->sgSendWarning((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 8: _t->sgPartDbReady(); break;
        case 9: _t->onRecvCurJob((*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[1]))); break;
        case 10: _t->onRecvModelName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 11: _t->onStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->onRecvResult(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (lpAutoChangeModelMgr::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)(QSharedPointer<QJsonObject> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgNewJob)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgAskCurJob)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgReadData)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)(const QString & , const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgAlarmPLCEx)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)(QString , int , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgSendWarning)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModelMgr::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModelMgr::sgPartDbReady)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject lpAutoChangeModelMgr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_lpAutoChangeModelMgr.data,
      qt_meta_data_lpAutoChangeModelMgr,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *lpAutoChangeModelMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lpAutoChangeModelMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lpAutoChangeModelMgr.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lpAutoChangeModelMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void lpAutoChangeModelMgr::sgStart(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lpAutoChangeModelMgr::sgNewJob(QSharedPointer<QJsonObject> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lpAutoChangeModelMgr::sgAskCurJob()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void lpAutoChangeModelMgr::sgReadData(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 5
void lpAutoChangeModelMgr::sgAlarmPLCEx(const QString & _t1, const QString & _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 7
void lpAutoChangeModelMgr::sgSendWarning(QString _t1, int _t2, QVariant _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void lpAutoChangeModelMgr::sgPartDbReady()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
