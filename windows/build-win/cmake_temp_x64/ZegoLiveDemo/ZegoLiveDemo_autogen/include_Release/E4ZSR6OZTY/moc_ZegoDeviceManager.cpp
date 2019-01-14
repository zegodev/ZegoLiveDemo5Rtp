/****************************************************************************
** Meta object code from reading C++ file 'ZegoDeviceManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Device/ZegoDeviceManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoDeviceManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoDeviceManager_t {
    QByteArrayData data[24];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoDeviceManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoDeviceManager_t qt_meta_stringdata_ZegoDeviceManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ZegoDeviceManager"
QT_MOC_LITERAL(1, 18, 14), // "sigDeviceAdded"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "type"
QT_MOC_LITERAL(4, 39, 10), // "deviceName"
QT_MOC_LITERAL(5, 50, 16), // "sigDeviceDeleted"
QT_MOC_LITERAL(6, 67, 5), // "index"
QT_MOC_LITERAL(7, 73, 13), // "sigDeviceNone"
QT_MOC_LITERAL(8, 87, 14), // "sigDeviceExist"
QT_MOC_LITERAL(9, 102, 18), // "sigCameraIdChanged"
QT_MOC_LITERAL(10, 121, 8), // "deviceId"
QT_MOC_LITERAL(11, 130, 19), // "sigCameraId2Changed"
QT_MOC_LITERAL(12, 150, 15), // "sigMicIdChanged"
QT_MOC_LITERAL(13, 166, 29), // "sigMicCaptureSoundLevelUpdate"
QT_MOC_LITERAL(14, 196, 10), // "soundlevel"
QT_MOC_LITERAL(15, 207, 25), // "OnAudioDeviceStateChanged"
QT_MOC_LITERAL(16, 233, 19), // "AV::AudioDeviceType"
QT_MOC_LITERAL(17, 253, 10), // "deviceType"
QT_MOC_LITERAL(18, 264, 11), // "strDeviceId"
QT_MOC_LITERAL(19, 276, 13), // "strDeviceName"
QT_MOC_LITERAL(20, 290, 15), // "AV::DeviceState"
QT_MOC_LITERAL(21, 306, 5), // "state"
QT_MOC_LITERAL(22, 312, 25), // "OnVideoDeviceStateChanged"
QT_MOC_LITERAL(23, 338, 28) // "OnMicCaptureSoundLevelUpdate"

    },
    "ZegoDeviceManager\0sigDeviceAdded\0\0"
    "type\0deviceName\0sigDeviceDeleted\0index\0"
    "sigDeviceNone\0sigDeviceExist\0"
    "sigCameraIdChanged\0deviceId\0"
    "sigCameraId2Changed\0sigMicIdChanged\0"
    "sigMicCaptureSoundLevelUpdate\0soundlevel\0"
    "OnAudioDeviceStateChanged\0AV::AudioDeviceType\0"
    "deviceType\0strDeviceId\0strDeviceName\0"
    "AV::DeviceState\0state\0OnVideoDeviceStateChanged\0"
    "OnMicCaptureSoundLevelUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoDeviceManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    2,   74,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x06 /* Public */,
       9,    1,   85,    2, 0x06 /* Public */,
      11,    1,   88,    2, 0x06 /* Public */,
      12,    1,   91,    2, 0x06 /* Public */,
      13,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    4,   97,    2, 0x09 /* Protected */,
      22,    3,  106,    2, 0x09 /* Protected */,
      23,    1,  113,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    6,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Float,   14,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 16, QMetaType::QString, QMetaType::QString, 0x80000000 | 20,   17,   18,   19,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 20,   18,   19,   21,
    QMetaType::Void, QMetaType::Float,   14,

       0        // eod
};

void ZegoDeviceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoDeviceManager *_t = static_cast<ZegoDeviceManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDeviceAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sigDeviceDeleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sigDeviceNone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sigDeviceExist((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sigCameraIdChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sigCameraId2Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sigMicIdChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->sigMicCaptureSoundLevelUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->OnAudioDeviceStateChanged((*reinterpret_cast< AV::AudioDeviceType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< AV::DeviceState(*)>(_a[4]))); break;
        case 9: _t->OnVideoDeviceStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< AV::DeviceState(*)>(_a[3]))); break;
        case 10: _t->OnMicCaptureSoundLevelUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoDeviceManager::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigDeviceAdded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigDeviceDeleted)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigDeviceNone)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigDeviceExist)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigCameraIdChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigCameraId2Changed)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigMicIdChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ZegoDeviceManager::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoDeviceManager::sigMicCaptureSoundLevelUpdate)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject ZegoDeviceManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZegoDeviceManager.data,
      qt_meta_data_ZegoDeviceManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoDeviceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoDeviceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoDeviceManager.stringdata0))
        return static_cast<void*>(const_cast< ZegoDeviceManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ZegoDeviceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ZegoDeviceManager::sigDeviceAdded(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZegoDeviceManager::sigDeviceDeleted(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZegoDeviceManager::sigDeviceNone(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZegoDeviceManager::sigDeviceExist(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZegoDeviceManager::sigCameraIdChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZegoDeviceManager::sigCameraId2Changed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ZegoDeviceManager::sigMicIdChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ZegoDeviceManager::sigMicCaptureSoundLevelUpdate(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
