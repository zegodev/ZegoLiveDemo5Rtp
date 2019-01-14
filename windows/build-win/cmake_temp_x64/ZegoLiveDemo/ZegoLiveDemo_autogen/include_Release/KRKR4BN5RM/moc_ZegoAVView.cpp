/****************************************************************************
** Meta object code from reading C++ file 'ZegoAVView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/UI/ZegoAVView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoAVView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QZegoAVView_t {
    QByteArrayData data[15];
    char stringdata0[440];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QZegoAVView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QZegoAVView_t qt_meta_stringdata_QZegoAVView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QZegoAVView"
QT_MOC_LITERAL(1, 12, 32), // "sigSnapShotPreviewOnSingleAnchor"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 39), // "sigSnapShotOnSingleAudienceWi..."
QT_MOC_LITERAL(4, 86, 8), // "streamID"
QT_MOC_LITERAL(5, 95, 30), // "sigSnapShotPreviewOnMoreAnchor"
QT_MOC_LITERAL(6, 126, 35), // "sigSnapShotOnMoreAnchorWithSt..."
QT_MOC_LITERAL(7, 162, 32), // "sigSnapShotPreviewOnMoreAudience"
QT_MOC_LITERAL(8, 195, 37), // "sigSnapShotOnMoreAudienceWith..."
QT_MOC_LITERAL(9, 233, 35), // "sigSnapShotPreviewOnMixStream..."
QT_MOC_LITERAL(10, 269, 40), // "sigSnapShotOnMixStreamAnchorW..."
QT_MOC_LITERAL(11, 310, 37), // "sigSnapShotPreviewOnMixStream..."
QT_MOC_LITERAL(12, 348, 42), // "sigSnapShotOnMixStreamAudienc..."
QT_MOC_LITERAL(13, 391, 23), // "OnMenuSnapShotTriggered"
QT_MOC_LITERAL(14, 415, 24) // "OnMenukickForceTriggered"

    },
    "QZegoAVView\0sigSnapShotPreviewOnSingleAnchor\0"
    "\0sigSnapShotOnSingleAudienceWithStreamID\0"
    "streamID\0sigSnapShotPreviewOnMoreAnchor\0"
    "sigSnapShotOnMoreAnchorWithStreamID\0"
    "sigSnapShotPreviewOnMoreAudience\0"
    "sigSnapShotOnMoreAudienceWithStreamID\0"
    "sigSnapShotPreviewOnMixStreamAnchor\0"
    "sigSnapShotOnMixStreamAnchorWithStreamID\0"
    "sigSnapShotPreviewOnMixStreamAudience\0"
    "sigSnapShotOnMixStreamAudienceWithStreamID\0"
    "OnMenuSnapShotTriggered\0"
    "OnMenukickForceTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QZegoAVView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    0,   78,    2, 0x06 /* Public */,
       6,    1,   79,    2, 0x06 /* Public */,
       7,    0,   82,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,
       9,    0,   86,    2, 0x06 /* Public */,
      10,    1,   87,    2, 0x06 /* Public */,
      11,    0,   90,    2, 0x06 /* Public */,
      12,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QZegoAVView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QZegoAVView *_t = static_cast<QZegoAVView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSnapShotPreviewOnSingleAnchor(); break;
        case 1: _t->sigSnapShotOnSingleAudienceWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sigSnapShotPreviewOnMoreAnchor(); break;
        case 3: _t->sigSnapShotOnMoreAnchorWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sigSnapShotPreviewOnMoreAudience(); break;
        case 5: _t->sigSnapShotOnMoreAudienceWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->sigSnapShotPreviewOnMixStreamAnchor(); break;
        case 7: _t->sigSnapShotOnMixStreamAnchorWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->sigSnapShotPreviewOnMixStreamAudience(); break;
        case 9: _t->sigSnapShotOnMixStreamAudienceWithStreamID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->OnMenuSnapShotTriggered(); break;
        case 11: _t->OnMenukickForceTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QZegoAVView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotPreviewOnSingleAnchor)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotOnSingleAudienceWithStreamID)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotPreviewOnMoreAnchor)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotOnMoreAnchorWithStreamID)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotPreviewOnMoreAudience)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotOnMoreAudienceWithStreamID)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotPreviewOnMixStreamAnchor)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotOnMixStreamAnchorWithStreamID)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotPreviewOnMixStreamAudience)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (QZegoAVView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QZegoAVView::sigSnapShotOnMixStreamAudienceWithStreamID)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject QZegoAVView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_QZegoAVView.data,
      qt_meta_data_QZegoAVView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QZegoAVView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QZegoAVView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QZegoAVView.stringdata0))
        return static_cast<void*>(const_cast< QZegoAVView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int QZegoAVView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void QZegoAVView::sigSnapShotPreviewOnSingleAnchor()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QZegoAVView::sigSnapShotOnSingleAudienceWithStreamID(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QZegoAVView::sigSnapShotPreviewOnMoreAnchor()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void QZegoAVView::sigSnapShotOnMoreAnchorWithStreamID(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QZegoAVView::sigSnapShotPreviewOnMoreAudience()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void QZegoAVView::sigSnapShotOnMoreAudienceWithStreamID(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QZegoAVView::sigSnapShotPreviewOnMixStreamAnchor()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void QZegoAVView::sigSnapShotOnMixStreamAnchorWithStreamID(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QZegoAVView::sigSnapShotPreviewOnMixStreamAudience()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void QZegoAVView::sigSnapShotOnMixStreamAudienceWithStreamID(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
struct qt_meta_stringdata_QZegoAVScene_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QZegoAVScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QZegoAVScene_t qt_meta_stringdata_QZegoAVScene = {
    {
QT_MOC_LITERAL(0, 0, 12) // "QZegoAVScene"

    },
    "QZegoAVScene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QZegoAVScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QZegoAVScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QZegoAVScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_QZegoAVScene.data,
      qt_meta_data_QZegoAVScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QZegoAVScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QZegoAVScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QZegoAVScene.stringdata0))
        return static_cast<void*>(const_cast< QZegoAVScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int QZegoAVScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
