#ifndef OPENWIDGET_H
#define OPENWIDGET_H

#include <QWidget>
#include <QPushButton>

class OpenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenWidget(QWidget *parent = nullptr);

signals:
    void beginButtonClicked();

private:
    QPushButton *beginButton;
};

#endif // OPENWIDGET_H
