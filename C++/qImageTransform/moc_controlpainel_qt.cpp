/****************************************************************************
** Meta object code from reading C++ file 'controlpainel_qt.h'
**
** Created: Mon Mar 9 22:54:20 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controlpainel_qt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpainel_qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlPainel_qt[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      27,   18,   17,   17, 0x05,
      46,   17,   17,   17, 0x05,
      59,   17,   17,   17, 0x05,
      72,   17,   17,   17, 0x05,
      86,   17,   17,   17, 0x05,
     100,   17,   17,   17, 0x05,
     115,   17,   17,   17, 0x05,
     130,   17,   17,   17, 0x05,
     139,   17,   17,   17, 0x05,
     154,  148,   17,   17, 0x05,
     175,  148,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     196,   17,   17,   17, 0x08,
     203,   17,   17,   17, 0x08,
     215,   17,   17,   17, 0x08,
     227,   17,   17,   17, 0x08,
     240,   17,   17,   17, 0x08,
     253,   17,   17,   17, 0x08,
     267,   17,   17,   17, 0x08,
     281,   17,   17,   17, 0x08,
     289,   17,   17,   17, 0x08,
     297,  148,   17,   17, 0x08,
     317,  148,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlPainel_qt[] = {
    "ControlPainel_qt\0\0fileName\0"
    "pressOpen(QString)\0sDrawLineA()\0"
    "sDrawLineB()\0sClearLineA()\0sClearLineB()\0"
    "sFilterLineA()\0sFilterLineB()\0sMaskA()\0"
    "sMaskB()\0state\0sStateShowMaskA(int)\0"
    "sStateShowMaskB(int)\0open()\0drawLineA()\0"
    "drawLineB()\0clearLineA()\0clearLineB()\0"
    "filterLineA()\0filterLineB()\0maskA()\0"
    "maskB()\0stateShowMaskA(int)\0"
    "stateShowMaskB(int)\0"
};

const QMetaObject ControlPainel_qt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlPainel_qt,
      qt_meta_data_ControlPainel_qt, 0 }
};

const QMetaObject *ControlPainel_qt::metaObject() const
{
    return &staticMetaObject;
}

void *ControlPainel_qt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPainel_qt))
        return static_cast<void*>(const_cast< ControlPainel_qt*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlPainel_qt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pressOpen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: sDrawLineA(); break;
        case 2: sDrawLineB(); break;
        case 3: sClearLineA(); break;
        case 4: sClearLineB(); break;
        case 5: sFilterLineA(); break;
        case 6: sFilterLineB(); break;
        case 7: sMaskA(); break;
        case 8: sMaskB(); break;
        case 9: sStateShowMaskA((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: sStateShowMaskB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: open(); break;
        case 12: drawLineA(); break;
        case 13: drawLineB(); break;
        case 14: clearLineA(); break;
        case 15: clearLineB(); break;
        case 16: filterLineA(); break;
        case 17: filterLineB(); break;
        case 18: maskA(); break;
        case 19: maskB(); break;
        case 20: stateShowMaskA((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: stateShowMaskB((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void ControlPainel_qt::pressOpen(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlPainel_qt::sDrawLineA()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ControlPainel_qt::sDrawLineB()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ControlPainel_qt::sClearLineA()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ControlPainel_qt::sClearLineB()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ControlPainel_qt::sFilterLineA()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ControlPainel_qt::sFilterLineB()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ControlPainel_qt::sMaskA()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void ControlPainel_qt::sMaskB()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void ControlPainel_qt::sStateShowMaskA(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ControlPainel_qt::sStateShowMaskB(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
