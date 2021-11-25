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
}

MainWindow::~MainWindow()
{
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
