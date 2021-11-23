#ifndef BDD_H
#define BDD_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


//class <BDD> [<BDD.cpp>]
class BDD
{
public:
    BDD();
    void stocker_donnee_HIM(QStringList liste, QStringList liste2);
private:
    QSqlDatabase bdd;
};

#endif // BDD_H
