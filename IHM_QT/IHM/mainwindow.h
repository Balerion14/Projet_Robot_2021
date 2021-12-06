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

    void on_high_Button_clicked();

    void on_up_button_clicked();

    void on_low_button_clicked();

    void on_left_button_clicked();

    void on_right_button_clicked();

    void on_down_button_clicked();

    void on_high_Button_released();

    void on_up_button_released();

    void on_low_button_released();

    void on_left_button_released();

    void on_right_button_released();

    void on_down_button_released();

    void demander_trames();

    void on_STOP_clicked();

    //
    //A voir pourquoi sa ne marche pas
    //void remplirInfoBDD(QString nom, QString  description);

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
    QPixmap image;
    BDD *bdd;

    bool verif = true;

    void gerer_deplacement_robot();

    //A voir pourquoi sa ne marche pas
    void remplir_bdd(QString x, QString y, QString angle, QString snirium, QString distance, QString date);
};
#endif // MAINWINDOW_H
