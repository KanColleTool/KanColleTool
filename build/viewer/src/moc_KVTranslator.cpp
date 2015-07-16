/****************************************************************************
** Meta object code from reading C++ file 'KVTranslator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/src/KVTranslator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVTranslator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KVTranslator_t {
    QByteArrayData data[18];
    char stringdata[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KVTranslator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KVTranslator_t qt_meta_stringdata_KVTranslator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KVTranslator"
QT_MOC_LITERAL(1, 13, 12), // "loadFinished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "loadFailed"
QT_MOC_LITERAL(4, 38, 5), // "error"
QT_MOC_LITERAL(5, 44, 14), // "waitingForLoad"
QT_MOC_LITERAL(6, 59, 15), // "loadTranslation"
QT_MOC_LITERAL(7, 75, 8), // "language"
QT_MOC_LITERAL(8, 84, 9), // "translate"
QT_MOC_LITERAL(9, 94, 4), // "line"
QT_MOC_LITERAL(10, 99, 17), // "lastPathComponent"
QT_MOC_LITERAL(11, 117, 3), // "key"
QT_MOC_LITERAL(12, 121, 13), // "translateJson"
QT_MOC_LITERAL(13, 135, 4), // "json"
QT_MOC_LITERAL(14, 140, 7), // "fixTime"
QT_MOC_LITERAL(15, 148, 4), // "time"
QT_MOC_LITERAL(16, 153, 26), // "translationRequestFinished"
QT_MOC_LITERAL(17, 180, 24) // "blacklistRequestFinished"

    },
    "KVTranslator\0loadFinished\0\0loadFailed\0"
    "error\0waitingForLoad\0loadTranslation\0"
    "language\0translate\0line\0lastPathComponent\0"
    "key\0translateJson\0json\0fixTime\0time\0"
    "translationRequestFinished\0"
    "blacklistRequestFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KVTranslator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,
       5,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   84,    2, 0x0a /* Public */,
       6,    0,   87,    2, 0x2a /* Public | MethodCloned */,
       8,    3,   88,    2, 0x0a /* Public */,
       8,    2,   95,    2, 0x2a /* Public | MethodCloned */,
       8,    1,  100,    2, 0x2a /* Public | MethodCloned */,
      12,    2,  103,    2, 0x0a /* Public */,
      12,    1,  108,    2, 0x2a /* Public | MethodCloned */,
      14,    1,  111,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   10,   11,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::QString, QMetaType::QString,    9,
    QMetaType::QByteArray, QMetaType::QByteArray, QMetaType::QString,   13,   10,
    QMetaType::QByteArray, QMetaType::QByteArray,   13,
    QMetaType::QString, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KVTranslator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KVTranslator *_t = static_cast<KVTranslator *>(_o);
        switch (_id) {
        case 0: _t->loadFinished(); break;
        case 1: _t->loadFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->waitingForLoad(); break;
        case 3: _t->loadTranslation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->loadTranslation(); break;
        case 5: { QString _r = _t->translate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->translate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: { QString _r = _t->translate((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QByteArray _r = _t->translateJson((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 9: { QByteArray _r = _t->translateJson((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->fixTime((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: _t->translationRequestFinished(); break;
        case 12: _t->blacklistRequestFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KVTranslator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVTranslator::loadFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (KVTranslator::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVTranslator::loadFailed)) {
                *result = 1;
            }
        }
        {
            typedef void (KVTranslator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVTranslator::waitingForLoad)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject KVTranslator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KVTranslator.data,
      qt_meta_data_KVTranslator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KVTranslator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVTranslator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KVTranslator.stringdata))
        return static_cast<void*>(const_cast< KVTranslator*>(this));
    return QObject::qt_metacast(_clname);
}

int KVTranslator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void KVTranslator::loadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void KVTranslator::loadFailed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KVTranslator::waitingForLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
