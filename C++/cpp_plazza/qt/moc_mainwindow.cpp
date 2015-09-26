/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   11,   11,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      53,   11,   11,   11, 0x0a,
      66,   11,   11,   11, 0x0a,
      80,   11,   11,   11, 0x0a,
      95,   11,   11,   11, 0x0a,
     111,   11,   11,   11, 0x0a,
     127,   11,   11,   11, 0x0a,
     143,   11,   11,   11, 0x0a,
     160,   11,   11,   11, 0x0a,
     178,   11,   11,   11, 0x0a,
     195,   11,   11,   11, 0x0a,
     212,   11,   11,   11, 0x0a,
     229,   11,   11,   11, 0x0a,
     247,   11,   11,   11, 0x0a,
     266,   11,   11,   11, 0x0a,
     281,   11,   11,   11, 0x0a,
     296,   11,   11,   11, 0x0a,
     311,   11,   11,   11, 0x0a,
     327,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0askForRegina()\0askReginaS()\0"
    "askReginaM()\0askReginaL()\0askReginaXL()\0"
    "askReginaXXL()\0askMargaritaS()\0"
    "askMargaritaM()\0askMargaritaL()\0"
    "askMargaritaXL()\0askMargaritaXXL()\0"
    "askAmericaineS()\0askAmericaineM()\0"
    "askAmericaineL()\0askAmericaineXL()\0"
    "askAmericaineXXL()\0askFantasiaS()\0"
    "askFantasiaM()\0askFantasiaL()\0"
    "askFantasiaXL()\0askFantasiaXXL()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->askForRegina(); break;
        case 1: _t->askReginaS(); break;
        case 2: _t->askReginaM(); break;
        case 3: _t->askReginaL(); break;
        case 4: _t->askReginaXL(); break;
        case 5: _t->askReginaXXL(); break;
        case 6: _t->askMargaritaS(); break;
        case 7: _t->askMargaritaM(); break;
        case 8: _t->askMargaritaL(); break;
        case 9: _t->askMargaritaXL(); break;
        case 10: _t->askMargaritaXXL(); break;
        case 11: _t->askAmericaineS(); break;
        case 12: _t->askAmericaineM(); break;
        case 13: _t->askAmericaineL(); break;
        case 14: _t->askAmericaineXL(); break;
        case 15: _t->askAmericaineXXL(); break;
        case 16: _t->askFantasiaS(); break;
        case 17: _t->askFantasiaM(); break;
        case 18: _t->askFantasiaL(); break;
        case 19: _t->askFantasiaXL(); break;
        case 20: _t->askFantasiaXXL(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::askForRegina()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
