/****************************************************************************
** Meta object code from reading C++ file 'KVNetworkReply.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/src/KVNetworkReply.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVNetworkReply.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KVNetworkReply_t {
    QByteArrayData data[6];
    char stringdata[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KVNetworkReply_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KVNetworkReply_t qt_meta_stringdata_KVNetworkReply = {
    {
QT_MOC_LITERAL(0, 0, 14), // "KVNetworkReply"
QT_MOC_LITERAL(1, 15, 14), // "handleResponse"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "postToTool"
QT_MOC_LITERAL(4, 42, 4), // "body"
QT_MOC_LITERAL(5, 47, 11) // "writeToDisk"

    },
    "KVNetworkReply\0handleResponse\0\0"
    "postToTool\0body\0writeToDisk"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KVNetworkReply[] = {

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
       1,    0,   29,    2, 0x09 /* Protected */,
       3,    1,   30,    2, 0x09 /* Protected */,
       5,    1,   33,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QByteArray,    4,

       0        // eod
};

void KVNetworkReply::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KVNetworkReply *_t = static_cast<KVNetworkReply *>(_o);
        switch (_id) {
        case 0: _t->handleResponse(); break;
        case 1: _t->postToTool((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->writeToDisk((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject KVNetworkReply::staticMetaObject = {
    { &QNetworkReply::staticMetaObject, qt_meta_stringdata_KVNetworkReply.data,
      qt_meta_data_KVNetworkReply,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KVNetworkReply::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVNetworkReply::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KVNetworkReply.stringdata))
        return static_cast<void*>(const_cast< KVNetworkReply*>(this));
    return QNetworkReply::qt_metacast(_clname);
}

int KVNetworkReply::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkReply::qt_metacall(_c, _id, _a);
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
