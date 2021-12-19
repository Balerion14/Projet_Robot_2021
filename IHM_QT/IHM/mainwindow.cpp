#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Initialisation pointeur mainwindows et affichage valeur des cases des connexions(port, ip)
    ui->setupUi(this);
    ui->input_ip->setText("Mettre ici adresse IP");
    ui->input_port->setText("Mettre ici le port");

    //Initialisations des images
    init_image();

    //Chargements des images
    load_image();

    //Affichage des images
    display_image();

    //Afficher robots au depart au millieu de la map
    affichage_robot();

    // Attachement d'un slot qui sera appelé à chaque fois que des données arrivent (mode asynchrone)
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(gerer_donnees()));

    // Association du "tick" du timer à l'appel d'une méthode SLOT
    connect(pTimer, SIGNAL(timeout()), this, SLOT(demander_trames()));

    // Idem pour les erreurs
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(afficher_erreur(QAbstractSocket::SocketError)));

    //qDebug() << donnee_recue->decrypter_data("loris") << "\n";
}

void MainWindow::demander_trames()
{
    //Preparation requete
    QByteArray requete2 = "T";

    //Envoie requete
    tcpSocket->write(requete2);
    qDebug() << "IHM => " << requete2 << "\n";
}

MainWindow::~MainWindow()
{
    //Suppression des pointeurs allouer dynamiquement
    delete pTimer;
    delete pBackground;
    delete pBanderole;
    delete pAngleD;
    delete pAngleG;
    delete pConnected;
    delete pDisconnected;
    delete donnee_recue;
    delete tcpSocket;
    delete ui;
    delete bdd;
    delete map;
    delete Bastion;
}

void MainWindow::init_image()
{
    //Creation dynamique des objets
    pBackground = new QImage();
    pBanderole = new QImage();
    pAngleD = new QImage();
    pAngleG = new QImage();
    pConnected = new QImage();
    pDisconnected = new QImage();
    donnee_recue = new data_received();
    tcpSocket = new QTcpSocket();
    pTimer = new QTimer();
    bdd = new BDD();
    bdd_image = new QImage();
    map = new QImage();
    Bastion = new robot_lego();
}

void MainWindow::affichage_robot()
{
    //Image robot
    bastion.load("robot_legos.png");
    bastion_rezise = bastion.scaled(50, 50, Qt::KeepAspectRatio);

    //Affichage du robot
    ui->robot->setPixmap(QPixmap::fromImage(bastion_rezise));

    //Affichage robot
    ui->robot->move(Bastion->dep_x(), Bastion->dep_y());
}

void MainWindow::affichage_robot_rotation(int angle)
{
    //Sotckage de l'image rotate
    rotate_robot = bastion_rezise.transformed(QTransform().rotate(angle));

    //Affichage du robot apres rotation
    ui->robot->setPixmap(QPixmap::fromImage(rotate_robot));
}

void MainWindow::affichage_robot_move(int coord_x, int coord_y)
{
    //Bouger robot
    ui->robot->move(coord_x, coord_y);
}

void MainWindow::load_image()
{
    //Chargement image dans pointeur
    pBackground->load("Background.png");
    pBanderole->load("Banderole.png");
    pAngleG->load("Tableau_angle_gauche.png");
    pAngleD->load("Tableau_angle_droit.png");
    pConnected->load("connecte.png");
    pDisconnected->load("non_connecte.png");
    bdd_image->load("fond-vert.jpg");
    map->load("mars.jpg");
}

void MainWindow::display_image()
{
    //Affichage image dans mainWindows
    ui->label_background->setPixmap(QPixmap::fromImage(*pBackground));
    ui->label_banderole->setPixmap(QPixmap::fromImage(*pBanderole));
    ui->img_angle->setPixmap(QPixmap::fromImage(*pAngleG));
    ui->img_posit->setPixmap(QPixmap::fromImage(*pAngleD));
    ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));
    ui->bdd_image->setPixmap(QPixmap::fromImage(*bdd_image));
    ui->label_map->setPixmap(QPixmap::fromImage(*map));

    //Blocage ou deblocage des boutons
    ui->connect_button->setEnabled(true);
    ui->connect_forced->setEnabled(false);
    ui->disconnect_button->setEnabled(false);
    ui->bdd_bouton->setEnabled(false);
}

void MainWindow::gerer_donnees()
{
    // Réception des données
    QByteArray reponse = tcpSocket->readAll();

    //Decrypter message
    QString message = donnee_recue->decrypter_data(reponse);

    //Trouver moyen d'avoir la date automatiquement
    QString date = "2021-12-03";

    //Condition pour renvoi message erreur dans ihm
    if(message == "-connection" || message == "-deconnexion" || message == "-action_effectue" || message == "-erreur")
    {
        if (message == "-connection")
        {
            ui->input_ip->setText("Connected");
            ui->input_port->setText("");
            ui->action_status->setText("Mode force = désactivé");

            ui->label_co->setPixmap(QPixmap::fromImage(*pConnected));
        }

        else if (message == "-deconnexion")
        {
            ui->input_ip->setText("Mettre ici adresse IP");
            ui->input_port->setText("Mettre ici le port");
            ui->action_status->setText("Mode force = désactivé");

            ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));
        }

        else if (message == "-action_effectue")
        {
            ui->action_status->setText("Action effectué");
        }

        else
        {
            ui->input_ip->setText("En attente d'ordre");
            ui->action_status->setText("Réponce reçue...");
            ui->input_port->setText(message);
        }
    }

    //Gerer affichage donne recu par le serveur
    else
    {
        //Debug
        qDebug() << "er1";

        //------------------------------------------Recup donne qui vient du robot
        donnee_recue->separer_data(message);

        //Recuperation info dans liste
        QStringList list = donnee_recue->_liste();

        //Debug
        qDebug() << "er2";

        //------------------------------------------transfert valeur dans variables pour affichage
        QString x = QString::number(Bastion->x());
        QString y = QString::number(Bastion->y());
        QString obstacle = list[2];
        QString angle_robot = list[3];
        QString taux_snirium = list[4];

        //Debug
        qDebug() << "angle:" << list[3] << " angle_gauche:" << list[0] << " angle_droit: " <<list[1];

        //------------------------------------------Choix rotate image ou move ou rien
        int choix = 0;
        choix = Bastion->choose_action(list[3], list[0], list[1], list[2]);

        affichage_robot_rotation(Bastion->angle_());
        affichage_robot_move(Bastion->x(), Bastion->y());

        /*if(choix == 1)
        {
            affichage_robot_rotation(Bastion->angle_());
        }
        else if(choix == 2)
        {
            affichage_robot_move(Bastion->x(), Bastion->y());
            //Affichage du robot apres rotation
            //ui->robot->setPixmap(QPixmap::fromImage(rotate_robot));
        }*/

       //--------------------------------------------Mettre obstacle
       bool _obstacle {false};
       _obstacle = Bastion->distance_obstacle(list[3]);
       qDebug() << "valeur-obstacle : " << _obstacle << "\n";

       if(_obstacle == true)
       {
          QPainter p(map);
          p.setPen(Qt::white);
          p.setBrush(Qt::white);
          p.drawEllipse(Bastion->xobs(), Bastion->yobs(), 10, 10);
          p.end();
          ui->label_map->setPixmap(QPixmap::fromImage(*map));
       }

       //-----------------------------------------------Mettre trace Snirium
       if(100-list[4].toInt() < 100)
       {
           QPainter p2(map);
           p2.setPen(Qt::white);
           p2.setBrush(QColor(0, 255, 0, 100-list[4].toInt()));//R,G,B,transparence
           p2.drawEllipse(Bastion->x(), Bastion->y(), 5, 5);//x, y , dimension
           p2.end();
           ui->label_map->setPixmap(QPixmap::fromImage(*map));
       }

       //----------------------------------------------Affichage
       ui->txt_dst_obstacle->setText(obstacle);
       ui->labelangle_g->setText(x);
       ui->labelangle_d->setText(y);
       ui->labelangle->setText(angle_robot);
       ui->txt_snirium->setText(taux_snirium);

       //----------------------------------------------Gerer base de donne
       remplir_bdd(x, y, angle_robot, taux_snirium, obstacle, date);

       //Debug
       qDebug() << "inf0";
    }
}//v15

void MainWindow::on_connect_forced_clicked()
{    
    // En attente de fonction
}

void MainWindow::on_connect_button_clicked()
{
    //Blocages ou deblocages boutons
    ui->connect_button->setEnabled(false);
    ui->connect_forced->setEnabled(true);
    ui->disconnect_button->setEnabled(true);
    ui->bdd_bouton->setEnabled(true);

    // Récupération des paramètres
    QString adresse_ip = ui->input_ip->text();
    unsigned short port_tcp = ui->input_port->text().toInt();

    // Connexion au serveur
    tcpSocket->connectToHost(adresse_ip, port_tcp);

    // Préparation de la requête
    QByteArray requete1 = "alpha-go";

    // Envoi de la requête
    tcpSocket->write(requete1);
    qDebug() << "IHM => " << requete1 << "\n";

    //Timer de 1s lie au slot pour que cette fonction s'effectue toutes les 1 seconde
    pTimer -> start(1000);
}

void MainWindow::on_disconnect_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "deconnecte"; // REQUETE A VERIFIER

    // Envoi de la requête
    tcpSocket->write(requete);

    // Déconnexion du serveur
    tcpSocket->close();

    //Blocage ou deblocage bonton
    ui->connect_button->setEnabled(true);
    ui->connect_forced->setEnabled(false);
    ui->disconnect_button->setEnabled(false);

    //arret du timer
    pTimer->stop();

    //Affichage bouton deconnexion
    ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));

    // Message de débug
    qDebug() << "deconnecte" << "\n";
}

void MainWindow::on_high_Button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "A";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_high_Button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_up_button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "Z";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_up_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_low_button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "E";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_low_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_left_button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "Q";

    // Envoi de la requête
    tcpSocket->write(requete);

    qDebug() << "IHM => " << "LEFTCLIC" << "\n";
}

void MainWindow::on_left_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);

    qDebug() << "IHM => " << "LEFTRELEASE" << "\n";
}

void MainWindow::on_right_button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "D";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_right_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_down_button_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "S";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";


}

void MainWindow::on_down_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::on_STOP_pressed()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
    qDebug() << "IHM => " << requete << "\n";
}

void MainWindow::remplir_bdd(QString x, QString y, QString angle, QString snirium, QString distance, QString date)
{
        qDebug() << "0" << "\n";
        QStringList liste;
        QStringList liste2;

        //ajout valeur tableau
        liste.append(x);
        liste.append(y);
        liste.append(angle);
        liste.append(snirium);
        liste.append(distance);
        liste.append(date);

        //ajout valeur tableau 2
        liste2.append("x");
        liste2.append("y");
        liste2.append("angle");
        liste2.append("snirium");
        liste2.append("distance");
        liste2.append("date");

        qDebug() << "0.5" << "\n";

        //appel de la methode pour ajouter valeur
        bdd->stocker_donnee_robot(liste, liste2);
        qDebug() << "0.9" << "\n";
}

void MainWindow::afficher_erreur(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Hôte introuvable"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Connexion refusée"));
            break;
        default:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Erreur : %1.")
                                     .arg(tcpSocket->errorString()));
    }
}




void MainWindow::on_bdd_bouton_clicked()
{
    //Blocage bouton
    ui->bdd_bouton->setEnabled(false);

    qDebug() << "b" << "\n";

    //Recuperation des valeur marque par l'utilisateur pour les stockers
    QString nom = ui->bdd_nom->text();
    QString description = ui->bdd_description->text();

    //Envoie dans Base de donnee
    bdd->stocker_info_robot(nom, description);//Nom et description projet

    //Debug
    qDebug() << "b" << "\n";
}

