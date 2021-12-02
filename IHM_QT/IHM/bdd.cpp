#include "bdd.h"

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





void BDD::stocker_donnee_HIM(QStringList liste, QStringList liste2)//liste->value liste2->string
{
    //cree un QSqlQuery
    QSqlQuery query;

    //inserer valeur dans base de donnee en utilisant notamment la concatenation
    query.prepare("INSERT INTO robot (taux_snirium, obstacle, angle_gauch, angle_droit, angle_robot) VALUES (:taux_snirium, :obstacle, :angle_gauch, :angle_droit, :angle_robot)");
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
}
