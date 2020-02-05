/****************************************************************************
** Meta object code from reading C++ file 'koralsetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../koralsetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'koralsetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_cKoralSetting_t {
    QByteArrayData data[25];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cKoralSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cKoralSetting_t qt_meta_stringdata_cKoralSetting = {
    {
QT_MOC_LITERAL(0, 0, 13), // "cKoralSetting"
QT_MOC_LITERAL(1, 14, 7), // "setAddr"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "adr"
QT_MOC_LITERAL(4, 27, 7), // "setType"
QT_MOC_LITERAL(5, 35, 4), // "type"
QT_MOC_LITERAL(6, 40, 12), // "setFixedType"
QT_MOC_LITERAL(7, 53, 6), // "setErr"
QT_MOC_LITERAL(8, 60, 2), // "er"
QT_MOC_LITERAL(9, 63, 7), // "setStat"
QT_MOC_LITERAL(10, 71, 2), // "st"
QT_MOC_LITERAL(11, 74, 7), // "setRnd1"
QT_MOC_LITERAL(12, 82, 3), // "rnd"
QT_MOC_LITERAL(13, 86, 7), // "setRnd2"
QT_MOC_LITERAL(14, 94, 9), // "setValue1"
QT_MOC_LITERAL(15, 104, 1), // "v"
QT_MOC_LITERAL(16, 106, 9), // "setValue2"
QT_MOC_LITERAL(17, 116, 7), // "setInc1"
QT_MOC_LITERAL(18, 124, 1), // "i"
QT_MOC_LITERAL(19, 126, 7), // "setInc2"
QT_MOC_LITERAL(20, 134, 9), // "incValue1"
QT_MOC_LITERAL(21, 144, 9), // "incValue2"
QT_MOC_LITERAL(22, 154, 10), // "randValue1"
QT_MOC_LITERAL(23, 165, 10), // "randValue2"
QT_MOC_LITERAL(24, 176, 16) // "restoreFromBlink"

    },
    "cKoralSetting\0setAddr\0\0adr\0setType\0"
    "type\0setFixedType\0setErr\0er\0setStat\0"
    "st\0setRnd1\0rnd\0setRnd2\0setValue1\0v\0"
    "setValue2\0setInc1\0i\0setInc2\0incValue1\0"
    "incValue2\0randValue1\0randValue2\0"
    "restoreFromBlink"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cKoralSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x0a /* Public */,
       4,    1,   97,    2, 0x0a /* Public */,
       6,    0,  100,    2, 0x0a /* Public */,
       7,    1,  101,    2, 0x0a /* Public */,
       9,    1,  104,    2, 0x0a /* Public */,
      11,    1,  107,    2, 0x0a /* Public */,
      13,    1,  110,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      16,    1,  116,    2, 0x0a /* Public */,
      17,    1,  119,    2, 0x0a /* Public */,
      19,    1,  122,    2, 0x0a /* Public */,
      20,    0,  125,    2, 0x0a /* Public */,
      21,    0,  126,    2, 0x0a /* Public */,
      22,    0,  127,    2, 0x0a /* Public */,
      23,    0,  128,    2, 0x0a /* Public */,
      24,    0,  129,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void cKoralSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cKoralSetting *_t = static_cast<cKoralSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setAddr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setFixedType(); break;
        case 3: _t->setErr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setStat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setRnd1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setRnd2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setValue1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setValue2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setInc1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setInc2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->incValue1(); break;
        case 12: _t->incValue2(); break;
        case 13: _t->randValue1(); break;
        case 14: _t->randValue2(); break;
        case 15: _t->restoreFromBlink(); break;
        default: ;
        }
    }
}

const QMetaObject cKoralSetting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cKoralSetting.data,
      qt_meta_data_cKoralSetting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *cKoralSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cKoralSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_cKoralSetting.stringdata0))
        return static_cast<void*>(const_cast< cKoralSetting*>(this));
    return QWidget::qt_metacast(_clname);
}

int cKoralSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
