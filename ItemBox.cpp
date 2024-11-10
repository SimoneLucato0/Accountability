#include "ItemBox.h"

void ItemBox::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    itemFrame->setGeometry(QRect(QPoint(0, 0), event->size()));
}

ItemBox::ItemBox(QWidget* parent) : QWidget(parent){
    itemFrame = new QFrame(this);
    QHBoxLayout* itemLayout = new QHBoxLayout(itemFrame);
    QVBoxLayout* leftLayout = new QVBoxLayout();
    name = new QLabel();
    date = new QLabel();
    amount = new QLabel();

    itemFrame->setFrameShape(QFrame::Box);
    name->setFont(QFont("Helvetica", 10));
    date->setFont(QFont("Helvetica", 10));
    amount->setFont(QFont("Helvetica", 10));


    leftLayout->addWidget(name);
    leftLayout->addWidget(date);
    itemLayout->addLayout(leftLayout);
    itemLayout->addWidget(amount, 0 , Qt::AlignRight);
    itemLayout->setContentsMargins(11,11,14,11);

    setMinimumSize(400,150);
}

void ItemBox::setName(const QString &n){
    name->setText(n);
}

void ItemBox::setDate(const QString &d){
    date->setText(d);
}

void ItemBox::setAmount(const double &a){
    amount->setText(QString::number(a));
    if(amount->text().toDouble() > 0)
        amount->setStyleSheet("QLabel{color: green;}");
    else
        amount->setStyleSheet("QLabel{color: red;}");
}

