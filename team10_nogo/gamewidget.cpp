#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "boardwidget.h"
#include "settingswindow.h"
#include "readydialog.h"
#include "network/networkdata.h"
#include "network/networkserver.h"
#include "network/networksocket.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QDateTime>
#include <QDebug>
#include <QDateTime>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::GameWidget)
{
    setWindowTitle("NoGo");
    ui->setupUi(this);
    IP = "127.0.0.1";
    PORT = 16667;
    //服务器
    this->server = new NetworkServer(this);

    lastOne = nullptr;

    // 创建一个客户端
    this->socket = new NetworkSocket(new QTcpSocket(),this);
   /* server = new NetworkServer(this);
    socket = new NetworkSocket(new QTcpSocket(), this);*/
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
        QPushButton *PvpButton = new QPushButton("PvP Settings", this);
        PvpButton->setGeometry(QRect(10, 250, 120, 50));
        player1 = new QLabel("player 1(you)", this);
        player1->setGeometry(QRect(560, 50, 160, 50));
        player2 = new QLabel("player 2", this);
        player2->setGeometry(QRect(560, 100, 160, 50));
        playerc1 = new QLabel("black", this);
        playerc1->setGeometry(QRect(560, 70, 160, 50));
        playerc2 = new QLabel("white", this);
        playerc2->setGeometry(QRect(560, 120, 160, 50));

    //连接(联机部分)


    //连接其他部分
        connect(beginButton, &QPushButton::clicked, this, &GameWidget::onSizeButton9Clicked);
        connect(sizeButton11, &QPushButton::clicked, this, &GameWidget::onSizeButton11Clicked);
        connect(sizeButton13, &QPushButton::clicked, this, &GameWidget::onSizeButton13Clicked);
        connect(newGame, &QPushButton::clicked, this, [this]() { this->newGame(); });
        connect(reStart, &QPushButton::clicked, this, &GameWidget::restartGame);
        connect(PvpButton, &QPushButton::clicked, this, &GameWidget::onPvpButtonClicked);
    // 连接 NetworkServer 和 NetworkSocket 的信号和槽
       /* connect(server, &NetworkServer::newConnectionRequest, this, &GameWidget::onNewConnectionRequest);
        connect(server, &NetworkServer::receive, this, &GameWidget::onServerReceive);
        connect(socket, &NetworkSocket::receive, this, &GameWidget::onSocketReceive);
        connect(socket->base(), &QAbstractSocket::errorOccurred, this, &GameWidget::displayError);
        connect(socket->base(), &QAbstractSocket::connected, this, &GameWidget::connected);
        // gamewidget.cpp
        connect(socket->base(), &QIODevice::readyRead, this, &GameWidget::onDeviceReadyRead);*/

}

GameWidget::~GameWidget()
{
delete ui;
}

void GameWidget::initWidget()
{
    //QMessageBox::warning(this, tr("警告"), tr("不允许自杀！"));
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
    connect(boardWidget, &BoardWidget::send, this, &GameWidget::Send);
    boardWidget->setPlayerName(userName);
}


void GameWidget::newGame()
{
 if (boardWidget!=nullptr) {  boardWidget->newGame();}
}
void GameWidget::onSizeButton11Clicked()
{
    if(!boardWidget){
    boardSize=11;
   initWidget();}
}

void GameWidget::onSizeButton9Clicked()
{
   if(!boardWidget){
    boardSize=9;
   initWidget();}
}

void GameWidget::onSizeButton13Clicked()
{
    if(!boardWidget){
    boardSize=13;
   initWidget();}
}
void GameWidget::restartGame()
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
//联机部分
// gamewidget.cpp
void GameWidget::onPvpButtonClicked()
{
    settingsWindow = new SettingsWindow(this);
    connect(settingsWindow, &SettingsWindow::connectToServer, this, &GameWidget::connectToServer);
    connect(settingsWindow, &SettingsWindow::startServer, this, &GameWidget::startServer);
    connect(settingsWindow, &SettingsWindow::sets, this, &GameWidget::setsUser);
    connect(settingsWindow, &SettingsWindow::beginGame, this, &GameWidget::sendReady);
    connect(settingsWindow, &SettingsWindow::disconnectAll, this, &GameWidget::disconnectAll);
    connect(settingsWindow, &SettingsWindow::sendChatMessage, this, &GameWidget::onSendChatMessage);
    settingsWindow->show();
}
void GameWidget::onSendChatMessage(const QString &message)
{
    settingsWindow->appendChatMessage("You: " + message);

    NetworkData chatData(OPCODE::CHAT_OP, message, "");
    Send(chatData);
}
void GameWidget::setsUser(QString color,QString name)
{
    userName=name;
    userColor=color;
    player1->setText(name);
    playerc1->setText(color=="w"?"white":"black");
    playerc2->setText(color=="b"?"white":"black");
    update();
}
void GameWidget::startServer(int port)
{
    if (server)
    {
        delete server;
    }
    server = new NetworkServer(this);
    connect(this->server,&NetworkServer::receive,this,&GameWidget::handleClientData);
    server->listen(QHostAddress::Any, port);
    qDebug()<<"start listening";
}

void GameWidget::connectToServer(const QString &ip, int port)
{
    this->socket->bye();
    this->socket->hello(ip,port);
    connect(this->socket->base(), &QTcpSocket::connected, settingsWindow, &SettingsWindow::setConnectionStatus, Qt::QueuedConnection);
    connect(this->socket,&NetworkSocket::receive,this,&GameWidget::handleData);
    qDebug()<<"start reconnect";
    if(!this->socket->base()->waitForConnected(3000))
    {
        qDebug()<<"reconnect fail";
    }
}
void GameWidget::disconnectAll()
{
    Send(NetworkData(OPCODE::LEAVE_OP,userName,"byebye"));
    //本机作为客户端
    if(lastOne==nullptr) socket->bye();
    //本机作为服务端
   // else server->leave(lastOne);
}
void GameWidget::handleData(NetworkData data)
{
    handleNetworkMessage(nullptr, data);
};
void GameWidget::handleClientData(QTcpSocket* client, NetworkData data)
{
    lastOne=client;
    handleNetworkMessage(client, data);
};
void GameWidget::handleNetworkMessage(QTcpSocket* client, NetworkData data)
{
    switch (data.op)
    {
    case OPCODE::READY_OP:
        // 处理 READY_OP 请求，如创建 boardWidget 棋盘和设置初始状态
        ready(data);
        break;
    case OPCODE::REJECT_OP:
        // 处理 REJECT_OP 请求
        reject(data);
        break;
    case OPCODE::CHAT_OP:
        // 处理 CHAT_OP 请求，如聊天或交换信息
        chat(data);
        break;
    case OPCODE::LEAVE_OP:
        // 处理 LEAVE_OP 请求，对方发此信号我方不用回复，可以断开连接
        leave(data);
        break;
    case OPCODE::MOVE_OP:
        // 处理 MOVE_OP 请求，如根据对方的信号，在棋盘上落下对方的棋子（调用 downPiece 函数）
        // 同时我方开始计时下棋，落子后也向对方发送 MOVE_OP
        move(data);
        break;
    case OPCODE::GIVEUP_OP:
        // 处理 GIVEUP_OP 请求，收到此信号说明对方认输，本局游戏结束，我方胜利
        giveup(data);
        break;
    case OPCODE::TIMEOUT_END_OP:
        // 处理 GG_OP 请求，收到对方此信号后说明我方失败，对方胜利，我方需要回复相同操作表示确认
        timeoutend(data);
        break;
    case OPCODE::SUICIDE_END_OP:
        // 处理 GG_OP 请求，收到对方此信号后说明我方失败，对方胜利，我方需要回复相同操作表示确认
        suicideend(data);
        break;
    case OPCODE::GIVEUP_END_OP:
        // 处理 GG_OP 请求，收到对方此信号后说明我方失败，对方胜利，我方需要回复相同操作表示确认
        giveupend(data);
        break;
    default:
        // 处理未知操作码
        break;
    }
}
void GameWidget::sendReady(OPCODE op, QString name, QString color)
{
    this->socket->send(NetworkData(OPCODE::READY_OP,name,color));
    PVPTime=settingsWindow->time;
   // qDebug()<<"sendReady color="<<color;
}
void GameWidget::handleReadyClicked(const NetworkData &data)
{
    QString opponentName = data.data1;
    QString myColor = (data.data2 == "b" ? "w" : "b");
    QString opponentColor = data.data2;
    PVPTime=settingsWindow->time;

    // 更新 UI
    setsUser(myColor, userName);
    PVPTime=settingsWindow->time;
    player2->setText(opponentName);
    onSizeButton9Clicked();
    boardWidget->isPVP=1;
    boardWidget->SET_TIME=PVPTime;
    boardWidget->setPlayerName(userName);
    //设置棋子颜色（有bug）
    boardWidget->PVPColor=(data.data2 == "b" ? 1 : 2);
    player=(data.data2 == "b" ? true : false);
    // 向对方发送 READY_OP 信号
    NetworkData readyData(OPCODE::READY_OP, userName, myColor);
    sendToSocket(readyData);
   // qDebug()<<"server color :"<<boardWidget->PVPColor<<"ispvp"<<boardWidget->isPVP;
}

void GameWidget::handleRejectClicked()
{
    // 处理 reject 操作
    NetworkData rejectData(OPCODE::REJECT_OP, userName, "xia_ci_yi_ding");
    sendToSocket(rejectData.encode());
}
void GameWidget::Send(NetworkData data)
{
    //qDebug() << "send it";
    //本机作为客户端
    if(lastOne==nullptr) sendToServer(data);
    //本机作为服务端
    else sendToSocket(data);
}
void GameWidget::sendToSocket(NetworkData data)
{
    server->send(lastOne,data);
    qDebug() << "send OP to SOCKET "<<data.encode()<<" "<<data.data1<<" "<<data.data2;
}
void GameWidget::sendToServer(NetworkData data)
{
    socket->send(data);
    qDebug() << "send OP to SERVER "<<data.encode()<<" "<<data.data1<<" "<<data.data2;
}
void GameWidget::ready(NetworkData data)
{
  qDebug() << "receiveReady";

  if(!settingsWindow->connected)
  {
    ReadyDialog dialog(this);
    connect(&dialog, &ReadyDialog::readyClicked, this, [this, data] {
        handleReadyClicked(data);
    });

    connect(&dialog, &ReadyDialog::rejectClicked, this, [this] {
        handleRejectClicked();
    });

    dialog.exec();
  }
  else
  {
      QString opponentName = data.data1;
      QString myColor = (data.data2 == "b" ? "w" : "b");
      QString opponentColor = data.data2;

      setsUser(myColor, userName);
      player2->setText(opponentName);

      onSizeButton9Clicked();
      boardWidget->isPVP=1;
      boardWidget->SET_TIME=PVPTime;
      //(有bug)
      boardWidget->setPlayerName(userName);
      boardWidget->PVPColor=(data.data2 == "b" ? 1 : 2);
      player=(data.data2 == "b" ? true : false);
      qDebug()<<"socket color :"<<boardWidget->PVPColor<<"ispvp"<<boardWidget->isPVP;
  }
}

void GameWidget::reject(NetworkData data)
{
    qDebug() << "对方拒绝了你的对局申请";
};
void GameWidget::move(NetworkData data)
{
    qDebug() << "receive MOVE_OP";
    int r=data.data1.at(0).unicode() - 'A';
    int c=data.data1.at(1).unicode() - '1';
    boardWidget->downPiece(c,r);
    qint64 opponentTimestamp = data.data2.toLongLong();
    qint64 currentTimestamp = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTimestamp - opponentTimestamp;
    int ct=2*elapsed/1000;
    boardWidget->elapsed=ct;
};
void GameWidget::giveup(NetworkData data)
{
    Send(NetworkData(OPCODE::GIVEUP_END_OP,userName,"goodgame"));
    sended=true;
    boardWidget->gameOver(!player);
};
void GameWidget::leave(NetworkData data)
{
    if(lastOne==nullptr) socket->bye();
    else return;
};
void GameWidget::chat(NetworkData data)
{
    if(lastOne!=nullptr)
settingsWindow->appendChatMessage("client: " + data.data1);
    else settingsWindow->appendChatMessage("server: " + data.data1);
};
void GameWidget::timeoutend(NetworkData data)
{    if(!boardWidget->sended)
    {
      Send(NetworkData(OPCODE::TIMEOUT_END_OP,userName,"goodgame"));
      boardWidget->gameOver(player);
    }
};
void GameWidget::suicideend(NetworkData data)
{
    if(!sended)
    {
      Send(NetworkData(OPCODE::SUICIDE_END_OP,userName,"goodgame"));
      boardWidget->gameOver(player);
    }
};

void GameWidget::giveupend(NetworkData data)
{
    if(!sended) Send(NetworkData(OPCODE::GIVEUP_END_OP,userName,"goodgame"));
};

