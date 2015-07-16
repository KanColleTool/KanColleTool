/****************************************************************************
** Meta object code from reading C++ file 'KCTViewerTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/test/KCTViewerTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCTViewerTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCTViewerTest_t {
    QByteArrayData data[6];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCTViewerTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCTViewerTest_t qt_meta_stringdata_KCTViewerTest = {
    {
QT_MOC_LITERAL(0, 0, 13), // "KCTViewerTest"
QT_MOC_LITERAL(1, 14, 12), // "initTestCase"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 25), // "testTranslationTranslated"
QT_MOC_LITERAL(4, 54, 27), // "testTranslationUntranslated"
QT_MOC_LITERAL(5, 82, 22) // "testTranslationUnknown"

    },
    "KCTViewerTest\0initTestCase\0\0"
    "testTranslationTranslated\0"
    "testTranslationUntranslated\0"
    "testTranslationUnknown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCTViewerTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KCTViewerTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCTViewerTest *_t = static_cast<KCTViewerTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->testTranslationTranslated(); break;
        case 2: _t->testTranslationUntranslated(); break;
        case 3: _t->testTranslationUnknown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject KCTViewerTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCTViewerTest.data,
      qt_meta_data_KCTViewerTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCTViewerTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCTViewerTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCTViewerTest.stringdata))
        return static_cast<void*>(const_cast< KCTViewerTest*>(this));
    return QObject::qt_metacast(_clname);
}

int KCTViewerTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
