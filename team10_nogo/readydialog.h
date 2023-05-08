#ifndef READYDIALOG_H
#define READYDIALOG_H

#include <QDialog>

class QPushButton;

class ReadyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadyDialog(QWidget *parent = nullptr);
    ~ReadyDialog();

signals:
    void readyClicked();
    void rejectClicked();

private:
    QPushButton *readyButton;
    QPushButton *rejectButton;
};

#endif // READYDIALOG_H
