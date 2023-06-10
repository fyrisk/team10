#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include "network/networkdata.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    int connected=0;  //是否连接成功
    int time=60;      //默认时间
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void onResetButtonClicked();    //启动服务器
    void onReconnectButtonClicked();//连接到服务器
    void onBeginButtonClicked();    //发送readyop开始游戏
    void onSetButtonClicked();      //设置用户名等信息
    void onDisconnectButtonClicked();//断开连接，发送leaveop

    void appendChatMessage(const QString &message);//聊天
signals://以下信号都是传给gamewidget，相应设置界面的按钮
    void settingsChanged(const QString &ip, int port);
    void startServer(int port);
    void connectToServer(const QString &ip, int port);
    void sets(QString color,QString name);//设置用户名和颜色
    void beginGame(OPCODE op, QString name, QString color);
    void disconnectAll();
    void sendChatMessage(const QString &message);
public slots:
    //判断是否连接上，更新状态
    void setConnectionStatus();
    //显示聊天的内容
    void onSendButtonClicked();
private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
