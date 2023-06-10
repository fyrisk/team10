#include "gomokuai.h"
#include "boardwidget.h"
#include <QDebug>
#include <QTime>
#include <cstdlib>

GomokuAi::GomokuAi(BoardWidget* boardWidget, QObject* parent) : QObject(parent), boardWidget(boardWidget)
{
    // 将BoardWidget的turnNextPlayer信号与GomokuAi的makeMove槽连接
    connect(boardWidget, &BoardWidget::turnNextPlayer, this, &GomokuAi::makeMove);
}

void GomokuAi::makeMove()
{
     qDebug()<<"into makemove";
    if(boardWidget->isplayerturn==1||boardWidget->isEVE)
    {
    // 调用AI策略选择最佳落子位置
    QPoint bestMove = findBestMove();

    // 发送aiMove信号，传递最佳落子位置的坐标
    if(bestMove.x()==-1)
    {
        return;
    }
    QTime delayTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < delayTime)
        QCoreApplication::processEvents();
    emit aiMove(bestMove.x(), bestMove.y());
    }
}

QPoint GomokuAi::findBestMove()
{
    int boardWidth = boardWidget->getBoardWidth();
    int boardHeight = boardWidget->getBoardHeight();

    // 优先选择与已有棋子相邻的空格子
    QVector<QPoint> Positions;
    boardWidget->setScores();
    int max=-999999;
    int flag=0;
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; y++)
        {
            if(boardWidget->canDown1[x][y]==1)
            {
                flag=1;
               if(boardWidget->scores[x][y]>max) max=boardWidget->scores[x][y];
            }
        }
    }
    if(flag==0) return QPoint(-1, -1);
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; y++)
        {
           if(boardWidget->canDown1[x][y]==1&&boardWidget->scores[x][y]==max) Positions.append(QPoint(x,y));
        }
    }


    if (!Positions.isEmpty())
    {
        srand(QTime::currentTime().msec());
        int randomIndex = rand() % Positions.size();
        return Positions[randomIndex];
    }

    return QPoint(-1, -1);
}

