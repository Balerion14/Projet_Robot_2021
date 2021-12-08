#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_ip->setText("Mettre ici adresse IP");
    ui->input_port->setText("Mettre ici le port");

    init_image();


    load_image();


    display_image();


    // Attachement d'un slot qui sera appelé à chaque fois que des données arrivent (mode asynchrone)
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(gerer_donnees()));

    // Association du "tick" du timer à l'appel d'une méthode SLOT
    connect(pTimer, SIGNAL(timeout()), this, SLOT(demander_trames()));

    // Idem pour les erreurs
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(afficher_erreur(QAbstractSocket::SocketError)));

    //qDebug() << donnee_recue->decrypter_data("lnpjw") << "\n";

}

void MainWindow::demander_trames()
{
    QByteArray requete2 = "T";

    tcpSocket->write(requete2);
    qDebug() << "IHM => " << requete2 << "\n";
}

MainWindow::~MainWindow()
{
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
}



// This will create pictures
void MainWindow::init_image()
{
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
}

// This will load pictures
void MainWindow::load_image()
{
    pBackground->load("Background.png");
    pBanderole->load("Banderole.png");
    pAngleG->load("Tableau_angle_gauche.png");
    pAngleD->load("Tableau_angle_droit.png");
    pConnected->load("connecte.png");
    pDisconnected->load("non_connecte.png");
}


// This will display pictures
void MainWindow::display_image()
{
    ui->label_background->setPixmap(QPixmap::fromImage(*pBackground));
    ui->label_banderole->setPixmap(QPixmap::fromImage(*pBanderole));
    ui->img_angle->setPixmap(QPixmap::fromImage(*pAngleG));
    ui->img_posit->setPixmap(QPixmap::fromImage(*pAngleD));
    ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));

    ui->connect_button->setEnabled(true);
    ui->connect_forced->setEnabled(false);
    ui->disconnect_button->setEnabled(false);
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
    if(reponse == "-connection" || reponse == "-deconnexion" || reponse == "-action_effectue" || reponse == "-erreur")
    {
        if (reponse == "-connection")
        {
            ui->input_ip->setText("Connected");
            ui->input_port->setText("");
            ui->action_status->setText("Mode force = désactivé");

            ui->label_co->setPixmap(QPixmap::fromImage(*pConnected));
        }

        else if (reponse == "-deconnexion")
        {
            ui->input_ip->setText("Mettre ici adresse IP");
            ui->input_port->setText("Mettre ici le port");
            ui->action_status->setText("Mode force = désactivé");

            ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));
        }

        else if (reponse == "-action_effectue")
        {
            ui->action_status->setText("Action effectué");
        }

        else
        {
            ui->input_ip->setText("En attente d'ordre");
            ui->action_status->setText("Réponce reçue...");
            ui->input_port->setText(reponse);
        }
    }

    //Gerer affichage donne recu par le serveur
    else
    {
        ///si message crypte commence par - alors elle n'est pas traitée
        /// Penser à gerer pour afficher la position x et y
        donnee_recue->separer_data(message);

        //Recuperation info dans liste
        QStringList list = donnee_recue->_liste();

        //Attente position gauche et droit en x
        //Atention le x et le y sont l'angle gauche et droit mais juste pour le stest car apres sa sera la position x et y calcule
        QString x = list[0];
        QString y = list[1];
        QString obstacle = list[2];
        QString angle_robot = list[3];
        QString taux_snirium = list[4];


        ui->txt_dst_obstacle->setText(obstacle);
        ui->labelangle_g->setText(x);
        ui->labelangle_d->setText(y);
        ui->labelangle->setText(angle_robot);
        ui->txt_snirium->setText(taux_snirium);

        //Gerer base de donne
        remplir_bdd("x", "y", angle_robot, taux_snirium, obstacle, date);
        //A voir pourquoi sa marche pas
        bdd->stocker_info_robot("Cyborg", "Robot d'exploration");//Nom et description projet
        qDebug() << "inf0";
    }
}

void MainWindow::on_connect_forced_clicked()
{    
    // A REPROGRAMMER CAR PAS UTILE
}

void MainWindow::on_connect_button_clicked()
{
    ui->connect_button->setEnabled(false);
    ui->connect_forced->setEnabled(true);
    ui->disconnect_button->setEnabled(true);

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

    ui->connect_button->setEnabled(true);
    ui->connect_forced->setEnabled(false);
    ui->disconnect_button->setEnabled(false);

    pTimer->stop();

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

