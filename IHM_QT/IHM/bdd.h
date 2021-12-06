#ifndef BDD_H
#define BDD_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class BDD
{
    public:
        BDD();
        void stocker_donnee_robot(QStringList liste, QStringList liste2);
        void stocker_info_robot(QString nom, QString description);

    private:
        QSqlDatabase bdd;
};

#endif // BDD_H
