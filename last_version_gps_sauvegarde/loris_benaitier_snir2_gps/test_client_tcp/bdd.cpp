#include "bdd.h"


/**
 * \fn BDD BDD()
 * \brief constructeur qui va initialiser et donc se connecter à la base de donnée sqlite
 *
 * \param
 * \return rien
 */
BDD::BDD()
{
    // "Connexion" à la base de données SQLite
    bdd = QSqlDatabase::addDatabase("QSQLITE");
    bdd.setDatabaseName("ma_bdd.sqlite");
    if (!bdd.open())
    {
     qDebug() << "Error: connection with database fail";
    }
    else
    {
     qDebug() << "Database: connection ok";
    }
}

/**
 * \fn stocker_donnee_HIM()
 * \brief stocker valeur HIM dans base de donnee sqlite
 *
 * \param QStringList liste, contient valeur et nom correspondant à remplir
 * \return rien
 */
void BDD::stocker_donnee_HIM(QStringList liste, QStringList liste2)//liste->value liste2->string
{
    //cree un QSqlQuery
    QSqlQuery query;

    //inserer valeur dans base de donnee en utilisant notamment la concatenation
    query.prepare("INSERT INTO personnes (altitude, longitude, timestamps, distance, speed, calorie, latitude, frequence_car) VALUES (:altitude, :longitude, :timestamps, :distance, :speed, :calorie, :latitude, :frequence_car)");
    for(auto i = 0; i<liste2.size(); i++)
    {
        query.bindValue(":"+liste2[i]+"", liste[i]);
    }

    //gestion erreur
    if(!query.exec())
    {
     qDebug() << query.lastError().text();
    }

    //verification si erreur
    try{
        if(!query.exec())
        {
         qDebug() << query.lastError().text();
        }
    }
    catch(...){

        qDebug() << query.lastError().text();
        qDebug() << "ERROR!!!";
    };

    //A voir pourquoi cette methode ne fonctionne pas pour passer valeur//
    /*QString commmande = "INSERT INTO personnes ("+liste2[0]+", "+liste2[1]+", "+liste2[2]+", "+liste2[3]+", "+liste2[4]+", "+liste2[5]+", "+liste2[6]+", "+liste2[7]+") VALUES (:"+liste2[0]+", :"+liste2[1]+", :"+liste2[2]+", :"+liste2[3]+", :"+liste2[4]+", :"+liste2[5]+", :"+liste2[6]+", :"+liste2[7]+")";

    //attribuer valeur au champs
    for(auto i = 0; i<liste2.size(); i++)
    {
        query.bindValue(":"+liste2[i]+"", liste[i]);
    }*/
}
