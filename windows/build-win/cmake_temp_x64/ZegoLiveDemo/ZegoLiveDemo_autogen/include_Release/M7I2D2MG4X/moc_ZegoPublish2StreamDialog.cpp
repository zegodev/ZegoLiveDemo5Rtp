/****************************************************************************
** Meta object code from reading C++ file 'ZegoPublish2StreamDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Dialog/ZegoPublish2StreamDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoPublish2StreamDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoPublish2StreamDialog_t {
    QByteArrayData data[29];
    char stringdata0[366];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoPublish2StreamDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoPublish2StreamDialog_t qt_meta_stringdata_ZegoPublish2StreamDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ZegoPublish2StreamDialog"
QT_MOC_LITERAL(1, 25, 11), // "OnLoginRoom"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 9), // "errorCode"
QT_MOC_LITERAL(4, 48, 6), // "roomId"
QT_MOC_LITERAL(5, 55, 18), // "QVector<StreamPtr>"
QT_MOC_LITERAL(6, 74, 11), // "vStreamList"
QT_MOC_LITERAL(7, 86, 15), // "OnStreamUpdated"
QT_MOC_LITERAL(8, 102, 30), // "LIVEROOM::ZegoStreamUpdateType"
QT_MOC_LITERAL(9, 133, 4), // "type"
QT_MOC_LITERAL(10, 138, 20), // "OnPublishStateUpdate"
QT_MOC_LITERAL(11, 159, 9), // "stateCode"
QT_MOC_LITERAL(12, 169, 8), // "streamId"
QT_MOC_LITERAL(13, 178, 9), // "StreamPtr"
QT_MOC_LITERAL(14, 188, 10), // "streamInfo"
QT_MOC_LITERAL(15, 199, 22), // "OnPublishQualityUpdate"
QT_MOC_LITERAL(16, 222, 7), // "quality"
QT_MOC_LITERAL(17, 230, 6), // "capFPS"
QT_MOC_LITERAL(18, 237, 8), // "videoFPS"
QT_MOC_LITERAL(19, 246, 8), // "videoKBS"
QT_MOC_LITERAL(20, 255, 8), // "audioKBS"
QT_MOC_LITERAL(21, 264, 3), // "rtt"
QT_MOC_LITERAL(22, 268, 11), // "pktLostRate"
QT_MOC_LITERAL(23, 280, 17), // "OnPlayStateUpdate"
QT_MOC_LITERAL(24, 298, 17), // "OnJoinLiveRequest"
QT_MOC_LITERAL(25, 316, 3), // "seq"
QT_MOC_LITERAL(26, 320, 10), // "fromUserId"
QT_MOC_LITERAL(27, 331, 12), // "fromUserName"
QT_MOC_LITERAL(28, 344, 21) // "OnButtonSwitchPublish"

    },
    "ZegoPublish2StreamDialog\0OnLoginRoom\0"
    "\0errorCode\0roomId\0QVector<StreamPtr>\0"
    "vStreamList\0OnStreamUpdated\0"
    "LIVEROOM::ZegoStreamUpdateType\0type\0"
    "OnPublishStateUpdate\0stateCode\0streamId\0"
    "StreamPtr\0streamInfo\0OnPublishQualityUpdate\0"
    "quality\0capFPS\0videoFPS\0videoKBS\0"
    "audioKBS\0rtt\0pktLostRate\0OnPlayStateUpdate\0"
    "OnJoinLiveRequest\0seq\0fromUserId\0"
    "fromUserName\0OnButtonSwitchPublish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoPublish2StreamDialog[] = {

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
       1,    3,   49,    2, 0x09 /* Protected */,
       7,    3,   56,    2, 0x09 /* Protected */,
      10,    3,   63,    2, 0x09 /* Protected */,
      15,    8,   70,    2, 0x09 /* Protected */,
      23,    2,   87,    2, 0x09 /* Protected */,
      24,    4,   92,    2, 0x09 /* Protected */,
      28,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5, 0x80000000 | 8,    4,    6,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,   12,   16,   17,   18,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   25,   26,   27,    4,
    QMetaType::Void,

       0        // eod
};

void ZegoPublish2StreamDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoPublish2StreamDialog *_t = static_cast<ZegoPublish2StreamDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnLoginRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[3]))); break;
        case 1: _t->OnStreamUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[2])),(*reinterpret_cast< LIVEROOM::ZegoStreamUpdateType(*)>(_a[3]))); break;
        case 2: _t->OnPublishStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< StreamPtr(*)>(_a[3]))); break;
        case 3: _t->OnPublishQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 4: _t->OnPlayStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->OnJoinLiveRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->OnButtonSwitchPublish(); break;
        default: ;
        }
    }
}

const QMetaObject ZegoPublish2StreamDialog::staticMetaObject = {
    { &ZegoBaseDialog::staticMetaObject, qt_meta_stringdata_ZegoPublish2StreamDialog.data,
      qt_meta_data_ZegoPublish2StreamDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoPublish2StreamDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoPublish2StreamDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoPublish2StreamDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoPublish2StreamDialog*>(this));
    return ZegoBaseDialog::qt_metacast(_clname);
}

int ZegoPublish2StreamDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoBaseDialog::qt_metacall(_c, _id, _a);
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
