#ifndef NETWORKS_H
#define NETWORKS_H
/*#include "network/networkdata.h"
#include "network/networkserver.h"
#include "network/networksocket.h "
#include <QtCore>
class Networks
{
    Q_OBJECT
public:
    Networks();


public:
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
    void showTime();

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
};*/

#endif // NETWORKS_H
