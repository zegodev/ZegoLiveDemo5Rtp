/****************************************************************************
** Meta object code from reading C++ file 'ZegoSDKSignal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/Signal/ZegoSDKSignal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoSDKSignal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QZegoAVSignal_t {
    QByteArrayData data[87];
    char stringdata0[1153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QZegoAVSignal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QZegoAVSignal_t qt_meta_stringdata_QZegoAVSignal = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QZegoAVSignal"
QT_MOC_LITERAL(1, 14, 10), // "sigInitSDK"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "nError"
QT_MOC_LITERAL(4, 33, 12), // "sigLoginRoom"
QT_MOC_LITERAL(5, 46, 9), // "errorCode"
QT_MOC_LITERAL(6, 56, 6), // "roomId"
QT_MOC_LITERAL(7, 63, 18), // "QVector<StreamPtr>"
QT_MOC_LITERAL(8, 82, 11), // "vStreamList"
QT_MOC_LITERAL(9, 94, 13), // "sigLogoutRoom"
QT_MOC_LITERAL(10, 108, 13), // "sigDisconnect"
QT_MOC_LITERAL(11, 122, 10), // "sigKickOut"
QT_MOC_LITERAL(12, 133, 6), // "reason"
QT_MOC_LITERAL(13, 140, 18), // "sigSendRoomMessage"
QT_MOC_LITERAL(14, 159, 7), // "sendSeq"
QT_MOC_LITERAL(15, 167, 9), // "messageId"
QT_MOC_LITERAL(16, 177, 18), // "sigRecvRoomMessage"
QT_MOC_LITERAL(17, 196, 19), // "QVector<RoomMsgPtr>"
QT_MOC_LITERAL(18, 216, 12), // "vRoomMsgList"
QT_MOC_LITERAL(19, 229, 16), // "sigStreamUpdated"
QT_MOC_LITERAL(20, 246, 30), // "LIVEROOM::ZegoStreamUpdateType"
QT_MOC_LITERAL(21, 277, 4), // "type"
QT_MOC_LITERAL(22, 282, 25), // "sigStreamExtraInfoUpdated"
QT_MOC_LITERAL(23, 308, 21), // "sigPublishStateUpdate"
QT_MOC_LITERAL(24, 330, 9), // "stateCode"
QT_MOC_LITERAL(25, 340, 8), // "streamId"
QT_MOC_LITERAL(26, 349, 9), // "StreamPtr"
QT_MOC_LITERAL(27, 359, 10), // "streamInfo"
QT_MOC_LITERAL(28, 370, 18), // "sigPlayStateUpdate"
QT_MOC_LITERAL(29, 389, 23), // "sigPublishQualityUpdate"
QT_MOC_LITERAL(30, 413, 7), // "quality"
QT_MOC_LITERAL(31, 421, 8), // "videoFPS"
QT_MOC_LITERAL(32, 430, 8), // "videoKBS"
QT_MOC_LITERAL(33, 439, 24), // "sigPublishQualityUpdate2"
QT_MOC_LITERAL(34, 464, 6), // "capFPS"
QT_MOC_LITERAL(35, 471, 8), // "audioKBS"
QT_MOC_LITERAL(36, 480, 3), // "rtt"
QT_MOC_LITERAL(37, 484, 11), // "pktLostRate"
QT_MOC_LITERAL(38, 496, 20), // "sigPlayQualityUpdate"
QT_MOC_LITERAL(39, 517, 11), // "sigAuxInput"
QT_MOC_LITERAL(40, 529, 14), // "unsigned char*"
QT_MOC_LITERAL(41, 544, 5), // "pData"
QT_MOC_LITERAL(42, 550, 4), // "int*"
QT_MOC_LITERAL(43, 555, 8), // "pDataLen"
QT_MOC_LITERAL(44, 564, 13), // "pDataLenValue"
QT_MOC_LITERAL(45, 578, 11), // "pSampleRate"
QT_MOC_LITERAL(46, 590, 12), // "pNumChannels"
QT_MOC_LITERAL(47, 603, 18), // "sigJoinLiveRequest"
QT_MOC_LITERAL(48, 622, 3), // "seq"
QT_MOC_LITERAL(49, 626, 10), // "fromUserId"
QT_MOC_LITERAL(50, 637, 12), // "fromUserName"
QT_MOC_LITERAL(51, 650, 19), // "sigJoinLiveResponse"
QT_MOC_LITERAL(52, 670, 6), // "result"
QT_MOC_LITERAL(53, 677, 21), // "sigAudioDeviceChanged"
QT_MOC_LITERAL(54, 699, 19), // "AV::AudioDeviceType"
QT_MOC_LITERAL(55, 719, 10), // "deviceType"
QT_MOC_LITERAL(56, 730, 11), // "strDeviceId"
QT_MOC_LITERAL(57, 742, 13), // "strDeviceName"
QT_MOC_LITERAL(58, 756, 15), // "AV::DeviceState"
QT_MOC_LITERAL(59, 772, 5), // "state"
QT_MOC_LITERAL(60, 778, 21), // "sigVideoDeviceChanged"
QT_MOC_LITERAL(61, 800, 13), // "sigUserUpdate"
QT_MOC_LITERAL(62, 814, 16), // "QVector<QString>"
QT_MOC_LITERAL(63, 831, 7), // "userIDs"
QT_MOC_LITERAL(64, 839, 9), // "userNames"
QT_MOC_LITERAL(65, 849, 12), // "QVector<int>"
QT_MOC_LITERAL(66, 862, 9), // "userFlags"
QT_MOC_LITERAL(67, 872, 9), // "userRoles"
QT_MOC_LITERAL(68, 882, 9), // "userCount"
QT_MOC_LITERAL(69, 892, 28), // "LIVEROOM::ZegoUserUpdateType"
QT_MOC_LITERAL(70, 921, 12), // "sigMixStream"
QT_MOC_LITERAL(71, 934, 6), // "hlsUrl"
QT_MOC_LITERAL(72, 941, 7), // "rtmpUrl"
QT_MOC_LITERAL(73, 949, 11), // "mixStreamID"
QT_MOC_LITERAL(74, 961, 14), // "sigMixStreamEx"
QT_MOC_LITERAL(75, 976, 25), // "sigRecvEndJoinLiveCommand"
QT_MOC_LITERAL(76, 1002, 6), // "userId"
QT_MOC_LITERAL(77, 1009, 8), // "userName"
QT_MOC_LITERAL(78, 1018, 21), // "sigSurfaceMergeResult"
QT_MOC_LITERAL(79, 1040, 16), // "surfaceMergeData"
QT_MOC_LITERAL(80, 1057, 10), // "datalength"
QT_MOC_LITERAL(81, 1068, 18), // "sigPreviewSnapshot"
QT_MOC_LITERAL(82, 1087, 6), // "pImage"
QT_MOC_LITERAL(83, 1094, 11), // "sigSnapshot"
QT_MOC_LITERAL(84, 1106, 8), // "streamID"
QT_MOC_LITERAL(85, 1115, 26), // "sigCaptureSoundLevelUpdate"
QT_MOC_LITERAL(86, 1142, 10) // "soundlevel"

    },
    "QZegoAVSignal\0sigInitSDK\0\0nError\0"
    "sigLoginRoom\0errorCode\0roomId\0"
    "QVector<StreamPtr>\0vStreamList\0"
    "sigLogoutRoom\0sigDisconnect\0sigKickOut\0"
    "reason\0sigSendRoomMessage\0sendSeq\0"
    "messageId\0sigRecvRoomMessage\0"
    "QVector<RoomMsgPtr>\0vRoomMsgList\0"
    "sigStreamUpdated\0LIVEROOM::ZegoStreamUpdateType\0"
    "type\0sigStreamExtraInfoUpdated\0"
    "sigPublishStateUpdate\0stateCode\0"
    "streamId\0StreamPtr\0streamInfo\0"
    "sigPlayStateUpdate\0sigPublishQualityUpdate\0"
    "quality\0videoFPS\0videoKBS\0"
    "sigPublishQualityUpdate2\0capFPS\0"
    "audioKBS\0rtt\0pktLostRate\0sigPlayQualityUpdate\0"
    "sigAuxInput\0unsigned char*\0pData\0int*\0"
    "pDataLen\0pDataLenValue\0pSampleRate\0"
    "pNumChannels\0sigJoinLiveRequest\0seq\0"
    "fromUserId\0fromUserName\0sigJoinLiveResponse\0"
    "result\0sigAudioDeviceChanged\0"
    "AV::AudioDeviceType\0deviceType\0"
    "strDeviceId\0strDeviceName\0AV::DeviceState\0"
    "state\0sigVideoDeviceChanged\0sigUserUpdate\0"
    "QVector<QString>\0userIDs\0userNames\0"
    "QVector<int>\0userFlags\0userRoles\0"
    "userCount\0LIVEROOM::ZegoUserUpdateType\0"
    "sigMixStream\0hlsUrl\0rtmpUrl\0mixStreamID\0"
    "sigMixStreamEx\0sigRecvEndJoinLiveCommand\0"
    "userId\0userName\0sigSurfaceMergeResult\0"
    "surfaceMergeData\0datalength\0"
    "sigPreviewSnapshot\0pImage\0sigSnapshot\0"
    "streamID\0sigCaptureSoundLevelUpdate\0"
    "soundlevel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QZegoAVSignal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      27,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  149,    2, 0x06 /* Public */,
       4,    3,  152,    2, 0x06 /* Public */,
       9,    2,  159,    2, 0x06 /* Public */,
      10,    2,  164,    2, 0x06 /* Public */,
      11,    2,  169,    2, 0x06 /* Public */,
      13,    4,  174,    2, 0x06 /* Public */,
      16,    2,  183,    2, 0x06 /* Public */,
      19,    3,  188,    2, 0x06 /* Public */,
      22,    2,  195,    2, 0x06 /* Public */,
      23,    3,  200,    2, 0x06 /* Public */,
      28,    2,  207,    2, 0x06 /* Public */,
      29,    4,  212,    2, 0x06 /* Public */,
      33,    8,  221,    2, 0x06 /* Public */,
      38,    4,  238,    2, 0x06 /* Public */,
      39,    5,  247,    2, 0x06 /* Public */,
      47,    4,  258,    2, 0x06 /* Public */,
      51,    4,  267,    2, 0x06 /* Public */,
      53,    4,  276,    2, 0x06 /* Public */,
      60,    3,  285,    2, 0x06 /* Public */,
      61,    6,  292,    2, 0x06 /* Public */,
      70,    5,  305,    2, 0x06 /* Public */,
      74,    5,  316,    2, 0x06 /* Public */,
      75,    3,  327,    2, 0x06 /* Public */,
      78,    2,  334,    2, 0x06 /* Public */,
      81,    1,  339,    2, 0x06 /* Public */,
      83,    2,  342,    2, 0x06 /* Public */,
      85,    1,  347,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   12,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::ULongLong,    5,    6,   14,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 17,    6,   18,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7, 0x80000000 | 20,    6,    8,   21,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 26,   24,   25,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   24,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double,   25,   30,   31,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,   25,   30,   34,   31,   32,   35,   36,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::Double,   25,   30,   31,   32,
    QMetaType::Void, 0x80000000 | 40, 0x80000000 | 42, QMetaType::Int, 0x80000000 | 42, 0x80000000 | 42,   41,   43,   44,   45,   46,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   48,   49,   50,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int,   52,   49,   50,   48,
    QMetaType::Void, 0x80000000 | 54, QMetaType::QString, QMetaType::QString, 0x80000000 | 58,   55,   56,   57,   59,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 58,   56,   57,   59,
    QMetaType::Void, 0x80000000 | 62, 0x80000000 | 62, 0x80000000 | 65, 0x80000000 | 65, QMetaType::UInt, 0x80000000 | 69,   63,   64,   66,   67,   68,   21,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    5,   71,   72,   73,   48,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    5,   71,   72,   73,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   76,   77,    6,
    QMetaType::Void, 0x80000000 | 40, QMetaType::Int,   79,   80,
    QMetaType::Void, QMetaType::VoidStar,   82,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::QString,   82,   84,
    QMetaType::Void, QMetaType::Float,   86,

       0        // eod
};

void QZegoAVSignal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QZegoAVSignal *_t = static_cast<QZegoAVSignal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigInitSDK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sigLoginRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[3]))); break;
        case 2: _t->sigLogoutRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->sigDisconnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->sigKickOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->sigSendRoomMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< unsigned long long(*)>(_a[4]))); break;
        case 6: _t->sigRecvRoomMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<RoomMsgPtr>(*)>(_a[2]))); break;
        case 7: _t->sigStreamUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[2])),(*reinterpret_cast< LIVEROOM::ZegoStreamUpdateType(*)>(_a[3]))); break;
        case 8: _t->sigStreamExtraInfoUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVector<StreamPtr>(*)>(_a[2]))); break;
        case 9: _t->sigPublishStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< StreamPtr(*)>(_a[3]))); break;
        case 10: _t->sigPlayStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: _t->sigPublishQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 12: _t->sigPublishQualityUpdate2((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 13: _t->sigPlayQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 14: _t->sigAuxInput((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4])),(*reinterpret_cast< int*(*)>(_a[5]))); break;
        case 15: _t->sigJoinLiveRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 16: _t->sigJoinLiveResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 17: _t->sigAudioDeviceChanged((*reinterpret_cast< AV::AudioDeviceType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< AV::DeviceState(*)>(_a[4]))); break;
        case 18: _t->sigVideoDeviceChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< AV::DeviceState(*)>(_a[3]))); break;
        case 19: _t->sigUserUpdate((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QVector<QString>(*)>(_a[2])),(*reinterpret_cast< QVector<int>(*)>(_a[3])),(*reinterpret_cast< QVector<int>(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< LIVEROOM::ZegoUserUpdateType(*)>(_a[6]))); break;
        case 20: _t->sigMixStream((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 21: _t->sigMixStreamEx((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 22: _t->sigRecvEndJoinLiveCommand((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 23: _t->sigSurfaceMergeResult((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->sigPreviewSnapshot((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 25: _t->sigSnapshot((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 26: _t->sigCaptureSoundLevelUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
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
            typedef void (QZegoAVSignal::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigInitSDK)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & , QVector<StreamPtr> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigLoginRoom)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigLogoutRoom)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigDisconnect)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigKickOut)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & , int , unsigned long long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigSendRoomMessage)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , QVector<RoomMsgPtr> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigRecvRoomMessage)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , QVector<StreamPtr> , LIVEROOM::ZegoStreamUpdateType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigStreamUpdated)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , QVector<StreamPtr> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigStreamExtraInfoUpdated)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & , StreamPtr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPublishStateUpdate)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPlayStateUpdate)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , int , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPublishQualityUpdate)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , int , double , double , double , double , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPublishQualityUpdate2)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , int , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPlayQualityUpdate)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(unsigned char * , int * , int , int * , int * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigAuxInput)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigJoinLiveRequest)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(int , const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigJoinLiveResponse)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(AV::AudioDeviceType , const QString & , const QString & , AV::DeviceState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigAudioDeviceChanged)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , const QString & , AV::DeviceState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigVideoDeviceChanged)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(QVector<QString> , QVector<QString> , QVector<int> , QVector<int> , unsigned int , LIVEROOM::ZegoUserUpdateType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigUserUpdate)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(unsigned int , const QString & , const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigMixStream)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(unsigned int , const QString & , const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigMixStreamEx)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigRecvEndJoinLiveCommand)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(unsigned char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigSurfaceMergeResult)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(void * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigPreviewSnapshot)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(void * , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigSnapshot)) {
                *result = 25;
                return;
            }
        }
        {
            typedef void (QZegoAVSignal::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVSignal::sigCaptureSoundLevelUpdate)) {
                *result = 26;
                return;
            }
        }
    }
}

const QMetaObject QZegoAVSignal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QZegoAVSignal.data,
      qt_meta_data_QZegoAVSignal,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QZegoAVSignal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QZegoAVSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QZegoAVSignal.stringdata0))
        return static_cast<void*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "LIVEROOM::IRoomCallback"))
        return static_cast< LIVEROOM::IRoomCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "LIVEROOM::ILivePublisherCallback"))
        return static_cast< LIVEROOM::ILivePublisherCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "LIVEROOM::ILivePlayerCallback"))
        return static_cast< LIVEROOM::ILivePlayerCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "LIVEROOM::IIMCallback"))
        return static_cast< LIVEROOM::IIMCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "AV::IZegoDeviceStateCallback"))
        return static_cast< AV::IZegoDeviceStateCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "SOUNDLEVEL::IZegoSoundLevelCallback"))
        return static_cast< SOUNDLEVEL::IZegoSoundLevelCallback*>(const_cast< QZegoAVSignal*>(this));
    if (!strcmp(_clname, "MIXSTREAM::IZegoMixStreamExCallback"))
        return static_cast< MIXSTREAM::IZegoMixStreamExCallback*>(const_cast< QZegoAVSignal*>(this));
    return QObject::qt_metacast(_clname);
}

int QZegoAVSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void QZegoAVSignal::sigInitSDK(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QZegoAVSignal::sigLoginRoom(int _t1, const QString & _t2, QVector<StreamPtr> _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QZegoAVSignal::sigLogoutRoom(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QZegoAVSignal::sigDisconnect(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QZegoAVSignal::sigKickOut(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QZegoAVSignal::sigSendRoomMessage(int _t1, const QString & _t2, int _t3, unsigned long long _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QZegoAVSignal::sigRecvRoomMessage(const QString & _t1, QVector<RoomMsgPtr> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QZegoAVSignal::sigStreamUpdated(const QString & _t1, QVector<StreamPtr> _t2, LIVEROOM::ZegoStreamUpdateType _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QZegoAVSignal::sigStreamExtraInfoUpdated(const QString & _t1, QVector<StreamPtr> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QZegoAVSignal::sigPublishStateUpdate(int _t1, const QString & _t2, StreamPtr _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QZegoAVSignal::sigPlayStateUpdate(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QZegoAVSignal::sigPublishQualityUpdate(const QString & _t1, int _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QZegoAVSignal::sigPublishQualityUpdate2(const QString & _t1, int _t2, double _t3, double _t4, double _t5, double _t6, int _t7, int _t8)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QZegoAVSignal::sigPlayQualityUpdate(const QString & _t1, int _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QZegoAVSignal::sigAuxInput(unsigned char * _t1, int * _t2, int _t3, int * _t4, int * _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void QZegoAVSignal::sigJoinLiveRequest(int _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void QZegoAVSignal::sigJoinLiveResponse(int _t1, const QString & _t2, const QString & _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void QZegoAVSignal::sigAudioDeviceChanged(AV::AudioDeviceType _t1, const QString & _t2, const QString & _t3, AV::DeviceState _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void QZegoAVSignal::sigVideoDeviceChanged(const QString & _t1, const QString & _t2, AV::DeviceState _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void QZegoAVSignal::sigUserUpdate(QVector<QString> _t1, QVector<QString> _t2, QVector<int> _t3, QVector<int> _t4, unsigned int _t5, LIVEROOM::ZegoUserUpdateType _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void QZegoAVSignal::sigMixStream(unsigned int _t1, const QString & _t2, const QString & _t3, const QString & _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void QZegoAVSignal::sigMixStreamEx(unsigned int _t1, const QString & _t2, const QString & _t3, const QString & _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void QZegoAVSignal::sigRecvEndJoinLiveCommand(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void QZegoAVSignal::sigSurfaceMergeResult(unsigned char * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void QZegoAVSignal::sigPreviewSnapshot(void * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void QZegoAVSignal::sigSnapshot(void * _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void QZegoAVSignal::sigCaptureSoundLevelUpdate(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}
QT_END_MOC_NAMESPACE
