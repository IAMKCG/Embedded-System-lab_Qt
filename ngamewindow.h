#ifndef NGAMEWINDOW_H
#define NGAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class NGameWindow;
}

class NGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NGameWindow(QWidget *parent = 0);
    ~NGameWindow();

private slots:
    void on_CreateGame_clicked();
    void on_JoinGame_clicked();

private:
    Ui::NGameWindow *ui;

};

#endif // NGAMEWINDOW_H
