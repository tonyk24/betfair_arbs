/****************************************************************************
** Meta object code from reading C++ file 'betfaircontrollerlib.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BetfairLib/betfaircontrollerlib.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'betfaircontrollerlib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BetfairControllerLib_t {
    QByteArrayData data[29];
    char stringdata0[477];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BetfairControllerLib_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BetfairControllerLib_t qt_meta_stringdata_BetfairControllerLib = {
    {
QT_MOC_LITERAL(0, 0, 20), // "BetfairControllerLib"
QT_MOC_LITERAL(1, 21, 18), // "valueChangedEvents"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 18), // "std::list<BfEvent>"
QT_MOC_LITERAL(4, 60, 6), // "events"
QT_MOC_LITERAL(5, 67, 19), // "valueChangedMarkets"
QT_MOC_LITERAL(6, 87, 5), // "event"
QT_MOC_LITERAL(7, 93, 24), // "std::list<BetfairMarket>"
QT_MOC_LITERAL(8, 118, 7), // "markets"
QT_MOC_LITERAL(9, 126, 24), // "valueChangedAccountFunds"
QT_MOC_LITERAL(10, 151, 17), // "BfAccountFundsRsp"
QT_MOC_LITERAL(11, 169, 15), // "accountFundsRsp"
QT_MOC_LITERAL(12, 185, 26), // "valueChangedAccountDetails"
QT_MOC_LITERAL(13, 212, 19), // "BfAccountDetailsRsp"
QT_MOC_LITERAL(14, 232, 19), // "placeOrdersResponse"
QT_MOC_LITERAL(15, 252, 22), // "BfPlaceExecutionReport"
QT_MOC_LITERAL(16, 275, 20), // "placeExecutionReport"
QT_MOC_LITERAL(17, 296, 5), // "error"
QT_MOC_LITERAL(18, 302, 17), // "BfApiNgException*"
QT_MOC_LITERAL(19, 320, 2), // "ex"
QT_MOC_LITERAL(20, 323, 14), // "eventsReceived"
QT_MOC_LITERAL(21, 338, 15), // "marketsReceived"
QT_MOC_LITERAL(22, 354, 22), // "placeOrdersRspReceived"
QT_MOC_LITERAL(23, 377, 20), // "accountFundsReceived"
QT_MOC_LITERAL(24, 398, 22), // "accountDetailsReceived"
QT_MOC_LITERAL(25, 421, 17), // "accountDetailsRsp"
QT_MOC_LITERAL(26, 439, 13), // "errorOccurred"
QT_MOC_LITERAL(27, 453, 6), // "update"
QT_MOC_LITERAL(28, 460, 16) // "keepAliveTimeout"

    },
    "BetfairControllerLib\0valueChangedEvents\0"
    "\0std::list<BfEvent>\0events\0"
    "valueChangedMarkets\0event\0"
    "std::list<BetfairMarket>\0markets\0"
    "valueChangedAccountFunds\0BfAccountFundsRsp\0"
    "accountFundsRsp\0valueChangedAccountDetails\0"
    "BfAccountDetailsRsp\0placeOrdersResponse\0"
    "BfPlaceExecutionReport\0placeExecutionReport\0"
    "error\0BfApiNgException*\0ex\0eventsReceived\0"
    "marketsReceived\0placeOrdersRspReceived\0"
    "accountFundsReceived\0accountDetailsReceived\0"
    "accountDetailsRsp\0errorOccurred\0update\0"
    "keepAliveTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BetfairControllerLib[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    2,   87,    2, 0x06 /* Public */,
       9,    1,   92,    2, 0x06 /* Public */,
      12,    1,   95,    2, 0x06 /* Public */,
      14,    1,   98,    2, 0x06 /* Public */,
      17,    1,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  104,    2, 0x0a /* Public */,
      21,    2,  107,    2, 0x0a /* Public */,
      22,    1,  112,    2, 0x0a /* Public */,
      23,    1,  115,    2, 0x0a /* Public */,
      24,    1,  118,    2, 0x0a /* Public */,
      26,    1,  121,    2, 0x0a /* Public */,
      27,    0,  124,    2, 0x08 /* Private */,
      28,    0,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   11,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   25,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BetfairControllerLib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BetfairControllerLib *_t = static_cast<BetfairControllerLib *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChangedEvents((*reinterpret_cast< std::list<BfEvent>(*)>(_a[1]))); break;
        case 1: _t->valueChangedMarkets((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 2: _t->valueChangedAccountFunds((*reinterpret_cast< BfAccountFundsRsp(*)>(_a[1]))); break;
        case 3: _t->valueChangedAccountDetails((*reinterpret_cast< BfAccountDetailsRsp(*)>(_a[1]))); break;
        case 4: _t->placeOrdersResponse((*reinterpret_cast< BfPlaceExecutionReport(*)>(_a[1]))); break;
        case 5: _t->error((*reinterpret_cast< BfApiNgException*(*)>(_a[1]))); break;
        case 6: _t->eventsReceived((*reinterpret_cast< std::list<BfEvent>(*)>(_a[1]))); break;
        case 7: _t->marketsReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 8: _t->placeOrdersRspReceived((*reinterpret_cast< BfPlaceExecutionReport(*)>(_a[1]))); break;
        case 9: _t->accountFundsReceived((*reinterpret_cast< BfAccountFundsRsp(*)>(_a[1]))); break;
        case 10: _t->accountDetailsReceived((*reinterpret_cast< BfAccountDetailsRsp(*)>(_a[1]))); break;
        case 11: _t->errorOccurred((*reinterpret_cast< BfApiNgException*(*)>(_a[1]))); break;
        case 12: _t->update(); break;
        case 13: _t->keepAliveTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BetfairControllerLib::*_t)(std::list<BfEvent> );
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
        {
            typedef void (BetfairControllerLib::*_t)(BfAccountFundsRsp );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::valueChangedAccountFunds)) {
                *result = 2;
            }
        }
        {
            typedef void (BetfairControllerLib::*_t)(BfAccountDetailsRsp );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::valueChangedAccountDetails)) {
                *result = 3;
            }
        }
        {
            typedef void (BetfairControllerLib::*_t)(BfPlaceExecutionReport );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::placeOrdersResponse)) {
                *result = 4;
            }
        }
        {
            typedef void (BetfairControllerLib::*_t)(BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BetfairControllerLib::error)) {
                *result = 5;
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
    if (!strcmp(_clname, qt_meta_stringdata_BetfairControllerLib.stringdata0))
        return static_cast<void*>(const_cast< BetfairControllerLib*>(this));
    return QObject::qt_metacast(_clname);
}

int BetfairControllerLib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void BetfairControllerLib::valueChangedEvents(std::list<BfEvent> _t1)
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

// SIGNAL 2
void BetfairControllerLib::valueChangedAccountFunds(BfAccountFundsRsp _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BetfairControllerLib::valueChangedAccountDetails(BfAccountDetailsRsp _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BetfairControllerLib::placeOrdersResponse(BfPlaceExecutionReport _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BetfairControllerLib::error(BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
