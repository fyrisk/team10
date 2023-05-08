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
    int connected=0;
    int time=60;
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void onResetButtonClicked();
    void onReconnectButtonClicked();
    void onBeginButtonClicked();
    void onSetButtonClicked();
    void onDisconnectButtonClicked();
    void appendChatMessage(const QString &message);
signals:
    void settingsChanged(const QString &ip, int port);
    void startServer(int port);
    void connectToServer(const QString &ip, int port);
    void sets(QString color,QString name);
    void beginGame(OPCODE op, QString name, QString color);
    void disconnectAll();
    void sendChatMessage(const QString &message);
public slots:
    void setConnectionStatus();
    void onSendButtonClicked();
private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
