/****************************************************************************
** Meta object code from reading C++ file 'KCTranslator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCTranslator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCTranslator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCTranslator_t {
    QByteArrayData data[10];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCTranslator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCTranslator_t qt_meta_stringdata_KCTranslator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KCTranslator"
QT_MOC_LITERAL(1, 13, 12), // "loadFinished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "loadFailed"
QT_MOC_LITERAL(4, 38, 5), // "error"
QT_MOC_LITERAL(5, 44, 9), // "translate"
QT_MOC_LITERAL(6, 54, 4), // "line"
QT_MOC_LITERAL(7, 59, 15), // "loadTranslation"
QT_MOC_LITERAL(8, 75, 8), // "language"
QT_MOC_LITERAL(9, 84, 26) // "translationRequestFinished"

    },
    "KCTranslator\0loadFinished\0\0loadFailed\0"
    "error\0translate\0line\0loadTranslation\0"
    "language\0translationRequestFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCTranslator[] = {

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
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x2a /* Public | MethodCloned */,
       9,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::QString, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KCTranslator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCTranslator *_t = static_cast<KCTranslator *>(_o);
        switch (_id) {
        case 0: _t->loadFinished(); break;
        case 1: _t->loadFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { QString _r = _t->translate((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->loadTranslation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->loadTranslation(); break;
        case 5: _t->translationRequestFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KCTranslator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCTranslator::loadFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (KCTranslator::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCTranslator::loadFailed)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject KCTranslator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCTranslator.data,
      qt_meta_data_KCTranslator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCTranslator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCTranslator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCTranslator.stringdata))
        return static_cast<void*>(const_cast< KCTranslator*>(this));
    return QObject::qt_metacast(_clname);
}

int KCTranslator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void KCTranslator::loadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void KCTranslator::loadFailed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
