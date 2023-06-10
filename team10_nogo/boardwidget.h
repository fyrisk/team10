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
#include "network/networkdata.h"
class GomokuAi; // 前向声明
typedef int (*Board)[15];   //存储棋盘状态

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
    //绘制棋盘，棋子，显示当前鼠标锁定位置，高光上一步
    void paintEvent(QPaintEvent *event);
    //落子指令，判断是否调用downPiece落子
    void mouseReleaseEvent(QMouseEvent *event);
    //将当前鼠标位置转化为坐标
    void mouseMoveEvent(QMouseEvent *event);
    //每秒执行，更新显示剩余时间的QLable，同时判断是否超时
    void onTimerTimeout();


private:
    //初始化棋盘控件
    void initBoard();
    //切换下一位下棋者
    void switchNextPlayer();

signals:
    void turnNextPlayer(int player);//由AI（gomokuai）接受，AI开始落子
    void send(NetworkData data);    //由gameWidget接受，发送信号，服务端发给客户端，客户端发给服务端
    void playerMoved(); // 由发送玩家落子信号（没用）
public :
    void setPlayerName( QString &playerName);//设置用户名
    //开始新游戏
    void newGame();
    //落子
    void downPiece(int x, int y);
    //初始化时间
    void initTime();
    void onChangeTimeButtonClicked(); //更改时间按钮，可以输入新的时间
    void onGiveUpButtonClicked();     //认输
    void onShowButtonClicked();       //展示上一把行棋记录
    void onShowLastButtonClicked();   //展示本次运行全部行棋记录

    //复现及附加功能
    void onStopButtonClicked();       //暂停复现
    void onContinueButtonClicked();   //继续复现
    void onLastButtonClicked();       //上一步
    void onNextButtonClicked();       //下一步
    void onJumpButtonClicked();       //跳步按钮
    void toTheStep(int x);            //调到第x步
    //void showLastEnd();
    void setTrackPos(const QPoint &value);//记录鼠标的位置，转成坐标

    //游戏胜负判断(public slots)
    bool isSuicidalMove(int x, int y);  //是否自杀
    //判断是否有气
    bool hasLiberties( Board tempBoard,QVector<QVector<bool>> &visited, int x, int y, int color);
    //判断在此落子是否吃到对方
    bool capturesOpponent(int x, int y);
    //游戏结算
    void gameOver(int loser);
    //初始化visited数组
    void initVisited();
    //记录与复现
    //从全部行棋记录中分离出上一把行棋记录
    void copyLast();
    //存储上一把行棋记录到本地
    void saveLastHistory(const QVector<QString>& lastHistory, const QString& filename);
    //读取文件中的上一把行棋记录
    QVector<QString> loadLastHistory(const QString& filename);
    //进入复线模式
    void showLast();
    //判断游戏模式
    void onSwitchModeButtonClicked();//AI按钮点击后调用
    //进入EVE模式
    void onEVEButtonClicked();

    //获取棋盘信息，供其他类访问
    int getPiece(int x, int y) const;
    int getBoardWidth() const;
    int getBoardHeight() const;

    //获取color方棋子当前所剩的气
    int getLiberty(int color);
    //获取color方当前局势的得分
    int getScore(int color);
    //把得分记录在scores数组中，供AI挑选最佳步骤
    void setScores();
    //判读能否落子在此处
    bool canDown(int x,int y,int color);
    //判断周围是否有颜色为color棋子
    bool hasNeighborPiece(int x, int y,int color) const;


private:
    //ai部分
    GomokuAi *aiPlayer; // AI玩家对象
    void startAIPlayer(); // 启动AI玩家的决策
    void stopAIPlayer(); // 停止AI玩家的决策
    void aiDropPiece(int x, int y);//AI落子在（x,y）调用downPiece
    void makeAiMove();   //AI开始落子



public:
    int scores[15][15];   //AI决策得分
    int canDown1[15][15]; //是否可落子
    static const QSize WIDGET_SIZE;         //棋盘控件大小
    static const QSize CELL_SIZE;           //棋盘单元格大小
    static const QPoint START_POS;          //棋盘单元格开始位置
    static const QPoint ROW_NUM_START;      //行标号开始位置
    static const QPoint CLU_NUM_START;      //列标号开始位置
     int BOARD_WIDTH = 15;      //棋盘列数(修改了类型，用于改大小 fy)
     int BOARD_HEIGHT = 15;     //棋盘行数
     int SET_TIME=60;           //计时
     //int elapsed=0;
    static const int NO_PIECE = 0;          //棋子标志，表示无子
    static const int WHITE_PIECE = 1;       //棋子标志, 表示白子
    static const int BLACK_PIECE = 2;       //棋子标志，表示黑子
    static const bool WHITE_PLAYER = true;  //棋手标志， 表示白方
    static const bool BLACK_PLAYER = false; //棋手标志， 表示黑方
    QVector<QVector<bool>> visited;         //在判断是否有气中搜索过程使用，判断是否访问过
    bool hasLiberty;                        //是否有气
    int nextPlayer;                         //当前棋手
    int isPVP=0;//是否联机
    int isEVE=0;//是否EVE
    int isGameWithAi=0;   //是否启用了AI
    int isplayerturn=0;   //是否该AI落子了
    int isAI[2]={0};      //黑/白子是否由AI控制
    int isAITurn[2]={0};  //是否轮到黑/白子AI落子
    int curColor=BLACK_PIECE;  //当前颜色
    int PVPColor=BLACK_PIECE;  //联机中本机的颜色
    int AIColor=WHITE_PIECE;   //AI控制的颜色
    bool sended=false;         //是否发送过某信号，用以判断是否需要回复相同信号，防止无限循环发送
    bool isStop=false;//用于复现过程判断是否暂停
    int i=0;          //用于复现记录当前步数
    int step=0;       //用于复现中传入步数
    int flag=0;//判断有无投降
    int flag2=0;//判断ai是否下错位置
    QStack<QPoint> dropedPieces;                //每一步落子位置
    QVector<QString> droppedPiecesM;             //行棋编码存储
    QVector<QString> lastHistory= QVector<QString>();//上一把游戏编码


private:
    int board[15][15];       //棋盘信息
    int value[15][15];       //不同棋盘位置的价值（四周与中心较高，其他较低）
    QString name;            //用户名
    QPoint trackPos;                            //记录鼠标在棋盘中的位置
    QPoint lastpiece;                           //记录最后一颗落子的位置
    QSet<int> receivePlayers;                   //棋盘接受点击下棋的棋手
    QTimer *timer;                              //计时
    QLabel *timeLabel;                          //显示剩余时间
    QLabel *whiteStepLabel;  // 白方步数
    QLabel *blackStepLabel;  // 黑方步数
    QLabel *totalStepLabel;  // 总步数
    int remainingTime;//计时用：当前剩余时间
    int whiteStepCount;//记录白棋步数
    int blackStepCount;//记录黑棋步数
    int whiteThinkingTime;//记录白方思考时间
    int blackThinkingTime;//记录黑方思考时间
    int originTime;//记录实际设置的思考时间
    double whiteAvgThinkingTime;//记录黑子平均思考时间
    double blackAvgThinkingTime;//记录白子平均思考时间
    double TotalTime;//记录总耗时
};

#endif // BOARDWIDGET_H
