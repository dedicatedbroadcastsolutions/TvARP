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
    QByteArrayData data[12];
    char stringdata[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFmpeg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFmpeg_t qt_meta_stringdata_FFmpeg = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 16),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 13),
QT_MOC_LITERAL(4, 39, 14),
QT_MOC_LITERAL(5, 54, 6),
QT_MOC_LITERAL(6, 61, 9),
QT_MOC_LITERAL(7, 71, 10),
QT_MOC_LITERAL(8, 82, 6),
QT_MOC_LITERAL(9, 89, 23),
QT_MOC_LITERAL(10, 113, 14),
QT_MOC_LITERAL(11, 128, 16)
    },
    "FFmpeg\0transcode_status\0\0ffmpeg_stdout\0"
    "encode_started\0encode\0inputfile\0"
    "outputfile\0ffplay\0readyReadStandardOutput\0"
    "processStarted\0encodingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFmpeg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       3,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   63,    2, 0x0a /* Public */,
       8,    1,   68,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString,    6,
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
        case 0: _t->transcode_status((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->ffmpeg_stdout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->encode_started(); break;
        case 3: _t->encode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->ffplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->readyReadStandardOutput(); break;
        case 6: _t->processStarted(); break;
        case 7: _t->encodingFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FFmpeg::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::transcode_status)) {
                *result = 0;
            }
        }
        {
            typedef void (FFmpeg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::ffmpeg_stdout)) {
                *result = 1;
            }
        }
        {
            typedef void (FFmpeg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpeg::encode_started)) {
                *result = 2;
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
void FFmpeg::transcode_status(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FFmpeg::ffmpeg_stdout(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FFmpeg::encode_started()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
