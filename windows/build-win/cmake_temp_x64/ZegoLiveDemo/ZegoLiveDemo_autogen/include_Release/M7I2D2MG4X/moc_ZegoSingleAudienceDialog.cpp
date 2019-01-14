/****************************************************************************
** Meta object code from reading C++ file 'ZegoSingleAudienceDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Dialog/ZegoSingleAudienceDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoSingleAudienceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoSingleAudienceDialog_t {
    QByteArrayData data[18];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoSingleAudienceDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoSingleAudienceDialog_t qt_meta_stringdata_ZegoSingleAudienceDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ZegoSingleAudienceDialog"
QT_MOC_LITERAL(1, 25, 11), // "OnLoginRoom"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 9), // "errorCode"
QT_MOC_LITERAL(4, 48, 6), // "roomId"
QT_MOC_LITERAL(5, 55, 18), // "QVector<StreamPtr>"
QT_MOC_LITERAL(6, 74, 11), // "vStreamList"
QT_MOC_LITERAL(7, 86, 15), // "OnStreamUpdated"
QT_MOC_LITERAL(8, 102, 30), // "LIVEROOM::ZegoStreamUpdateType"
QT_MOC_LITERAL(9, 133, 4), // "type"
QT_MOC_LITERAL(10, 138, 17), // "OnPlayStateUpdate"
QT_MOC_LITERAL(11, 156, 9), // "stateCode"
QT_MOC_LITERAL(12, 166, 8), // "streamId"
QT_MOC_LITERAL(13, 175, 19), // "OnPlayQualityUpdate"
QT_MOC_LITERAL(14, 195, 7), // "quality"
QT_MOC_LITERAL(15, 203, 8), // "videoFPS"
QT_MOC_LITERAL(16, 212, 8), // "videoKBS"
QT_MOC_LITERAL(17, 221, 24) // "OnStreamExtraInfoUpdated"

    },
    "ZegoSingleAudienceDialog\0OnLoginRoom\0"
    "\0errorCode\0roomId\0QVector<StreamPtr>\0"
    "vStreamList\0OnStreamUpdated\0"
    "LIVEROOM::ZegoStreamUpdateType\0type\0"
    "OnPlayStateUpdate\0stateCode\0streamId\0"
    "OnPlayQualityUpdate\0quality\0videoFPS\0"
    "videoKBS\0OnStreamExtraInfoUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoSingleAudienceDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x09 /* Protected */,
       7,    3,   46,    2, 0x09 /* Protected */,
      10,    2,   53,    2, 0x09 /* Protected */,
      13,    4,   58,    2, 0x09 /* Protected */,
      17,    2,   67,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5, 0x80000000 | 8,    4,    6,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double,   12,   14,   15,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    4,    6,

       0        // eod
};

void ZegoSingleAudienceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoSingleAudienceDialog *_t = static_cast<ZegoSingleAudienceDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnLoginRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[3]))); break;
        case 1: _t->OnStreamUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[2])),(*reinterpret_cast< LIVEROOM::ZegoStreamUpdateType(*)>(_a[3]))); break;
        case 2: _t->OnPlayStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->OnPlayQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 4: _t->OnStreamExtraInfoUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ZegoSingleAudienceDialog::staticMetaObject = {
    { &ZegoBaseDialog::staticMetaObject, qt_meta_stringdata_ZegoSingleAudienceDialog.data,
      qt_meta_data_ZegoSingleAudienceDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoSingleAudienceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoSingleAudienceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoSingleAudienceDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoSingleAudienceDialog*>(this));
    return ZegoBaseDialog::qt_metacast(_clname);
}

int ZegoSingleAudienceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
