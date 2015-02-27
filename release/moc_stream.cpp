/****************************************************************************
** Meta object code from reading C++ file 'stream.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Source/stream.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[17];
    char stringdata[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 14),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 13),
QT_MOC_LITERAL(4, 37, 8),
QT_MOC_LITERAL(5, 46, 7),
QT_MOC_LITERAL(6, 54, 8),
QT_MOC_LITERAL(7, 63, 11),
QT_MOC_LITERAL(8, 75, 12),
QT_MOC_LITERAL(9, 88, 12),
QT_MOC_LITERAL(10, 101, 11),
QT_MOC_LITERAL(11, 113, 11),
QT_MOC_LITERAL(12, 125, 15),
QT_MOC_LITERAL(13, 141, 17),
QT_MOC_LITERAL(14, 159, 8),
QT_MOC_LITERAL(15, 168, 13),
QT_MOC_LITERAL(16, 182, 11)
    },
    "Worker\0done_streaming\0\0datagram_sent\0"
    "datagram\0ts_info\0filename\0work_status\0"
    "start_stream\0QHostAddress\0stream_addr\0"
    "stream_port\0source_filename\0"
    "set_packet_period\0kbitrate\0read_datagram\0"
    "stream_init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    3,   64,    2, 0x0a /* Public */,
      13,    1,   71,    2, 0x0a /* Public */,
      15,    0,   74,    2, 0x08 /* Private */,
      16,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, QMetaType::UShort, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   12,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        switch (_id) {
        case 0: _t->done_streaming(); break;
        case 1: _t->datagram_sent((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->ts_info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->work_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->start_stream((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->set_packet_period((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->read_datagram(); break;
        case 7: { bool _r = _t->stream_init((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostAddress >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::done_streaming)) {
                *result = 0;
            }
        }
        {
            typedef void (Worker::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::datagram_sent)) {
                *result = 1;
            }
        }
        {
            typedef void (Worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::ts_info)) {
                *result = 2;
            }
        }
        {
            typedef void (Worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::work_status)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker.data,
      qt_meta_data_Worker,  qt_static_metacall, 0, 0}
};


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata))
        return static_cast<void*>(const_cast< Worker*>(this));
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Worker::done_streaming()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Worker::datagram_sent(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::ts_info(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::work_status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_stream_t {
    QByteArrayData data[18];
    char stringdata[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_stream_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_stream_t qt_meta_stringdata_stream = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 16),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 11),
QT_MOC_LITERAL(4, 37, 8),
QT_MOC_LITERAL(5, 46, 15),
QT_MOC_LITERAL(6, 62, 12),
QT_MOC_LITERAL(7, 75, 11),
QT_MOC_LITERAL(8, 87, 11),
QT_MOC_LITERAL(9, 99, 15),
QT_MOC_LITERAL(10, 115, 6),
QT_MOC_LITERAL(11, 122, 16),
QT_MOC_LITERAL(12, 139, 12),
QT_MOC_LITERAL(13, 152, 7),
QT_MOC_LITERAL(14, 160, 12),
QT_MOC_LITERAL(15, 173, 8),
QT_MOC_LITERAL(16, 182, 13),
QT_MOC_LITERAL(17, 196, 6)
    },
    "stream\0done_with_stream\0\0get_ts_info\0"
    "filename\0start_streaming\0QHostAddress\0"
    "stream_addr\0stream_port\0source_filename\0"
    "status\0done_with_worker\0stream_start\0"
    "ts_info\0set_kbitrate\0kbitrate\0"
    "worker_status\0string"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stream[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       5,    3,   63,    2, 0x06 /* Public */,
      10,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   73,    2, 0x0a /* Public */,
      12,    3,   74,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x0a /* Public */,
      14,    1,   84,    2, 0x0a /* Public */,
      16,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UShort, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UShort, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void stream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        stream *_t = static_cast<stream *>(_o);
        switch (_id) {
        case 0: _t->done_with_stream(); break;
        case 1: _t->get_ts_info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->start_streaming((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->done_with_worker(); break;
        case 5: _t->stream_start((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->ts_info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->set_kbitrate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->worker_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostAddress >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostAddress >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (stream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stream::done_with_stream)) {
                *result = 0;
            }
        }
        {
            typedef void (stream::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stream::get_ts_info)) {
                *result = 1;
            }
        }
        {
            typedef void (stream::*_t)(QHostAddress , quint16 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stream::start_streaming)) {
                *result = 2;
            }
        }
        {
            typedef void (stream::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stream::status)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject stream::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_stream.data,
      qt_meta_data_stream,  qt_static_metacall, 0, 0}
};


const QMetaObject *stream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stream::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_stream.stringdata))
        return static_cast<void*>(const_cast< stream*>(this));
    return QObject::qt_metacast(_clname);
}

int stream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void stream::done_with_stream()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void stream::get_ts_info(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void stream::start_streaming(QHostAddress _t1, quint16 _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void stream::status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
