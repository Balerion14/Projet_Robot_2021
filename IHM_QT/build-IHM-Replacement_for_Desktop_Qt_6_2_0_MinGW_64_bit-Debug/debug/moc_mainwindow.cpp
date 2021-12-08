/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../IHM/mainwindow.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[64];
    char stringdata0[542];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 10), // "load_image"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 10), // "init_image"
QT_MOC_LITERAL(34, 13), // "display_image"
QT_MOC_LITERAL(48, 13), // "gerer_donnees"
QT_MOC_LITERAL(62, 15), // "afficher_erreur"
QT_MOC_LITERAL(78, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(107, 25), // "on_connect_forced_clicked"
QT_MOC_LITERAL(133, 25), // "on_connect_button_clicked"
QT_MOC_LITERAL(159, 28), // "on_disconnect_button_clicked"
QT_MOC_LITERAL(188, 23), // "on_high_Button_released"
QT_MOC_LITERAL(212, 21), // "on_up_button_released"
QT_MOC_LITERAL(234, 22), // "on_low_button_released"
QT_MOC_LITERAL(257, 23), // "on_left_button_released"
QT_MOC_LITERAL(281, 24), // "on_right_button_released"
QT_MOC_LITERAL(306, 23), // "on_down_button_released"
QT_MOC_LITERAL(330, 15), // "demander_trames"
QT_MOC_LITERAL(346, 20), // "on_up_button_pressed"
QT_MOC_LITERAL(367, 22), // "on_high_Button_pressed"
QT_MOC_LITERAL(390, 22), // "on_left_button_pressed"
QT_MOC_LITERAL(413, 22), // "on_down_button_pressed"
QT_MOC_LITERAL(436, 23), // "on_right_button_pressed"
QT_MOC_LITERAL(460, 21), // "on_low_button_pressed"
QT_MOC_LITERAL(482, 15), // "on_STOP_pressed"
QT_MOC_LITERAL(498, 11), // "remplir_bdd"
QT_MOC_LITERAL(510, 1), // "x"
QT_MOC_LITERAL(512, 1), // "y"
QT_MOC_LITERAL(514, 5), // "angle"
QT_MOC_LITERAL(520, 7), // "snirium"
QT_MOC_LITERAL(528, 8), // "distance"
QT_MOC_LITERAL(537, 4) // "date"

    },
    "MainWindow\0load_image\0\0init_image\0"
    "display_image\0gerer_donnees\0afficher_erreur\0"
    "QAbstractSocket::SocketError\0"
    "on_connect_forced_clicked\0"
    "on_connect_button_clicked\0"
    "on_disconnect_button_clicked\0"
    "on_high_Button_released\0on_up_button_released\0"
    "on_low_button_released\0on_left_button_released\0"
    "on_right_button_released\0"
    "on_down_button_released\0demander_trames\0"
    "on_up_button_pressed\0on_high_Button_pressed\0"
    "on_left_button_pressed\0on_down_button_pressed\0"
    "on_right_button_pressed\0on_low_button_pressed\0"
    "on_STOP_pressed\0remplir_bdd\0x\0y\0angle\0"
    "snirium\0distance\0date"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x08,    0 /* Private */,
       3,    0,  153,    2, 0x08,    1 /* Private */,
       4,    0,  154,    2, 0x08,    2 /* Private */,
       5,    0,  155,    2, 0x08,    3 /* Private */,
       6,    1,  156,    2, 0x08,    4 /* Private */,
       8,    0,  159,    2, 0x08,    6 /* Private */,
       9,    0,  160,    2, 0x08,    7 /* Private */,
      10,    0,  161,    2, 0x08,    8 /* Private */,
      11,    0,  162,    2, 0x08,    9 /* Private */,
      12,    0,  163,    2, 0x08,   10 /* Private */,
      13,    0,  164,    2, 0x08,   11 /* Private */,
      14,    0,  165,    2, 0x08,   12 /* Private */,
      15,    0,  166,    2, 0x08,   13 /* Private */,
      16,    0,  167,    2, 0x08,   14 /* Private */,
      17,    0,  168,    2, 0x08,   15 /* Private */,
      18,    0,  169,    2, 0x08,   16 /* Private */,
      19,    0,  170,    2, 0x08,   17 /* Private */,
      20,    0,  171,    2, 0x08,   18 /* Private */,
      21,    0,  172,    2, 0x08,   19 /* Private */,
      22,    0,  173,    2, 0x08,   20 /* Private */,
      23,    0,  174,    2, 0x08,   21 /* Private */,
      24,    0,  175,    2, 0x08,   22 /* Private */,
      25,    6,  176,    2, 0x08,   23 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   26,   27,   28,   29,   30,   31,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->load_image(); break;
        case 1: _t->init_image(); break;
        case 2: _t->display_image(); break;
        case 3: _t->gerer_donnees(); break;
        case 4: _t->afficher_erreur((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->on_connect_forced_clicked(); break;
        case 6: _t->on_connect_button_clicked(); break;
        case 7: _t->on_disconnect_button_clicked(); break;
        case 8: _t->on_high_Button_released(); break;
        case 9: _t->on_up_button_released(); break;
        case 10: _t->on_low_button_released(); break;
        case 11: _t->on_left_button_released(); break;
        case 12: _t->on_right_button_released(); break;
        case 13: _t->on_down_button_released(); break;
        case 14: _t->demander_trames(); break;
        case 15: _t->on_up_button_pressed(); break;
        case 16: _t->on_high_Button_pressed(); break;
        case 17: _t->on_left_button_pressed(); break;
        case 18: _t->on_down_button_pressed(); break;
        case 19: _t->on_right_button_pressed(); break;
        case 20: _t->on_low_button_pressed(); break;
        case 21: _t->on_STOP_pressed(); break;
        case 22: _t->remplir_bdd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
