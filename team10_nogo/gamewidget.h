#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QQueue>
#include <QPushButton>
#include "boardwidget.h"
#include "settingswindow.h"
#include <QTimer>
#include "network/networkdata.h"
#include "network/networkserver.h"
#include "network/networksocket.h"
#include "gomokuai.h"
namespace Ui {
class GameWidget;
}
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    //棋盘大小
    int boardSize=15;
    //服务端
    NetworkServer* server;
    // 客户端
    NetworkSocket* socket;
    // 最后一个客户端
    QTcpSocket* lastOne;
    //客户端池
    QSet<QTcpSocket*> clients;
    //存储readyop信息，用于实现附加任务4
    struct Request
    {
        QTcpSocket* client;
        OPCODE op;
        QString a;
        QString b;
        NetworkData data=NetworkData(OPCODE::READY_OP, "", "");
        Request(OPCODE op, QString a,QString b,QTcpSocket* client):client(client),op(op),a(a),b(b)
        {
            data=NetworkData(op,a,b);
        }
    };
    //readyop请求队列，存储struct Request
    QQueue<Request> requestQueue;
    //联机信息
    QString IP;
    int PORT;
    int PVPTime=60;
    QString userName="team10";
    QString userColor="b";
    bool player=false;
    //显示用户信息
    QLabel *player1;
    QLabel *player2;
    QLabel *playerc1;
    QLabel *playerc2;
    bool gameInProgress;
    bool waitingForOpponent;

    //判断某信号是否发送过，是否需要回应，防止无限循环发送
    bool sended=false;
    bool readySended=false;

public slots:
    //开始服务器
    void startServer(int port);
    //连接到服务器
    void connectToServer(const QString &ip, int port);

    //处理接受到的数据
    //handleData函数会根据本机是服务端还是客户端选择调用handleClientData或handleNetworkMessage
    void handleData(NetworkData data);
    void handleClientData(QTcpSocket* client, NetworkData data);
    void handleNetworkMessage(QTcpSocket* client, NetworkData data);

    //设置用户信息
    void setsUser(QString color,QString name);

    //发送readyop请求
    void sendReady(OPCODE op, QString data1, QString data2);
    //接受对方的readyop请求
    void handleReadyClicked(const NetworkData &data);
    //拒绝对方的readyop请求
    void handleRejectClicked();

    //处理请求队列，实现附加任务4
    void handleReadys(QQueue<GameWidget::Request> & requestQueue);

    //发送信号
    //send函数会根据本机是服务端还是客户端选择调用sendToSocket或sendToServer
    void Send(NetworkData data);
    void sendToSocket(NetworkData data);
    void sendToServer(NetworkData data);

    //断开连接，发送leaveop
    void disconnectAll();
    //发送聊天信息
    void onSendChatMessage(const QString &message);
    //展示时间，日志系统中通过qdebug输出
    void showTime();

    //初始化游戏窗口界面
    void initWidget();
    //重置棋盘状态，新游戏;
    void newGame();
   // 选择棋盘
    void onSizeButton9Clicked();
    void onSizeButton11Clicked();
    void onSizeButton13Clicked();
    //删除当前棋盘
    void restartGame();

    //打开联机设置
    void onPvpButtonClicked();
    //进入复现模式
    void onLoadButtonClicked();
    //联机部分，以下九个是不同的信号处理
    void ready(NetworkData data,QTcpSocket* client);
    void reject(NetworkData data);
    void move(NetworkData data);
    void giveup(NetworkData data);
    void leave(NetworkData data);
    void chat(NetworkData data);
    void timeoutend(NetworkData data);
    void suicideend(NetworkData data);
    void giveupend(NetworkData data);


private:
    BoardWidget *boardWidget=nullptr;   //棋盘控件
    SettingsWindow *settingsWindow=nullptr;
     Ui::GameWidget *ui;
     /*NetworkServer *server;
     NetworkSocket *socket;*/
};

#endif // GAMEWIDGET_H
