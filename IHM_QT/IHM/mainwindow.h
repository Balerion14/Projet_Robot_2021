#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <iostream>
#include <QTimer>
#include "data_received.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void load_image();

    void init_image();

    void display_image();

    void gerer_donnees();

    void afficher_erreur(QAbstractSocket::SocketError);

    void on_connect_forced_clicked();

    void on_connect_button_clicked();

    void on_disconnect_button_clicked();


    void on_high_Button_clicked();

    void on_up_button_clicked();

    void on_low_button_clicked();

    void on_left_button_clicked();

    void on_stop_button_clicked();

    void on_right_button_clicked();

    void on_down_button_clicked();

private:
    // Object instanciation part
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTimer *pTimer;
    data_received *donnee_recue;

    // Picture part
    QImage *pBackground;
    QImage *pBanderole;
    QImage *pAngle;
    QImage *pPosition;
    QImage *pConnected;
    QImage *pDisconnected;
    QPixmap image;

    bool verif1 = false;
};
#endif // MAINWINDOW_H
