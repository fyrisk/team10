#ifndef GOMOKUAI_H
#define GOMOKUAI_H

#include <QObject>
#include <QPoint>

class BoardWidget;

class GomokuAi : public QObject
{
    Q_OBJECT
public:
    explicit GomokuAi(BoardWidget* boardWidget, QObject* parent = nullptr);
    //寻找最佳位置
    QPoint findBestMove();
signals:
    //发送AI落子的信号，由boardwidget接受
    void aiMove(int x, int y);

public slots:
    //接收boardwidget的信号AI进行落子
    void makeMove();
private:
    BoardWidget* boardWidget;
};

#endif // GOMOKUAI_H
