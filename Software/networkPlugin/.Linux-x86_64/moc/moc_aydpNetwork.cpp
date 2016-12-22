/****************************************************************************
** Meta object code from reading C++ file 'aydpNetwork.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../aydpNetwork.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aydpNetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_aydpNetwork[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   12,   12,   12, 0x0a,
      45,   12,   12,   12, 0x0a,
      72,   66,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_aydpNetwork[] = {
    "aydpNetwork\0\0pluginRunning()\0"
    "connectToPeer()\0disconnectFromPeer()\0"
    "sckId\0readData(int)\0"
};

void aydpNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        aydpNetwork *_t = static_cast<aydpNetwork *>(_o);
        switch (_id) {
        case 0: _t->pluginRunning(); break;
        case 1: _t->connectToPeer(); break;
        case 2: _t->disconnectFromPeer(); break;
        case 3: _t->readData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData aydpNetwork::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject aydpNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_aydpNetwork,
      qt_meta_data_aydpNetwork, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &aydpNetwork::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *aydpNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *aydpNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_aydpNetwork))
        return static_cast<void*>(const_cast< aydpNetwork*>(this));
    if (!strcmp(_clname, "networkInterface"))
        return static_cast< networkInterface*>(const_cast< aydpNetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int aydpNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void aydpNetwork::pluginRunning()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
