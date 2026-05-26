/****************************************************************************
** Meta object code from reading C++ file 'lpAutoChangeModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lpAutoChangeModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lpAutoChangeModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lpAutoChangeModel_t {
    QByteArrayData data[12];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lpAutoChangeModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lpAutoChangeModel_t qt_meta_stringdata_lpAutoChangeModel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "lpAutoChangeModel"
QT_MOC_LITERAL(1, 18, 13), // "sgChangeModel"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "model"
QT_MOC_LITERAL(4, 39, 7), // "jobName"
QT_MOC_LITERAL(5, 47, 14), // "sgChangeResult"
QT_MOC_LITERAL(6, 62, 9), // "isSuccess"
QT_MOC_LITERAL(7, 72, 17), // "onAutoChangeModel"
QT_MOC_LITERAL(8, 90, 9), // "modelName"
QT_MOC_LITERAL(9, 100, 12), // "onRecvCurJob"
QT_MOC_LITERAL(10, 113, 27), // "QSharedPointer<QJsonObject>"
QT_MOC_LITERAL(11, 141, 6) // "curJob"

    },
    "lpAutoChangeModel\0sgChangeModel\0\0model\0"
    "jobName\0sgChangeResult\0isSuccess\0"
    "onAutoChangeModel\0modelName\0onRecvCurJob\0"
    "QSharedPointer<QJsonObject>\0curJob"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lpAutoChangeModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   42,    2, 0x0a /* Public */,
       9,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    4,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void lpAutoChangeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lpAutoChangeModel *_t = static_cast<lpAutoChangeModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgChangeModel((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->sgChangeResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onAutoChangeModel((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->onRecvCurJob((*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (lpAutoChangeModel::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModel::sgChangeModel)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (lpAutoChangeModel::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModel::sgChangeResult)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject lpAutoChangeModel::staticMetaObject = {
    { &lpAutoChangeModelMgr::staticMetaObject, qt_meta_stringdata_lpAutoChangeModel.data,
      qt_meta_data_lpAutoChangeModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *lpAutoChangeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lpAutoChangeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lpAutoChangeModel.stringdata0))
        return static_cast<void*>(this);
    return lpAutoChangeModelMgr::qt_metacast(_clname);
}

int lpAutoChangeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = lpAutoChangeModelMgr::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void lpAutoChangeModel::sgChangeModel(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lpAutoChangeModel::sgChangeResult(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_PLCChangeProcess_t {
    QByteArrayData data[19];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PLCChangeProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PLCChangeProcess_t qt_meta_stringdata_PLCChangeProcess = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PLCChangeProcess"
QT_MOC_LITERAL(1, 17, 7), // "onStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "isStart"
QT_MOC_LITERAL(4, 34, 12), // "onRecvResult"
QT_MOC_LITERAL(5, 47, 15), // "onRecvModelName"
QT_MOC_LITERAL(6, 63, 3), // "cmd"
QT_MOC_LITERAL(7, 67, 2), // "vm"
QT_MOC_LITERAL(8, 70, 17), // "onAutoChangeModel"
QT_MOC_LITERAL(9, 88, 9), // "modelName"
QT_MOC_LITERAL(10, 98, 7), // "jobName"
QT_MOC_LITERAL(11, 106, 15), // "onRecvUi2Master"
QT_MOC_LITERAL(12, 122, 3), // "key"
QT_MOC_LITERAL(13, 126, 27), // "QSharedPointer<QJsonObject>"
QT_MOC_LITERAL(14, 154, 9), // "json_sptr"
QT_MOC_LITERAL(15, 164, 18), // "onRecvUIConnStatus"
QT_MOC_LITERAL(16, 183, 12), // "is_connected"
QT_MOC_LITERAL(17, 196, 10), // "onReqModel"
QT_MOC_LITERAL(18, 207, 19) // "onUndetectedTimeout"

    },
    "PLCChangeProcess\0onStart\0\0isStart\0"
    "onRecvResult\0onRecvModelName\0cmd\0vm\0"
    "onAutoChangeModel\0modelName\0jobName\0"
    "onRecvUi2Master\0key\0QSharedPointer<QJsonObject>\0"
    "json_sptr\0onRecvUIConnStatus\0is_connected\0"
    "onReqModel\0onUndetectedTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PLCChangeProcess[] = {

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
       4,    0,   57,    2, 0x0a /* Public */,
       5,    2,   58,    2, 0x0a /* Public */,
       8,    2,   63,    2, 0x0a /* Public */,
      11,    2,   68,    2, 0x0a /* Public */,
      15,    1,   73,    2, 0x0a /* Public */,
      17,    0,   76,    2, 0x08 /* Private */,
      18,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PLCChangeProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PLCChangeProcess *_t = static_cast<PLCChangeProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onRecvResult(); break;
        case 2: _t->onRecvModelName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 3: _t->onAutoChangeModel((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onRecvUi2Master((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[2]))); break;
        case 5: _t->onRecvUIConnStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onReqModel(); break;
        case 7: _t->onUndetectedTimeout(); break;
        default: ;
        }
    }
}

const QMetaObject PLCChangeProcess::staticMetaObject = {
    { &lpAutoChangeModel::staticMetaObject, qt_meta_stringdata_PLCChangeProcess.data,
      qt_meta_data_PLCChangeProcess,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PLCChangeProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCChangeProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PLCChangeProcess.stringdata0))
        return static_cast<void*>(this);
    return lpAutoChangeModel::qt_metacast(_clname);
}

int PLCChangeProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = lpAutoChangeModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_OtherAppChangeProcess_t {
    QByteArrayData data[17];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OtherAppChangeProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OtherAppChangeProcess_t qt_meta_stringdata_OtherAppChangeProcess = {
    {
QT_MOC_LITERAL(0, 0, 21), // "OtherAppChangeProcess"
QT_MOC_LITERAL(1, 22, 7), // "onStart"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "isStart"
QT_MOC_LITERAL(4, 39, 12), // "onRecvResult"
QT_MOC_LITERAL(5, 52, 15), // "onRecvModelName"
QT_MOC_LITERAL(6, 68, 3), // "cmd"
QT_MOC_LITERAL(7, 72, 2), // "vm"
QT_MOC_LITERAL(8, 75, 17), // "onAutoChangeModel"
QT_MOC_LITERAL(9, 93, 9), // "modelName"
QT_MOC_LITERAL(10, 103, 7), // "jobName"
QT_MOC_LITERAL(11, 111, 15), // "onRecvUi2Master"
QT_MOC_LITERAL(12, 127, 3), // "key"
QT_MOC_LITERAL(13, 131, 27), // "QSharedPointer<QJsonObject>"
QT_MOC_LITERAL(14, 159, 9), // "json_sptr"
QT_MOC_LITERAL(15, 169, 18), // "onRecvUIConnStatus"
QT_MOC_LITERAL(16, 188, 12) // "is_connected"

    },
    "OtherAppChangeProcess\0onStart\0\0isStart\0"
    "onRecvResult\0onRecvModelName\0cmd\0vm\0"
    "onAutoChangeModel\0modelName\0jobName\0"
    "onRecvUi2Master\0key\0QSharedPointer<QJsonObject>\0"
    "json_sptr\0onRecvUIConnStatus\0is_connected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OtherAppChangeProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    0,   47,    2, 0x0a /* Public */,
       5,    2,   48,    2, 0x0a /* Public */,
       8,    2,   53,    2, 0x0a /* Public */,
      11,    2,   58,    2, 0x0a /* Public */,
      15,    1,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void OtherAppChangeProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OtherAppChangeProcess *_t = static_cast<OtherAppChangeProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onRecvResult(); break;
        case 2: _t->onRecvModelName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 3: _t->onAutoChangeModel((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onRecvUi2Master((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[2]))); break;
        case 5: _t->onRecvUIConnStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject OtherAppChangeProcess::staticMetaObject = {
    { &lpAutoChangeModel::staticMetaObject, qt_meta_stringdata_OtherAppChangeProcess.data,
      qt_meta_data_OtherAppChangeProcess,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OtherAppChangeProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OtherAppChangeProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OtherAppChangeProcess.stringdata0))
        return static_cast<void*>(this);
    return lpAutoChangeModel::qt_metacast(_clname);
}

int OtherAppChangeProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = lpAutoChangeModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
