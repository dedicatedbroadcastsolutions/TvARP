/****************************************************************************
** Meta object code from reading C++ file 'ffmpeg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Source/ffmpeg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ffmpeg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FFmpeg_t {
    QByteArrayData data[23];
    char stringdata[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFmpeg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFmpeg_t qt_meta_stringdata_FFmpeg = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 15),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 13),
QT_MOC_LITERAL(4, 38, 13),
QT_MOC_LITERAL(5, 52, 14),
QT_MOC_LITERAL(6, 67, 13),
QT_MOC_LITERAL(7, 81, 6),
QT_MOC_LITERAL(8, 88, 9),
QT_MOC_LITERAL(9, 98, 10),
QT_MOC_LITERAL(10, 109, 3),
QT_MOC_LITERAL(11, 113, 8),
QT_MOC_LITERAL(12, 122, 12),
QT_MOC_LITERAL(13, 135, 4),
QT_MOC_LITERAL(14, 140, 4),
QT_MOC_LITERAL(15, 145, 6),
QT_MOC_LITERAL(16, 152, 4),
QT_MOC_LITERAL(17, 157, 23),
QT_MOC_LITERAL(18, 181, 14),
QT_MOC_LITERAL(19, 196, 21),
QT_MOC_LITERAL(20, 218, 16),
QT_MOC_LITERAL(21, 235, 12),
QT_MOC_LITERAL(22, 248, 16)
    },
    "FFmpeg\0ffmpeg_finished\0\0ffmpeg_status\0"
    "ffmpeg_stdout\0encode_started\0ffplay_stdout\0"
    "encode\0inputfile\0outputfile\0eas\0"
    "crossbar\0crossbar_pin\0vdev\0adev\0ffplay\0"
    "kill\0readyReadStandardOutput\0"
    "processStarted\0ffplay_processStarted\0"
    "readyread_ffplay\0playFinished\0"
    "encodingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFmpeg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    1,   87,    2, 0x06 /* Public */,
       4,    1,   90,    2, 0x06 /* Public */,
       5,    0,   93,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    7,   97,    2, 0x0a /* Public */,
      15,    1,  112,    2, 0x0a /* Public */,
      16,    0,  115,    2, 0x0a /* Public */,
      17,    0,  116,    2, 0x08 /* Private */,
      18,    0,  117,    2, 0x08 /* Private */,
      19,    0,  118,    2, 0x08 /* Private */,
      20,    0,  119,    2, 0x08 /* Private */,
      21,    0,  120,    2, 0x08 /* Private */,
      22,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::QString, QMetaType::QString,    8,    9,   10,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FFmpeg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FFmpeg *_t = static_cast<FFmpeg *>(_o);
        switch (_id) {
        case 0: _t->ffmpeg_finished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->ffmpeg_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ffmpeg_stdout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->encode_started(); break;
        case 4: _t->ffplay_stdout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->encode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 6: _t->ffplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->kill(); break;
        case 8: _t->readyReadStandardOutput(); break;
        case 9: _t->processStarted(); break;
        case 10: _t->ffplay_processStarted(); break;
        case 11: _t->readyread_ffplay(); break;
        case 12: _t->playFinished(); break;
        case 13: _t->encodingFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FFmpeg::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::ffmpeg_finished)) {
                *result = 0;
            }
        }
        {
            typedef void (FFmpeg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::ffmpeg_status)) {
                *result = 1;
            }
        }
        {
            typedef void (FFmpeg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::ffmpeg_stdout)) {
                *result = 2;
            }
        }
        {
            typedef void (FFmpeg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::encode_started)) {
                *result = 3;
            }
        }
        {
            typedef void (FFmpeg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::ffplay_stdout)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject FFmpeg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FFmpeg.data,
      qt_meta_data_FFmpeg,  qt_static_metacall, 0, 0}
};


const QMetaObject *FFmpeg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFmpeg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FFmpeg.stringdata))
        return static_cast<void*>(const_cast< FFmpeg*>(this));
    return QObject::qt_metacast(_clname);
}

int FFmpeg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void FFmpeg::ffmpeg_finished(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FFmpeg::ffmpeg_status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FFmpeg::ffmpeg_stdout(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FFmpeg::encode_started()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void FFmpeg::ffplay_stdout(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
