#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <QPoint>

typedef struct
{
  int x,y,l,r;
}value;
class Game
{
public:
    Game();
    int chess[15][15];
    int Who;
    bool win1(int x,int y);
    bool win2(int x,int y);
    bool win3(int x,int y);
    bool win4(int x,int y);
    bool canPosition(int x,int y);
    bool checkWin(int x,int y);
    void PlayerPosition(int x,int y);
    void TakeValue();
    int PositionValue(int cnt);
    void CalcValue();
    int computerColor=5;
    QPoint BotPosition();
private:
    QVector<QPoint> chessPoint;
    value NodeValue[15][15];
    int Map[15][15];
};

#endif // GAME_H
