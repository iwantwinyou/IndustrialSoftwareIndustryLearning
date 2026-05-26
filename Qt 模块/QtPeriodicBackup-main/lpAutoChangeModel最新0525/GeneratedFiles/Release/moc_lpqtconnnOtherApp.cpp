/****************************************************************************
** Meta object code from reading C++ file 'lpqtconnnOtherApp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lpqtconnnOtherApp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lpqtconnnOtherApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lpqtconnnOtherApp_t {
    QByteArrayData data[13];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lpqtconnnOtherApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lpqtconnnOtherApp_t qt_meta_stringdata_lpqtconnnOtherApp = {
    {
QT_MOC_LITERAL(0, 0, 17), // "lpqtconnnOtherApp"
QT_MOC_LITERAL(1, 18, 15), // "sgChangeJobName"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9), // "modelName"
QT_MOC_LITERAL(4, 45, 7), // "jobName"
QT_MOC_LITERAL(5, 53, 15), // "onNewConnection"
QT_MOC_LITERAL(6, 69, 16), // "on_data_received"
QT_MOC_LITERAL(7, 86, 14), // "on_socketError"
QT_MOC_LITERAL(8, 101, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 130, 3), // "err"
QT_MOC_LITERAL(10, 134, 12), // "on_send_data"
QT_MOC_LITERAL(11, 147, 8), // "isSucess"
QT_MOC_LITERAL(12, 156, 8) // "on_close"

    },
    "lpqtconnnOtherApp\0sgChangeJobName\0\0"
    "modelName\0jobName\0onNewConnection\0"
    "on_data_received\0on_socketError\0"
    "QAbstractSocket::SocketError\0err\0"
    "on_send_data\0isSucess\0on_close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lpqtconnnOtherApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,

       0        // eod
};

void lpqtconnnOtherApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lpqtconnnOtherApp *_t = static_cast<lpqtconnnOtherApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgChangeJobName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onNewConnection(); break;
        case 2: _t->on_data_received(); break;
        case 3: _t->on_socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->on_send_data((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (lpqtconnnOtherApp::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lpqtconnnOtherApp::sgChangeJobName)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject lpqtconnnOtherApp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_lpqtconnnOtherApp.data,
      qt_meta_data_lpqtconnnOtherApp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *lpqtconnnOtherApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lpqtconnnOtherApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lpqtconnnOtherApp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lpqtconnnOtherApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void lpqtconnnOtherApp::sgChangeJobName(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
