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



private:
    void initBoard();
    void switchNextPlayer();
signals:
    void turnNextPlayer(int player);
public slots:
    void newGame();
    void downPiece(int x, int y);
    void initTime();
    void onTimerTimeout();
    void onChangeTimeButtonClicked();
    void setTrackPos(const QPoint &value);  //设置当前鼠标所在棋盘中的位置


public:
    static const QSize WIDGET_SIZE;         //棋盘控件大小
    static const QSize CELL_SIZE;           //棋盘单元格大小
    static const QPoint START_POS;          //棋盘单元格开始位置
    static const QPoint ROW_NUM_START;      //行标号开始位置
    static const QPoint CLU_NUM_START;      //列标号开始位置
     int BOARD_WIDTH = 15;      //棋盘列数(修改了类型，用于改大小 fy)
     int BOARD_HEIGHT = 15;     //棋盘行数
     int SET_TIME=60;
    static const int NO_PIECE = 0;          //棋子标志，表示无子
    static const int WHITE_PIECE = 1;       //棋子标志, 表示白子
    static const int BLACK_PIECE = 2;       //棋子标志，表示黑子
    static const bool WHITE_PLAYER = true;  //棋手标志， 表示白方
    static const bool BLACK_PLAYER = false; //棋手标志， 表示黑方

private:
    int board[15][15];       //棋盘信息
    int nextPlayer;                             //表示下一位棋手
    QPoint trackPos;                            //记录鼠标在棋盘中的位置
    QSet<int> receivePlayers;                   //棋盘接受点击下棋的棋手
    QStack<QPoint> dropedPieces;                //每一步落子位置
    QTimer *timer;
    QLabel *timeLabel;
    int remainingTime;//计时用：显示时间 fy
};

#endif // BOARDWIDGET_H
