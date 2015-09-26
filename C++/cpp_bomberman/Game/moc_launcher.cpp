/****************************************************************************
** Meta object code from reading C++ file 'launcher.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Menu/launcher.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'launcher.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Launcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      23,    9,    9,    9, 0x08,
      50,   46,   42,    9, 0x08,
      90,    9,    9,    9, 0x08,
     104,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Launcher[] = {
    "Launcher\0\0returnHome()\0enableButtonPlay()\0"
    "int\0,,,\0newRound(std::vector<int>&,int,int,int)\0"
    "launchGame1()\0launchGame2()\0"
};

void Launcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Launcher *_t = static_cast<Launcher *>(_o);
        switch (_id) {
        case 0: _t->returnHome(); break;
        case 1: _t->enableButtonPlay(); break;
        case 2: { int _r = _t->newRound((*reinterpret_cast< std::vector<int>(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: _t->launchGame1(); break;
        case 4: _t->launchGame2(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Launcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Launcher::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Launcher,
      qt_meta_data_Launcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Launcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Launcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Launcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Launcher))
        return static_cast<void*>(const_cast< Launcher*>(this));
    return QWidget::qt_metacast(_clname);
}

int Launcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
