#include "robot_lego.h"
#include "ui_mainwindow.h"

robot_lego::robot_lego()
{
}

robot_lego::~robot_lego()
{
}

int robot_lego::choose_action(QString __angle, QString __angle_gauche, QString __angle_droit, QString _distance)
{
    //Transformation Qstring en int pour pouvoir utiliser les valeurs
    angle = __angle.toInt();
    angle = angle-90;
    angle_gauche = __angle_gauche.toInt();
    angle_droit = __angle_droit.toInt();
    distance = _distance.toInt();

    //Debug
    qDebug() << "angle: " << angle << "angle_gauche" << angle_gauche << "angle droit: " << angle_droit;

    //Calcule difference entre new et old angle
    int diff {0};
    diff = angle - Angle[0];
    qDebug() << "diff: " << diff;
    qDebug() << "angle_old: " << Angle[0];

    calcule_angle_rotation();
    //calcule_position();

    //Condition pour action sur image
    /*if(diff != 0)
    {
        //Rotation
        calcule_angle_rotation();
        return 1;
    }
    else if(diff == 0 && angle_gauche != Angle_cote[0] && angle_droit != Angle_cote[1])
    {
        //Move
        calcule_position();
        return 2;
    }*/

    //Si aucun des cas, aucun changements
    return 3;
}

int robot_lego::conversion_pixel(int distance)
{
    //851x841 10 mm->2 mm sur carte
    //Conversion pixel
    return (distance *2)/10;
}

void robot_lego::calcule_position()//Bug
{
    //Initilaisation
    int perimetre_roue = 0;
    int angle_gauche_droit = 0;
    int direction = 0;
    int dx = 0;
    int dy = 0;
    int x2 = 0;
    int y2 = 0;

    //Calcule perimetre
    perimetre_roue = (2 * M_PI * (diametre/2));

    //Calcule diff angle avec une moyenne des deux
    angle_gauche_droit = ((angle_gauche - Angle_cote[0]) + (angle_droit - Angle_cote[1])) / 2;
    qDebug() << "angle_gauche_droit: " << angle_gauche_droit;

    //Calcule distance
    direction = (angle_gauche_droit * perimetre_roue) / 360;
    direction = conversion_pixel(direction);
    qDebug() << "direction: " << direction;

    //Calcule dx et dy
    dx = direction * cos((angle*M_PI)/180);//(angle * (2*M_PI)
    dy = direction * sin((angle*M_PI)/180);//(angle * (2*M_PI)
    qDebug() << "dx: " << dx;
    qDebug() << "dy: " << dy;


    //Nouvelle coordonne
    x2 = coord_x + dx;
    y2 = coord_y + dy;
    qDebug() << "x2: " << x2;
    qDebug() << "y2: " << y2;

    //Save angle roue pour prochain calcule
    Angle_cote[0] = angle_gauche;
    Angle_cote[1] = angle_droit;

    //Save coordonne pour pro calcule
    coord_x = x2;
    coord_y = y2;

    //debug
    qDebug() << "x: " << coord_x << "y: " << coord_y;
}

bool robot_lego::distance_obstacle(QString angle)
{
    //Variables
    int dx = 0;
    int dy = 0;
    int x2 = 0;
    int y2 = 0;

    //Transformation qstring en int
    int angle_gyro = angle.toInt();

    //Passage en pixel
    int _distance = conversion_pixel(distance);

    if(_distance != 0)
    {
        //Calcule
        dx = _distance * cos(angle_gyro);
        dy = _distance * sin(angle_gyro);
        x2 = coord_x + dx;
        y2 = coord_y + dy;

        //Save values
        x2_obs = x2;
        y2_obs = y2;

        //Debug
        qDebug() << "dx: " << dx;
        qDebug() << "dy: " << dy;
        qDebug() << "x_obs: " << x2;
        qDebug() << "y_obs: " << y2;
        qDebug() << "distance: " << _distance;

        //Distance existe
        return true;
    }

    //Distance null
    return false;
}

void robot_lego::calcule_angle_rotation()//Seule sa fonctionne
{
    //Creation variables
    int _angle = angle;

    //determinier angle pour la rotation par rapport à l'ancien
    _angle -= Angle[0];

    //stockage de l'angle de base
    Angle[0] = angle;

    if(_angle != 0)
    {
        //Mise a jour de la valeur de l'angle à rotate
        angle = _angle;
        qDebug() << "angle-rotate" << angle;
    }
}

const int robot_lego::dep_x()
{
    return coord_x_dep;
}

const int robot_lego::dep_y()
{
    return coord_y_dep;
}

const int robot_lego::x()
{
    return coord_x;
}

const int robot_lego::y()
{
    return coord_y;
}

const int robot_lego::angle_()
{
    return angle;
}

const int robot_lego::xobs()
{
    return x2_obs;
}

const int robot_lego::yobs()
{
    return y2_obs;
}
