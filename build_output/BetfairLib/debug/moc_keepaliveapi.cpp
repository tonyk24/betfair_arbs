/****************************************************************************
** Meta object code from reading C++ file 'keepaliveapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../github_BetfairLib/BetfairLib/betfairapi/keepaliveapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keepaliveapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BfLib__KeepAliveApi_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BfLib__KeepAliveApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BfLib__KeepAliveApi_t qt_meta_stringdata_BfLib__KeepAliveApi = {
    {
QT_MOC_LITERAL(0, 0, 19), // "BfLib::KeepAliveApi"
QT_MOC_LITERAL(1, 20, 5), // "error"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(4, 52, 2), // "ex"
QT_MOC_LITERAL(5, 55, 16), // "replyFinishToken"
QT_MOC_LITERAL(6, 72, 14), // "QNetworkReply*"
QT_MOC_LITERAL(7, 87, 5) // "reply"

    },
    "BfLib::KeepAliveApi\0error\0\0"
    "BfLib::BfApiNgException*\0ex\0"
    "replyFinishToken\0QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BfLib__KeepAliveApi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void BfLib::KeepAliveApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeepAliveApi *_t = static_cast<KeepAliveApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 1: _t->replyFinishToken((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeepAliveApi::*_t)(BfLib::BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeepAliveApi::error)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject BfLib::KeepAliveApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BfLib__KeepAliveApi.data,
      qt_meta_data_BfLib__KeepAliveApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BfLib::KeepAliveApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BfLib::KeepAliveApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BfLib__KeepAliveApi.stringdata0))
        return static_cast<void*>(const_cast< KeepAliveApi*>(this));
    return QObject::qt_metacast(_clname);
}

int BfLib::KeepAliveApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void BfLib::KeepAliveApi::error(BfLib::BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
