/****************************************************************************
** Meta object code from reading C++ file 'interactiveapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BetfairLogger/interactiveapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interactiveapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InteractiveApp_t {
    QByteArrayData data[9];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InteractiveApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InteractiveApp_t qt_meta_stringdata_InteractiveApp = {
    {
QT_MOC_LITERAL(0, 0, 14), // "InteractiveApp"
QT_MOC_LITERAL(1, 15, 11), // "aboutToQuit"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "finished"
QT_MOC_LITERAL(4, 37, 11), // "recDebugMsg"
QT_MOC_LITERAL(5, 49, 3), // "msg"
QT_MOC_LITERAL(6, 53, 4), // "quit"
QT_MOC_LITERAL(7, 58, 3), // "run"
QT_MOC_LITERAL(8, 62, 10) // "waitForRsp"

    },
    "InteractiveApp\0aboutToQuit\0\0finished\0"
    "recDebugMsg\0msg\0quit\0run\0waitForRsp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InteractiveApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   46,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

void InteractiveApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InteractiveApp *_t = static_cast<InteractiveApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->aboutToQuit(); break;
        case 1: _t->finished(); break;
        case 2: _t->recDebugMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->quit(); break;
        case 4: _t->run(); break;
        case 5: { QString _r = _t->waitForRsp();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InteractiveApp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InteractiveApp::aboutToQuit)) {
                *result = 0;
            }
        }
        {
            typedef void (InteractiveApp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InteractiveApp::finished)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject InteractiveApp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InteractiveApp.data,
      qt_meta_data_InteractiveApp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InteractiveApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InteractiveApp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InteractiveApp.stringdata0))
        return static_cast<void*>(const_cast< InteractiveApp*>(this));
    return QObject::qt_metacast(_clname);
}

int InteractiveApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void InteractiveApp::aboutToQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void InteractiveApp::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
