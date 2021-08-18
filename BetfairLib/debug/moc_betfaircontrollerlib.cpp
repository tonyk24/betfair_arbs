/****************************************************************************
** Meta object code from reading C++ file 'betfaircontrollerlib.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../betfaircontrollerlib.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'betfaircontrollerlib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BetfairControllerLib_t {
    QByteArrayData data[12];
    char stringdata[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BetfairControllerLib_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BetfairControllerLib_t qt_meta_stringdata_BetfairControllerLib = {
    {
QT_MOC_LITERAL(0, 0, 20), // "BetfairControllerLib"
QT_MOC_LITERAL(1, 21, 18), // "valueChangedEvents"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 23), // "std::list<BetFairEvent>"
QT_MOC_LITERAL(4, 65, 6), // "events"
QT_MOC_LITERAL(5, 72, 19), // "valueChangedMarkets"
QT_MOC_LITERAL(6, 92, 5), // "event"
QT_MOC_LITERAL(7, 98, 24), // "std::list<BetfairMarket>"
QT_MOC_LITERAL(8, 123, 7), // "markets"
QT_MOC_LITERAL(9, 131, 14), // "eventsReceived"
QT_MOC_LITERAL(10, 146, 15), // "marketsReceived"
QT_MOC_LITERAL(11, 162, 6) // "update"

    },
    "BetfairControllerLib\0valueChangedEvents\0"
    "\0std::list<BetFairEvent>\0events\0"
    "valueChangedMarkets\0event\0"
    "std::list<BetfairMarket>\0markets\0"
    "eventsReceived\0marketsReceived\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BetfairControllerLib[] = {

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
       5,    2,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   47,    2, 0x0a /* Public */,
      10,    2,   50,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    6,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    6,    8,
    QMetaType::Void,

       0        // eod
};

void BetfairControllerLib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BetfairControllerLib *_t = static_cast<BetfairControllerLib *>(_o);
        switch (_id) {
        case 0: _t->valueChangedEvents((*reinterpret_cast< std::list<BetFairEvent>(*)>(_a[1]))); break;
        case 1: _t->valueChangedMarkets((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 2: _t->eventsReceived((*reinterpret_cast< std::list<BetFairEvent>(*)>(_a[1]))); break;
        case 3: _t->marketsReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 4: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BetfairControllerLib::*_t)(std::list<BetFairEvent> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::valueChangedEvents)) {
                *result = 0;
            }
        }
        {
            typedef void (BetfairControllerLib::*_t)(QString , std::list<BetfairMarket> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::valueChangedMarkets)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BetfairControllerLib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BetfairControllerLib.data,
      qt_meta_data_BetfairControllerLib,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BetfairControllerLib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BetfairControllerLib::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BetfairControllerLib.stringdata))
        return static_cast<void*>(const_cast< BetfairControllerLib*>(this));
    return QObject::qt_metacast(_clname);
}

int BetfairControllerLib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void BetfairControllerLib::valueChangedEvents(std::list<BetFairEvent> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BetfairControllerLib::valueChangedMarkets(QString _t1, std::list<BetfairMarket> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
