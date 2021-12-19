#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Importation bibliotèque
#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <iostream>
#include <QTimer>
#include "data_received.h"
#include <QDebug>
#include <bdd.h>
#include <robot_lego.h>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Classe Mainwindows
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /*!
     *  Methode de la classe mainWindos pour le chargement de son images
     *  @param Aucun parametre
     *  @param return rien
     */
    void load_image();

    /*!
     *  Methode de la classe mainWindos pour initialiser les images
     *  @param Aucun parametre
     *  @param return rien
     */
    void init_image();

    /*!
     *  Methode de la classe mainWindos pour l'afficahge du robot et le chargement de son images
     *  @param Aucun parametre
     *  @param return rien
     */
    void affichage_robot();

    /*!
     *  Methode de la classe mainWindows pour afficher le robot sur la carte en rotation
     *  @param int angle
     *  @param return rien
     */
    void affichage_robot_rotation(int angle);

    /*!
     *  Methode de la classe mainWindows pour afficher le robot sur la carte en bougeant
     *  @param int coord_x
     *  @param int coord_y
     *  @param return rien
     */
    void affichage_robot_move(int coord_x, int coord_y);

    /*!
     *  Methode de la classe mainWindows pour afficher image sur interface
     *  @param aucun
     *  @param rien
     */
    void display_image();

    /*!
     *  Methode de la classe mainWindows pour gerer les donnees recues
     *  @param aucun
     *  @param rien
     */
    void gerer_donnees();

    /*!
     *  Methode de la classe mainWindows pour gerer les erreurs
     *  @param socket errror
     *  @param rien
     */
    void afficher_erreur(QAbstractSocket::SocketError);

    /*!
     *  Methode de la classe mainWindows pour gerer bouton forcer connexion
     *  @param aucun
     *  @param rien
     */
    void on_connect_forced_clicked();

    /*!
     *  Methode de la classe mainWindows pour gerer bouton  connexion
     *  @param aucun
     *  @param rien
     */
    void on_connect_button_clicked();

    /*!
     *  Methode de la classe mainWindows pour gerer bouton forcer deconnexion
     *  @param aucun
     *  @param rien
     */
    void on_disconnect_button_clicked();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_high_Button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_up_button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_low_button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_left_button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_right_button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_down_button_released();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void demander_trames();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_up_button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_high_Button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_left_button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_down_button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_right_button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_low_button_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_STOP_pressed();

    /*!
     *  Methode de la classe mainWindows pour gerer l'envoient des donnees
     *  @param x
     *  @param y
     *  @param angle
     *  @param taux snirium
     *  @param distance
     *  @param date
     *  @param rien
     */
    void remplir_bdd(QString x, QString y, QString angle, QString snirium, QString distance, QString date);

    /*!
     *  Methode de la classe mainWindows pour gerer les commandes du robot
     *  @param aucun
     *  @param rien
     */
    void on_bdd_bouton_clicked();

private:

    //Attributs de la classe
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTimer *pTimer;
    data_received *donnee_recue;

    QImage *pBackground;
    QImage *pBanderole;
    QImage *pAngleD;
    QImage *pAngleG;
    QImage *pConnected;
    QImage *pDisconnected;
    QImage *bdd_image;
    QImage *map;
    QImage bastion;
    QImage bastion_rezise;
    QImage rotate_robot;
    QPixmap image;
    BDD *bdd;
    robot_lego *Bastion;

    bool verif = true;
};
#endif // MAINWINDOW_H
