#ifndef ROBOT_LEGO_H
#define ROBOT_LEGO_H

//Biblioteque
#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <iostream>
#include <QTimer>
#include <QImage>

//CLasse robot-lego pour l'affichage et les differents calcule lie au robot
class robot_lego
{
public:

    /*!
     *  Constructeur de la classe robot_lego pour initialiser la classe
     *  Aucun parametre
     *  return rien
     */
    robot_lego();

    /*!
     *  destructeur de la classe robot_lego pour la destruction de l'objet robot_lego
     *  Aucun parametre
     *  return rien
     */
    ~robot_lego();

    /*!
     *  Methode de la classe robot_lego sur le choix de l'action à faire
     *  QString angle
     *  QString angle_gauche
     *  QString angle_droit
     *  QString distance
     *  return int
     */
    int choose_action(QString angle, QString angle_gauche, QString angle_droit, QString distance);

    /*!
     *  Methode de la classe robot_lego sur le calcule de la position x et y
     *  Aucun parametre
     *  return rien
     */
    void calcule_position();

    /*!
     *  Methode de la classe robot_lego pour avoir l'avoir l'angle rotation
     *  Aucun parametre
     *  return rien
     */
    void calcule_angle_rotation();

    /*!
     *  Methode de la classe robot_lego pour avoir le point x et y de l'obstacle
     *  1 parametre angle
     *  return bool
     */
    bool distance_obstacle(QString angle);

    /*!
     *  Methode de la classe robot_lego pour convertir distance reel en pixel correspondants à l'image
     *  int distance
     *  return conversion distance
     */
    int conversion_pixel(int distance);

    /*!
     *  Methode de la classe robot_lego pour recuperer x
     *  Aucun parametre
     *  return la postion x en int
     */
    const int x();

    /*!
     *  Methode de la classe robot_lego pour recuperer x
     *  Aucun parametre
     *  return postion y en int
     */
    const int y();

    /*!
     *  Methode de la classe robot_lego pour recuperer l'angle rotation
     *  Aucun parametre
     *  return angle en int
     */
    const int angle_();

    /*!
     *  Methode de la classe robot_lego pour recuperer x de depart
     *  Aucun parametre
     *  return position de depart x en int
     */
    const int dep_x();

    /*!
     *  Methode de la classe robot_lego pour recuperer y de depart
     *  Aucun parametre
     *  return position de depart y en int
     */
    const int dep_y();


    /*!
     *  Methode de la classe robot_lego pour recuperer x obstacle
     *  Aucun parametre
     *  return position de depart y en int
     */
    const int xobs();


    /*!
     *  Methode de la classe robot_lego pour recuperer y obstacle
     *  Aucun parametre
     *  return position de depart y en int
     */
    const int yobs();

private:

    //Variables classe
    int coord_x {410};
    int coord_y {646};//650

    const int coord_x_dep {420};
    const int coord_y_dep {550};
    const int coord_x_zero {0};
    const int coord_y_zero {0};

    int angle {0};
    int angle_gauche {0};
    int angle_droit {0};
    int angle_gauche_save {0};
    int angle_droit_save {0};
    int distance {0};
    int x2_obs {0};
    int y2_obs {0};

    const int diametre {56};

    int coordonne [2] = {0, 0};
    int Angle [1] = {0};
    int Angle_cote[2] = {0, 0};
};

#endif // ROBOT_LEGO_H
