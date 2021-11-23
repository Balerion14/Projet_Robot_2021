/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
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
    const uint offsetsAndSize[62];
    char stringdata0[444];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 26), // "on_connexionButton_clicked"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 28), // "on_deconnexionButton_clicked"
QT_MOC_LITERAL(68, 22), // "on_envoiButton_clicked"
QT_MOC_LITERAL(91, 13), // "gerer_donnees"
QT_MOC_LITERAL(105, 10), // "draw_image"
QT_MOC_LITERAL(116, 15), // "afficher_erreur"
QT_MOC_LITERAL(132, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(161, 10), // "load_image"
QT_MOC_LITERAL(172, 23), // "create_dynamical_object"
QT_MOC_LITERAL(196, 14), // "barre_progress"
QT_MOC_LITERAL(211, 6), // "valeur"
QT_MOC_LITERAL(218, 19), // "draw_graph_altitude"
QT_MOC_LITERAL(238, 8), // "altitude"
QT_MOC_LITERAL(247, 18), // "draw_graph_feq_car"
QT_MOC_LITERAL(266, 19), // "frequence_cardiaque"
QT_MOC_LITERAL(286, 11), // "pb_satelite"
QT_MOC_LITERAL(298, 11), // "nb_satelite"
QT_MOC_LITERAL(310, 11), // "pb_checksum"
QT_MOC_LITERAL(322, 14), // "verif_ckecksum"
QT_MOC_LITERAL(337, 19), // "on_checkBox_toggled"
QT_MOC_LITERAL(357, 7), // "checked"
QT_MOC_LITERAL(365, 11), // "remplir_bdd"
QT_MOC_LITERAL(377, 9), // "longitude"
QT_MOC_LITERAL(387, 10), // "timestamps"
QT_MOC_LITERAL(398, 8), // "distance"
QT_MOC_LITERAL(407, 5), // "speed"
QT_MOC_LITERAL(413, 7), // "calorie"
QT_MOC_LITERAL(421, 8), // "latitude"
QT_MOC_LITERAL(430, 13) // "frequence_car"

    },
    "MainWindow\0on_connexionButton_clicked\0"
    "\0on_deconnexionButton_clicked\0"
    "on_envoiButton_clicked\0gerer_donnees\0"
    "draw_image\0afficher_erreur\0"
    "QAbstractSocket::SocketError\0load_image\0"
    "create_dynamical_object\0barre_progress\0"
    "valeur\0draw_graph_altitude\0altitude\0"
    "draw_graph_feq_car\0frequence_cardiaque\0"
    "pb_satelite\0nb_satelite\0pb_checksum\0"
    "verif_ckecksum\0on_checkBox_toggled\0"
    "checked\0remplir_bdd\0longitude\0timestamps\0"
    "distance\0speed\0calorie\0latitude\0"
    "frequence_car"
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
       6,    0,  108,    2, 0x08,    4 /* Private */,
       7,    1,  109,    2, 0x08,    5 /* Private */,
       9,    0,  112,    2, 0x08,    7 /* Private */,
      10,    0,  113,    2, 0x08,    8 /* Private */,
      11,    1,  114,    2, 0x08,    9 /* Private */,
      13,    1,  117,    2, 0x08,   11 /* Private */,
      15,    1,  120,    2, 0x08,   13 /* Private */,
      17,    1,  123,    2, 0x08,   15 /* Private */,
      19,    1,  126,    2, 0x08,   17 /* Private */,
      21,    1,  129,    2, 0x08,   19 /* Private */,
      23,    8,  132,    2, 0x08,   21 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   24,   25,   26,   27,   28,   29,   30,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_connexionButton_clicked(); break;
        case 1: _t->on_deconnexionButton_clicked(); break;
        case 2: _t->on_envoiButton_clicked(); break;
        case 3: _t->gerer_donnees(); break;
        case 4: _t->draw_image(); break;
        case 5: _t->afficher_erreur((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->load_image(); break;
        case 7: _t->create_dynamical_object(); break;
        case 8: _t->barre_progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->draw_graph_altitude((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->draw_graph_feq_car((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->pb_satelite((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->pb_checksum((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->remplir_bdd((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
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

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>


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
