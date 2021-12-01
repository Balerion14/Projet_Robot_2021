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

    qDebug() << donnee_recue->decrypter_data("lnpjw") << "\n";

}

void MainWindow::demander_trames()
{
    QByteArray requete2 = "T";

    tcpSocket->write(requete2);
    qDebug() << requete2 << "\n";
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
    QString message = donnee_recue->decrypter_data(reponse);


    if(message[0] == '-')
    {
        if (message == "-connection")
        {
            ui->input_ip->setText("Connected");
            ui->input_port->setText("");
            ui->action_status->setText("Mode force = désactivé");
        }

        else if (message == "-deconnexion" || message == "-deconnexion-delai-depasse")
        {
            ui->input_ip->setText("Mettre ici adresse IP");
            ui->input_port->setText("Mettre ici le port");
            ui->action_status->setText("Mode force = désactivé");
        }

        else if (message == "-connection-force")
        {
            ui->input_ip->setText("Connection forcée");
            ui->input_port->setText("");
            ui->action_status->setText("Mode force = activé");
        }

        else if (message == "-Inactivite-detecte")
        {
            ui->input_ip->setText("Attention inactivité détécté");
            ui->input_port->setText("");
            ui->action_status->setText("Mode force = désactivé");
        }

        else if (message == "-action_effectue")
        {
            ui->action_status->setText("Action effectué");
        }

        else
        {
            ui->input_ip->setText("Erreur message");
            ui->action_status->setText("Réponce reçue...");
            ui->input_port->setText(reponse);
        }
    }

    else
    {
        donnee_recue->separer_data(message);

        QStringList list = donnee_recue->_liste();

        QString taux_snirium = list[0];//
        QString obstacle = list[1];//
        QString angle_gauch = list[2];
        QString angle_droit = list[3];
        QString angle_robot = list[4];


        ui->txt_dst_obstacle->setText(obstacle);
        ui->labelangle_g->setText(angle_gauch);
        ui->labelangle_d->setText(angle_droit);
        ui->labelangle->setText(angle_robot);
        ui->txt_snirium->setText(taux_snirium);
    }
}





void MainWindow::on_connect_forced_clicked()
{    

        // Préparation de la requête
        QByteArray message;
        QByteArray requete = "connexion-force"; // REQUETE A VERIFIER

        // Envoi de la requête
        tcpSocket->write(requete);

        ui->label_co->setPixmap(QPixmap::fromImage(*pConnected));

        ui->connect_button->setEnabled(false);
        ui->connect_forced->setEnabled(false);
        ui->disconnect_button->setEnabled(true);

        qDebug() << requete << "\n";

}





void MainWindow::on_connect_button_clicked()
{
    ui->label_co->setPixmap(QPixmap::fromImage(*pConnected));
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
    qDebug() << requete1 << "\n";

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


    ui->label_co->setPixmap(QPixmap::fromImage(*pDisconnected));

    ui->connect_button->setEnabled(true);
    ui->connect_forced->setEnabled(false);
    ui->disconnect_button->setEnabled(false);

    pTimer->stop();

    // Message de débug
    qDebug() << "deconnecte" << "\n";
}





void MainWindow::on_high_Button_clicked()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "A";

    // Envoi de la requête
    tcpSocket->write(requete);
}

void MainWindow::on_high_Button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

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

void MainWindow::on_up_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

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

void MainWindow::on_low_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

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

    qDebug() << "LEFTCLIC" << "\n";
}

void MainWindow::on_left_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

    // Envoi de la requête
    tcpSocket->write(requete);

    qDebug() << "LEFTRELEASE" << "\n";
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

void MainWindow::on_right_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

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

void MainWindow::on_down_button_released()
{
    // Préparation de la requête
    QByteArray message;
    QByteArray requete = "C";

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
