#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "boardwidget.h"
#include "settingswindow.h"
#include <QTimer>
#include "network/networkdata.h"
#include "network/networkserver.h"
#include "network/networksocket.h"
namespace Ui {
class GameWidget;
}
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    int boardSize=15;
    NetworkServer* server;
    // 客户端
    NetworkSocket* socket;
    // 最后一个客户端
    QTcpSocket* lastOne;
    QString IP;
    int PORT;
    int PVPTime=60;
    QString userName="team10";
    QString userColor="b";
    bool player=false;
    QLabel *player1;
    QLabel *player2;
    QLabel *playerc1;
    QLabel *playerc2;
    bool gameInProgress;
    bool waitingForOpponent;
    bool sended=false;
public slots:
    void startServer(int port);
    void connectToServer(const QString &ip, int port);
    void handleData(NetworkData data);
    void handleClientData(QTcpSocket* client, NetworkData data);
    void handleNetworkMessage(QTcpSocket* client, NetworkData data);
    void setsUser(QString color,QString name);
    void sendReady(OPCODE op, QString data1, QString data2);
    void handleReadyClicked(const NetworkData &data);
    void handleRejectClicked();
    void Send(NetworkData data);
    void sendToSocket(NetworkData data);
    void sendToServer(NetworkData data);
    void disconnectAll();
    void onSendChatMessage(const QString &message);

    //初始化游戏窗口界面
    void initWidget();
    //新游戏;
    void newGame();
   //fy 选择棋盘
    void onSizeButton9Clicked();
    void onSizeButton11Clicked();
    void onSizeButton13Clicked();
    void restartGame();
    void onPvpButtonClicked();
    //联机部分
    void ready(NetworkData data);
    void reject(NetworkData data);
    void move(NetworkData data);
    void giveup(NetworkData data);
    void leave(NetworkData data);
    void chat(NetworkData data);
    void timeoutend(NetworkData data);
    void suicideend(NetworkData data);
    void giveupend(NetworkData data);
    /*void connected();
private slots:
    void onDeviceReadyRead();
    void onNewConnectionRequest(QTcpSocket *client);
signals:
    void gameStarted();*/


private:
    BoardWidget *boardWidget=nullptr;   //棋盘控件
    SettingsWindow *settingsWindow=nullptr;
     Ui::GameWidget *ui;
     /*NetworkServer *server;
     NetworkSocket *socket;*/
};

#endif // GAMEWIDGET_H
