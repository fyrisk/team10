#include "readydialog.h"
#include <QPushButton>
#include <QVBoxLayout>

ReadyDialog::ReadyDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    readyButton = new QPushButton("Ready", this);
    layout->addWidget(readyButton);
    connect(readyButton, &QPushButton::clicked, this, &ReadyDialog::readyClicked);

    rejectButton = new QPushButton("Reject", this);
    layout->addWidget(rejectButton);
    connect(rejectButton, &QPushButton::clicked, this, &ReadyDialog::rejectClicked);

    setLayout(layout);
}

ReadyDialog::~ReadyDialog()
{
}
