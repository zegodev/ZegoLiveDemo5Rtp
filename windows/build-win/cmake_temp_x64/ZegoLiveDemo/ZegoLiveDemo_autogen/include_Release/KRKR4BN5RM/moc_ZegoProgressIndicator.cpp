/****************************************************************************
** Meta object code from reading C++ file 'ZegoProgressIndicator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoLiveDemo/UI/ZegoProgressIndicator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoProgressIndicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoProgressIndicator_t {
    QByteArrayData data[14];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoProgressIndicator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoProgressIndicator_t qt_meta_stringdata_ZegoProgressIndicator = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ZegoProgressIndicator"
QT_MOC_LITERAL(1, 22, 8), // "Finished"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "startAnimation"
QT_MOC_LITERAL(4, 47, 13), // "stopAnimation"
QT_MOC_LITERAL(5, 61, 17), // "setAnimationDelay"
QT_MOC_LITERAL(6, 79, 5), // "delay"
QT_MOC_LITERAL(7, 85, 23), // "setDisplayedWhenStopped"
QT_MOC_LITERAL(8, 109, 5), // "state"
QT_MOC_LITERAL(9, 115, 8), // "setColor"
QT_MOC_LITERAL(10, 124, 5), // "color"
QT_MOC_LITERAL(11, 130, 10), // "onProgress"
QT_MOC_LITERAL(12, 141, 9), // "_progress"
QT_MOC_LITERAL(13, 151, 20) // "displayedWhenStopped"

    },
    "ZegoProgressIndicator\0Finished\0\0"
    "startAnimation\0stopAnimation\0"
    "setAnimationDelay\0delay\0setDisplayedWhenStopped\0"
    "state\0setColor\0color\0onProgress\0"
    "_progress\0displayedWhenStopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoProgressIndicator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       3,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       9,    1,   58,    2, 0x0a /* Public */,
      11,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QColor,   10,
    QMetaType::Void, QMetaType::Short,   12,

 // properties: name, type, flags
       6, QMetaType::Int, 0x00095003,
      13, QMetaType::Bool, 0x00095103,
      10, QMetaType::QColor, 0x00095103,

       0        // eod
};

void ZegoProgressIndicator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoProgressIndicator *_t = static_cast<ZegoProgressIndicator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Finished(); break;
        case 1: _t->startAnimation(); break;
        case 2: _t->stopAnimation(); break;
        case 3: _t->setAnimationDelay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setDisplayedWhenStopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 6: _t->onProgress((*reinterpret_cast< short(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoProgressIndicator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoProgressIndicator::Finished)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ZegoProgressIndicator *_t = static_cast<ZegoProgressIndicator *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->animationDelay(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isDisplayedWhenStopped(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ZegoProgressIndicator *_t = static_cast<ZegoProgressIndicator *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAnimationDelay(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setDisplayedWhenStopped(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ZegoProgressIndicator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZegoProgressIndicator.data,
      qt_meta_data_ZegoProgressIndicator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoProgressIndicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoProgressIndicator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoProgressIndicator.stringdata0))
        return static_cast<void*>(const_cast< ZegoProgressIndicator*>(this));
    return QWidget::qt_metacast(_clname);
}

int ZegoProgressIndicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ZegoProgressIndicator::Finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
