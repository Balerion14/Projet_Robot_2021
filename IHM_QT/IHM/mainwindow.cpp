#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    init_image();


    load_image();


    display_image();

    // Attachement d'un slot qui sera appelé à chaque fois que des données arrivent (mode asynchrone)
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(gerer_donnees()));

    // Association du "tick" du timer à l'appel d'une méthode SLOT
    connect(pTimer, SIGNAL(timeout()), this, SLOT(on_connect_forced_clicked()));

    // Idem pour les erreurs
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(afficher_erreur(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete pTimer;
    delete pBackground;
    delete pBanderole;
    delete pPosition;
    delete pAngle;
    delete pConnected;
    delete pDisconnected;
    delete donnee_recue;
    delete tcpSocket;
    delete ui;
}



// This will create pictures
void MainWindow::init_image()
{
    pBackground = new QImage();
    pBanderole = new QImage();
    pPosition = new QImage();
    pAngle = new QImage();
    pConnected = new QImage();
    pDisconnected = new QImage();
    donnee_recue = new data_received();

    tcpSocket = new QTcpSocket();
    pTimer = new QTimer();
}

// This will load pictures
void MainWindow::load_image()
{
    pBackground->load("Background.png");
    pBanderole->load("Banderole.png");
    pAngle->load("Tableau_angle.png");
    pPosition->load("Tableau_position.png");
    pConnected->load("connecte.png");
    pDisconnected->load("non_connecte.png");
}


// This will display pictures
void MainWindow::display_image()
{
    ui->label_background->setPixmap(QPixmap::fromImage(*pBackground));
    ui->label_banderole->setPixmap(QPixmap::fromImage(*pBanderole));
    ui->img_angle->setPixmap(QPixmap::fromImage(*pAngle));
    ui->img_posit->setPixmap(QPixmap::fromImage(*pPosition));
    //ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));
    //ui->label_co->setPixmap(QPixmap::fromImage(*pConnected));
}


void MainWindow::gerer_donnees()
{
    // Réception des données
    QByteArray reponse = tcpSocket->readAll();
    donnee_recue->_liste(1);
}



void MainWindow::on_connect_forced_clicked()
{    
    if (verif1 == false)
    {
        // Préparation de la requête
        QByteArray message;
        QByteArray requete = "F";

        // Envoi de la requête
        tcpSocket->write(requete);

        verif1 = true;
    }
    else
    {
        // Préparation de la requête
        QByteArray message;
        QByteArray requete = "T";

        // Envoi de la requête
        tcpSocket->write(requete);

        //lancement timer
        pTimer->start(1000);
    }
}


void MainWindow::on_connect_button_clicked()
{
    // Récupération des paramètres
    QString adresse_ip = ui->input_ip->text();
    unsigned short port_tcp = ui->input_port->text().toInt();

    // Connexion au serveur
    tcpSocket->connectToHost(adresse_ip, port_tcp);

    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "alpha-go";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_disconnect_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "deconnecte";

    // Envoi de la requête
    tcpSocket->write(requete);

    // Association du "tick" du timer à l'appel d'une méthode SLOT
    connect(pTimer, SIGNAL(timeout()), this, SLOT(on_connect_forced_clicked()));

    // Déconnexion du serveur
    tcpSocket->close();

    // Message de débug
    qDebug()<<"Deconnecter";

    verif1 = false;
}


void MainWindow::on_high_Button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "A";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_up_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "Z";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_low_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "E";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_left_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "Q";

    // Envoi de la requête
    tcpSocket->write(requete);
}

void MainWindow::on_stop_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_right_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "D";

    // Envoi de la requête
    tcpSocket->write(requete);
}


void MainWindow::on_down_button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "S";

    // Envoi de la requête
    tcpSocket->write(requete);
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
