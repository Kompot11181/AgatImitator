/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "on_pbOpen_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "on_pbSend_clicked"
QT_MOC_LITERAL(4, 48, 13), // "serialReceive"
QT_MOC_LITERAL(5, 62, 4), // "pack"
QT_MOC_LITERAL(6, 67, 10), // "serialSend"
QT_MOC_LITERAL(7, 78, 3), // "snd"
QT_MOC_LITERAL(8, 82, 18), // "on_pbClear_clicked"
QT_MOC_LITERAL(9, 101, 20), // "on_pbCalcCRC_clicked"
QT_MOC_LITERAL(10, 122, 17), // "on_pbPlus_clicked"
QT_MOC_LITERAL(11, 140, 18), // "on_pbMinus_clicked"
QT_MOC_LITERAL(12, 159, 26), // "on_leOutputData_textEdited"
QT_MOC_LITERAL(13, 186, 4), // "arg1"
QT_MOC_LITERAL(14, 191, 20), // "contextMenuRequested"
QT_MOC_LITERAL(15, 212, 18), // "copyFromOutputData"
QT_MOC_LITERAL(16, 231, 17), // "on_pbSave_clicked"
QT_MOC_LITERAL(17, 249, 17), // "on_pbLoad_clicked"
QT_MOC_LITERAL(18, 267, 13), // "keyPressEvent"
QT_MOC_LITERAL(19, 281, 10), // "QKeyEvent*"
QT_MOC_LITERAL(20, 292, 5) // "event"

    },
    "MainWindow\0on_pbOpen_clicked\0\0"
    "on_pbSend_clicked\0serialReceive\0pack\0"
    "serialSend\0snd\0on_pbClear_clicked\0"
    "on_pbCalcCRC_clicked\0on_pbPlus_clicked\0"
    "on_pbMinus_clicked\0on_leOutputData_textEdited\0"
    "arg1\0contextMenuRequested\0copyFromOutputData\0"
    "on_pbSave_clicked\0on_pbLoad_clicked\0"
    "keyPressEvent\0QKeyEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       6,    1,   89,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      14,    1,   99,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x08 /* Private */,
      18,    1,  105,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pbOpen_clicked(); break;
        case 1: _t->on_pbSend_clicked(); break;
        case 2: _t->serialReceive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->serialSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->on_pbClear_clicked(); break;
        case 5: _t->on_pbCalcCRC_clicked(); break;
        case 6: _t->on_pbPlus_clicked(); break;
        case 7: _t->on_pbMinus_clicked(); break;
        case 8: _t->on_leOutputData_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->contextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: _t->copyFromOutputData(); break;
        case 11: _t->on_pbSave_clicked(); break;
        case 12: _t->on_pbLoad_clicked(); break;
        case 13: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
