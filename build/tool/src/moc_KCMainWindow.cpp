/****************************************************************************
** Meta object code from reading C++ file 'KCMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tool/src/KCMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KCMainWindow_t {
    QByteArrayData data[46];
    char stringdata[860];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCMainWindow_t qt_meta_stringdata_KCMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KCMainWindow"
QT_MOC_LITERAL(1, 13, 20), // "postConstructorSetup"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "toggleApplication"
QT_MOC_LITERAL(4, 53, 15), // "showApplication"
QT_MOC_LITERAL(5, 69, 15), // "hideApplication"
QT_MOC_LITERAL(6, 85, 16), // "updateFleetsPage"
QT_MOC_LITERAL(7, 102, 15), // "updateShipsPage"
QT_MOC_LITERAL(8, 118, 17), // "updateRepairsPage"
QT_MOC_LITERAL(9, 136, 23), // "updateConstructionsPage"
QT_MOC_LITERAL(10, 160, 12), // "updateTimers"
QT_MOC_LITERAL(11, 173, 19), // "updateSettingThings"
QT_MOC_LITERAL(12, 193, 8), // "loadData"
QT_MOC_LITERAL(13, 202, 18), // "leaveNoNetworkPage"
QT_MOC_LITERAL(14, 221, 25), // "onTranslationLoadFinished"
QT_MOC_LITERAL(15, 247, 23), // "onTranslationLoadFailed"
QT_MOC_LITERAL(16, 271, 5), // "error"
QT_MOC_LITERAL(17, 277, 17), // "onReceivedAdmiral"
QT_MOC_LITERAL(18, 295, 19), // "onReceivedShipTypes"
QT_MOC_LITERAL(19, 315, 15), // "onReceivedShips"
QT_MOC_LITERAL(20, 331, 16), // "onReceivedFleets"
QT_MOC_LITERAL(21, 348, 17), // "onReceivedRepairs"
QT_MOC_LITERAL(22, 366, 23), // "onReceivedConstructions"
QT_MOC_LITERAL(23, 390, 14), // "onRequestError"
QT_MOC_LITERAL(24, 405, 19), // "KCClient::ErrorCode"
QT_MOC_LITERAL(25, 425, 19), // "onTrayIconActivated"
QT_MOC_LITERAL(26, 445, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(27, 479, 6), // "reason"
QT_MOC_LITERAL(28, 486, 15), // "onDockCompleted"
QT_MOC_LITERAL(29, 502, 7), // "KCDock*"
QT_MOC_LITERAL(30, 510, 4), // "dock"
QT_MOC_LITERAL(31, 515, 18), // "onMissionCompleted"
QT_MOC_LITERAL(32, 534, 8), // "KCFleet*"
QT_MOC_LITERAL(33, 543, 5), // "fleet"
QT_MOC_LITERAL(34, 549, 25), // "on_actionFleets_triggered"
QT_MOC_LITERAL(35, 575, 24), // "on_actionShips_triggered"
QT_MOC_LITERAL(36, 600, 26), // "on_actionRepairs_triggered"
QT_MOC_LITERAL(37, 627, 31), // "on_actionConstruction_triggered"
QT_MOC_LITERAL(38, 659, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(39, 687, 25), // "on_settingsButton_clicked"
QT_MOC_LITERAL(40, 713, 34), // "on_noNetworkSettingsButton_cl..."
QT_MOC_LITERAL(41, 748, 24), // "on_tabBar_currentChanged"
QT_MOC_LITERAL(42, 773, 5), // "index"
QT_MOC_LITERAL(43, 779, 30), // "on_fleetsTabBar_currentChanged"
QT_MOC_LITERAL(44, 810, 21), // "checkExpeditionStatus"
QT_MOC_LITERAL(45, 832, 27) // "onExpeditionReminderTimeout"

    },
    "KCMainWindow\0postConstructorSetup\0\0"
    "toggleApplication\0showApplication\0"
    "hideApplication\0updateFleetsPage\0"
    "updateShipsPage\0updateRepairsPage\0"
    "updateConstructionsPage\0updateTimers\0"
    "updateSettingThings\0loadData\0"
    "leaveNoNetworkPage\0onTranslationLoadFinished\0"
    "onTranslationLoadFailed\0error\0"
    "onReceivedAdmiral\0onReceivedShipTypes\0"
    "onReceivedShips\0onReceivedFleets\0"
    "onReceivedRepairs\0onReceivedConstructions\0"
    "onRequestError\0KCClient::ErrorCode\0"
    "onTrayIconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0onDockCompleted\0KCDock*\0dock\0"
    "onMissionCompleted\0KCFleet*\0fleet\0"
    "on_actionFleets_triggered\0"
    "on_actionShips_triggered\0"
    "on_actionRepairs_triggered\0"
    "on_actionConstruction_triggered\0"
    "on_actionSettings_triggered\0"
    "on_settingsButton_clicked\0"
    "on_noNetworkSettingsButton_clicked\0"
    "on_tabBar_currentChanged\0index\0"
    "on_fleetsTabBar_currentChanged\0"
    "checkExpeditionStatus\0onExpeditionReminderTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  189,    2, 0x09 /* Protected */,
       3,    0,  190,    2, 0x0a /* Public */,
       4,    0,  191,    2, 0x0a /* Public */,
       5,    0,  192,    2, 0x0a /* Public */,
       6,    0,  193,    2, 0x0a /* Public */,
       7,    0,  194,    2, 0x0a /* Public */,
       8,    0,  195,    2, 0x0a /* Public */,
       9,    0,  196,    2, 0x0a /* Public */,
      10,    0,  197,    2, 0x0a /* Public */,
      11,    0,  198,    2, 0x0a /* Public */,
      12,    0,  199,    2, 0x0a /* Public */,
      13,    0,  200,    2, 0x0a /* Public */,
      14,    0,  201,    2, 0x08 /* Private */,
      15,    1,  202,    2, 0x08 /* Private */,
      17,    0,  205,    2, 0x08 /* Private */,
      18,    0,  206,    2, 0x08 /* Private */,
      19,    0,  207,    2, 0x08 /* Private */,
      20,    0,  208,    2, 0x08 /* Private */,
      21,    0,  209,    2, 0x08 /* Private */,
      22,    0,  210,    2, 0x08 /* Private */,
      23,    1,  211,    2, 0x08 /* Private */,
      25,    1,  214,    2, 0x08 /* Private */,
      28,    1,  217,    2, 0x08 /* Private */,
      31,    1,  220,    2, 0x08 /* Private */,
      34,    0,  223,    2, 0x08 /* Private */,
      35,    0,  224,    2, 0x08 /* Private */,
      36,    0,  225,    2, 0x08 /* Private */,
      37,    0,  226,    2, 0x08 /* Private */,
      38,    0,  227,    2, 0x08 /* Private */,
      39,    0,  228,    2, 0x08 /* Private */,
      40,    0,  229,    2, 0x08 /* Private */,
      41,    1,  230,    2, 0x08 /* Private */,
      43,    1,  233,    2, 0x08 /* Private */,
      44,    0,  236,    2, 0x08 /* Private */,
      45,    0,  237,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   16,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KCMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KCMainWindow *_t = static_cast<KCMainWindow *>(_o);
        switch (_id) {
        case 0: _t->postConstructorSetup(); break;
        case 1: _t->toggleApplication(); break;
        case 2: _t->showApplication(); break;
        case 3: _t->hideApplication(); break;
        case 4: _t->updateFleetsPage(); break;
        case 5: _t->updateShipsPage(); break;
        case 6: _t->updateRepairsPage(); break;
        case 7: _t->updateConstructionsPage(); break;
        case 8: _t->updateTimers(); break;
        case 9: _t->updateSettingThings(); break;
        case 10: _t->loadData(); break;
        case 11: _t->leaveNoNetworkPage(); break;
        case 12: _t->onTranslationLoadFinished(); break;
        case 13: _t->onTranslationLoadFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->onReceivedAdmiral(); break;
        case 15: _t->onReceivedShipTypes(); break;
        case 16: _t->onReceivedShips(); break;
        case 17: _t->onReceivedFleets(); break;
        case 18: _t->onReceivedRepairs(); break;
        case 19: _t->onReceivedConstructions(); break;
        case 20: _t->onRequestError((*reinterpret_cast< KCClient::ErrorCode(*)>(_a[1]))); break;
        case 21: _t->onTrayIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 22: _t->onDockCompleted((*reinterpret_cast< KCDock*(*)>(_a[1]))); break;
        case 23: _t->onMissionCompleted((*reinterpret_cast< KCFleet*(*)>(_a[1]))); break;
        case 24: _t->on_actionFleets_triggered(); break;
        case 25: _t->on_actionShips_triggered(); break;
        case 26: _t->on_actionRepairs_triggered(); break;
        case 27: _t->on_actionConstruction_triggered(); break;
        case 28: _t->on_actionSettings_triggered(); break;
        case 29: _t->on_settingsButton_clicked(); break;
        case 30: _t->on_noNetworkSettingsButton_clicked(); break;
        case 31: _t->on_tabBar_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_fleetsTabBar_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->checkExpeditionStatus(); break;
        case 34: _t->onExpeditionReminderTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KCDock* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KCFleet* >(); break;
            }
            break;
        }
    }
}

const QMetaObject KCMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_KCMainWindow.data,
      qt_meta_data_KCMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KCMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KCMainWindow.stringdata))
        return static_cast<void*>(const_cast< KCMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int KCMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
