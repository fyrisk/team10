/****************************************************************************
** Meta object code from reading C++ file 'gamewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../team10_nogo/gamewidget.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameWidget_t {
    uint offsetsAndSizes[90];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[16];
    char stringdata5[3];
    char stringdata6[11];
    char stringdata7[12];
    char stringdata8[5];
    char stringdata9[17];
    char stringdata10[12];
    char stringdata11[7];
    char stringdata12[21];
    char stringdata13[9];
    char stringdata14[6];
    char stringdata15[5];
    char stringdata16[10];
    char stringdata17[7];
    char stringdata18[3];
    char stringdata19[6];
    char stringdata20[6];
    char stringdata21[19];
    char stringdata22[20];
    char stringdata23[5];
    char stringdata24[13];
    char stringdata25[13];
    char stringdata26[14];
    char stringdata27[18];
    char stringdata28[8];
    char stringdata29[11];
    char stringdata30[8];
    char stringdata31[21];
    char stringdata32[22];
    char stringdata33[22];
    char stringdata34[12];
    char stringdata35[19];
    char stringdata36[6];
    char stringdata37[7];
    char stringdata38[5];
    char stringdata39[7];
    char stringdata40[6];
    char stringdata41[5];
    char stringdata42[11];
    char stringdata43[11];
    char stringdata44[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GameWidget_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_GameWidget_t qt_meta_stringdata_GameWidget = {
    {
        QT_MOC_LITERAL(0, 10),  // "GameWidget"
        QT_MOC_LITERAL(11, 11),  // "startServer"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 4),  // "port"
        QT_MOC_LITERAL(29, 15),  // "connectToServer"
        QT_MOC_LITERAL(45, 2),  // "ip"
        QT_MOC_LITERAL(48, 10),  // "handleData"
        QT_MOC_LITERAL(59, 11),  // "NetworkData"
        QT_MOC_LITERAL(71, 4),  // "data"
        QT_MOC_LITERAL(76, 16),  // "handleClientData"
        QT_MOC_LITERAL(93, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(105, 6),  // "client"
        QT_MOC_LITERAL(112, 20),  // "handleNetworkMessage"
        QT_MOC_LITERAL(133, 8),  // "setsUser"
        QT_MOC_LITERAL(142, 5),  // "color"
        QT_MOC_LITERAL(148, 4),  // "name"
        QT_MOC_LITERAL(153, 9),  // "sendReady"
        QT_MOC_LITERAL(163, 6),  // "OPCODE"
        QT_MOC_LITERAL(170, 2),  // "op"
        QT_MOC_LITERAL(173, 5),  // "data1"
        QT_MOC_LITERAL(179, 5),  // "data2"
        QT_MOC_LITERAL(185, 18),  // "handleReadyClicked"
        QT_MOC_LITERAL(204, 19),  // "handleRejectClicked"
        QT_MOC_LITERAL(224, 4),  // "Send"
        QT_MOC_LITERAL(229, 12),  // "sendToSocket"
        QT_MOC_LITERAL(242, 12),  // "sendToServer"
        QT_MOC_LITERAL(255, 13),  // "disconnectAll"
        QT_MOC_LITERAL(269, 17),  // "onSendChatMessage"
        QT_MOC_LITERAL(287, 7),  // "message"
        QT_MOC_LITERAL(295, 10),  // "initWidget"
        QT_MOC_LITERAL(306, 7),  // "newGame"
        QT_MOC_LITERAL(314, 20),  // "onSizeButton9Clicked"
        QT_MOC_LITERAL(335, 21),  // "onSizeButton11Clicked"
        QT_MOC_LITERAL(357, 21),  // "onSizeButton13Clicked"
        QT_MOC_LITERAL(379, 11),  // "restartGame"
        QT_MOC_LITERAL(391, 18),  // "onPvpButtonClicked"
        QT_MOC_LITERAL(410, 5),  // "ready"
        QT_MOC_LITERAL(416, 6),  // "reject"
        QT_MOC_LITERAL(423, 4),  // "move"
        QT_MOC_LITERAL(428, 6),  // "giveup"
        QT_MOC_LITERAL(435, 5),  // "leave"
        QT_MOC_LITERAL(441, 4),  // "chat"
        QT_MOC_LITERAL(446, 10),  // "timeoutend"
        QT_MOC_LITERAL(457, 10),  // "suicideend"
        QT_MOC_LITERAL(468, 9)   // "giveupend"
    },
    "GameWidget",
    "startServer",
    "",
    "port",
    "connectToServer",
    "ip",
    "handleData",
    "NetworkData",
    "data",
    "handleClientData",
    "QTcpSocket*",
    "client",
    "handleNetworkMessage",
    "setsUser",
    "color",
    "name",
    "sendReady",
    "OPCODE",
    "op",
    "data1",
    "data2",
    "handleReadyClicked",
    "handleRejectClicked",
    "Send",
    "sendToSocket",
    "sendToServer",
    "disconnectAll",
    "onSendChatMessage",
    "message",
    "initWidget",
    "newGame",
    "onSizeButton9Clicked",
    "onSizeButton11Clicked",
    "onSizeButton13Clicked",
    "restartGame",
    "onPvpButtonClicked",
    "ready",
    "reject",
    "move",
    "giveup",
    "leave",
    "chat",
    "timeoutend",
    "suicideend",
    "giveupend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  194,    2, 0x0a,    1 /* Public */,
       4,    2,  197,    2, 0x0a,    3 /* Public */,
       6,    1,  202,    2, 0x0a,    6 /* Public */,
       9,    2,  205,    2, 0x0a,    8 /* Public */,
      12,    2,  210,    2, 0x0a,   11 /* Public */,
      13,    2,  215,    2, 0x0a,   14 /* Public */,
      16,    3,  220,    2, 0x0a,   17 /* Public */,
      21,    1,  227,    2, 0x0a,   21 /* Public */,
      22,    0,  230,    2, 0x0a,   23 /* Public */,
      23,    1,  231,    2, 0x0a,   24 /* Public */,
      24,    1,  234,    2, 0x0a,   26 /* Public */,
      25,    1,  237,    2, 0x0a,   28 /* Public */,
      26,    0,  240,    2, 0x0a,   30 /* Public */,
      27,    1,  241,    2, 0x0a,   31 /* Public */,
      29,    0,  244,    2, 0x0a,   33 /* Public */,
      30,    0,  245,    2, 0x0a,   34 /* Public */,
      31,    0,  246,    2, 0x0a,   35 /* Public */,
      32,    0,  247,    2, 0x0a,   36 /* Public */,
      33,    0,  248,    2, 0x0a,   37 /* Public */,
      34,    0,  249,    2, 0x0a,   38 /* Public */,
      35,    0,  250,    2, 0x0a,   39 /* Public */,
      36,    1,  251,    2, 0x0a,   40 /* Public */,
      37,    1,  254,    2, 0x0a,   42 /* Public */,
      38,    1,  257,    2, 0x0a,   44 /* Public */,
      39,    1,  260,    2, 0x0a,   46 /* Public */,
      40,    1,  263,    2, 0x0a,   48 /* Public */,
      41,    1,  266,    2, 0x0a,   50 /* Public */,
      42,    1,  269,    2, 0x0a,   52 /* Public */,
      43,    1,  272,    2, 0x0a,   54 /* Public */,
      44,    1,  275,    2, 0x0a,   56 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 7,   11,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 7,   11,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString, QMetaType::QString,   18,   19,   20,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void GameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startServer((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->connectToServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->handleData((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 3: _t->handleClientData((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[2]))); break;
        case 4: _t->handleNetworkMessage((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[2]))); break;
        case 5: _t->setsUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->sendReady((*reinterpret_cast< std::add_pointer_t<OPCODE>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 7: _t->handleReadyClicked((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 8: _t->handleRejectClicked(); break;
        case 9: _t->Send((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 10: _t->sendToSocket((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 11: _t->sendToServer((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 12: _t->disconnectAll(); break;
        case 13: _t->onSendChatMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->initWidget(); break;
        case 15: _t->newGame(); break;
        case 16: _t->onSizeButton9Clicked(); break;
        case 17: _t->onSizeButton11Clicked(); break;
        case 18: _t->onSizeButton13Clicked(); break;
        case 19: _t->restartGame(); break;
        case 20: _t->onPvpButtonClicked(); break;
        case 21: _t->ready((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 22: _t->reject((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 23: _t->move((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 24: _t->giveup((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 25: _t->leave((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 26: _t->chat((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 27: _t->timeoutend((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 28: _t->suicideend((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 29: _t->giveupend((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

const QMetaObject GameWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GameWidget.offsetsAndSizes,
    qt_meta_data_GameWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GameWidget_t
, QtPrivate::TypeAndForceComplete<GameWidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<OPCODE, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const NetworkData &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>


>,
    nullptr
} };


const QMetaObject *GameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
