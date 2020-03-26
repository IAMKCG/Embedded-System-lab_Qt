#include "ngamewindow.h"
#include "ui_ngamewindow.h"
#include "newnetgame.h"
#include "joinnetgamewindow.h"


void NGameWindow::on_CreateGame_clicked()
{
    this->close();
    NewNetGame* GW = new NewNetGame;
    GW->show();
}

void NGameWindow::on_JoinGame_clicked()
{
    this->close();
    JoinNetGameWindow* GW = new JoinNetGameWindow();
    GW->show();
}

NGameWindow::NGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NGameWindow)
{
    ui->setupUi(this);
}

NGameWindow::~NGameWindow()
{
    delete ui;
}
