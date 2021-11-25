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
    const uint offsetsAndSize[36];
    char stringdata0[347];
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
QT_MOC_LITERAL(188, 22), // "on_high_Button_clicked"
QT_MOC_LITERAL(211, 20), // "on_up_button_clicked"
QT_MOC_LITERAL(232, 21), // "on_low_button_clicked"
QT_MOC_LITERAL(254, 22), // "on_left_button_clicked"
QT_MOC_LITERAL(277, 22), // "on_stop_button_clicked"
QT_MOC_LITERAL(300, 23), // "on_right_button_clicked"
QT_MOC_LITERAL(324, 22) // "on_down_button_clicked"

    },
    "MainWindow\0load_image\0\0init_image\0"
    "display_image\0gerer_donnees\0afficher_erreur\0"
    "QAbstractSocket::SocketError\0"
    "on_connect_forced_clicked\0"
    "on_connect_button_clicked\0"
    "on_disconnect_button_clicked\0"
    "on_high_Button_clicked\0on_up_button_clicked\0"
    "on_low_button_clicked\0on_left_button_clicked\0"
    "on_stop_button_clicked\0on_right_button_clicked\0"
    "on_down_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    0 /* Private */,
       3,    0,  105,    2, 0x08,    1 /* Private */,
       4,    0,  106,    2, 0x08,    2 /* Private */,
       5,    0,  107,    2, 0x08,    3 /* Private */,
       6,    1,  108,    2, 0x08,    4 /* Private */,
       8,    0,  111,    2, 0x08,    6 /* Private */,
       9,    0,  112,    2, 0x08,    7 /* Private */,
      10,    0,  113,    2, 0x08,    8 /* Private */,
      11,    0,  114,    2, 0x08,    9 /* Private */,
      12,    0,  115,    2, 0x08,   10 /* Private */,
      13,    0,  116,    2, 0x08,   11 /* Private */,
      14,    0,  117,    2, 0x08,   12 /* Private */,
      15,    0,  118,    2, 0x08,   13 /* Private */,
      16,    0,  119,    2, 0x08,   14 /* Private */,
      17,    0,  120,    2, 0x08,   15 /* Private */,

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
        case 8: _t->on_high_Button_clicked(); break;
        case 9: _t->on_up_button_clicked(); break;
        case 10: _t->on_low_button_clicked(); break;
        case 11: _t->on_left_button_clicked(); break;
        case 12: _t->on_stop_button_clicked(); break;
        case 13: _t->on_right_button_clicked(); break;
        case 14: _t->on_down_button_clicked(); break;
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

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
