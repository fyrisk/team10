#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "boardwidget.h"
#include <QTimer>
namespace Ui {
class GameWidget;
}
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = 0);
    ~GameWidget();
    int boardSize=15;

private:
    //初始化游戏窗口界面
    void initWidget();
    //新游戏;
    void newGame();
   //fy 选择棋盘
    void onSizeButton9Clicked();
    void onSizeButton11Clicked();
    void onSizeButton13Clicked();
    void restartGame();
private:
    BoardWidget *boardWidget;   //棋盘控件
     Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
