#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include "QMessageBox"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setFixedSize(660,660);
    this->autoFillBackground();
    mouseflag=true;
}

void GameWindow::mouseReleaseEvent(QMouseEvent * event)
{
    int x,y;
    if (mouseflag==true)
    {
        x=(event->y()-40)/40;
        y=(event->x()-20)/40;
        if (event->x()>=20 && event->x()<620 && event->y()>=40 && event->y()<=640)
        {
            if (game.canPosition(x,y))
            {
                game.PlayerPosition(x,y);
                lastX=x;
                lastY=y;
                update();
                if (game.checkWin(x,y))
                {
                    if ((game.Who-1)%2==1)
                        QMessageBox::about(this,QStringLiteral("Oh no"),QStringLiteral("You Lose"));
                    else
                        QMessageBox::about(this,QStringLiteral("Congratulations"),QStringLiteral("You Win"));
                    mouseflag=false;
                    return;
                }
                mouseflag=false;
                QPoint point=game.BotPosition();
                lastX=point.x();
                lastY=point.y();
                update();
                mouseflag=true;
                if (game.checkWin(lastX,lastY))
                {
                    if ((game.Who-1)%2==1)
                        QMessageBox::about(this,QStringLiteral("Oh no"),QStringLiteral("You Lose"));
                    else
                        QMessageBox::about(this,QStringLiteral("Congratulations"),QStringLiteral("You Win"));
                    mouseflag=false;
                    return;
                }
            }
        }
        update();
    }
}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QPen pen=p.pen();
    pen.setColor(Qt::black);
    pen.setWidth(1);
    p.setPen(pen);
    for (int i=0;i<15;i++)
    {
        p.drawLine(40+i*40,60,40+i*40,620);
        p.drawLine(40,60+i*40,600,60+i*40);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    p.setBrush(brush);
    p.drawRect(155,175,10,10);
    p.drawRect(475,175,10,10);
    p.drawRect(155,495,10,10);
    p.drawRect(475,495,10,10);
    p.drawRect(315,335,10,10);

    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            if (game.chess[i][j]==4)
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((j+1)*40,(i+1)*40+20),18,18);
            }
            else if (game.chess[i][j]==5)
            {
                brush.setColor(Qt::white);
                p.setPen(Qt::NoPen);
                p.setBrush(brush);
                p.drawEllipse(QPoint((j+1)*40,(i+1)*40+20),18,18);
            }
        }

    pen.setColor(Qt::red);
    pen.setWidth(1);
    p.setPen(pen);
    p.drawLine((lastY+1)*40-1,(lastX+1)*40+20,(lastY+1)*40-6,(lastX+1)*40+20);
    p.drawLine((lastY+1)*40+1,(lastX+1)*40+20,(lastY+1)*40+6,(lastX+1)*40+20);
    p.drawLine((lastY+1)*40,(lastX+1)*40+19,(lastY+1)*40,(lastX+1)*40+14);
    p.drawLine((lastY+1)*40,(lastX+1)*40+21,(lastY+1)*40,(lastX+1)*40+26);
}

GameWindow::~GameWindow()
{
    delete ui;
}
