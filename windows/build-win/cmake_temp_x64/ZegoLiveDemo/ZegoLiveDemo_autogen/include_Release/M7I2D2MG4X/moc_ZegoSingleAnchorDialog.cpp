/****************************************************************************
** Meta object code from reading C++ file 'ZegoSingleAnchorDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Dialog/ZegoSingleAnchorDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoSingleAnchorDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoSingleAnchorDialog_t {
    QByteArrayData data[21];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoSingleAnchorDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoSingleAnchorDialog_t qt_meta_stringdata_ZegoSingleAnchorDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ZegoSingleAnchorDialog"
QT_MOC_LITERAL(1, 23, 11), // "OnLoginRoom"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 9), // "errorCode"
QT_MOC_LITERAL(4, 46, 6), // "roomId"
QT_MOC_LITERAL(5, 53, 18), // "QVector<StreamPtr>"
QT_MOC_LITERAL(6, 72, 11), // "vStreamList"
QT_MOC_LITERAL(7, 84, 20), // "OnPublishStateUpdate"
QT_MOC_LITERAL(8, 105, 9), // "stateCode"
QT_MOC_LITERAL(9, 115, 8), // "streamId"
QT_MOC_LITERAL(10, 124, 9), // "StreamPtr"
QT_MOC_LITERAL(11, 134, 10), // "streamInfo"
QT_MOC_LITERAL(12, 145, 22), // "OnPublishQualityUpdate"
QT_MOC_LITERAL(13, 168, 7), // "quality"
QT_MOC_LITERAL(14, 176, 6), // "capFPS"
QT_MOC_LITERAL(15, 183, 8), // "videoFPS"
QT_MOC_LITERAL(16, 192, 8), // "videoKBS"
QT_MOC_LITERAL(17, 201, 8), // "audioKBS"
QT_MOC_LITERAL(18, 210, 3), // "rtt"
QT_MOC_LITERAL(19, 214, 11), // "pktLostRate"
QT_MOC_LITERAL(20, 226, 21) // "OnButtonSwitchPublish"

    },
    "ZegoSingleAnchorDialog\0OnLoginRoom\0\0"
    "errorCode\0roomId\0QVector<StreamPtr>\0"
    "vStreamList\0OnPublishStateUpdate\0"
    "stateCode\0streamId\0StreamPtr\0streamInfo\0"
    "OnPublishQualityUpdate\0quality\0capFPS\0"
    "videoFPS\0videoKBS\0audioKBS\0rtt\0"
    "pktLostRate\0OnButtonSwitchPublish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoSingleAnchorDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x09 /* Protected */,
       7,    3,   41,    2, 0x09 /* Protected */,
      12,    8,   48,    2, 0x09 /* Protected */,
      20,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 10,    8,    9,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,    9,   13,   14,   15,   16,   17,   18,   19,
    QMetaType::Void,

       0        // eod
};

void ZegoSingleAnchorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoSingleAnchorDialog *_t = static_cast<ZegoSingleAnchorDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnLoginRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[3]))); break;
        case 1: _t->OnPublishStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< StreamPtr(*)>(_a[3]))); break;
        case 2: _t->OnPublishQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 3: _t->OnButtonSwitchPublish(); break;
        default: ;
        }
    }
}

const QMetaObject ZegoSingleAnchorDialog::staticMetaObject = {
    { &ZegoBaseDialog::staticMetaObject, qt_meta_stringdata_ZegoSingleAnchorDialog.data,
      qt_meta_data_ZegoSingleAnchorDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoSingleAnchorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoSingleAnchorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoSingleAnchorDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoSingleAnchorDialog*>(this));
    return ZegoBaseDialog::qt_metacast(_clname);
}

int ZegoSingleAnchorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
