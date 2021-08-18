/****************************************************************************
** Meta object code from reading C++ file 'marketcatalogueapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../github_BetfairLib/BetfairLib/betfairapi/marketcatalogueapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'marketcatalogueapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BfLib__MarketCatalogueApi_t {
    QByteArrayData data[12];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BfLib__MarketCatalogueApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BfLib__MarketCatalogueApi_t qt_meta_stringdata_BfLib__MarketCatalogueApi = {
    {
QT_MOC_LITERAL(0, 0, 25), // "BfLib::MarketCatalogueApi"
QT_MOC_LITERAL(1, 26, 12), // "valueChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "eventId"
QT_MOC_LITERAL(4, 48, 31), // "std::list<BfLib::BetfairMarket>"
QT_MOC_LITERAL(5, 80, 7), // "markets"
QT_MOC_LITERAL(6, 88, 5), // "error"
QT_MOC_LITERAL(7, 94, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(8, 119, 2), // "ex"
QT_MOC_LITERAL(9, 122, 11), // "replyFinish"
QT_MOC_LITERAL(10, 134, 6), // "answer"
QT_MOC_LITERAL(11, 141, 13) // "errorOccurred"

    },
    "BfLib::MarketCatalogueApi\0valueChanged\0"
    "\0eventId\0std::list<BfLib::BetfairMarket>\0"
    "markets\0error\0BfLib::BfApiNgException*\0"
    "ex\0replyFinish\0answer\0errorOccurred"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BfLib__MarketCatalogueApi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   42,    2, 0x0a /* Public */,
      11,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void BfLib::MarketCatalogueApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarketCatalogueApi *_t = static_cast<MarketCatalogueApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BfLib::BetfairMarket>(*)>(_a[2]))); break;
        case 1: _t->error((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 2: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MarketCatalogueApi::*_t)(QString , std::list<BfLib::BetfairMarket> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketCatalogueApi::valueChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (MarketCatalogueApi::*_t)(BfLib::BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketCatalogueApi::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BfLib::MarketCatalogueApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BfLib__MarketCatalogueApi.data,
      qt_meta_data_BfLib__MarketCatalogueApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BfLib::MarketCatalogueApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BfLib::MarketCatalogueApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BfLib__MarketCatalogueApi.stringdata0))
        return static_cast<void*>(const_cast< MarketCatalogueApi*>(this));
    return QObject::qt_metacast(_clname);
}

int BfLib::MarketCatalogueApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BfLib::MarketCatalogueApi::valueChanged(QString _t1, std::list<BfLib::BetfairMarket> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BfLib::MarketCatalogueApi::error(BfLib::BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
