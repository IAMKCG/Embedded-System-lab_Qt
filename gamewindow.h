#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "game.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    virtual void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent * event);


private:
    Ui::GameWindow *ui;
    Game game;
    int lastX,lastY;
    bool mouseflag;
};

#endif // GAMEWINDOW_H
