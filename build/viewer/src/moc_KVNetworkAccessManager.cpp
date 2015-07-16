/****************************************************************************
** Meta object code from reading C++ file 'KVNetworkAccessManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/src/KVNetworkAccessManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVNetworkAccessManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KVNetworkAccessManager_t {
    QByteArrayData data[8];
    char stringdata[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KVNetworkAccessManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KVNetworkAccessManager_t qt_meta_stringdata_KVNetworkAccessManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "KVNetworkAccessManager"
QT_MOC_LITERAL(1, 23, 22), // "trackedProgressChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 8), // "progress"
QT_MOC_LITERAL(4, 56, 5), // "total"
QT_MOC_LITERAL(5, 62, 25), // "trackedGETMetaDataChanged"
QT_MOC_LITERAL(6, 88, 19), // "trackedGETReadyRead"
QT_MOC_LITERAL(7, 108, 18) // "trackedGETFinished"

    },
    "KVNetworkAccessManager\0trackedProgressChanged\0"
    "\0progress\0total\0trackedGETMetaDataChanged\0"
    "trackedGETReadyRead\0trackedGETFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KVNetworkAccessManager[] = {

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
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x09 /* Protected */,
       6,    0,   40,    2, 0x09 /* Protected */,
       7,    0,   41,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KVNetworkAccessManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KVNetworkAccessManager *_t = static_cast<KVNetworkAccessManager *>(_o);
        switch (_id) {
        case 0: _t->trackedProgressChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->trackedGETMetaDataChanged(); break;
        case 2: _t->trackedGETReadyRead(); break;
        case 3: _t->trackedGETFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KVNetworkAccessManager::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVNetworkAccessManager::trackedProgressChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KVNetworkAccessManager::staticMetaObject = {
    { &QNetworkAccessManager::staticMetaObject, qt_meta_stringdata_KVNetworkAccessManager.data,
      qt_meta_data_KVNetworkAccessManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KVNetworkAccessManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVNetworkAccessManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KVNetworkAccessManager.stringdata))
        return static_cast<void*>(const_cast< KVNetworkAccessManager*>(this));
    return QNetworkAccessManager::qt_metacast(_clname);
}

int KVNetworkAccessManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkAccessManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KVNetworkAccessManager::trackedProgressChanged(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
