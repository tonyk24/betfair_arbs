/****************************************************************************
** Meta object code from reading C++ file 'extbetstablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Better/widgets/extbetstablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extbetstablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ExtBetsTableWidget_t {
    QByteArrayData data[20];
    char stringdata0[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtBetsTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtBetsTableWidget_t qt_meta_stringdata_ExtBetsTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ExtBetsTableWidget"
QT_MOC_LITERAL(1, 19, 14), // "extBetsUpdated"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "std::list<ExtBet>"
QT_MOC_LITERAL(4, 53, 19), // "extBetsGreenUpdated"
QT_MOC_LITERAL(5, 73, 20), // "placeExtBetSimulated"
QT_MOC_LITERAL(6, 94, 6), // "ExtBet"
QT_MOC_LITERAL(7, 101, 27), // "placeExtBetSimulatedRemoved"
QT_MOC_LITERAL(8, 129, 24), // "receivedExtArbBetsUpdate"
QT_MOC_LITERAL(9, 154, 7), // "extBets"
QT_MOC_LITERAL(10, 162, 25), // "receivedBfPriceSimLaySize"
QT_MOC_LITERAL(11, 188, 28), // "std::list<BfPriceSimLaySize>"
QT_MOC_LITERAL(12, 217, 17), // "BflayPriceSimSize"
QT_MOC_LITERAL(13, 235, 29), // "on_tableWidgetExt_cellChanged"
QT_MOC_LITERAL(14, 265, 3), // "row"
QT_MOC_LITERAL(15, 269, 6), // "column"
QT_MOC_LITERAL(16, 276, 32), // "on_pushButtonSimulateExt_checked"
QT_MOC_LITERAL(17, 309, 12), // "updateSPOdds"
QT_MOC_LITERAL(18, 322, 13), // "ExtSiteSPOdds"
QT_MOC_LITERAL(19, 336, 4) // "odds"

    },
    "ExtBetsTableWidget\0extBetsUpdated\0\0"
    "std::list<ExtBet>\0extBetsGreenUpdated\0"
    "placeExtBetSimulated\0ExtBet\0"
    "placeExtBetSimulatedRemoved\0"
    "receivedExtArbBetsUpdate\0extBets\0"
    "receivedBfPriceSimLaySize\0"
    "std::list<BfPriceSimLaySize>\0"
    "BflayPriceSimSize\0on_tableWidgetExt_cellChanged\0"
    "row\0column\0on_pushButtonSimulateExt_checked\0"
    "updateSPOdds\0ExtSiteSPOdds\0odds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtBetsTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       7,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      13,    2,   77,    2, 0x0a /* Public */,
      16,    2,   82,    2, 0x0a /* Public */,
      17,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void ExtBetsTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExtBetsTableWidget *_t = static_cast<ExtBetsTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->extBetsUpdated((*reinterpret_cast< std::list<ExtBet>(*)>(_a[1]))); break;
        case 1: _t->extBetsGreenUpdated((*reinterpret_cast< std::list<ExtBet>(*)>(_a[1]))); break;
        case 2: _t->placeExtBetSimulated((*reinterpret_cast< ExtBet(*)>(_a[1]))); break;
        case 3: _t->placeExtBetSimulatedRemoved((*reinterpret_cast< ExtBet(*)>(_a[1]))); break;
        case 4: _t->receivedExtArbBetsUpdate((*reinterpret_cast< std::list<ExtBet>(*)>(_a[1]))); break;
        case 5: _t->receivedBfPriceSimLaySize((*reinterpret_cast< std::list<BfPriceSimLaySize>(*)>(_a[1]))); break;
        case 6: _t->on_tableWidgetExt_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_pushButtonSimulateExt_checked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->updateSPOdds((*reinterpret_cast< ExtSiteSPOdds(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ExtBetsTableWidget::*_t)(std::list<ExtBet> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExtBetsTableWidget::extBetsUpdated)) {
                *result = 0;
            }
        }
        {
            typedef void (ExtBetsTableWidget::*_t)(std::list<ExtBet> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExtBetsTableWidget::extBetsGreenUpdated)) {
                *result = 1;
            }
        }
        {
            typedef void (ExtBetsTableWidget::*_t)(ExtBet );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExtBetsTableWidget::placeExtBetSimulated)) {
                *result = 2;
            }
        }
        {
            typedef void (ExtBetsTableWidget::*_t)(ExtBet );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExtBetsTableWidget::placeExtBetSimulatedRemoved)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ExtBetsTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_ExtBetsTableWidget.data,
      qt_meta_data_ExtBetsTableWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ExtBetsTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtBetsTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ExtBetsTableWidget.stringdata0))
        return static_cast<void*>(const_cast< ExtBetsTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int ExtBetsTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ExtBetsTableWidget::extBetsUpdated(std::list<ExtBet> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtBetsTableWidget::extBetsGreenUpdated(std::list<ExtBet> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExtBetsTableWidget::placeExtBetSimulated(ExtBet _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ExtBetsTableWidget::placeExtBetSimulatedRemoved(ExtBet _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
