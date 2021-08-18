/****************************************************************************
** Meta object code from reading C++ file 'betplottingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Better/widgets/betplottingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'betplottingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BetPlottingWidget_t {
    QByteArrayData data[6];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BetPlottingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BetPlottingWidget_t qt_meta_stringdata_BetPlottingWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "BetPlottingWidget"
QT_MOC_LITERAL(1, 18, 18), // "receivedMarketData"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 31), // "std::list<BfLib::BetfairMarket>"
QT_MOC_LITERAL(4, 70, 21), // "comboSelectionChanged"
QT_MOC_LITERAL(5, 92, 17) // "plotButtonClicked"

    },
    "BetPlottingWidget\0receivedMarketData\0"
    "\0std::list<BfLib::BetfairMarket>\0"
    "comboSelectionChanged\0plotButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BetPlottingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void BetPlottingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BetPlottingWidget *_t = static_cast<BetPlottingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receivedMarketData((*reinterpret_cast< std::list<BfLib::BetfairMarket>(*)>(_a[1]))); break;
        case 1: _t->comboSelectionChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->plotButtonClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BetPlottingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BetPlottingWidget.data,
      qt_meta_data_BetPlottingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BetPlottingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BetPlottingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BetPlottingWidget.stringdata0))
        return static_cast<void*>(const_cast< BetPlottingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BetPlottingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
