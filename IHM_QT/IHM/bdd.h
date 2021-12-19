#ifndef BDD_H
#define BDD_H

//Importation de bibliotèque
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

//Classe BDD
class BDD
{

public:

    /*!
     *  Constructeur de la classe bdd pour la connection à une base de donnee
     *  @param aucun
     *  @param rien
     */
    BDD();

    /*!
     *  Enregistrer infos capteur dans base de donnee
     *  @param liste des infos
     *  @param liste des champs en qstring pour la selection
     *  @param rien
     */
    void stocker_donnee_robot(QStringList liste, QStringList liste2);

    /*!
     *  Enregistrer infos donnee par l'utilisateur dans base de donnee
     *  @param liste des infos
     *  @param liste des champs en qstring pour la selection
     *  @param rien
     */
    void stocker_info_robot(QString nom, QString description);

private:

    //Attribut de la classe
    QSqlDatabase bdd;
};

#endif // BDD_H
