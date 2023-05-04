#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QStack>
#include <QPoint>
#include <QSet>
#include <QPushButton>
#include <QInputDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QMessageBox>


typedef int (*Board)[15];

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(int boardSize, QWidget *parent = nullptr);

    //设置棋盘控件接受的下棋方，在ai模式中只接受白色方，双人模式中都接受
    void setReceivePlayers(const QSet<int> &value);
    //获取棋盘信息
    Board getBoard();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void onTimerTimeout();


private:
    //初始化棋盘控件
    void initBoard();
    //切换下一位下棋者
    void switchNextPlayer();

signals:
    void turnNextPlayer(int player);

public slots:
    //开始新游戏
    void newGame();
    //落子
    void downPiece(int x, int y);
    void initTime();
    void onTimeTimeout();
    void onChangeTimeButtonClicked();
    void setTrackPos(const QPoint &value);//设置当前鼠标所在棋盘中的位置

    //游戏胜负判断(public slots)
    bool isSuicidalMove(int x, int y);
    bool hasLiberties( Board tempBoard,QVector<QVector<bool>> &visited, int x, int y, int color);
    bool capturesOpponent(int x, int y);
    void captureStones(int x, int y);
    void gameOver(int loser);
    void initVisited();



public:
    static const QSize WIDGET_SIZE;         //棋盘控件大小
    static const QSize CELL_SIZE;           //棋盘单元格大小
    static const QPoint START_POS;          //棋盘单元格开始位置
    static const QPoint ROW_NUM_START;      //行标号开始位置
    static const QPoint CLU_NUM_START;      //列标号开始位置
     int BOARD_WIDTH = 15;      //棋盘列数(修改了类型，用于改大小 fy)
     int BOARD_HEIGHT = 15;
     int SET_TIME=60;     //棋盘行数
    static const int NO_PIECE = 0;          //棋子标志，表示无子
    static const int WHITE_PIECE = 1;       //棋子标志, 表示白子
    static const int BLACK_PIECE = 2;       //棋子标志，表示黑子
    static const bool WHITE_PLAYER = true;  //棋手标志， 表示白方
    static const bool BLACK_PLAYER = false; //棋手标志， 表示黑方
    QVector<QVector<bool>> visited;
    bool hasLiberty;


private:
    int board[15][15];       //棋盘信息
    int nextPlayer;                             //表示下一位棋手
    QPoint trackPos;                            //记录鼠标在棋盘中的位置
    QPoint lastpiece;                           //记录最后一颗落子的位置
    QSet<int> receivePlayers;                   //棋盘接受点击下棋的棋手
    QStack<QPoint> dropedPieces;                //每一步落子位置
    QTimer *timer;
    QLabel *timeLabel;
    int remainingTime;//计时用：显示时间 fy
};

#endif // BOARDWIDGET_H
