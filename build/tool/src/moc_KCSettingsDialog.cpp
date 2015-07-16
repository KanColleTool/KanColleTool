/****************************************************************************
** Meta object code from reading C++ file 'KCSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCSettingsDialog_t {
    QByteArrayData data[13];
    char stringdata[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCSettingsDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCSettingsDialog_t qt_meta_stringdata_KCSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "KCSettingsDialog"
QT_MOC_LITERAL(1, 17, 5), // "apply"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "accept"
QT_MOC_LITERAL(4, 31, 13), // "applySettings"
QT_MOC_LITERAL(5, 45, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(6, 66, 16), // "QAbstractButton*"
QT_MOC_LITERAL(7, 83, 6), // "button"
QT_MOC_LITERAL(8, 90, 25), // "on_notifyCheckbox_toggled"
QT_MOC_LITERAL(9, 116, 7), // "checked"
QT_MOC_LITERAL(10, 124, 43), // "on_notifyExpeditionReminderCh..."
QT_MOC_LITERAL(11, 168, 49), // "on_notifyExpeditionReminderRe..."
QT_MOC_LITERAL(12, 218, 50) // "on_notifyExpeditionReminderSu..."

    },
    "KCSettingsDialog\0apply\0\0accept\0"
    "applySettings\0on_buttonBox_clicked\0"
    "QAbstractButton*\0button\0"
    "on_notifyCheckbox_toggled\0checked\0"
    "on_notifyExpeditionReminderCheckbox_toggled\0"
    "on_notifyExpeditionReminderRepeatCheckbox_toggled\0"
    "on_notifyExpeditionReminderSuspendCheckbox_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCSettingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
      10,    1,   63,    2, 0x08 /* Private */,
      11,    1,   66,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,

       0        // eod
};

void KCSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCSettingsDialog *_t = static_cast<KCSettingsDialog *>(_o);
        switch (_id) {
        case 0: _t->apply(); break;
        case 1: _t->accept(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->on_notifyCheckbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_notifyExpeditionReminderCheckbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_notifyExpeditionReminderRepeatCheckbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_notifyExpeditionReminderSuspendCheckbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KCSettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KCSettingsDialog::apply)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KCSettingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KCSettingsDialog.data,
      qt_meta_data_KCSettingsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCSettingsDialog.stringdata))
        return static_cast<void*>(const_cast< KCSettingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int KCSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void KCSettingsDialog::apply()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
