#include "HomePage.h"

HomePage::HomePage(User& u, olist<const User> allUsers, QWidget *parent) : QWidget(parent), user(u), allUserList(allUsers){
    QHBoxLayout* homeLayout = new QHBoxLayout(this);
    QHBoxLayout* accountHeader = new QHBoxLayout();
    QHBoxLayout* groupHeader = new QHBoxLayout();

    QFrame* accountFrame = new QFrame(this);
    QVBoxLayout* accountLayout = new QVBoxLayout(accountFrame);
    QFrame* groupFrame = new QFrame(this);
    QVBoxLayout* groupLayout = new QVBoxLayout(groupFrame);

    QLabel* accountLabel = new QLabel(tr("I miei conti"));
    QPixmap addPm (":/images/imgs/add.png");
    QPushButtonAR* addRegisterButton = new QPushButtonAR();
    registerList = new CustomListWidget(user.getRegisters());

    accountFrame->setFrameShape(QFrame::Box);
    accountLabel->setFont(QFont("Helvetica", 12));
    accountLabel->setStyleSheet("QLabel{color: rgba(6, 84, 49, 0.9);}");
    addRegisterButton->setIcon(addPm);
    addRegisterButton->setIconSize(QSize(40, 40));
    addRegisterButton->setMaximumSize(QSize(50,50));


    QLabel* groupLabel = new QLabel(tr("I miei gruppi"));
    QPushButtonAR* addGroupButton = new QPushButtonAR();
    groupList = new CustomListWidget(user.getSubscriptions(), static_cast<const Group*>(nullptr));

    groupFrame->setFrameShape(QFrame::Box);
    groupLabel->setFont(QFont("Helvetica", 12));
    groupLabel->setStyleSheet("QLabel{color: rgba(6, 84, 49, 0.9);}");
    addGroupButton->setIcon(addPm);
    addGroupButton->setIconSize(QSize(40, 40));
    addGroupButton->setMaximumSize(QSize(50,50));


    accountHeader->addWidget(accountLabel, 0 , Qt::AlignHCenter);
    accountHeader->addWidget(addRegisterButton, 0, Qt::AlignRight);
    accountLayout->addLayout(accountHeader);
    accountLayout->addWidget(registerList);

    groupHeader->addWidget(groupLabel, 0, Qt::AlignCenter);
    groupHeader->addWidget(addGroupButton, 0, Qt::AlignRight);
    groupLayout->addLayout(groupHeader);
    groupLayout->addWidget(groupList);


    homeLayout->addWidget(accountFrame);
    homeLayout->addWidget(groupFrame);

    setLayout(homeLayout);

    connect(addRegisterButton, &QPushButtonAR::clicked, this, &HomePage::showAddRegister);
    connect(addGroupButton, &QPushButtonAR::clicked, this, &HomePage::showAddGroup);
    connect(registerList, &QListWidget::itemClicked, [=](QListWidgetItem* item){
        emit showRegister(static_cast<CustomListWidget::Box<const Register>*>(item->listWidget()->itemWidget(item))->getItem());
    });
    connect(groupList, &QListWidget::itemClicked, [=](QListWidgetItem* item){
        emit showGroup(static_cast<CustomListWidget::Box<const Group>*>(item->listWidget()->itemWidget(item))->getItem());
    });
}

void HomePage::resetLists(){
    registerList->resetVerticalScrollMode();
    registerList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    registerList->scrollToTop();
    registerList->refresh(user.getRegisters());
    groupList->resetVerticalScrollMode();
    groupList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    groupList->scrollToTop();
    groupList->refresh<const Subscription, const Group>(user.getSubscriptions());
}

void HomePage::setUserList(const olist<const User>& u){
    allUserList = u;
}

void HomePage::showAddRegister(){
    QFrame* addRegisterFrame = new QFrame();
    QVBoxLayout* addRegisterLayout = new QVBoxLayout(addRegisterFrame);
    QVBoxLayout* nameLayout = new QVBoxLayout();
    QVBoxLayout* balanceLayout = new QVBoxLayout();

    QErrLabel* accountNameError = new QErrLabel(tr("È necessario inserire il nome dell'account"));
    QLineEdit* accountNameRequest = new QLineEdit();
    QLineEdit* balanceRequest = new QLineEdit();
    QPushButton* sendButton = new QPushButton("Invio");
    QDoubleValidator* validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2);

    accountNameRequest->setPlaceholderText(tr("Nome dell'account") + "*");
    accountNameRequest->setMaximumSize(250, 30);
    balanceRequest->setPlaceholderText(tr("Bilancio"));
    balanceRequest->setMaximumSize(250, 30);
    balanceRequest->setValidator(validator);
    QSizePolicy name_sr = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name_sr.setRetainSizeWhenHidden(true);
    accountNameError->setSizePolicy(name_sr);

    nameLayout->addWidget(accountNameError);
    nameLayout->addWidget(accountNameRequest);
    nameLayout->setContentsMargins(0,0,0,0);
    nameLayout->setSpacing(5);
    balanceLayout->addWidget(balanceRequest);

    addRegisterLayout->addLayout(nameLayout);
    addRegisterLayout->addLayout(balanceLayout);
    addRegisterLayout->addWidget(sendButton, 0, Qt::AlignRight);
    addRegisterLayout->setSizeConstraint(QLayout::SetFixedSize);

    addRegisterFrame->show();
    addRegisterFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addRegisterFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addRegisterFrame->height()/2)));

    connect(sendButton, &QPushButton::clicked, [=](){
        accountNameError->setVisible(false);
        if(accountNameRequest->text().isEmpty())
            accountNameError->setVisible(true);
        else{
            emit sendAddRegisterInfo(accountNameRequest->text(), user, balanceRequest->text().toDouble(), std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
            addRegisterFrame->close();
            registerList->refresh(user.getRegisters());
        }
    });
}

void HomePage::showAddGroup(){
    QFrame* addGroupFrame = new QFrame();
    QVBoxLayout* addGroupLayout = new QVBoxLayout(addGroupFrame);
    QVBoxLayout* nameLayout = new QVBoxLayout();
    QVBoxLayout* descriptionLayout = new QVBoxLayout();

    QErrLabel* nameError = new QErrLabel(tr("È necessario inserire il nome del gruppo"));
    QLineEdit* nameRequest = new QLineEdit();
    QLineEdit* descriptionRequest = new QLineEdit();
    users = new UserFilterList(allUserList);

    QPushButton* sendButton = new QPushButton(tr("Invia"));

    nameRequest->setPlaceholderText(tr("Nome del gruppo") + "*");
    descriptionRequest->setPlaceholderText(tr("Descrizione del gruppo"));

    nameLayout->addWidget(nameError);
    nameLayout->addWidget(nameRequest);
    descriptionLayout->addWidget(descriptionRequest);
    addGroupLayout->addLayout(nameLayout);
    addGroupLayout->addLayout(descriptionLayout);
    addGroupLayout->addWidget(users);
    addGroupLayout->addWidget(sendButton, 0, Qt::AlignRight);

    addGroupFrame->show();
    addGroupFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addGroupFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addGroupFrame->height()/2)));

    
    connect(sendButton, &QPushButton::clicked, [=](){
        nameError->setVisible(false);
        if(nameRequest->text().isEmpty())
            nameError->setVisible(true);
        else{
            emit sendAddGroupInfo(nameRequest->text(), user, descriptionRequest->text(), users->getSelectedUsers());
            groupList->refresh<const Subscription, const Group>(user.getSubscriptions());
            addGroupFrame->close();
        }
    });
}
