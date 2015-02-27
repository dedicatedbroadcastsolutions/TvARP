/****************************************************************************
** Meta object code from reading C++ file 'ts_info.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Source/ts_info.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ts_info.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TS_Info_t {
    QByteArrayData data[9];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TS_Info_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TS_Info_t qt_meta_stringdata_TS_Info = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 6),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 12),
QT_MOC_LITERAL(4, 29, 16),
QT_MOC_LITERAL(5, 46, 15),
QT_MOC_LITERAL(6, 62, 6),
QT_MOC_LITERAL(7, 69, 3),
QT_MOC_LITERAL(8, 73, 6)
    },
    "TS_Info\0status\0\0process_file\0"
    "Transport_Stream\0source_filename\0"
    "getPCR\0PCR\0packet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TS_Info[] = {

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
       3,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    0x80000000 | 4, QMetaType::QString,    5,
    0x80000000 | 7, QMetaType::QByteArray,    8,

       0        // eod
};

void TS_Info::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TS_Info *_t = static_cast<TS_Info *>(_o);
        switch (_id) {
        case 0: _t->status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { Transport_Stream _r = _t->process_file((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Transport_Stream*>(_a[0]) = _r; }  break;
        case 2: { PCR _r = _t->getPCR((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< PCR*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TS_Info::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TS_Info::status)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TS_Info::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TS_Info.data,
      qt_meta_data_TS_Info,  qt_static_metacall, 0, 0}
};


const QMetaObject *TS_Info::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TS_Info::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TS_Info.stringdata))
        return static_cast<void*>(const_cast< TS_Info*>(this));
    return QObject::qt_metacast(_clname);
}

int TS_Info::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void TS_Info::status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
