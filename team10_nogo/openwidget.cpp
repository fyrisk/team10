#include "openwidget.h"

OpenWidget::OpenWidget(QWidget *parent) : QWidget(parent)
{
    beginButton = new QPushButton("Begin", this);
    connect(beginButton, &QPushButton::clicked, this, &OpenWidget::beginButtonClicked);
}
