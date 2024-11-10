#include "InnerPage.h"

void InnerPage::setBalance(const double &b){
    balance->setText(QString::number(b));
    if(b >= 0)
        balance->setStyleSheet("QLabel{color:green;}");
    else
        balance->setStyleSheet("QLabel{color:red;}");
}

InnerPage::InnerPage(CustomListWidget* l, QWidget *parent) : QWidget(parent), backButton(new QPushButtonAR()), name(new QLabel()), balance(new QLabel()),
                                                             addButtonL(new QPushButton()), buttonLayout(new QHBoxLayout()), list(l){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* headerLayout = new QHBoxLayout();
    QPixmap backPm (":/images/imgs/back-button.png");
    QFrame* listFrame = new QFrame(this);
    QVBoxLayout* listLayout = new QVBoxLayout(listFrame);

    name->setFont(QFont("Helvetica", 20));
    balance->setFont(QFont("Helvetica", 15));
    backButton->setIcon(backPm);
    backButton->setIconSize(QSize(40,40));
    backButton->setMaximumSize(QSize(50,50));
    addButtonL->setMaximumSize(250, 50);


    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(name, 0, Qt::AlignJustify);
    headerLayout->addWidget(balance, 0, Qt::AlignJustify);
    buttonLayout->addWidget(addButtonL);
    buttonLayout->setAlignment(Qt::AlignRight);
    buttonLayout->setSpacing(1);
    listLayout->addLayout(buttonLayout);
    listLayout->addWidget(list);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(listFrame);

    setContentsMargins(0,0,0,0);
}
