/****************************************************************************
** Meta object code from reading C++ file 'KVSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer/src/KVSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KVSettingsDialog_t {
    QByteArrayData data[14];
    char stringdata[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KVSettingsDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KVSettingsDialog_t qt_meta_stringdata_KVSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "KVSettingsDialog"
QT_MOC_LITERAL(1, 17, 5), // "apply"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "accept"
QT_MOC_LITERAL(4, 31, 13), // "applySettings"
QT_MOC_LITERAL(5, 45, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(6, 66, 16), // "QAbstractButton*"
QT_MOC_LITERAL(7, 83, 6), // "button"
QT_MOC_LITERAL(8, 90, 29), // "on_proxyCheckbox_stateChanged"
QT_MOC_LITERAL(9, 120, 5), // "state"
QT_MOC_LITERAL(10, 126, 35), // "on_translationCheckbox_stateC..."
QT_MOC_LITERAL(11, 162, 41), // "on_uploadScreenshotsCheckbox_..."
QT_MOC_LITERAL(12, 204, 23), // "on_browseButton_pressed"
QT_MOC_LITERAL(13, 228, 21) // "on_openButton_pressed"

    },
    "KVSettingsDialog\0apply\0\0accept\0"
    "applySettings\0on_buttonBox_clicked\0"
    "QAbstractButton*\0button\0"
    "on_proxyCheckbox_stateChanged\0state\0"
    "on_translationCheckbox_stateChanged\0"
    "on_uploadScreenshotsCheckbox_stateChanged\0"
    "on_browseButton_pressed\0on_openButton_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KVSettingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    1,   62,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
      10,    1,   68,    2, 0x08 /* Private */,
      11,    1,   71,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KVSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KVSettingsDialog *_t = static_cast<KVSettingsDialog *>(_o);
        switch (_id) {
        case 0: _t->apply(); break;
        case 1: _t->accept(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->on_proxyCheckbox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_translationCheckbox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_uploadScreenshotsCheckbox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_browseButton_pressed(); break;
        case 8: _t->on_openButton_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KVSettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KVSettingsDialog::apply)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KVSettingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KVSettingsDialog.data,
      qt_meta_data_KVSettingsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KVSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KVSettingsDialog.stringdata))
        return static_cast<void*>(const_cast< KVSettingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int KVSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void KVSettingsDialog::apply()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
