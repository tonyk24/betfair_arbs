/****************************************************************************
** Meta object code from reading C++ file 'logcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BetfairLogger/logcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LogController_t {
    QByteArrayData data[28];
    char stringdata0[447];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogController_t qt_meta_stringdata_LogController = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LogController"
QT_MOC_LITERAL(1, 14, 8), // "finished"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "run"
QT_MOC_LITERAL(4, 28, 14), // "aboutToQuitApp"
QT_MOC_LITERAL(5, 43, 9), // "placeBets"
QT_MOC_LITERAL(6, 53, 48), // "std::map<QString,std::list<Bf..."
QT_MOC_LITERAL(7, 102, 14), // "eventsReceived"
QT_MOC_LITERAL(8, 117, 18), // "std::list<BfEvent>"
QT_MOC_LITERAL(9, 136, 6), // "events"
QT_MOC_LITERAL(10, 143, 14), // "receiveMarkets"
QT_MOC_LITERAL(11, 158, 5), // "event"
QT_MOC_LITERAL(12, 164, 24), // "std::list<BetfairMarket>"
QT_MOC_LITERAL(13, 189, 7), // "markets"
QT_MOC_LITERAL(14, 197, 22), // "placeOrdersRspReceived"
QT_MOC_LITERAL(15, 220, 22), // "BfPlaceExecutionReport"
QT_MOC_LITERAL(16, 243, 20), // "placeExecutionReport"
QT_MOC_LITERAL(17, 264, 20), // "accountFundsReceived"
QT_MOC_LITERAL(18, 285, 17), // "BfAccountFundsRsp"
QT_MOC_LITERAL(19, 303, 15), // "accountFundsRsp"
QT_MOC_LITERAL(20, 319, 22), // "accountDetailsReceived"
QT_MOC_LITERAL(21, 342, 19), // "BfAccountDetailsRsp"
QT_MOC_LITERAL(22, 362, 17), // "accountDetailsRsp"
QT_MOC_LITERAL(23, 380, 13), // "errorOccurred"
QT_MOC_LITERAL(24, 394, 17), // "BfApiNgException*"
QT_MOC_LITERAL(25, 412, 14), // "apiNgException"
QT_MOC_LITERAL(26, 427, 11), // "threadError"
QT_MOC_LITERAL(27, 439, 7) // "errorno"

    },
    "LogController\0finished\0\0run\0aboutToQuitApp\0"
    "placeBets\0std::map<QString,std::list<BfPlaceInstruction> >\0"
    "eventsReceived\0std::list<BfEvent>\0"
    "events\0receiveMarkets\0event\0"
    "std::list<BetfairMarket>\0markets\0"
    "placeOrdersRspReceived\0BfPlaceExecutionReport\0"
    "placeExecutionReport\0accountFundsReceived\0"
    "BfAccountFundsRsp\0accountFundsRsp\0"
    "accountDetailsReceived\0BfAccountDetailsRsp\0"
    "accountDetailsRsp\0errorOccurred\0"
    "BfApiNgException*\0apiNgException\0"
    "threadError\0errorno"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    1,   72,    2, 0x0a /* Public */,
       7,    1,   75,    2, 0x08 /* Private */,
      10,    2,   78,    2, 0x08 /* Private */,
      14,    1,   83,    2, 0x08 /* Private */,
      17,    1,   86,    2, 0x08 /* Private */,
      20,    1,   89,    2, 0x08 /* Private */,
      23,    1,   92,    2, 0x08 /* Private */,
      26,    1,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    5,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, QMetaType::QString,   27,

       0        // eod
};

void LogController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LogController *_t = static_cast<LogController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->run(); break;
        case 2: _t->aboutToQuitApp(); break;
        case 3: _t->placeBets((*reinterpret_cast< const std::map<QString,std::list<BfPlaceInstruction> >(*)>(_a[1]))); break;
        case 4: _t->eventsReceived((*reinterpret_cast< std::list<BfEvent>(*)>(_a[1]))); break;
        case 5: _t->receiveMarkets((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BetfairMarket>(*)>(_a[2]))); break;
        case 6: _t->placeOrdersRspReceived((*reinterpret_cast< BfPlaceExecutionReport(*)>(_a[1]))); break;
        case 7: _t->accountFundsReceived((*reinterpret_cast< BfAccountFundsRsp(*)>(_a[1]))); break;
        case 8: _t->accountDetailsReceived((*reinterpret_cast< BfAccountDetailsRsp(*)>(_a[1]))); break;
        case 9: _t->errorOccurred((*reinterpret_cast< BfApiNgException*(*)>(_a[1]))); break;
        case 10: _t->threadError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LogController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LogController::finished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject LogController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LogController.data,
      qt_meta_data_LogController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LogController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LogController.stringdata0))
        return static_cast<void*>(const_cast< LogController*>(this));
    return QObject::qt_metacast(_clname);
}

int LogController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void LogController::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
