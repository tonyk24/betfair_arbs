/****************************************************************************
** Meta object code from reading C++ file 'httpjsonclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../betfairapi/httpjsonclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpjsonclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HttpJsonClient_t {
    QByteArrayData data[9];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HttpJsonClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HttpJsonClient_t qt_meta_stringdata_HttpJsonClient = {
    {
QT_MOC_LITERAL(0, 0, 14), // "HttpJsonClient"
QT_MOC_LITERAL(1, 15, 11), // "replyFinish"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "answer"
QT_MOC_LITERAL(4, 35, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 50, 5), // "reply"
QT_MOC_LITERAL(6, 56, 17), // "sslErrorsReceived"
QT_MOC_LITERAL(7, 74, 16), // "QList<QSslError>"
QT_MOC_LITERAL(8, 91, 14) // "loginCompleted"

    },
    "HttpJsonClient\0replyFinish\0\0answer\0"
    "QNetworkReply*\0reply\0sslErrorsReceived\0"
    "QList<QSslError>\0loginCompleted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HttpJsonClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       1,    1,   37,    2, 0x0a /* Public */,
       6,    2,   40,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 7,    2,    2,
    QMetaType::Void,

       0        // eod
};

void HttpJsonClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpJsonClient *_t = static_cast<HttpJsonClient *>(_o);
        switch (_id) {
        case 0: _t->replyFinish((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->replyFinish((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->sslErrorsReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QList<QSslError>(*)>(_a[2]))); break;
        case 3: _t->loginCompleted(); break;
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
        case 2:
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
    }
}

const QMetaObject HttpJsonClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HttpJsonClient.data,
      qt_meta_data_HttpJsonClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HttpJsonClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpJsonClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HttpJsonClient.stringdata))
        return static_cast<void*>(const_cast< HttpJsonClient*>(this));
    return QObject::qt_metacast(_clname);
}

int HttpJsonClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void HttpJsonClient::replyFinish(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
