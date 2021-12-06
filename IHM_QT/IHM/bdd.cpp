#include "bdd.h"

BDD::BDD()
{
    // "Connexion" à la base de données SQLite
    bdd = QSqlDatabase::addDatabase("QSQLITE");
    bdd.setDatabaseName("bdd.db");
    if (!bdd.open())
    {
     qDebug() << "Error: connection with database fail";
    }
    else
    {
     qDebug() << "Database: connection ok";
    }
}

void BDD::stocker_info_robot(QString nom, QString description)
{
    //cree un QSqlQuery
    QSqlQuery query;
    QStringList liste;
    QStringList liste2;

    //Tableau
    liste[0] = nom;
    liste[1] = description;
    liste2[0] = "nom";
    liste2[1] = "description";


    //inserer valeur dans base de donnee en utilisant notamment la concatenation
    query.prepare("INSERT INTO Campagnes (nom, description) VALUES (:nom, :description)");
    for(auto i = 0; i<liste2.size(); i++)
    {
        query.bindValue(":"+liste2[i]+"", liste[i]);
    }
}

void BDD::stocker_donnee_robot(QStringList liste, QStringList liste2)//liste->value liste2->string
{
    //cree un QSqlQuery
    QSqlQuery query;

    //inserer valeur dans base de donnee en utilisant notamment la concatenation
    query.prepare("INSERT INTO Mesures (x, y, angle, snirium, distance, date) VALUES (:x, :y, :angle, :snirium, :distance, :date)");
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
