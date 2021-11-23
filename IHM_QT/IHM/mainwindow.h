#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void load_image();
    void init_image();
    void display_image();

private:
    Ui::MainWindow *ui;
    QImage *pBackground;
    QImage *pBanderole;
    QPixmap image;
};
#endif // MAINWINDOW_H
