#include "settingswindow.h"
#include "ui_settingswindow.h"
SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->ui->ipEdit->setText("127.0.0.1");
    this->ui->portEdit->setText(QString::number(16667));
    this->ui->textEdit->setReadOnly(true);
    connect(ui->reSetButton, &QPushButton::clicked, this, &SettingsWindow::onResetButtonClicked);
    connect(ui->reConnectButton, &QPushButton::clicked, this, &SettingsWindow::onReconnectButtonClicked);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &SettingsWindow::onDisconnectButtonClicked);
    connect(ui->setButton, &QPushButton::clicked, this, &SettingsWindow::onSetButtonClicked);
    connect(ui->beginButton, &QPushButton::clicked, this, &SettingsWindow::onBeginButtonClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &SettingsWindow::onSendButtonClicked);

    //connect(this, &SettingsWindow::settingsChanged, this, &GameWidget::updateSettings);

}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
void SettingsWindow::onResetButtonClicked()
{
    QString ip = ui->ipEdit->text(); // 获取用户输入的 IP 地址。
    int port = ui->portEdit->text().toInt(); // 获取用户输入的端口号。

    // 执行其他重置操作...

    // 在重置完成后，触发 settingsChanged 信号。
    emit startServer(port);
    qDebug()<<"start reset";
   // emit settingsChanged(ip, port);
}

void SettingsWindow::onReconnectButtonClicked()
{
    QString ip = ui->ipEdit->text(); // 获取用户输入的 IP 地址。
    int port = ui->portEdit->text().toInt(); // 获取用户输入的端口号。

    // 执行其他重连操作...

    // 在重连完成后，触发 settingsChanged 信号。
    emit connectToServer(ip, port);
   // emit settingsChanged(ip, port);
}
void SettingsWindow::onSetButtonClicked()
{
    if(ui->timeEdit->text()!="") time=ui->timeEdit->text().toInt();
    QString selectedColor = ui->usercolorBox->currentText();
    QString userName=ui->usernameEdit->text();
    emit sets(selectedColor,userName);
}
//客户端发给服务端
void SettingsWindow::onBeginButtonClicked()
{
    if(ui->timeEdit->text()!="") time=ui->timeEdit->text().toInt();
    QString selectedColor = ui->usercolorBox->currentText();
    qDebug()<<"selectedColor ="<<selectedColor;
    QString userName=ui->usernameEdit->text();
    emit beginGame(OPCODE::READY_OP,userName,selectedColor);
    qDebug()<<"color  =  "<<selectedColor;
    qDebug()<<"time  =  "<<time;
}
void SettingsWindow::setConnectionStatus()
{
    connected=1;//意味着作为客户端
    ui->connectLabel->setText("connection succeed");
    qDebug()<<"start setConnectionStatus";
}
void SettingsWindow::onDisconnectButtonClicked()
{
    emit disconnectAll();
}
void SettingsWindow::onSendButtonClicked()
{
    QString message = ui->sendEdit->text().trimmed();
    if (!message.isEmpty())
    {
        emit sendChatMessage(message);
        ui->sendEdit->clear();
    }
}
void SettingsWindow::appendChatMessage(const QString &message)
{
    ui->textEdit->append(message);
}







