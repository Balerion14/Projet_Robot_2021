#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <iostream>
#include <QTimer>
#include "data_received.h"
#include <QDebug>
#include <bdd.h>

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

    void on_high_Button_released();

    void on_up_button_released();

    void on_low_button_released();

    void on_left_button_released();

    void on_right_button_released();

    void on_down_button_released();

    void demander_trames();

    void on_up_button_pressed();

    void on_high_Button_pressed();

    void on_left_button_pressed();

    void on_down_button_pressed();

    void on_right_button_pressed();

    void on_low_button_pressed();

    void on_STOP_pressed();

    void remplir_bdd(QString x, QString y, QString angle, QString snirium, QString distance, QString date);

    void on_bdd_bouton_clicked();

private:
    // Object instanciation part
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTimer *pTimer;
    data_received *donnee_recue;

    // Picture part
    QImage *pBackground;
    QImage *pBanderole;
    QImage *pAngleD;
    QImage *pAngleG;
    QImage *pConnected;
    QImage *pDisconnected;
    QImage *bdd_image;
    QPixmap image;
    BDD *bdd;

    bool verif = true;
};
#endif // MAINWINDOW_H
