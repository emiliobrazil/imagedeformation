/****************************************************************************
** Meta object code from reading C++ file 'qimagetransform.h'
**
** Created: Mon Mar 9 23:02:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qimagetransform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qimagetransform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qImageTransform[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      29,   16,   16,   16, 0x0a,
      41,   16,   16,   16, 0x0a,
      54,   16,   16,   16, 0x0a,
      67,   16,   16,   16, 0x0a,
      81,   16,   16,   16, 0x0a,
      95,   16,   16,   16, 0x0a,
     108,   16,   16,   16, 0x0a,
     127,  121,   16,   16, 0x0a,
     147,  121,   16,   16, 0x0a,
     167,   16,   16,   16, 0x08,
     188,  179,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_qImageTransform[] = {
    "qImageTransform\0\0drawLineA()\0drawLineB()\0"
    "clearLineA()\0clearLineB()\0filterLineA()\0"
    "filterLineB()\0buildMaskA()\0buildMaskB()\0"
    "state\0stateShowMaskA(int)\0stateShowMaskB(int)\0"
    "drawImage()\0fileName\0loadImage(QString)\0"
};

const QMetaObject qImageTransform::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qImageTransform,
      qt_meta_data_qImageTransform, 0 }
};

const QMetaObject *qImageTransform::metaObject() const
{
    return &staticMetaObject;
}

void *qImageTransform::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qImageTransform))
        return static_cast<void*>(const_cast< qImageTransform*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qImageTransform::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: drawLineA(); break;
        case 1: drawLineB(); break;
        case 2: clearLineA(); break;
        case 3: clearLineB(); break;
        case 4: filterLineA(); break;
        case 5: filterLineB(); break;
        case 6: buildMaskA(); break;
        case 7: buildMaskB(); break;
        case 8: stateShowMaskA((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: stateShowMaskB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: drawImage(); break;
        case 11: loadImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
