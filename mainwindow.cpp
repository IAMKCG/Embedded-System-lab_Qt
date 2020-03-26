#include "mainwindow.h"
#include "gamewindow.h"
#include "ngamewindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_vsBot_clicked()
{
    this->close();
    GameWindow* GW = new GameWindow;
    GW->show();
}

void MainWindow::on_vsOnline_clicked()
{
    this->close();
    NGameWindow* NGW = new NGameWindow;
    NGW->show();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
