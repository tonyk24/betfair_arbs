/****************************************************************************
** Meta object code from reading C++ file 'marketbookeapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../betfairapi/marketbookeapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'marketbookeapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MarketBookApi_t {
    QByteArrayData data[9];
    char stringdata[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MarketBookApi_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MarketBookApi_t qt_meta_stringdata_MarketBookApi = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MarketBookApi"
QT_MOC_LITERAL(1, 14, 12), // "valueChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "eventId"
QT_MOC_LITERAL(4, 36, 24), // "std::list<BetfairMarket>"
QT_MOC_LITERAL(5, 61, 7), // "markets"
QT_MOC_LITERAL(6, 69, 11), // "replyFinish"
QT_MOC_LITERAL(7, 81, 6), // "answer"
QT_MOC_LITERAL(8, 88, 27) // "valueChangedMarketCatalogue"

    },
    "MarketBookApi\0valueChanged\0\0eventId\0"
    "std::list<BetfairMarket>\0markets\0"
    "replyFinish\0answer\0valueChangedMarketCatalogue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarketBookApi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   34,    2, 0x0a /* Public */,
       8,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

       0        // eod
};

void MarketBookApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarketBookApi *_t = static_cast<MarketBookApi *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 1: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->valueChangedMarketCatalogue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MarketBookApi::*_t)(QString , std::list<BetfairMarket> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketBookApi::valueChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MarketBookApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MarketBookApi.data,
      qt_meta_data_MarketBookApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MarketBookApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarketBookApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MarketBookApi.stringdata))
        return static_cast<void*>(const_cast< MarketBookApi*>(this));
    return QObject::qt_metacast(_clname);
}

int MarketBookApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MarketBookApi::valueChanged(QString _t1, std::list<BetfairMarket> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
