/****************************************************************************
** Meta object code from reading C++ file 'KCDock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCDock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCDock_t {
    QByteArrayData data[5];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCDock_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCDock_t qt_meta_stringdata_KCDock = {
    {
QT_MOC_LITERAL(0, 0, 6), // "KCDock"
QT_MOC_LITERAL(1, 7, 9), // "completed"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "shipChanged"
QT_MOC_LITERAL(4, 30, 9) // "onTimeout"

    },
    "KCDock\0completed\0\0shipChanged\0onTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCDock[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void KCDock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCDock *_t = static_cast<KCDock *>(_o);
        switch (_id) {
        case 0: _t->completed(); break;
        case 1: _t->shipChanged(); break;
        case 2: _t->onTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KCDock::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCDock::completed)) {
                *result = 0;
            }
        }
        {
            typedef void (KCDock::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCDock::shipChanged)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject KCDock::staticMetaObject = {
    { &KCGameObject::staticMetaObject, qt_meta_stringdata_KCDock.data,
      qt_meta_data_KCDock,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCDock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCDock::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCDock.stringdata))
        return static_cast<void*>(const_cast< KCDock*>(this));
    return KCGameObject::qt_metacast(_clname);
}

int KCDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KCGameObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void KCDock::completed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void KCDock::shipChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
