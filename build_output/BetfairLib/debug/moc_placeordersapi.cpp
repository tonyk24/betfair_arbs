/****************************************************************************
** Meta object code from reading C++ file 'placeordersapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../github_BetfairLib/BetfairLib/betfairapi/placeordersapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'placeordersapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BfLib__PlaceOrdersApi_t {
    QByteArrayData data[11];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BfLib__PlaceOrdersApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BfLib__PlaceOrdersApi_t qt_meta_stringdata_BfLib__PlaceOrdersApi = {
    {
QT_MOC_LITERAL(0, 0, 21), // "BfLib::PlaceOrdersApi"
QT_MOC_LITERAL(1, 22, 19), // "placeOrdersResponse"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 29), // "BfLib::BfPlaceExecutionReport"
QT_MOC_LITERAL(4, 73, 20), // "placeExecutionReport"
QT_MOC_LITERAL(5, 94, 5), // "error"
QT_MOC_LITERAL(6, 100, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(7, 125, 2), // "ex"
QT_MOC_LITERAL(8, 128, 11), // "replyFinish"
QT_MOC_LITERAL(9, 140, 6), // "answer"
QT_MOC_LITERAL(10, 147, 13) // "errorOccurred"

    },
    "BfLib::PlaceOrdersApi\0placeOrdersResponse\0"
    "\0BfLib::BfPlaceExecutionReport\0"
    "placeExecutionReport\0error\0"
    "BfLib::BfApiNgException*\0ex\0replyFinish\0"
    "answer\0errorOccurred"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BfLib__PlaceOrdersApi[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   40,    2, 0x0a /* Public */,
      10,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void BfLib::PlaceOrdersApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlaceOrdersApi *_t = static_cast<PlaceOrdersApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->placeOrdersResponse((*reinterpret_cast< BfLib::BfPlaceExecutionReport(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 2: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlaceOrdersApi::*_t)(BfLib::BfPlaceExecutionReport );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlaceOrdersApi::placeOrdersResponse)) {
                *result = 0;
            }
        }
        {
            typedef void (PlaceOrdersApi::*_t)(BfLib::BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlaceOrdersApi::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BfLib::PlaceOrdersApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BfLib__PlaceOrdersApi.data,
      qt_meta_data_BfLib__PlaceOrdersApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BfLib::PlaceOrdersApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BfLib::PlaceOrdersApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BfLib__PlaceOrdersApi.stringdata0))
        return static_cast<void*>(const_cast< PlaceOrdersApi*>(this));
    return QObject::qt_metacast(_clname);
}

int BfLib::PlaceOrdersApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void BfLib::PlaceOrdersApi::placeOrdersResponse(BfLib::BfPlaceExecutionReport _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BfLib::PlaceOrdersApi::error(BfLib::BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
