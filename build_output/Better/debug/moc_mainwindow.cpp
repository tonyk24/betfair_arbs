/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Better/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[31];
    char stringdata0[574];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 26), // "on_pushButtonFunds_clicked"
QT_MOC_LITERAL(4, 61, 27), // "on_pushButtonEvents_clicked"
QT_MOC_LITERAL(5, 89, 28), // "on_tableWidget_doubleClicked"
QT_MOC_LITERAL(6, 118, 5), // "index"
QT_MOC_LITERAL(7, 124, 17), // "tabCloseRequested"
QT_MOC_LITERAL(8, 142, 29), // "on_lineEditFilter_textChanged"
QT_MOC_LITERAL(9, 172, 4), // "arg1"
QT_MOC_LITERAL(10, 177, 35), // "on_pushButtonAddWalletEntry_c..."
QT_MOC_LITERAL(11, 213, 14), // "updateExtSites"
QT_MOC_LITERAL(12, 228, 25), // "on_pushButtonHorn_clicked"
QT_MOC_LITERAL(13, 254, 22), // "receivedAccountDetails"
QT_MOC_LITERAL(14, 277, 26), // "BfLib::BfAccountDetailsRsp"
QT_MOC_LITERAL(15, 304, 17), // "accountDetailsRsp"
QT_MOC_LITERAL(16, 322, 20), // "receivedAccountFunds"
QT_MOC_LITERAL(17, 343, 24), // "BfLib::BfAccountFundsRsp"
QT_MOC_LITERAL(18, 368, 15), // "accountFundsRsp"
QT_MOC_LITERAL(19, 384, 14), // "receivedEvents"
QT_MOC_LITERAL(20, 399, 23), // "QVector<BfLib::BfEvent>"
QT_MOC_LITERAL(21, 423, 6), // "events"
QT_MOC_LITERAL(22, 430, 13), // "errorOccurred"
QT_MOC_LITERAL(23, 444, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(24, 469, 2), // "ex"
QT_MOC_LITERAL(25, 472, 16), // "onReceivedSPBets"
QT_MOC_LITERAL(26, 489, 24), // "std::list<ExtSiteSPOdds>"
QT_MOC_LITERAL(27, 514, 6), // "result"
QT_MOC_LITERAL(28, 521, 24), // "onReceivedGameHasArbBets"
QT_MOC_LITERAL(29, 546, 10), // "hasArbBets"
QT_MOC_LITERAL(30, 557, 16) // "keepAliveTimeout"

    },
    "MainWindow\0on_pushButton_clicked\0\0"
    "on_pushButtonFunds_clicked\0"
    "on_pushButtonEvents_clicked\0"
    "on_tableWidget_doubleClicked\0index\0"
    "tabCloseRequested\0on_lineEditFilter_textChanged\0"
    "arg1\0on_pushButtonAddWalletEntry_clicked\0"
    "updateExtSites\0on_pushButtonHorn_clicked\0"
    "receivedAccountDetails\0"
    "BfLib::BfAccountDetailsRsp\0accountDetailsRsp\0"
    "receivedAccountFunds\0BfLib::BfAccountFundsRsp\0"
    "accountFundsRsp\0receivedEvents\0"
    "QVector<BfLib::BfEvent>\0events\0"
    "errorOccurred\0BfLib::BfApiNgException*\0"
    "ex\0onReceivedSPBets\0std::list<ExtSiteSPOdds>\0"
    "result\0onReceivedGameHasArbBets\0"
    "hasArbBets\0keepAliveTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    1,   97,    2, 0x08 /* Private */,
       7,    1,  100,    2, 0x08 /* Private */,
       8,    1,  103,    2, 0x08 /* Private */,
      10,    0,  106,    2, 0x08 /* Private */,
      11,    0,  107,    2, 0x08 /* Private */,
      12,    0,  108,    2, 0x08 /* Private */,
      13,    1,  109,    2, 0x0a /* Public */,
      16,    1,  112,    2, 0x0a /* Public */,
      19,    1,  115,    2, 0x0a /* Public */,
      22,    1,  118,    2, 0x0a /* Public */,
      25,    1,  121,    2, 0x0a /* Public */,
      28,    1,  124,    2, 0x0a /* Public */,
      30,    0,  127,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    6,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButtonFunds_clicked(); break;
        case 2: _t->on_pushButtonEvents_clicked(); break;
        case 3: _t->on_tableWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_lineEditFilter_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_pushButtonAddWalletEntry_clicked(); break;
        case 7: _t->updateExtSites(); break;
        case 8: _t->on_pushButtonHorn_clicked(); break;
        case 9: _t->receivedAccountDetails((*reinterpret_cast< BfLib::BfAccountDetailsRsp(*)>(_a[1]))); break;
        case 10: _t->receivedAccountFunds((*reinterpret_cast< BfLib::BfAccountFundsRsp(*)>(_a[1]))); break;
        case 11: _t->receivedEvents((*reinterpret_cast< QVector<BfLib::BfEvent>(*)>(_a[1]))); break;
        case 12: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 13: _t->onReceivedSPBets((*reinterpret_cast< std::list<ExtSiteSPOdds>(*)>(_a[1]))); break;
        case 14: _t->onReceivedGameHasArbBets((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->keepAliveTimeout(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
