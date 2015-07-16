/****************************************************************************
** Meta object code from reading C++ file 'KCClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCClient_t {
    QByteArrayData data[27];
    char stringdata[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCClient_t qt_meta_stringdata_KCClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "KCClient"
QT_MOC_LITERAL(1, 9, 14), // "focusRequested"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "credentialsGained"
QT_MOC_LITERAL(4, 43, 15), // "receivedAdmiral"
QT_MOC_LITERAL(5, 59, 17), // "receivedShipTypes"
QT_MOC_LITERAL(6, 77, 13), // "receivedShips"
QT_MOC_LITERAL(7, 91, 14), // "receivedFleets"
QT_MOC_LITERAL(8, 106, 15), // "receivedRepairs"
QT_MOC_LITERAL(9, 122, 21), // "receivedConstructions"
QT_MOC_LITERAL(10, 144, 12), // "requestError"
QT_MOC_LITERAL(11, 157, 19), // "KCClient::ErrorCode"
QT_MOC_LITERAL(12, 177, 5), // "error"
QT_MOC_LITERAL(13, 183, 13), // "dockCompleted"
QT_MOC_LITERAL(14, 197, 7), // "KCDock*"
QT_MOC_LITERAL(15, 205, 4), // "dock"
QT_MOC_LITERAL(16, 210, 16), // "missionCompleted"
QT_MOC_LITERAL(17, 227, 8), // "KCFleet*"
QT_MOC_LITERAL(18, 236, 5), // "fleet"
QT_MOC_LITERAL(19, 242, 14), // "loadMasterData"
QT_MOC_LITERAL(20, 257, 11), // "loadAdmiral"
QT_MOC_LITERAL(21, 269, 8), // "loadPort"
QT_MOC_LITERAL(22, 278, 11), // "loadRepairs"
QT_MOC_LITERAL(23, 290, 17), // "loadConstructions"
QT_MOC_LITERAL(24, 308, 15), // "onDockCompleted"
QT_MOC_LITERAL(25, 324, 17), // "onDockShipChanged"
QT_MOC_LITERAL(26, 342, 18) // "onMissionCompleted"

    },
    "KCClient\0focusRequested\0\0credentialsGained\0"
    "receivedAdmiral\0receivedShipTypes\0"
    "receivedShips\0receivedFleets\0"
    "receivedRepairs\0receivedConstructions\0"
    "requestError\0KCClient::ErrorCode\0error\0"
    "dockCompleted\0KCDock*\0dock\0missionCompleted\0"
    "KCFleet*\0fleet\0loadMasterData\0loadAdmiral\0"
    "loadPort\0loadRepairs\0loadConstructions\0"
    "onDockCompleted\0onDockShipChanged\0"
    "onMissionCompleted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    0,  111,    2, 0x06 /* Public */,
       5,    0,  112,    2, 0x06 /* Public */,
       6,    0,  113,    2, 0x06 /* Public */,
       7,    0,  114,    2, 0x06 /* Public */,
       8,    0,  115,    2, 0x06 /* Public */,
       9,    0,  116,    2, 0x06 /* Public */,
      10,    1,  117,    2, 0x06 /* Public */,
      13,    1,  120,    2, 0x06 /* Public */,
      16,    1,  123,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  126,    2, 0x0a /* Public */,
      20,    0,  127,    2, 0x0a /* Public */,
      21,    0,  128,    2, 0x0a /* Public */,
      22,    0,  129,    2, 0x0a /* Public */,
      23,    0,  130,    2, 0x0a /* Public */,
      24,    0,  131,    2, 0x09 /* Protected */,
      25,    0,  132,    2, 0x09 /* Protected */,
      26,    0,  133,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KCClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCClient *_t = static_cast<KCClient *>(_o);
        switch (_id) {
        case 0: _t->focusRequested(); break;
        case 1: _t->credentialsGained(); break;
        case 2: _t->receivedAdmiral(); break;
        case 3: _t->receivedShipTypes(); break;
        case 4: _t->receivedShips(); break;
        case 5: _t->receivedFleets(); break;
        case 6: _t->receivedRepairs(); break;
        case 7: _t->receivedConstructions(); break;
        case 8: _t->requestError((*reinterpret_cast< KCClient::ErrorCode(*)>(_a[1]))); break;
        case 9: _t->dockCompleted((*reinterpret_cast< KCDock*(*)>(_a[1]))); break;
        case 10: _t->missionCompleted((*reinterpret_cast< KCFleet*(*)>(_a[1]))); break;
        case 11: _t->loadMasterData(); break;
        case 12: _t->loadAdmiral(); break;
        case 13: _t->loadPort(); break;
        case 14: _t->loadRepairs(); break;
        case 15: _t->loadConstructions(); break;
        case 16: _t->onDockCompleted(); break;
        case 17: _t->onDockShipChanged(); break;
        case 18: _t->onMissionCompleted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KCDock* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KCFleet* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::focusRequested)) {
                *result = 0;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::credentialsGained)) {
                *result = 1;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedAdmiral)) {
                *result = 2;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedShipTypes)) {
                *result = 3;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedShips)) {
                *result = 4;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedFleets)) {
                *result = 5;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedRepairs)) {
                *result = 6;
            }
        }
        {
            typedef void (KCClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::receivedConstructions)) {
                *result = 7;
            }
        }
        {
            typedef void (KCClient::*_t)(KCClient::ErrorCode );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::requestError)) {
                *result = 8;
            }
        }
        {
            typedef void (KCClient::*_t)(KCDock * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::dockCompleted)) {
                *result = 9;
            }
        }
        {
            typedef void (KCClient::*_t)(KCFleet * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCClient::missionCompleted)) {
                *result = 10;
            }
        }
    }
}

const QMetaObject KCClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCClient.data,
      qt_meta_data_KCClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCClient.stringdata))
        return static_cast<void*>(const_cast< KCClient*>(this));
    return QObject::qt_metacast(_clname);
}

int KCClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void KCClient::focusRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void KCClient::credentialsGained()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void KCClient::receivedAdmiral()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void KCClient::receivedShipTypes()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void KCClient::receivedShips()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void KCClient::receivedFleets()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void KCClient::receivedRepairs()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void KCClient::receivedConstructions()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void KCClient::requestError(KCClient::ErrorCode _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void KCClient::dockCompleted(KCDock * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void KCClient::missionCompleted(KCFleet * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
