#ifndef JOINNETGAMEWINDOW_H
#define JOINNETGAMEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "game.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"QString"

namespace Ui {
class JoinNetGameWindow;
}

class JoinNetGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoinNetGameWindow(QWidget *parent = 0);
    ~JoinNetGameWindow();
    virtual void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Ui::JoinNetGameWindow *ui;
    QString IPadd;
    Game game;
    int lastX,lastY;
    bool mouseflag;
    int sockfd, fd;
    struct sockaddr_in server_addr,  client_addr;
    socklen_t len;
    fd_set rfds;
    char _content[1024];
};

#endif // JOINNETGAMEWINDOW_H
