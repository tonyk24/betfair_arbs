/****************************************************************************
** Meta object code from reading C++ file 'soccergame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Better/soccergame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'soccergame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SoccerGame_t {
    QByteArrayData data[51];
    char stringdata0[925];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SoccerGame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SoccerGame_t qt_meta_stringdata_SoccerGame = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SoccerGame"
QT_MOC_LITERAL(1, 11, 18), // "marketsDataUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 31), // "std::list<BfLib::BetfairMarket>"
QT_MOC_LITERAL(4, 63, 10), // "marketBook"
QT_MOC_LITERAL(5, 74, 19), // "resultMatrixUpdated"
QT_MOC_LITERAL(6, 94, 6), // "ResMat"
QT_MOC_LITERAL(7, 101, 10), // "resmatReal"
QT_MOC_LITERAL(8, 112, 13), // "resmatRealSim"
QT_MOC_LITERAL(9, 126, 9), // "resmatSim"
QT_MOC_LITERAL(10, 136, 15), // "resmatLuckyBets"
QT_MOC_LITERAL(11, 152, 17), // "totalGoalsUpdated"
QT_MOC_LITERAL(12, 170, 25), // "EventStats::TOTALGOALS_EQ"
QT_MOC_LITERAL(13, 196, 25), // "EventStats::TOTALGOALS_LE"
QT_MOC_LITERAL(14, 222, 17), // "placedBetsUpdated"
QT_MOC_LITERAL(15, 240, 74), // "std::list<std::pair<BfLib::Bf..."
QT_MOC_LITERAL(16, 315, 13), // "arbBetsUpdate"
QT_MOC_LITERAL(17, 329, 19), // "std::list<BfArbBet>"
QT_MOC_LITERAL(18, 349, 17), // "arbBetsExtChanged"
QT_MOC_LITERAL(19, 367, 17), // "std::list<ExtBet>"
QT_MOC_LITERAL(20, 385, 7), // "extBets"
QT_MOC_LITERAL(21, 393, 23), // "bfSimulationBetsUpdated"
QT_MOC_LITERAL(22, 417, 36), // "std::list<BfLib::BfPlaceInstr..."
QT_MOC_LITERAL(23, 454, 23), // "receivedMarketCatalogue"
QT_MOC_LITERAL(24, 478, 5), // "event"
QT_MOC_LITERAL(25, 484, 15), // "marketCatalogue"
QT_MOC_LITERAL(26, 500, 22), // "receivedMarketBookData"
QT_MOC_LITERAL(27, 523, 22), // "receivedPlaceOrdersRsp"
QT_MOC_LITERAL(28, 546, 29), // "BfLib::BfPlaceExecutionReport"
QT_MOC_LITERAL(29, 576, 20), // "placeExecutionReport"
QT_MOC_LITERAL(30, 597, 28), // "receivedListCurrentOrdersRsp"
QT_MOC_LITERAL(31, 626, 32), // "std::list<BfLib::BfCurrentOrder>"
QT_MOC_LITERAL(32, 659, 13), // "currentOrders"
QT_MOC_LITERAL(33, 673, 17), // "placeBetSimulated"
QT_MOC_LITERAL(34, 691, 8), // "marketId"
QT_MOC_LITERAL(35, 700, 11), // "selectionId"
QT_MOC_LITERAL(36, 712, 8), // "handicap"
QT_MOC_LITERAL(37, 721, 19), // "BfLib::BfSide::Enum"
QT_MOC_LITERAL(38, 741, 4), // "side"
QT_MOC_LITERAL(39, 746, 9), // "takePrice"
QT_MOC_LITERAL(40, 756, 8), // "takeSize"
QT_MOC_LITERAL(41, 765, 23), // "placeBetSimulatedRemove"
QT_MOC_LITERAL(42, 789, 8), // "placeBet"
QT_MOC_LITERAL(43, 798, 25), // "BfLib::BfPlaceInstruction"
QT_MOC_LITERAL(44, 824, 2), // "pi"
QT_MOC_LITERAL(45, 827, 20), // "placeExtBetSimulated"
QT_MOC_LITERAL(46, 848, 6), // "ExtBet"
QT_MOC_LITERAL(47, 855, 27), // "placeExtBetSimulatedRemoved"
QT_MOC_LITERAL(48, 883, 13), // "errorOccurred"
QT_MOC_LITERAL(49, 897, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(50, 922, 2) // "ex"

    },
    "SoccerGame\0marketsDataUpdated\0\0"
    "std::list<BfLib::BetfairMarket>\0"
    "marketBook\0resultMatrixUpdated\0ResMat\0"
    "resmatReal\0resmatRealSim\0resmatSim\0"
    "resmatLuckyBets\0totalGoalsUpdated\0"
    "EventStats::TOTALGOALS_EQ\0"
    "EventStats::TOTALGOALS_LE\0placedBetsUpdated\0"
    "std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrde"
    "r> >\0"
    "arbBetsUpdate\0std::list<BfArbBet>\0"
    "arbBetsExtChanged\0std::list<ExtBet>\0"
    "extBets\0bfSimulationBetsUpdated\0"
    "std::list<BfLib::BfPlaceInstruction>\0"
    "receivedMarketCatalogue\0event\0"
    "marketCatalogue\0receivedMarketBookData\0"
    "receivedPlaceOrdersRsp\0"
    "BfLib::BfPlaceExecutionReport\0"
    "placeExecutionReport\0receivedListCurrentOrdersRsp\0"
    "std::list<BfLib::BfCurrentOrder>\0"
    "currentOrders\0placeBetSimulated\0"
    "marketId\0selectionId\0handicap\0"
    "BfLib::BfSide::Enum\0side\0takePrice\0"
    "takeSize\0placeBetSimulatedRemove\0"
    "placeBet\0BfLib::BfPlaceInstruction\0"
    "pi\0placeExtBetSimulated\0ExtBet\0"
    "placeExtBetSimulatedRemoved\0errorOccurred\0"
    "BfLib::BfApiNgException*\0ex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SoccerGame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       5,    4,  107,    2, 0x06 /* Public */,
      11,    2,  116,    2, 0x06 /* Public */,
      14,    1,  121,    2, 0x06 /* Public */,
      16,    1,  124,    2, 0x06 /* Public */,
      18,    1,  127,    2, 0x06 /* Public */,
      21,    1,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    2,  133,    2, 0x0a /* Public */,
      26,    1,  138,    2, 0x0a /* Public */,
      27,    1,  141,    2, 0x0a /* Public */,
      30,    1,  144,    2, 0x0a /* Public */,
      33,    6,  147,    2, 0x0a /* Public */,
      41,    4,  160,    2, 0x0a /* Public */,
      42,    6,  169,    2, 0x0a /* Public */,
      42,    2,  182,    2, 0x0a /* Public */,
      45,    1,  187,    2, 0x0a /* Public */,
      47,    1,  190,    2, 0x0a /* Public */,
      48,    1,  193,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 6,    7,    8,    9,   10,
    QMetaType::Int, 0x80000000 | 12, 0x80000000 | 13,    2,    2,
    QMetaType::Int, 0x80000000 | 15,    2,
    QMetaType::Int, 0x80000000 | 17,    2,
    QMetaType::Int, 0x80000000 | 19,   20,
    QMetaType::Int, 0x80000000 | 22,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,   24,   25,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::Double, 0x80000000 | 37, QMetaType::Double, QMetaType::Double,   34,   35,   36,   38,   39,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::Double, 0x80000000 | 37,   34,   35,   36,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::Double, 0x80000000 | 37, QMetaType::Double, QMetaType::Double,   34,   35,   36,   38,   39,   40,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 43,   34,   44,
    QMetaType::Void, 0x80000000 | 46,    2,
    QMetaType::Void, 0x80000000 | 46,    2,
    QMetaType::Void, 0x80000000 | 49,   50,

       0        // eod
};

void SoccerGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SoccerGame *_t = static_cast<SoccerGame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->marketsDataUpdated((*reinterpret_cast< std::list<BfLib::BetfairMarket>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->resultMatrixUpdated((*reinterpret_cast< ResMat(*)>(_a[1])),(*reinterpret_cast< ResMat(*)>(_a[2])),(*reinterpret_cast< ResMat(*)>(_a[3])),(*reinterpret_cast< ResMat(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->totalGoalsUpdated((*reinterpret_cast< EventStats::TOTALGOALS_EQ(*)>(_a[1])),(*reinterpret_cast< EventStats::TOTALGOALS_LE(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->placedBetsUpdated((*reinterpret_cast< std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> >(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->arbBetsUpdate((*reinterpret_cast< std::list<BfArbBet>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->arbBetsExtChanged((*reinterpret_cast< std::list<ExtBet>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->bfSimulationBetsUpdated((*reinterpret_cast< std::list<BfLib::BfPlaceInstruction>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: _t->receivedMarketCatalogue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::list<BfLib::BetfairMarket>(*)>(_a[2]))); break;
        case 8: _t->receivedMarketBookData((*reinterpret_cast< std::list<BfLib::BetfairMarket>(*)>(_a[1]))); break;
        case 9: _t->receivedPlaceOrdersRsp((*reinterpret_cast< BfLib::BfPlaceExecutionReport(*)>(_a[1]))); break;
        case 10: _t->receivedListCurrentOrdersRsp((*reinterpret_cast< std::list<BfLib::BfCurrentOrder>(*)>(_a[1]))); break;
        case 11: _t->placeBetSimulated((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< BfLib::BfSide::Enum(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 12: _t->placeBetSimulatedRemove((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< BfLib::BfSide::Enum(*)>(_a[4]))); break;
        case 13: _t->placeBet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< BfLib::BfSide::Enum(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 14: _t->placeBet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BfLib::BfPlaceInstruction(*)>(_a[2]))); break;
        case 15: _t->placeExtBetSimulated((*reinterpret_cast< ExtBet(*)>(_a[1]))); break;
        case 16: _t->placeExtBetSimulatedRemoved((*reinterpret_cast< ExtBet(*)>(_a[1]))); break;
        case 17: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (SoccerGame::*_t)(std::list<BfLib::BetfairMarket> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::marketsDataUpdated)) {
                *result = 0;
            }
        }
        {
            typedef int (SoccerGame::*_t)(ResMat , ResMat , ResMat , ResMat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::resultMatrixUpdated)) {
                *result = 1;
            }
        }
        {
            typedef int (SoccerGame::*_t)(EventStats::TOTALGOALS_EQ , EventStats::TOTALGOALS_LE );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::totalGoalsUpdated)) {
                *result = 2;
            }
        }
        {
            typedef int (SoccerGame::*_t)(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> > );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::placedBetsUpdated)) {
                *result = 3;
            }
        }
        {
            typedef int (SoccerGame::*_t)(std::list<BfArbBet> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::arbBetsUpdate)) {
                *result = 4;
            }
        }
        {
            typedef int (SoccerGame::*_t)(std::list<ExtBet> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::arbBetsExtChanged)) {
                *result = 5;
            }
        }
        {
            typedef int (SoccerGame::*_t)(std::list<BfLib::BfPlaceInstruction> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerGame::bfSimulationBetsUpdated)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject SoccerGame::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SoccerGame.data,
      qt_meta_data_SoccerGame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SoccerGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SoccerGame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SoccerGame.stringdata0))
        return static_cast<void*>(const_cast< SoccerGame*>(this));
    return QObject::qt_metacast(_clname);
}

int SoccerGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
int SoccerGame::marketsDataUpdated(std::list<BfLib::BetfairMarket> _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int SoccerGame::resultMatrixUpdated(ResMat _t1, ResMat _t2, ResMat _t3, ResMat _t4)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
int SoccerGame::totalGoalsUpdated(EventStats::TOTALGOALS_EQ _t1, EventStats::TOTALGOALS_LE _t2)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
int SoccerGame::placedBetsUpdated(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> > _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}

// SIGNAL 4
int SoccerGame::arbBetsUpdate(std::list<BfArbBet> _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
    return _t0;
}

// SIGNAL 5
int SoccerGame::arbBetsExtChanged(std::list<ExtBet> _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
    return _t0;
}

// SIGNAL 6
int SoccerGame::bfSimulationBetsUpdated(std::list<BfLib::BfPlaceInstruction> _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
