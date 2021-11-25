/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_background;
    QPushButton *up_button;
    QPushButton *pushButton_2;
    QPushButton *down_button;
    QPushButton *left_button;
    QPushButton *right_button;
    QTextEdit *input_ip;
    QTextEdit *input_port;
    QPushButton *connect_button;
    QPushButton *disconnect_button;
    QLabel *label_map;
    QLabel *label_banderole;
    QLabel *txt_snirium;
    QLabel *txt_dst_obstacle;
    QPushButton *high_Button;
    QPushButton *pushButton;
    QLabel *img_angle;
    QLabel *img_posit;
    QLabel *label_co;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        QFont font;
        font.setPointSize(16);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_background = new QLabel(centralwidget);
        label_background->setObjectName(QString::fromUtf8("label_background"));
        label_background->setGeometry(QRect(0, 0, 1920, 1080));
        up_button = new QPushButton(centralwidget);
        up_button->setObjectName(QString::fromUtf8("up_button"));
        up_button->setGeometry(QRect(1200, 275, 150, 150));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Bahnschrift SemiBold Condensed")});
        font1.setPointSize(11);
        up_button->setFont(font1);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1200, 450, 150, 150));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Bahnschrift SemiBold SemiConden")});
        font2.setPointSize(14);
        pushButton_2->setFont(font2);
        down_button = new QPushButton(centralwidget);
        down_button->setObjectName(QString::fromUtf8("down_button"));
        down_button->setGeometry(QRect(1200, 625, 150, 150));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Bahnschrift SemiBold SemiConden")});
        font3.setPointSize(11);
        down_button->setFont(font3);
        left_button = new QPushButton(centralwidget);
        left_button->setObjectName(QString::fromUtf8("left_button"));
        left_button->setGeometry(QRect(1025, 450, 150, 150));
        left_button->setFont(font3);
        right_button = new QPushButton(centralwidget);
        right_button->setObjectName(QString::fromUtf8("right_button"));
        right_button->setGeometry(QRect(1375, 450, 150, 150));
        right_button->setFont(font3);
        input_ip = new QTextEdit(centralwidget);
        input_ip->setObjectName(QString::fromUtf8("input_ip"));
        input_ip->setGeometry(QRect(1025, 25, 350, 30));
        input_port = new QTextEdit(centralwidget);
        input_port->setObjectName(QString::fromUtf8("input_port"));
        input_port->setGeometry(QRect(1025, 75, 350, 30));
        connect_button = new QPushButton(centralwidget);
        connect_button->setObjectName(QString::fromUtf8("connect_button"));
        connect_button->setGeometry(QRect(1375, 25, 150, 30));
        QFont font4;
        font4.setPointSize(8);
        connect_button->setFont(font4);
        disconnect_button = new QPushButton(centralwidget);
        disconnect_button->setObjectName(QString::fromUtf8("disconnect_button"));
        disconnect_button->setGeometry(QRect(1375, 75, 150, 30));
        disconnect_button->setFont(font4);
        label_map = new QLabel(centralwidget);
        label_map->setObjectName(QString::fromUtf8("label_map"));
        label_map->setGeometry(QRect(50, 150, 800, 625));
        label_map->setAutoFillBackground(true);
        label_banderole = new QLabel(centralwidget);
        label_banderole->setObjectName(QString::fromUtf8("label_banderole"));
        label_banderole->setGeometry(QRect(50, 25, 800, 100));
        txt_snirium = new QLabel(centralwidget);
        txt_snirium->setObjectName(QString::fromUtf8("txt_snirium"));
        txt_snirium->setGeometry(QRect(125, 65, 200, 50));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Power Green")});
        font5.setPointSize(16);
        txt_snirium->setFont(font5);
        txt_dst_obstacle = new QLabel(centralwidget);
        txt_dst_obstacle->setObjectName(QString::fromUtf8("txt_dst_obstacle"));
        txt_dst_obstacle->setGeometry(QRect(600, 65, 200, 50));
        txt_dst_obstacle->setFont(font5);
        high_Button = new QPushButton(centralwidget);
        high_Button->setObjectName(QString::fromUtf8("high_Button"));
        high_Button->setGeometry(QRect(1025, 350, 150, 75));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Bahnschrift SemiBold Condensed")});
        font6.setPointSize(11);
        font6.setBold(true);
        high_Button->setFont(font6);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1375, 350, 150, 75));
        pushButton->setFont(font6);
        img_angle = new QLabel(centralwidget);
        img_angle->setObjectName(QString::fromUtf8("img_angle"));
        img_angle->setGeometry(QRect(1025, 625, 150, 150));
        img_posit = new QLabel(centralwidget);
        img_posit->setObjectName(QString::fromUtf8("img_posit"));
        img_posit->setGeometry(QRect(1375, 625, 150, 150));
        label_co = new QLabel(centralwidget);
        label_co->setObjectName(QString::fromUtf8("label_co"));
        label_co->setGeometry(QRect(1025, 140, 500, 100));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_background->setText(QString());
        up_button->setText(QCoreApplication::translate("MainWindow", "Avancer (Forward)", nullptr));
#if QT_CONFIG(shortcut)
        up_button->setShortcut(QCoreApplication::translate("MainWindow", "Z", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Arr\303\252ter (Stop)", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_2->setShortcut(QCoreApplication::translate("MainWindow", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
        down_button->setText(QCoreApplication::translate("MainWindow", "Reculer (Backward)", nullptr));
#if QT_CONFIG(shortcut)
        down_button->setShortcut(QCoreApplication::translate("MainWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        left_button->setText(QCoreApplication::translate("MainWindow", "Gauche (Left)", nullptr));
#if QT_CONFIG(shortcut)
        left_button->setShortcut(QCoreApplication::translate("MainWindow", "Q", nullptr));
#endif // QT_CONFIG(shortcut)
        right_button->setText(QCoreApplication::translate("MainWindow", "Droite (Right)", nullptr));
#if QT_CONFIG(shortcut)
        right_button->setShortcut(QCoreApplication::translate("MainWindow", "D", nullptr));
#endif // QT_CONFIG(shortcut)
        input_ip->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7.8pt;\">Mettez ici l'adresse IP / Put here the IP address</span></p></body></html>", nullptr));
        input_port->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7.8pt;\">Mettez ici le port / Put here the port</span></p></body></html>", nullptr));
        connect_button->setText(QCoreApplication::translate("MainWindow", "Connecter (Connect)", nullptr));
        disconnect_button->setText(QCoreApplication::translate("MainWindow", "D\303\251connecter (Disconnect)", nullptr));
        label_map->setText(QString());
        label_banderole->setText(QString());
        txt_snirium->setText(QCoreApplication::translate("MainWindow", "XXXXXXXXXXXXX", nullptr));
        txt_dst_obstacle->setText(QCoreApplication::translate("MainWindow", "XXXXXXXXXXXXX", nullptr));
        high_Button->setText(QCoreApplication::translate("MainWindow", "Lever (Up)", nullptr));
#if QT_CONFIG(shortcut)
        high_Button->setShortcut(QCoreApplication::translate("MainWindow", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton->setText(QCoreApplication::translate("MainWindow", "Dessendre (Down)", nullptr));
#if QT_CONFIG(shortcut)
        pushButton->setShortcut(QCoreApplication::translate("MainWindow", "Down", nullptr));
#endif // QT_CONFIG(shortcut)
        img_angle->setText(QString());
        img_posit->setText(QString());
        label_co->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
