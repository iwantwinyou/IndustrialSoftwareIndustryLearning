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
    QByteArrayData data[22];
    char stringdata0[259];
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
QT_MOC_LITERAL(7, 72, 16), // "sgSendCurJobInfo"
QT_MOC_LITERAL(8, 89, 27), // "QSharedPointer<QJsonObject>"
QT_MOC_LITERAL(9, 117, 10), // "curJobInfo"
QT_MOC_LITERAL(10, 128, 17), // "onAutoChangeModel"
QT_MOC_LITERAL(11, 146, 9), // "modelName"
QT_MOC_LITERAL(12, 156, 12), // "onRecvCurJob"
QT_MOC_LITERAL(13, 169, 6), // "curJob"
QT_MOC_LITERAL(14, 176, 15), // "onRecvModelName"
QT_MOC_LITERAL(15, 192, 3), // "cmd"
QT_MOC_LITERAL(16, 196, 2), // "vm"
QT_MOC_LITERAL(17, 199, 7), // "onStart"
QT_MOC_LITERAL(18, 207, 7), // "isStart"
QT_MOC_LITERAL(19, 215, 12), // "onRecvResult"
QT_MOC_LITERAL(20, 228, 10), // "onReqModel"
QT_MOC_LITERAL(21, 239, 19) // "onUndetectedTimeout"

    },
    "lpAutoChangeModel\0sgChangeModel\0\0model\0"
    "jobName\0sgChangeResult\0isSuccess\0"
    "sgSendCurJobInfo\0QSharedPointer<QJsonObject>\0"
    "curJobInfo\0onAutoChangeModel\0modelName\0"
    "onRecvCurJob\0curJob\0onRecvModelName\0"
    "cmd\0vm\0onStart\0isStart\0onRecvResult\0"
    "onReqModel\0onUndetectedTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lpAutoChangeModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    1,   69,    2, 0x06 /* Public */,
       7,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   75,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      14,    2,   83,    2, 0x0a /* Public */,
      17,    1,   88,    2, 0x0a /* Public */,
      19,    0,   91,    2, 0x0a /* Public */,
      20,    0,   92,    2, 0x0a /* Public */,
      21,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,    4,
    QMetaType::Void, 0x80000000 | 8,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,   15,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        case 2: _t->sgSendCurJobInfo((*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[1]))); break;
        case 3: _t->onAutoChangeModel((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onRecvCurJob((*reinterpret_cast< QSharedPointer<QJsonObject>(*)>(_a[1]))); break;
        case 5: _t->onRecvModelName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 6: _t->onStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onRecvResult(); break;
        case 8: _t->onReqModel(); break;
        case 9: _t->onUndetectedTimeout(); break;
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
        {
            typedef void (lpAutoChangeModel::*_t)(QSharedPointer<QJsonObject> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpAutoChangeModel::sgSendCurJobInfo)) {
                *result = 2;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
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

// SIGNAL 2
void lpAutoChangeModel::sgSendCurJobInfo(QSharedPointer<QJsonObject> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
