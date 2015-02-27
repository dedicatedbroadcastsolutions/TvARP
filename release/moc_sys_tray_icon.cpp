/****************************************************************************
** Meta object code from reading C++ file 'sys_tray_icon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Source/sys_tray_icon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sys_tray_icon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sys_Tray_Icon_t {
    QByteArrayData data[12];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sys_Tray_Icon_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sys_Tray_Icon_t qt_meta_stringdata_sys_Tray_Icon = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 16),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 15),
QT_MOC_LITERAL(4, 48, 7),
QT_MOC_LITERAL(5, 56, 5),
QT_MOC_LITERAL(6, 62, 13),
QT_MOC_LITERAL(7, 76, 33),
QT_MOC_LITERAL(8, 110, 6),
QT_MOC_LITERAL(9, 117, 11),
QT_MOC_LITERAL(10, 129, 14),
QT_MOC_LITERAL(11, 144, 12)
    },
    "sys_Tray_Icon\0on_newConnection\0\0"
    "program_running\0setIcon\0index\0"
    "iconActivated\0QSystemTrayIcon::ActivationReason\0"
    "reason\0showMessage\0messageClicked\0"
    "quit_program"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sys_Tray_Icon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    1,   51,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sys_Tray_Icon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sys_Tray_Icon *_t = static_cast<sys_Tray_Icon *>(_o);
        switch (_id) {
        case 0: _t->on_newConnection(); break;
        case 1: { bool _r = _t->program_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->setIcon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 4: _t->showMessage(); break;
        case 5: _t->messageClicked(); break;
        case 6: _t->quit_program(); break;
        default: ;
        }
    }
}

const QMetaObject sys_Tray_Icon::staticMetaObject = {
    { &MainWindow::staticMetaObject, qt_meta_stringdata_sys_Tray_Icon.data,
      qt_meta_data_sys_Tray_Icon,  qt_static_metacall, 0, 0}
};


const QMetaObject *sys_Tray_Icon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sys_Tray_Icon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sys_Tray_Icon.stringdata))
        return static_cast<void*>(const_cast< sys_Tray_Icon*>(this));
    return MainWindow::qt_metacast(_clname);
}

int sys_Tray_Icon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
