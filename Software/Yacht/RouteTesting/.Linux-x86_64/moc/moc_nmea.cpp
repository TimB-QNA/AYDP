/****************************************************************************
** Meta object code from reading C++ file 'nmea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../nmea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nmea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NMEA_t {
    QByteArrayData data[33];
    char stringdata[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NMEA_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NMEA_t qt_meta_stringdata_NMEA = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 8),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 3),
QT_MOC_LITERAL(4, 19, 5),
QT_MOC_LITERAL(5, 25, 7),
QT_MOC_LITERAL(6, 33, 8),
QT_MOC_LITERAL(7, 42, 5),
QT_MOC_LITERAL(8, 48, 8),
QT_MOC_LITERAL(9, 57, 8),
QT_MOC_LITERAL(10, 66, 7),
QT_MOC_LITERAL(11, 74, 6),
QT_MOC_LITERAL(12, 81, 10),
QT_MOC_LITERAL(13, 92, 10),
QT_MOC_LITERAL(14, 103, 19),
QT_MOC_LITERAL(15, 123, 19),
QT_MOC_LITERAL(16, 143, 14),
QT_MOC_LITERAL(17, 158, 11),
QT_MOC_LITERAL(18, 170, 10),
QT_MOC_LITERAL(19, 181, 9),
QT_MOC_LITERAL(20, 191, 12),
QT_MOC_LITERAL(21, 204, 10),
QT_MOC_LITERAL(22, 215, 16),
QT_MOC_LITERAL(23, 232, 11),
QT_MOC_LITERAL(24, 244, 10),
QT_MOC_LITERAL(25, 255, 13),
QT_MOC_LITERAL(26, 269, 7),
QT_MOC_LITERAL(27, 277, 13),
QT_MOC_LITERAL(28, 291, 11),
QT_MOC_LITERAL(29, 303, 9),
QT_MOC_LITERAL(30, 313, 8),
QT_MOC_LITERAL(31, 322, 9),
QT_MOC_LITERAL(32, 332, 9)
    },
    "NMEA\0location\0\0fix\0speed\0heading\0"
    "altitude\0track\0VTGtrack\0VTGspeed\0"
    "logData\0time_t\0wind_speed\0wind_angle\0"
    "wind_speed_relative\0wind_angle_relative\0"
    "temp_sea_water\0speed_water\0dist_total\0"
    "dist_trip\0depth_offset\0depth_keel\0"
    "depth_transducer\0sat_in_view\0sat_active\0"
    "numActiveSats\0meanDOP\0horizontalDOP\0"
    "verticalDOP\0aisString\0openPort\0closePort\0"
    "parseData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NMEA[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      30,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  169,    2, 0x06 /* Public */,
       3,    1,  172,    2, 0x06 /* Public */,
       4,    1,  175,    2, 0x06 /* Public */,
       5,    1,  178,    2, 0x06 /* Public */,
       6,    1,  181,    2, 0x06 /* Public */,
       7,    1,  184,    2, 0x06 /* Public */,
       8,    1,  187,    2, 0x06 /* Public */,
       9,    1,  190,    2, 0x06 /* Public */,
      10,    2,  193,    2, 0x06 /* Public */,
      10,    3,  198,    2, 0x06 /* Public */,
      12,    1,  205,    2, 0x06 /* Public */,
      13,    1,  208,    2, 0x06 /* Public */,
      14,    1,  211,    2, 0x06 /* Public */,
      15,    1,  214,    2, 0x06 /* Public */,
      16,    1,  217,    2, 0x06 /* Public */,
      17,    1,  220,    2, 0x06 /* Public */,
      18,    1,  223,    2, 0x06 /* Public */,
      19,    1,  226,    2, 0x06 /* Public */,
      20,    1,  229,    2, 0x06 /* Public */,
      21,    1,  232,    2, 0x06 /* Public */,
      22,    1,  235,    2, 0x06 /* Public */,
      23,    4,  238,    2, 0x06 /* Public */,
      24,    1,  247,    2, 0x06 /* Public */,
      25,    1,  250,    2, 0x06 /* Public */,
      26,    1,  253,    2, 0x06 /* Public */,
      27,    1,  256,    2, 0x06 /* Public */,
      28,    1,  259,    2, 0x06 /* Public */,
      29,    1,  262,    2, 0x06 /* Public */,
      30,    0,  265,    2, 0x06 /* Public */,
      31,    0,  266,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    1,  267,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void NMEA::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NMEA *_t = static_cast<NMEA *>(_o);
        switch (_id) {
        case 0: _t->location((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->fix((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->speed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->heading((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->altitude((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->track((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->VTGtrack((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->VTGspeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->logData((*reinterpret_cast< time_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->logData((*reinterpret_cast< time_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 10: _t->wind_speed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->wind_angle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->wind_speed_relative((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->wind_angle_relative((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->temp_sea_water((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->speed_water((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->dist_total((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->dist_trip((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->depth_offset((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->depth_keel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->depth_transducer((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->sat_in_view((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 22: _t->sat_active((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->numActiveSats((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->meanDOP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->horizontalDOP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->verticalDOP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->aisString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->openPort(); break;
        case 29: _t->closePort(); break;
        case 30: _t->parseData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NMEA::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::location)) {
                *result = 0;
            }
        }
        {
            typedef void (NMEA::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::fix)) {
                *result = 1;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::speed)) {
                *result = 2;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::heading)) {
                *result = 3;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::altitude)) {
                *result = 4;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::track)) {
                *result = 5;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::VTGtrack)) {
                *result = 6;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::VTGspeed)) {
                *result = 7;
            }
        }
        {
            typedef void (NMEA::*_t)(time_t , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::logData)) {
                *result = 8;
            }
        }
        {
            typedef void (NMEA::*_t)(time_t , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::logData)) {
                *result = 9;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::wind_speed)) {
                *result = 10;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::wind_angle)) {
                *result = 11;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::wind_speed_relative)) {
                *result = 12;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::wind_angle_relative)) {
                *result = 13;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::temp_sea_water)) {
                *result = 14;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::speed_water)) {
                *result = 15;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::dist_total)) {
                *result = 16;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::dist_trip)) {
                *result = 17;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::depth_offset)) {
                *result = 18;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::depth_keel)) {
                *result = 19;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::depth_transducer)) {
                *result = 20;
            }
        }
        {
            typedef void (NMEA::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::sat_in_view)) {
                *result = 21;
            }
        }
        {
            typedef void (NMEA::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::sat_active)) {
                *result = 22;
            }
        }
        {
            typedef void (NMEA::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::numActiveSats)) {
                *result = 23;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::meanDOP)) {
                *result = 24;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::horizontalDOP)) {
                *result = 25;
            }
        }
        {
            typedef void (NMEA::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::verticalDOP)) {
                *result = 26;
            }
        }
        {
            typedef void (NMEA::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::aisString)) {
                *result = 27;
            }
        }
        {
            typedef void (NMEA::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::openPort)) {
                *result = 28;
            }
        }
        {
            typedef void (NMEA::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NMEA::closePort)) {
                *result = 29;
            }
        }
    }
}

const QMetaObject NMEA::staticMetaObject = {
    { &dataCollector::staticMetaObject, qt_meta_stringdata_NMEA.data,
      qt_meta_data_NMEA,  qt_static_metacall, 0, 0}
};


const QMetaObject *NMEA::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NMEA::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NMEA.stringdata))
        return static_cast<void*>(const_cast< NMEA*>(this));
    return dataCollector::qt_metacast(_clname);
}

int NMEA::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dataCollector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void NMEA::location(QPointF _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NMEA::fix(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NMEA::speed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NMEA::heading(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NMEA::altitude(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NMEA::track(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NMEA::VTGtrack(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void NMEA::VTGspeed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void NMEA::logData(time_t _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void NMEA::logData(time_t _t1, int _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void NMEA::wind_speed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void NMEA::wind_angle(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void NMEA::wind_speed_relative(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void NMEA::wind_angle_relative(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void NMEA::temp_sea_water(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void NMEA::speed_water(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void NMEA::dist_total(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void NMEA::dist_trip(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void NMEA::depth_offset(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void NMEA::depth_keel(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void NMEA::depth_transducer(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void NMEA::sat_in_view(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void NMEA::sat_active(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void NMEA::numActiveSats(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void NMEA::meanDOP(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void NMEA::horizontalDOP(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void NMEA::verticalDOP(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void NMEA::aisString(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void NMEA::openPort()
{
    QMetaObject::activate(this, &staticMetaObject, 28, 0);
}

// SIGNAL 29
void NMEA::closePort()
{
    QMetaObject::activate(this, &staticMetaObject, 29, 0);
}
QT_END_MOC_NAMESPACE
