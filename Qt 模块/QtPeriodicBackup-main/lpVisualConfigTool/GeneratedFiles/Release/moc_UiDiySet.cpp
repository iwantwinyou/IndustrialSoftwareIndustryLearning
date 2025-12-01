/****************************************************************************
** Meta object code from reading C++ file 'UiDiySet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UiDiySet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UiDiySet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiDiySet_t {
    QByteArrayData data[13];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiDiySet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiDiySet_t qt_meta_stringdata_UiDiySet = {
    {
QT_MOC_LITERAL(0, 0, 8), // "UiDiySet"
QT_MOC_LITERAL(1, 9, 16), // "sgDiyDataUpdated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "parentKey"
QT_MOC_LITERAL(4, 37, 2), // "vm"
QT_MOC_LITERAL(5, 40, 14), // "sgSendShowTips"
QT_MOC_LITERAL(6, 55, 8), // "showTips"
QT_MOC_LITERAL(7, 64, 11), // "initConnect"
QT_MOC_LITERAL(8, 76, 28), // "onCustomContextMenuRequested"
QT_MOC_LITERAL(9, 105, 3), // "pos"
QT_MOC_LITERAL(10, 109, 8), // "onAddRow"
QT_MOC_LITERAL(11, 118, 11), // "onDeleteRow"
QT_MOC_LITERAL(12, 130, 22) // "onConfirmButtonClicked"

    },
    "UiDiySet\0sgDiyDataUpdated\0\0parentKey\0"
    "vm\0sgSendShowTips\0showTips\0initConnect\0"
    "onCustomContextMenuRequested\0pos\0"
    "onAddRow\0onDeleteRow\0onConfirmButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiDiySet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   57,    2, 0x08 /* Private */,
       8,    1,   58,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,
      11,    0,   62,    2, 0x08 /* Private */,
      12,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UiDiySet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiDiySet *_t = static_cast<UiDiySet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgDiyDataUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 1: _t->sgSendShowTips((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->initConnect(); break;
        case 3: _t->onCustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->onAddRow(); break;
        case 5: _t->onDeleteRow(); break;
        case 6: _t->onConfirmButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UiDiySet::*_t)(const QString & , const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiDiySet::sgDiyDataUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UiDiySet::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiDiySet::sgSendShowTips)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UiDiySet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UiDiySet.data,
      qt_meta_data_UiDiySet,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UiDiySet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiDiySet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UiDiySet.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int UiDiySet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UiDiySet::sgDiyDataUpdated(const QString & _t1, const QVariantMap & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UiDiySet::sgSendShowTips(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
