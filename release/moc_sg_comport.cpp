/****************************************************************************
** Meta object code from reading C++ file 'sg_comport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sg_comport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sg_comport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SgComPort_t {
    QByteArrayData data[11];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SgComPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SgComPort_t qt_meta_stringdata_SgComPort = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SgComPort"
QT_MOC_LITERAL(1, 10, 12), // "packRecieved"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "pack"
QT_MOC_LITERAL(4, 29, 5), // "error"
QT_MOC_LITERAL(5, 35, 11), // "errorString"
QT_MOC_LITERAL(6, 47, 4), // "read"
QT_MOC_LITERAL(7, 52, 9), // "com_error"
QT_MOC_LITERAL(8, 62, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(9, 91, 3), // "err"
QT_MOC_LITERAL(10, 95, 5) // "write"

    },
    "SgComPort\0packRecieved\0\0pack\0error\0"
    "errorString\0read\0com_error\0"
    "QSerialPort::SerialPortError\0err\0write"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SgComPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x08 /* Private */,
       7,    1,   46,    2, 0x08 /* Private */,
      10,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QByteArray,    3,

       0        // eod
};

void SgComPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SgComPort *_t = static_cast<SgComPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->packRecieved((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->read(); break;
        case 3: _t->com_error((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 4: _t->write((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SgComPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SgComPort::packRecieved)) {
                *result = 0;
            }
        }
        {
            typedef void (SgComPort::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SgComPort::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SgComPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SgComPort.data,
      qt_meta_data_SgComPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SgComPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SgComPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SgComPort.stringdata0))
        return static_cast<void*>(const_cast< SgComPort*>(this));
    return QObject::qt_metacast(_clname);
}

int SgComPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SgComPort::packRecieved(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SgComPort::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
