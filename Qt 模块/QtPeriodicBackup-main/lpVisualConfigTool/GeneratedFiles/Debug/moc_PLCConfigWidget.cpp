/****************************************************************************
** Meta object code from reading C++ file 'PLCConfigWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PLCConfigWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PLCConfigWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PLCConfigWidget_t {
    QByteArrayData data[18];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PLCConfigWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PLCConfigWidget_t qt_meta_stringdata_PLCConfigWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PLCConfigWidget"
QT_MOC_LITERAL(1, 16, 14), // "sgSendShowTips"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "showTips"
QT_MOC_LITERAL(4, 41, 12), // "onSaveConfig"
QT_MOC_LITERAL(5, 54, 11), // "initConnect"
QT_MOC_LITERAL(6, 66, 10), // "onTestLink"
QT_MOC_LITERAL(7, 77, 22), // "onDiyItemDoubleClicked"
QT_MOC_LITERAL(8, 100, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(9, 118, 4), // "item"
QT_MOC_LITERAL(10, 123, 12), // "onUpdataData"
QT_MOC_LITERAL(11, 136, 9), // "fieldPath"
QT_MOC_LITERAL(12, 146, 11), // "updatedData"
QT_MOC_LITERAL(13, 158, 20), // "onAddDataToReadTable"
QT_MOC_LITERAL(14, 179, 7), // "newData"
QT_MOC_LITERAL(15, 187, 17), // "onSendCellChanged"
QT_MOC_LITERAL(16, 205, 3), // "row"
QT_MOC_LITERAL(17, 209, 3) // "col"

    },
    "PLCConfigWidget\0sgSendShowTips\0\0"
    "showTips\0onSaveConfig\0initConnect\0"
    "onTestLink\0onDiyItemDoubleClicked\0"
    "QTableWidgetItem*\0item\0onUpdataData\0"
    "fieldPath\0updatedData\0onAddDataToReadTable\0"
    "newData\0onSendCellChanged\0row\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PLCConfigWidget[] = {

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
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
      10,    2,   63,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      15,    2,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,   11,   12,
    QMetaType::Void, QMetaType::QVariantMap,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,

       0        // eod
};

void PLCConfigWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PLCConfigWidget *_t = static_cast<PLCConfigWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgSendShowTips((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = _t->onSaveConfig();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->initConnect(); break;
        case 3: _t->onTestLink(); break;
        case 4: _t->onDiyItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->onUpdataData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 6: _t->onAddDataToReadTable((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 7: _t->onSendCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PLCConfigWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCConfigWidget::sgSendShowTips)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PLCConfigWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PLCConfigWidget.data,
      qt_meta_data_PLCConfigWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PLCConfigWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCConfigWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PLCConfigWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PLCConfigWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void PLCConfigWidget::sgSendShowTips(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
