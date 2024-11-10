#include "GroupView.h"

GroupView::GroupView(const Group& g, const User& user, QWidget *parent) : InnerPage(new CustomListWidget(g.getCommonFunds()), parent), currentUser(user), group(g), userDifference(){
    name->setText(QString::fromStdString(group.getName()));
    addButtonL->setText(tr("Aggiungi cassa comune"));
    QPushButton* addUserButton = new QPushButton(tr("Aggiungi utente"));
    list->setStyleSheet("QListWidget::item:hover {background-color: rgba(67, 166, 40, 0.1)}");

    addUserButton->setMaximumSize(250, 50);

    buttonLayout->addWidget(addUserButton, 0, Qt::AlignRight);

    connect(backButton, &QPushButtonAR::clicked, [=](){
        hide();
        emit showHomePage();});
    connect(addUserButton, &QPushButton::clicked, this, &GroupView::showAddUser);
    connect(addButtonL, &QPushButton::clicked, this, &GroupView::showAddCommonFund);
    connect(list, &QListWidget::itemClicked, [=](QListWidgetItem* item){
        emit showCommonFund(static_cast<CustomListWidget::Box<const CommonFund>*>(item->listWidget()->itemWidget(item))->getItem());
    });

}

olist<const User> GroupView::getUsers() const{
    olist<const User> aux;
    for (auto i : group.getSubscriptions())
        aux.insert(i.getUser());
    return aux;
}

void GroupView::resetList(){
    list->resetVerticalScrollMode();
    list->scrollToTop();
    list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    list->refresh(group.getCommonFunds());
}

void GroupView::setUserDifference(const olist<const User> &d){
    userDifference = d;
}

void GroupView::showAddCommonFund(){
    QFrame* addCommonFundFrame = new QFrame();
    QVBoxLayout* addCommonFundLayout = new QVBoxLayout(addCommonFundFrame);
    QErrLabel* nameError = new QErrLabel(tr("Il nome della cassa comune non può essere vuoto"));
    QLineEdit* nameRequest = new QLineEdit();
    QLineEdit* balanceRequest = new QLineEdit();
    QDoubleValidator* validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2);

    olist<const User> u = olist<const User>();
    for (auto i : group.getSubscriptions()){
        if(!(i.getUser() == currentUser))
            u.insert(i.getUser());
    }
    users = new UserFilterList(u);
    QPushButton* sendButton = new QPushButton(tr("Invia"));

    nameRequest->setPlaceholderText(tr("Nome della cassa comune") + "*");
    nameRequest->setMaximumSize(250, 30);
    balanceRequest->setPlaceholderText(tr("Bilancio"));
    balanceRequest->setValidator(validator);

    addCommonFundLayout->addWidget(nameError);
    addCommonFundLayout->addWidget(nameRequest);
    addCommonFundLayout->addWidget(balanceRequest);
    addCommonFundLayout->addWidget(users);
    addCommonFundLayout->addWidget(sendButton, 0 , Qt::AlignRight);

    setMinimumSize(250, 250);

    addCommonFundFrame->show();
    addCommonFundFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addCommonFundFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addCommonFundFrame->height()/2)));


    connect(sendButton, &QPushButton::clicked, [=](){
        nameError->setVisible(false);
        if(!nameRequest->text().isEmpty()){
            emit sendAddCommonFund(group, nameRequest->text(), balanceRequest->text().toDouble(), users->getSelectedUsers());
            addCommonFundFrame->close();
            list->refresh(group.getCommonFunds());
        }
        else
            nameError->setVisible(true);
    });

}

void GroupView::showAddUser(){
    olist<const User> usersInGroup;
    for(auto i : group.getSubscriptions())
        usersInGroup.insert(i.getUser());
    emit userDifferenceRequest(usersInGroup);
    QFrame* addUserFrame = new QFrame();
    QVBoxLayout* addUserLayout = new QVBoxLayout(addUserFrame);
    QLabel* description = new QLabel(tr("Inserisci partecipanti"));
    QErrLabel* usersMandatory = new QErrLabel(tr("È necessario inserire i partecipanti"));
    UserFilterList* users = new UserFilterList(olist<const User>());
    QPushButton* sendButton = new QPushButton(tr("Invio"));

    users->setUsers(userDifference);

    addUserLayout->addWidget(description);
    addUserLayout->addWidget(usersMandatory);
    addUserLayout->addWidget(users);
    addUserLayout->addWidget(sendButton, 0, Qt::AlignRight);

    connect(sendButton, &QPushButton::clicked, [=](){
       usersMandatory->setVisible(false);
       if(!(users->getSelectedUsers() == olist<QString>())){
           emit sendAddUsers(group, users->getSelectedUsers());
           addUserFrame->close();
       }
       else
           usersMandatory->setVisible(true);
    });

    addUserFrame->show();
    addUserFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addUserFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addUserFrame->height()/2)));

}
