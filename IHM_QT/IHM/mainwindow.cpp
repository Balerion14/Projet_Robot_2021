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
}

// This will load pictures
void MainWindow::load_image()
{
    pBackground->load("Background.png");
    pBanderole->load("Banderole.png");
}

// This will display pictures
void MainWindow::display_image()
{
    ui->label_background->setPixmap(QPixmap::fromImage(*pBackground));
    ui->label_banderole->setPixmap(QPixmap::fromImage(*pBanderole));
}
