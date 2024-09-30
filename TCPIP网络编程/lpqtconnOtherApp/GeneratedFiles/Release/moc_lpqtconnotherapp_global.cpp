/****************************************************************************
** Meta object code from reading C++ file 'lpqtconnotherapp_global.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lpqtconnotherapp_global.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lpqtconnotherapp_global.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lpconnOtherAppBase_t {
    QByteArrayData data[8];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lpconnOtherAppBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lpconnOtherAppBase_t qt_meta_stringdata_lpconnOtherAppBase = {
    {
QT_MOC_LITERAL(0, 0, 18), // "lpconnOtherAppBase"
QT_MOC_LITERAL(1, 19, 15), // "sgAskConnStatus"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15), // "sgConnectStatus"
QT_MOC_LITERAL(4, 52, 10), // "is_connect"
QT_MOC_LITERAL(5, 63, 15), // "sgChangeJobName"
QT_MOC_LITERAL(6, 79, 9), // "modelName"
QT_MOC_LITERAL(7, 89, 7) // "jobName"

    },
    "lpconnOtherAppBase\0sgAskConnStatus\0\0"
    "sgConnectStatus\0is_connect\0sgChangeJobName\0"
    "modelName\0jobName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lpconnOtherAppBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,
       5,    2,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,

       0        // eod
};

void lpconnOtherAppBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lpconnOtherAppBase *_t = static_cast<lpconnOtherAppBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgAskConnStatus(); break;
        case 1: _t->sgConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sgChangeJobName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (lpconnOtherAppBase::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpconnOtherAppBase::sgAskConnStatus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (lpconnOtherAppBase::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpconnOtherAppBase::sgConnectStatus)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (lpconnOtherAppBase::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpconnOtherAppBase::sgChangeJobName)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject lpconnOtherAppBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_lpconnOtherAppBase.data,
      qt_meta_data_lpconnOtherAppBase,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *lpconnOtherAppBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lpconnOtherAppBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lpconnOtherAppBase.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lpconnOtherAppBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void lpconnOtherAppBase::sgAskConnStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lpconnOtherAppBase::sgConnectStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lpconnOtherAppBase::sgChangeJobName(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
