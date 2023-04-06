#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "boardwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::GameWidget)
{
    setWindowTitle("NoGo");
    ui->setupUi(this);
    // 创建 "Begin" 按钮
        QPushButton *beginButton = new QPushButton("Begin 9*9", this);
        beginButton->setGeometry(QRect(10, 10, 150, 30));
    //调整棋盘大小
        QPushButton *sizeButton11 = new QPushButton("11*11", this);
        sizeButton11->setGeometry(QRect(10, 50, 100, 30));
        QPushButton *sizeButton13 = new QPushButton("13*13", this);
        sizeButton13->setGeometry(QRect(10, 90, 100, 30));
    //新游戏和改棋盘大小
        QPushButton *newGame = new QPushButton("New Game", this);
        newGame->setGeometry(QRect(10, 150, 100, 50));
        QPushButton *reStart = new QPushButton("New Boardsize", this);
        reStart->setGeometry(QRect(10, 210, 120, 50));

    //连接
        connect(beginButton, &QPushButton::clicked, this, &GameWidget::onSizeButton9Clicked);
        connect(sizeButton11, &QPushButton::clicked, this, &GameWidget::onSizeButton11Clicked);
        connect(sizeButton13, &QPushButton::clicked, this, &GameWidget::onSizeButton13Clicked);
        connect(newGame, &QPushButton::clicked, this, [this]() { this->newGame(); });
        connect(reStart, &QPushButton::clicked, this, &GameWidget::restartGame);
}

GameWidget::~GameWidget()//析构函数
{
delete ui;
}

void GameWidget::initWidget()//打开围棋界面，在onSizeButtonxClicked()中被调用
{

  QHBoxLayout *mainLayout = nullptr;
  if (!this->layout())
  {
    //创建水平布局作为总布局
      mainLayout = new QHBoxLayout(this);
  }
  else
     {
         mainLayout = qobject_cast<QHBoxLayout *>(this->layout());  // 如果 GameWidget 已经有布局，尝试将其转换为 QHBoxLayout
     }//（这个else应该不可省略，没有的话会在改棋盘时解引用空指针报错）

    //棋盘控件
    boardWidget = new BoardWidget(boardSize,this);
    mainLayout->addWidget(boardWidget);

}


void GameWidget::newGame()//在当前棋盘大小下重新开始游戏
{
 if (boardWidget!=nullptr) {  boardWidget->newGame();}
}
void GameWidget::onSizeButton9Clicked()//打开9*9棋盘
{
    if(!boardWidget){
    boardSize=9;
   initWidget();}
}
void GameWidget::onSizeButton11Clicked()//打开11*11棋盘
{
    if(!boardWidget){
    boardSize=11;
   initWidget();}
}
void GameWidget::onSizeButton13Clicked()//打开13*13棋盘
{
    if(!boardWidget){
    boardSize=13;
   initWidget();}
}
void GameWidget::restartGame()//不同于newGame函数，此函数可重新选择新的棋盘大小
{
    if (boardWidget)
       {
        boardWidget->newGame();
        boardWidget->hide();

        // 删除旧的 boardWidget
        delete boardWidget;
        boardWidget=nullptr;//（没有的话会在点newboardsize后再点newgame时报错）
       }
}








