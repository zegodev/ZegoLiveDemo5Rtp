/****************************************************************************
** Meta object code from reading C++ file 'ZegoBaseDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Base/ZegoBaseDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoBaseDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoBaseDialog_t {
    QByteArrayData data[68];
    char stringdata0[889];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoBaseDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoBaseDialog_t qt_meta_stringdata_ZegoBaseDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ZegoBaseDialog"
QT_MOC_LITERAL(1, 15, 20), // "sigSaveVideoSettings"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "SettingsPtr"
QT_MOC_LITERAL(4, 49, 8), // "settings"
QT_MOC_LITERAL(5, 58, 20), // "sigShowSnapShotImage"
QT_MOC_LITERAL(6, 79, 7), // "QImage*"
QT_MOC_LITERAL(7, 87, 9), // "imageData"
QT_MOC_LITERAL(8, 97, 12), // "OnUserUpdate"
QT_MOC_LITERAL(9, 110, 16), // "QVector<QString>"
QT_MOC_LITERAL(10, 127, 7), // "userIDs"
QT_MOC_LITERAL(11, 135, 9), // "userNames"
QT_MOC_LITERAL(12, 145, 12), // "QVector<int>"
QT_MOC_LITERAL(13, 158, 9), // "userFlags"
QT_MOC_LITERAL(14, 168, 9), // "userRoles"
QT_MOC_LITERAL(15, 178, 9), // "userCount"
QT_MOC_LITERAL(16, 188, 28), // "LIVEROOM::ZegoUserUpdateType"
QT_MOC_LITERAL(17, 217, 4), // "type"
QT_MOC_LITERAL(18, 222, 12), // "OnDisconnect"
QT_MOC_LITERAL(19, 235, 9), // "errorCode"
QT_MOC_LITERAL(20, 245, 6), // "roomId"
QT_MOC_LITERAL(21, 252, 9), // "OnKickOut"
QT_MOC_LITERAL(22, 262, 6), // "reason"
QT_MOC_LITERAL(23, 269, 12), // "OnAVAuxInput"
QT_MOC_LITERAL(24, 282, 14), // "unsigned char*"
QT_MOC_LITERAL(25, 297, 5), // "pData"
QT_MOC_LITERAL(26, 303, 4), // "int*"
QT_MOC_LITERAL(27, 308, 8), // "pDataLen"
QT_MOC_LITERAL(28, 317, 13), // "pDataLenValue"
QT_MOC_LITERAL(29, 331, 11), // "pSampleRate"
QT_MOC_LITERAL(30, 343, 12), // "pNumChannels"
QT_MOC_LITERAL(31, 356, 17), // "OnSendRoomMessage"
QT_MOC_LITERAL(32, 374, 6), // "roomID"
QT_MOC_LITERAL(33, 381, 7), // "sendSeq"
QT_MOC_LITERAL(34, 389, 9), // "messageId"
QT_MOC_LITERAL(35, 399, 17), // "OnRecvRoomMessage"
QT_MOC_LITERAL(36, 417, 19), // "QVector<RoomMsgPtr>"
QT_MOC_LITERAL(37, 437, 12), // "vRoomMsgList"
QT_MOC_LITERAL(38, 450, 17), // "OnPreviewSnapshot"
QT_MOC_LITERAL(39, 468, 6), // "pImage"
QT_MOC_LITERAL(40, 475, 10), // "OnSnapshot"
QT_MOC_LITERAL(41, 486, 8), // "streamID"
QT_MOC_LITERAL(42, 495, 18), // "OnClickTitleButton"
QT_MOC_LITERAL(43, 514, 7), // "OnClose"
QT_MOC_LITERAL(44, 522, 19), // "OnButtonSendMessage"
QT_MOC_LITERAL(45, 542, 20), // "OnButtonSoundCapture"
QT_MOC_LITERAL(46, 563, 18), // "OnButtonMircoPhone"
QT_MOC_LITERAL(47, 582, 13), // "OnButtonSound"
QT_MOC_LITERAL(48, 596, 14), // "OnButtonCamera"
QT_MOC_LITERAL(49, 611, 12), // "OnProgChange"
QT_MOC_LITERAL(50, 624, 10), // "soundlevel"
QT_MOC_LITERAL(51, 635, 11), // "OnShareLink"
QT_MOC_LITERAL(52, 647, 11), // "OnButtonAux"
QT_MOC_LITERAL(53, 659, 17), // "OnSnapshotPreview"
QT_MOC_LITERAL(54, 677, 22), // "OnSnapshotWithStreamID"
QT_MOC_LITERAL(55, 700, 15), // "OnUseDefaultAux"
QT_MOC_LITERAL(56, 716, 5), // "state"
QT_MOC_LITERAL(57, 722, 19), // "OnSwitchAudioDevice"
QT_MOC_LITERAL(58, 742, 2), // "id"
QT_MOC_LITERAL(59, 745, 19), // "OnSwitchVideoDevice"
QT_MOC_LITERAL(60, 765, 20), // "OnSwitchVideoDevice2"
QT_MOC_LITERAL(61, 786, 22), // "OnButtonShowFullScreen"
QT_MOC_LITERAL(62, 809, 19), // "OnShowSnapShotImage"
QT_MOC_LITERAL(63, 829, 13), // "OnDeviceAdded"
QT_MOC_LITERAL(64, 843, 11), // "device_type"
QT_MOC_LITERAL(65, 855, 11), // "device_name"
QT_MOC_LITERAL(66, 867, 15), // "OnDeviceDeleted"
QT_MOC_LITERAL(67, 883, 5) // "index"

    },
    "ZegoBaseDialog\0sigSaveVideoSettings\0"
    "\0SettingsPtr\0settings\0sigShowSnapShotImage\0"
    "QImage*\0imageData\0OnUserUpdate\0"
    "QVector<QString>\0userIDs\0userNames\0"
    "QVector<int>\0userFlags\0userRoles\0"
    "userCount\0LIVEROOM::ZegoUserUpdateType\0"
    "type\0OnDisconnect\0errorCode\0roomId\0"
    "OnKickOut\0reason\0OnAVAuxInput\0"
    "unsigned char*\0pData\0int*\0pDataLen\0"
    "pDataLenValue\0pSampleRate\0pNumChannels\0"
    "OnSendRoomMessage\0roomID\0sendSeq\0"
    "messageId\0OnRecvRoomMessage\0"
    "QVector<RoomMsgPtr>\0vRoomMsgList\0"
    "OnPreviewSnapshot\0pImage\0OnSnapshot\0"
    "streamID\0OnClickTitleButton\0OnClose\0"
    "OnButtonSendMessage\0OnButtonSoundCapture\0"
    "OnButtonMircoPhone\0OnButtonSound\0"
    "OnButtonCamera\0OnProgChange\0soundlevel\0"
    "OnShareLink\0OnButtonAux\0OnSnapshotPreview\0"
    "OnSnapshotWithStreamID\0OnUseDefaultAux\0"
    "state\0OnSwitchAudioDevice\0id\0"
    "OnSwitchVideoDevice\0OnSwitchVideoDevice2\0"
    "OnButtonShowFullScreen\0OnShowSnapShotImage\0"
    "OnDeviceAdded\0device_type\0device_name\0"
    "OnDeviceDeleted\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoBaseDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  164,    2, 0x06 /* Public */,
       5,    1,  167,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    6,  170,    2, 0x09 /* Protected */,
      18,    2,  183,    2, 0x09 /* Protected */,
      21,    2,  188,    2, 0x09 /* Protected */,
      23,    5,  193,    2, 0x09 /* Protected */,
      31,    4,  204,    2, 0x09 /* Protected */,
      35,    2,  213,    2, 0x09 /* Protected */,
      38,    1,  218,    2, 0x09 /* Protected */,
      40,    2,  221,    2, 0x09 /* Protected */,
      42,    0,  226,    2, 0x0a /* Public */,
      43,    0,  227,    2, 0x0a /* Public */,
      44,    0,  228,    2, 0x0a /* Public */,
      45,    0,  229,    2, 0x0a /* Public */,
      46,    0,  230,    2, 0x0a /* Public */,
      47,    0,  231,    2, 0x0a /* Public */,
      48,    0,  232,    2, 0x0a /* Public */,
      49,    1,  233,    2, 0x0a /* Public */,
      51,    0,  236,    2, 0x0a /* Public */,
      52,    0,  237,    2, 0x0a /* Public */,
      53,    0,  238,    2, 0x0a /* Public */,
      54,    1,  239,    2, 0x0a /* Public */,
      55,    1,  242,    2, 0x0a /* Public */,
      57,    1,  245,    2, 0x0a /* Public */,
      59,    1,  248,    2, 0x0a /* Public */,
      60,    1,  251,    2, 0x0a /* Public */,
      61,    0,  254,    2, 0x0a /* Public */,
      62,    1,  255,    2, 0x0a /* Public */,
      63,    2,  258,    2, 0x0a /* Public */,
      66,    2,  263,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 12, 0x80000000 | 12, QMetaType::UInt, 0x80000000 | 16,   10,   11,   13,   14,   15,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   22,   20,
    QMetaType::Void, 0x80000000 | 24, 0x80000000 | 26, QMetaType::Int, 0x80000000 | 26, 0x80000000 | 26,   25,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::ULongLong,   19,   32,   33,   34,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 36,   20,   37,
    QMetaType::Void, QMetaType::VoidStar,   39,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::QString,   39,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   41,
    QMetaType::Void, QMetaType::Bool,   56,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   64,   65,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   64,   67,

       0        // eod
};

void ZegoBaseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoBaseDialog *_t = static_cast<ZegoBaseDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSaveVideoSettings((*reinterpret_cast< SettingsPtr(*)>(_a[1]))); break;
        case 1: _t->sigShowSnapShotImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 2: _t->OnUserUpdate((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QVector<QString>(*)>(_a[2])),(*reinterpret_cast< QVector<int>(*)>(_a[3])),(*reinterpret_cast< QVector<int>(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< LIVEROOM::ZegoUserUpdateType(*)>(_a[6]))); break;
        case 3: _t->OnDisconnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->OnKickOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->OnAVAuxInput((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4])),(*reinterpret_cast< int*(*)>(_a[5]))); break;
        case 6: _t->OnSendRoomMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< unsigned long long(*)>(_a[4]))); break;
        case 7: _t->OnRecvRoomMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<RoomMsgPtr>(*)>(_a[2]))); break;
        case 8: _t->OnPreviewSnapshot((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 9: _t->OnSnapshot((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->OnClickTitleButton(); break;
        case 11: _t->OnClose(); break;
        case 12: _t->OnButtonSendMessage(); break;
        case 13: _t->OnButtonSoundCapture(); break;
        case 14: _t->OnButtonMircoPhone(); break;
        case 15: _t->OnButtonSound(); break;
        case 16: _t->OnButtonCamera(); break;
        case 17: _t->OnProgChange((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->OnShareLink(); break;
        case 19: _t->OnButtonAux(); break;
        case 20: _t->OnSnapshotPreview(); break;
        case 21: _t->OnSnapshotWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->OnUseDefaultAux((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->OnSwitchAudioDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->OnSwitchVideoDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->OnSwitchVideoDevice2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->OnButtonShowFullScreen(); break;
        case 27: _t->OnShowSnapShotImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 28: _t->OnDeviceAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->OnDeviceDeleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            case 3:
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoBaseDialog::*_t)(SettingsPtr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoBaseDialog::sigSaveVideoSettings)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZegoBaseDialog::*_t)(QImage * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoBaseDialog::sigShowSnapShotImage)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ZegoBaseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZegoBaseDialog.data,
      qt_meta_data_ZegoBaseDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoBaseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoBaseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoBaseDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoBaseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ZegoBaseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void ZegoBaseDialog::sigSaveVideoSettings(SettingsPtr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZegoBaseDialog::sigShowSnapShotImage(QImage * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
