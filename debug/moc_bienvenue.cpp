/****************************************************************************
** Meta object code from reading C++ file 'bienvenue.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bienvenue.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bienvenue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_bienvenue_t {
    QByteArrayData data[12];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bienvenue_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bienvenue_t qt_meta_stringdata_bienvenue = {
    {
QT_MOC_LITERAL(0, 0, 9), // "bienvenue"
QT_MOC_LITERAL(1, 10, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 57, 35), // "on_identifier_cursorPositionC..."
QT_MOC_LITERAL(5, 93, 6), // "oldPos"
QT_MOC_LITERAL(6, 100, 6), // "newPos"
QT_MOC_LITERAL(7, 107, 12), // "onTagScanned"
QT_MOC_LITERAL(8, 120, 3), // "uid"
QT_MOC_LITERAL(9, 124, 16), // "slot_emailStatus"
QT_MOC_LITERAL(10, 141, 7), // "message"
QT_MOC_LITERAL(11, 149, 23) // "on_pushButton_3_clicked"

    },
    "bienvenue\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0"
    "on_identifier_cursorPositionChanged\0"
    "oldPos\0newPos\0onTagScanned\0uid\0"
    "slot_emailStatus\0message\0"
    "on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bienvenue[] = {

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
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    2,   46,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       9,    1,   54,    2, 0x08 /* Private */,
      11,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void bienvenue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        bienvenue *_t = static_cast<bienvenue *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_identifier_cursorPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onTagScanned((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slot_emailStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject bienvenue::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_bienvenue.data,
      qt_meta_data_bienvenue,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *bienvenue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bienvenue::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_bienvenue.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int bienvenue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
