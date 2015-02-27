/****************************************************************************
** Meta object code from reading C++ file 'mux_control.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Source/mux_control.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mux_control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Mux_Control_t {
    QByteArrayData data[12];
    char stringdata[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mux_Control_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mux_Control_t qt_meta_stringdata_Mux_Control = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 13),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 16),
QT_MOC_LITERAL(4, 44, 10),
QT_MOC_LITERAL(5, 55, 10),
QT_MOC_LITERAL(6, 66, 12),
QT_MOC_LITERAL(7, 79, 17),
QT_MOC_LITERAL(8, 97, 14),
QT_MOC_LITERAL(9, 112, 18),
QT_MOC_LITERAL(10, 131, 11),
QT_MOC_LITERAL(11, 143, 14)
    },
    "Mux_Control\0process_debug\0\0mux_debug_status\0"
    "eas_insert\0QList<int>\0channel_list\0"
    "revert_eas_config\0program_splice\0"
    "return_from_splice\0handleError\0"
    "read_mux_debug"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mux_Control[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   60,    2, 0x0a /* Public */,
       7,    1,   63,    2, 0x0a /* Public */,
       8,    1,   66,    2, 0x0a /* Public */,
       9,    1,   69,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Mux_Control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Mux_Control *_t = static_cast<Mux_Control *>(_o);
        switch (_id) {
        case 0: _t->process_debug((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->mux_debug_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->eas_insert((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 3: _t->revert_eas_config((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 4: _t->program_splice((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 5: _t->return_from_splice((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 6: _t->handleError(); break;
        case 7: _t->read_mux_debug(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Mux_Control::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mux_Control::process_debug)) {
                *result = 0;
            }
        }
        {
            typedef void (Mux_Control::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mux_Control::mux_debug_status)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Mux_Control::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Mux_Control.data,
      qt_meta_data_Mux_Control,  qt_static_metacall, 0, 0}
};


const QMetaObject *Mux_Control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mux_Control::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mux_Control.stringdata))
        return static_cast<void*>(const_cast< Mux_Control*>(this));
    return QObject::qt_metacast(_clname);
}

int Mux_Control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Mux_Control::process_debug(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mux_Control::mux_debug_status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
