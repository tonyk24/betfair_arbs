/****************************************************************************
** Meta object code from reading C++ file 'cancelordersapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../github_BetfairLib/BetfairLib/betfairapi/cancelordersapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cancelordersapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BfLib__CancelOrdersApi_t {
    QByteArrayData data[11];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BfLib__CancelOrdersApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BfLib__CancelOrdersApi_t qt_meta_stringdata_BfLib__CancelOrdersApi = {
    {
QT_MOC_LITERAL(0, 0, 22), // "BfLib::CancelOrdersApi"
QT_MOC_LITERAL(1, 23, 20), // "cancelOrdersResponse"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 30), // "BfLib::BfCancelExecutionReport"
QT_MOC_LITERAL(4, 76, 21), // "cancelExecutionReport"
QT_MOC_LITERAL(5, 98, 5), // "error"
QT_MOC_LITERAL(6, 104, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(7, 129, 2), // "ex"
QT_MOC_LITERAL(8, 132, 11), // "replyFinish"
QT_MOC_LITERAL(9, 144, 6), // "answer"
QT_MOC_LITERAL(10, 151, 13) // "errorOccurred"

    },
    "BfLib::CancelOrdersApi\0cancelOrdersResponse\0"
    "\0BfLib::BfCancelExecutionReport\0"
    "cancelExecutionReport\0error\0"
    "BfLib::BfApiNgException*\0ex\0replyFinish\0"
    "answer\0errorOccurred"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BfLib__CancelOrdersApi[] = {

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

void BfLib::CancelOrdersApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CancelOrdersApi *_t = static_cast<CancelOrdersApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cancelOrdersResponse((*reinterpret_cast< BfLib::BfCancelExecutionReport(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 2: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CancelOrdersApi::*_t)(BfLib::BfCancelExecutionReport );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CancelOrdersApi::cancelOrdersResponse)) {
                *result = 0;
            }
        }
        {
            typedef void (CancelOrdersApi::*_t)(BfLib::BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CancelOrdersApi::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BfLib::CancelOrdersApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BfLib__CancelOrdersApi.data,
      qt_meta_data_BfLib__CancelOrdersApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BfLib::CancelOrdersApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BfLib::CancelOrdersApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BfLib__CancelOrdersApi.stringdata0))
        return static_cast<void*>(const_cast< CancelOrdersApi*>(this));
    return QObject::qt_metacast(_clname);
}

int BfLib::CancelOrdersApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void BfLib::CancelOrdersApi::cancelOrdersResponse(BfLib::BfCancelExecutionReport _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BfLib::CancelOrdersApi::error(BfLib::BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
