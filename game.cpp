#include "game.h"
#include <stdlib.h>
#include <string.h>

Game::Game()
{
    memset(chess,0,sizeof(chess));
    Who=0;
}

bool Game::canPosition(int x,int y)
{
    if (!chess[x][y])
        return true;
    else
        return false;
}

void Game::PlayerPosition(int x, int y)
{
    chess[x][y]=(Who%2)+4;
    Who++;
    chessPoint.push_back(QPoint(x,y));
}

QPoint Game::BotPosition()
{
    int tmp,nowx,nowy;
    tmp=nowx=nowy=0;
    TakeValue();
    CalcValue();
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            if (chess[i][j]==0)
                if (Map[i][j]>=tmp)
                {
                    tmp=Map[i][j];
                    nowx=i;
                    nowy=j;
                }
        }
    chess[nowx][nowy]=Who%2+4;
    Who++;
    chessPoint.push_back(QPoint(nowx,nowy));
    return QPoint(nowx,nowy);
}

bool Game::checkWin(int x, int y)
{
    if (win1(x,y) || win2(x,y) || win3(x,y) || win4(x,y))
        return true;
    else
        return false;
}

int Game::PositionValue(int cnt)
{
    int tmp;
    switch(cnt)
    {
        case 0: tmp=7;break;
        case 4: tmp=15;break;
        case 8: tmp=400;break;
        case 12: tmp=1800;break;
        case 16: tmp=100000;break;
        case 5: tmp=35;break;
        case 10: tmp=800;break;
        case 15: tmp=15000;break;
        case 20: tmp=800000;break;
        default: tmp=0;
    }
    return tmp;
}
bool Game::win1(int x,int y)
{
    int cnt=0;
    for(int i=1;i<5;i++)
    {
        if(y-i>=0&&chess[x][y]==chess[x][y-i])
            cnt++;
        else break;
    }
    for(int i=1;i<5;i++)
    {
        if(y+i<=14&&chess[x][y]==chess[x][y+i])
            cnt++;
        else break;
    }
    if(cnt>=4)
        return true;
    else
        return false;
}
bool Game::win2(int x,int y)
{
    int cnt=0;
    for(int i=1;i<5;i++)
    {
        if(x-i>=0&&chess[x][y]==chess[x-i][y])
            cnt++;
        else break;
    }
    for(int i=1;i<5;i++)
    {
        if(x+i<=14&&chess[x][y]==chess[x+i][y])
            cnt++;
        else break;
    }
    if(cnt>=4)
        return true;
    else
        return false;
}
bool Game::win3(int x,int y)
{
    int cnt=0;
    for(int i=1;i<5;i++)
    {
        if(x-i>=0&&y-i>=0&&chess[x][y]==chess[x-i][y-i])
            cnt++;
        else break;
    }
    for(int i=1;i<5;i++)
    {
        if(y+i<=14&&x+i<=14&&chess[x][y]==chess[x+i][y+i])
            cnt++;
        else break;
    }
    if(cnt>=4)
        return true;
    else
        return false;
}
bool Game::win4(int x,int y)
{
    int cnt=0;
    for(int i=1;i<5;i++)
    {
        if(x+i<=14&&y-i>=0&&chess[x][y]==chess[x+i][y-i])
            cnt++;
        else break;
    }
    for(int i=1;i<5;i++)
    {
        if(y+i<=14&&x-i>=0&&chess[x][y]==chess[x-i][y+i])
            cnt++;
        else break;
    }
    if(cnt>=4)
        return true;
    else
        return false;
}

void Game::TakeValue()
{
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            int cnt=0;
            if(i<11)
            {
                for (int k=0;k<5;k++)
                    cnt+=chess[i+k][j];
                NodeValue[i][j].y=PositionValue(cnt);
            }
            cnt=0;
            if (j<11)
            {
                for (int k=0;k<5;k++)
                    cnt+=chess[i][j+k];
                NodeValue[i][j].x=PositionValue(cnt);
            }
            cnt=0;
            if (i<11 && j<11)
            {
                for (int k=0;k<5;k++)
                    cnt+=chess[i+k][j+k];
                NodeValue[i][j].r=PositionValue(cnt);
            }
            cnt=0;
            if (j>=4&&i<11)
            {
                for (int k=0;k<5;k++)
                    cnt+=chess[i+k][j-k];
                NodeValue[i][j].l=PositionValue(cnt);
            }
        }
}

void Game::CalcValue()
{
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            Map[i][j]=NodeValue[i][j].x+NodeValue[i][j].y+NodeValue[i][j].l+NodeValue[i][j].r;
        }
}
