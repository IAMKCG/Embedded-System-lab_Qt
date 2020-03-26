#include "joinnetgamewindow.h"
#include "ui_joinnetgamewindow.h"
#include "ngamewindow.h"
#include "ui_ngamewindow.h"
#include <QPainter>
#include "QMessageBox"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"QString"

#define MyPort 3333

JoinNetGameWindow::JoinNetGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoinNetGameWindow)
{
    ui->setupUi(this);
    this->setFixedSize(660,660);
    this->autoFillBackground();
    mouseflag=true;
   // IPadd = tmp;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(MyPort);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);

   // QByteArray tmp =IPadd.toUtf8();
   // char *IPd=tmp.data();
    char *IPd="192.168.43.101";
    inet_aton(IPd, (struct in_addr *) & server_addr.sin_addr.s_addr);
    ::connect(sockfd, (struct sockaddr *) & server_addr, sizeof(struct sockaddr));
    memset(_content, 0, sizeof(_content));
    len = recv(sockfd, _content, 1024, 0);
    int xx,yy;
    xx=(_content[0]-'0')*10+(_content[1]-'0');
    yy=(_content[3]-'0')*10+(_content[4]-'0');
    game.PlayerPosition(xx,yy);
    lastX=xx;
    lastY=yy;
    repaint();
}

void JoinNetGameWindow::mouseReleaseEvent(QMouseEvent * event)
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
                memset(_content, 0, sizeof(_content));
                _content[0]=(x/10)+'0';
                _content[1]=(x%10)+'0';
                _content[2]=' ';
                _content[3]=(y/10)+'0';
                _content[4]=(y%10)+'0';
                len = send(fd, _content, 5, 0);
                memset(_content, 0, sizeof(_content));
                len = recv(fd, _content, 1024, 0);
                int xx,yy;
                xx=(_content[0]-'0')*10+(_content[1]-'0');
                yy=(_content[3]-'0')*10+(_content[4]-'0');
                game.PlayerPosition(xx,yy);
                lastX=xx;
                lastY=yy;
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

void JoinNetGameWindow::paintEvent(QPaintEvent *)
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

JoinNetGameWindow::~JoinNetGameWindow()
{
    delete ui;
}
