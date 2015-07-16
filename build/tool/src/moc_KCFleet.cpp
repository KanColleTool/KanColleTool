/****************************************************************************
** Meta object code from reading C++ file 'KCFleet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCFleet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCFleet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCFleet_t {
    QByteArrayData data[4];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCFleet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCFleet_t qt_meta_stringdata_KCFleet = {
    {
QT_MOC_LITERAL(0, 0, 7), // "KCFleet"
QT_MOC_LITERAL(1, 8, 16), // "missionCompleted"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16) // "onMissionTimeout"

    },
    "KCFleet\0missionCompleted\0\0onMissionTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCFleet[] = {

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
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void KCFleet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCFleet *_t = static_cast<KCFleet *>(_o);
        switch (_id) {
        case 0: _t->missionCompleted(); break;
        case 1: _t->onMissionTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KCFleet::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCFleet::missionCompleted)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject KCFleet::staticMetaObject = {
    { &KCGameObject::staticMetaObject, qt_meta_stringdata_KCFleet.data,
      qt_meta_data_KCFleet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCFleet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCFleet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCFleet.stringdata))
        return static_cast<void*>(const_cast< KCFleet*>(this));
    return KCGameObject::qt_metacast(_clname);
}

int KCFleet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KCGameObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void KCFleet::missionCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
