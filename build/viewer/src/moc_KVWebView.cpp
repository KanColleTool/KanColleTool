/****************************************************************************
** Meta object code from reading C++ file 'KVWebView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/src/KVWebView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVWebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KVWebView_t {
    QByteArrayData data[9];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KVWebView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KVWebView_t qt_meta_stringdata_KVWebView = {
    {
QT_MOC_LITERAL(0, 0, 9), // "KVWebView"
QT_MOC_LITERAL(1, 10, 17), // "gameFrameFinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "url"
QT_MOC_LITERAL(4, 33, 14), // "onFrameCreated"
QT_MOC_LITERAL(5, 48, 10), // "QWebFrame*"
QT_MOC_LITERAL(6, 59, 5), // "frame"
QT_MOC_LITERAL(7, 65, 23), // "onGameFrameLoadFinished"
QT_MOC_LITERAL(8, 89, 2) // "ok"

    },
    "KVWebView\0gameFrameFinished\0\0url\0"
    "onFrameCreated\0QWebFrame*\0frame\0"
    "onGameFrameLoadFinished\0ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KVWebView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x08 /* Private */,
       7,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QUrl,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void KVWebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KVWebView *_t = static_cast<KVWebView *>(_o);
        switch (_id) {
        case 0: _t->gameFrameFinished((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 1: _t->onFrameCreated((*reinterpret_cast< QWebFrame*(*)>(_a[1]))); break;
        case 2: _t->onGameFrameLoadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KVWebView::*_t)(QUrl );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVWebView::gameFrameFinished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KVWebView::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_KVWebView.data,
      qt_meta_data_KVWebView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KVWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KVWebView.stringdata))
        return static_cast<void*>(const_cast< KVWebView*>(this));
    return QWebView::qt_metacast(_clname);
}

int KVWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
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
void KVWebView::gameFrameFinished(QUrl _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
