/****************************************************************************
** Meta object code from reading C++ file 'httpjsonclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../github_BetfairLib/BetfairLib/betfairapi/httpjsonclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpjsonclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BfLib__HttpJsonClient_t {
    QByteArrayData data[14];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BfLib__HttpJsonClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BfLib__HttpJsonClient_t qt_meta_stringdata_BfLib__HttpJsonClient = {
    {
QT_MOC_LITERAL(0, 0, 21), // "BfLib::HttpJsonClient"
QT_MOC_LITERAL(1, 22, 11), // "replyFinish"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "answer"
QT_MOC_LITERAL(4, 42, 5), // "error"
QT_MOC_LITERAL(5, 48, 24), // "BfLib::BfApiNgException*"
QT_MOC_LITERAL(6, 73, 2), // "ex"
QT_MOC_LITERAL(7, 76, 7), // "execute"
QT_MOC_LITERAL(8, 84, 14), // "QNetworkReply*"
QT_MOC_LITERAL(9, 99, 5), // "reply"
QT_MOC_LITERAL(10, 105, 17), // "sslErrorsReceived"
QT_MOC_LITERAL(11, 123, 16), // "QList<QSslError>"
QT_MOC_LITERAL(12, 140, 14), // "loginCompleted"
QT_MOC_LITERAL(13, 155, 13) // "errorOccurred"

    },
    "BfLib::HttpJsonClient\0replyFinish\0\0"
    "answer\0error\0BfLib::BfApiNgException*\0"
    "ex\0execute\0QNetworkReply*\0reply\0"
    "sslErrorsReceived\0QList<QSslError>\0"
    "loginCompleted\0errorOccurred"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BfLib__HttpJsonClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   55,    2, 0x08 /* Private */,
       1,    1,   56,    2, 0x0a /* Public */,
      10,    2,   59,    2, 0x0a /* Public */,
      12,    0,   64,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 11,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void BfLib::HttpJsonClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpJsonClient *_t = static_cast<HttpJsonClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        case 2: _t->execute(); break;
        case 3: _t->replyFinish((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->sslErrorsReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QList<QSslError>(*)>(_a[2]))); break;
        case 5: _t->loginCompleted(); break;
        case 6: _t->errorOccurred((*reinterpret_cast< BfLib::BfApiNgException*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HttpJsonClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpJsonClient::replyFinish)) {
                *result = 0;
            }
        }
        {
            typedef void (HttpJsonClient::*_t)(BfLib::BfApiNgException * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpJsonClient::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BfLib::HttpJsonClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BfLib__HttpJsonClient.data,
      qt_meta_data_BfLib__HttpJsonClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BfLib::HttpJsonClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BfLib::HttpJsonClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BfLib__HttpJsonClient.stringdata0))
        return static_cast<void*>(const_cast< HttpJsonClient*>(this));
    return QObject::qt_metacast(_clname);
}

int BfLib::HttpJsonClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BfLib::HttpJsonClient::replyFinish(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BfLib::HttpJsonClient::error(BfLib::BfApiNgException * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
