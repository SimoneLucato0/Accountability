#include "Header.h"

Header::Header(QWidget* parent) : QWidget(parent){
    QFrame* headerFrame = new QFrame(this);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerFrame);

    QPixmap homePm (":/images/imgs/home.png");
    QPixmap quitPm(":/images/imgs/logout.png");

    homeButton = new QPushButtonAR();
    exitButton = new QPushButtonAR();

    homeButton->setIcon(homePm);
    homeButton->setIconSize(QSize(75,75));
    homeButton->setMaximumSize(QSize(150,150));
    homeButton->setVisible(false);
    exitButton->setIcon(quitPm);
    exitButton->setIconSize(QSize(75,75));
    exitButton->setMaximumSize(QSize(150,150));

    headerLayout->addWidget(homeButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(exitButton, 0, Qt::AlignRight);

    connect(homeButton, &QPushButton::clicked, [this](){emit showHomePage();});
    connect(exitButton, &QPushButton::clicked, this, &Header::showQuitConfirm);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMaximumHeight(150);
    setLayout(headerLayout);
}

void Header::showHomeButton(){
    homeButton->setVisible(true);
}

void Header::showQuitConfirm(){
    QMessageBox* quitBox = new QMessageBox();
    QPushButton* yesButton = quitBox->addButton(tr("Sì"), QMessageBox::YesRole);
    quitBox->addButton(tr("No"), QMessageBox::NoRole);
    quitBox->setDefaultButton(yesButton);
    quitBox->setText(tr("Sei sicuro di voler uscire?"));

    quitBox->exec();

    if(quitBox->clickedButton() == yesButton)
        emit closeAll();

}

