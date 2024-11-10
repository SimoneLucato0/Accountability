#include "CommonFundView.h"

CommonFundView::CommonFundView(const CommonFund &cf, QWidget *parent) : InnerPage(new CustomListWidget(cf.getMovements()), parent), commonFund(cf), userDifference(){
    name->setText(QString::fromStdString(commonFund.getName()));
    setBalance(commonFund.getBalance());
    addButtonL->setText(tr("Aggiungi utente"));
    QPushButton* showRecapButton = new QPushButton(tr("Resoconto"));
    QPushButton* addCommonEntryButton = new QPushButton(tr("Aggiungi entrata comune"));
    QPushButton* addFundRaiseButton = new QPushButton(tr("Aggiungi raccolta fondi"));
    QPushButton* addCommonExpenseButton = new QPushButton(tr("Aggiungi spesa comune"));

    buttonLayout->addWidget(showRecapButton);
    buttonLayout->addWidget(addFundRaiseButton);
    buttonLayout->addWidget(addCommonExpenseButton);
    buttonLayout->addWidget(addCommonEntryButton);

    connect(backButton, &QPushButtonAR::clicked, [this](){
        hide();
        emit showGroupView();
    });
    connect(addButtonL, &QPushButton::clicked, this, &CommonFundView::showAddUser);
    connect(showRecapButton, &QPushButton::clicked, this, &CommonFundView::showRecap);
    connect(addFundRaiseButton, &QPushButton::clicked, this, &CommonFundView::showAddFundRaise);
    connect(addCommonExpenseButton, &QPushButton::clicked, this, &CommonFundView::showAddCommonExpense);
    connect(addCommonEntryButton, &QPushButton::clicked, this, &CommonFundView::showAddCommonEntry);
}

olist<User> CommonFundView::getUsersInCommonFund() const{
    olist<User> aux;
    auto parts = commonFund.getPartecipations();
    for (olist<const Partecipation>::iterator cit = parts.begin(); cit != parts.end(); ++cit)
        aux.insert(cit->getUser());
    return aux;
}

void CommonFundView::setUserDifference(olist<const User> d){
    userDifference = d;
}

void CommonFundView::showAddUser(){
    olist<const User> userInCommonFund;
    for (auto i : commonFund.getPartecipations())
        userInCommonFund.insert(i.getUser());
    emit userDifferenceRequest(userInCommonFund);
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
            emit sendAddUsers(commonFund, users->getSelectedUsers());
            addUserFrame->close();
        }
        else
            usersMandatory->setVisible(true);
    });

    addUserFrame->show();
    addUserFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addUserFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addUserFrame->height()/2)));

}

void CommonFundView::showAddFundRaise(){
    QFrame* addFundRaiseFrame = new QFrame(nullptr, Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
    QVBoxLayout* addFundRaiseLayout = new QVBoxLayout(addFundRaiseFrame);
    QErrLabel* amountMandatory = new QErrLabel(tr("È necessario inserire l'importo"));
    QHBoxLayout* amountHelpLayout = new QHBoxLayout();
    QLineEdit* amountRequest = new QLineEdit();
    QErrLabel* descriptionMandatory = new QErrLabel(tr("È necessario inserire la descrizione"));
    QLineEdit* descriptionRequest = new QLineEdit();
    QLineEdit* noteRequest = new QLineEdit();
    QDateTimeEdit* dateRequest = new QDateTimeEdit(QDateTime::currentDateTime());
    QDoubleValidator* validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2);
    QWidget* singleContributions = new QWidget();
    QErrLabel* contributionsMandatory = new QErrLabel(tr("È obbligatorio inserire i contributi singoli"));
    QVBoxLayout* contributionsLayout = new QVBoxLayout(singleContributions);
    QLabel* description = new QLabel(tr("Inserisci l'importo dato accanto ad ogni persona"));
    UserInput* contributionsList = new UserInput(commonFund.getPartecipations());
    QPixmap qm(":/images/imgs/information.png");
    QPushButtonAR* helpButton = new QPushButtonAR();
    QPushButton* sendButton = new QPushButton(tr("Aggiungi"));

    amountRequest->setValidator(validator);
    amountRequest->setPlaceholderText(tr("Importo") + "*");
    descriptionRequest->setPlaceholderText(tr("Descrizione") + "*");
    noteRequest->setPlaceholderText(tr("Note"));
    helpButton->setIcon(qm);
    helpButton->setIconSize(QSize(30,30));

    amountHelpLayout->addWidget(amountRequest);
    amountHelpLayout->addWidget(helpButton, 0, Qt::AlignRight);
    contributionsLayout->addWidget(description);
    contributionsLayout->addWidget(contributionsMandatory);
    contributionsLayout->addWidget(contributionsList);
    contributionsLayout->setContentsMargins(0,0,0,0);
    addFundRaiseLayout->addWidget(amountMandatory);
    addFundRaiseLayout->addLayout(amountHelpLayout);
    addFundRaiseLayout->addWidget(descriptionMandatory);
    addFundRaiseLayout->addWidget(descriptionRequest);
    addFundRaiseLayout->addWidget(noteRequest);
    addFundRaiseLayout->addWidget(dateRequest);
    addFundRaiseLayout->addWidget(singleContributions);
    addFundRaiseLayout->addWidget(sendButton, 0, Qt::AlignRight);

    addFundRaiseFrame->show();
    addFundRaiseFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addFundRaiseFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addFundRaiseFrame->height()/2)));


    connect(helpButton, &QPushButton::clicked, [=](){
        QWhatsThis* wt;
        wt->showText(addFundRaiseFrame->mapToGlobal(QPoint(addFundRaiseFrame->rect().right() + 160, addFundRaiseFrame->rect().top())), tr("Inserisci l'importo raccolto a testa.\n"
                                                                                                                                          "Inserisci eventuali importi difformi raccolti in basso."));
        wt->enterWhatsThisMode();
    });

    connect(sendButton, &QPushButton::clicked, [=](){
        amountMandatory->setVisible(false);
        descriptionMandatory->setVisible(false);
        contributionsMandatory->setVisible(false);

        bool ok = true;
        if(amountRequest->text().isEmpty()){
           amountMandatory->setVisible(true);
           ok = false;
        }
        if(descriptionRequest->text().isEmpty()){
           descriptionMandatory->setVisible(true);
           ok = false;
        }
        std::map<QString, double> f;
        for (auto i : contributionsList->getResults()){
            if(i.second.isEmpty())
                f.insert({i.first, amountRequest->text().toDouble()});
            else
                f.insert({i.first, i.second.toDouble()});
        }
        if(ok){
            emit sendAddFundRaise(commonFund, descriptionRequest->text(), f, noteRequest->text(), dateRequest->dateTime().toSecsSinceEpoch());
            addFundRaiseFrame->close();
            list->refresh(commonFund.getMovements());
            setBalance(commonFund.getBalance());
        }
    });
}

void CommonFundView::showAddCommonExpense(){
    QFrame* addCommonExpenseFrame = new QFrame();
    QVBoxLayout* commonExpenseLayout = new QVBoxLayout(addCommonExpenseFrame);
    QHBoxLayout* amountHelpLayout = new QHBoxLayout();
    QErrLabel* amountMandatory = new QErrLabel(tr("È necessario inserire un importo positivo"));
    QLineEdit* amountRequest = new QLineEdit();
    QDoubleValidator* validator = new QDoubleValidator(0, DBL_MAX, 2);
    QErrLabel* descriptionMandatory = new QErrLabel(tr("È necessario inserire la descrizione"));
    QLineEdit* descriptionRequest = new QLineEdit();
    QLineEdit* noteRequest = new QLineEdit();
    QDateTimeEdit* dateRequest = new QDateTimeEdit(QDateTime::currentDateTime());

    QVBoxLayout* personalLayout = new QVBoxLayout();
    QCheckBox* personalExpensesCheck = new QCheckBox(tr("Qualcuno ha preso cose personali?"));
    QWidget* personalExpenses = new QWidget();
    QVBoxLayout* personalExpensesLayout = new QVBoxLayout(personalExpenses);
    UserInput* personalExpensesList = new UserInput(commonFund.getPartecipations());
    QCheckBox* personalPaymentsCheck = new QCheckBox(tr("Qualcuno ha contribuito di tasca propria?"));
    QWidget* personalPayments = new QWidget();
    QVBoxLayout* personalPaymentsLayout = new QVBoxLayout(personalPayments);
    UserInput* personalPaymentsList = new UserInput(*personalExpensesList);

    QPixmap qm(":/images/imgs/information.png");
    QPushButtonAR* helpButton = new QPushButtonAR();
    QPushButton* sendButton = new QPushButton(tr("Invia"));

    amountRequest->setValidator(validator);
    amountRequest->setPlaceholderText(tr("Importo") + "*");
    descriptionRequest->setPlaceholderText(tr("Descrizione") + "*");
    noteRequest->setPlaceholderText(tr("Note"));
    helpButton->setIcon(qm);
    helpButton->setIconSize(QSize(30,30));
    personalExpensesList->setVisible(false);
    personalPaymentsList->setVisible(false);

    amountHelpLayout->addWidget(amountRequest);
    amountHelpLayout->addWidget(helpButton, 0, Qt::AlignRight);
    personalExpensesLayout->addWidget(personalExpensesCheck);
    personalExpensesLayout->addWidget(personalExpensesList);
    personalPaymentsLayout->addWidget(personalPaymentsCheck);
    personalPaymentsLayout->addWidget(personalPaymentsList);
    personalLayout->addWidget(personalExpenses);
    personalLayout->addWidget(personalPayments);
    commonExpenseLayout->addWidget(amountMandatory);
    commonExpenseLayout->addLayout(amountHelpLayout);
    commonExpenseLayout->addWidget(descriptionMandatory);
    commonExpenseLayout->addWidget(descriptionRequest);
    commonExpenseLayout->addWidget(noteRequest);
    commonExpenseLayout->addWidget(dateRequest);
    commonExpenseLayout->addLayout(personalLayout);
    commonExpenseLayout->addWidget(sendButton, 0, Qt::AlignRight);

    connect(helpButton, &QPushButton::clicked, [=](){
        QWhatsThis* wt;
        wt->showText(addCommonExpenseFrame->mapToGlobal(QPoint(addCommonExpenseFrame->rect().right() + 160, addCommonExpenseFrame->rect().top())), tr("Inserisci la spesa complessiva.\n"
                                                                                                                                          "Se qualcuno si è preso qualcosa per sé, allora spunta il primo checkbox e inserisci la spesa accanto alla relativa persona.\n"
                                                                                                                                          "Se qualcuno ha anticipato soldi, allora spunta il secondo checkbox e inserisci quanti soldi ha anticipato accanto alla relativa persona."));
        wt->enterWhatsThisMode();
    });

    connect(personalPaymentsCheck, &QCheckBox::stateChanged, [=](int v){
        if(v == 2)
            personalPaymentsList->show();
        else if(v == 0){
            personalPaymentsList->hide();
            personalPaymentsList->clear();
        }
    });
    connect(personalExpensesCheck, &QCheckBox::stateChanged, [=](int v){
        if(v == 2)
            personalExpensesList->show();
        else if(v == 0){
            personalExpensesList->hide();
            personalExpensesList->clear();
        }
    });
    connect(sendButton, &QPushButton::clicked, [=](){
        amountMandatory->setVisible(false);
        descriptionMandatory->setVisible(false);

        bool ok = true;
        if(amountRequest->text().isEmpty()){
            amountMandatory->setVisible(true);
            ok = false;
        }
        if(descriptionRequest->text().isEmpty()){
            amountMandatory->setVisible(true);
            ok = false;
        }
        std::map<QString, double> pp = std::map<QString, double>();
        std::map<QString, double> pe = std::map<QString, double>();

        for(auto i : personalPaymentsList->getResults())
            if (!i.second.isEmpty())
                pp.insert({i.first, i.second.toDouble()});
        for(auto i : personalExpensesList->getResults())
            if (!i.second.isEmpty())
                pe.insert({i.first, i.second.toDouble()});

        if(ok){
            emit sendAddCommonExpense(commonFund, -amountRequest->text().toDouble(), descriptionRequest->text(), getUsersInCommonFund(), pe, pp, noteRequest->text(), dateRequest->dateTime().toSecsSinceEpoch());
            addCommonExpenseFrame->close();
            list->refresh(commonFund.getMovements());
            setBalance(commonFund.getBalance());
        }
    });

    addCommonExpenseFrame->show();
    addCommonExpenseFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addCommonExpenseFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addCommonExpenseFrame->height()/2)));


}

void CommonFundView::showAddCommonEntry(){
    QFrame* addCommonEntryFrame = new QFrame();
    QVBoxLayout* addCommonEntryLayout = new QVBoxLayout(addCommonEntryFrame);
    QHBoxLayout* amountHelpLayout = new QHBoxLayout();
    QErrLabel* amountMandatory = new QErrLabel(tr("È necessario inserire l'importo"));
    QLineEdit* amountRequest = new QLineEdit();
    QErrLabel* descriptionMandatory = new QErrLabel(tr("È necessario inserire la descrizione"));
    QLineEdit* descriptionRequest = new QLineEdit();
    QLineEdit* noteRequest = new QLineEdit();
    QDateTimeEdit* dateRequest = new QDateTimeEdit(QDateTime::currentDateTime());
    QDoubleValidator* validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2);
    QPixmap qm(":/images/imgs/information.png");
    QPushButtonAR* helpButton = new QPushButtonAR();
    QPushButton* sendButton = new QPushButton(tr("Aggiungi"));

    amountRequest->setValidator(validator);
    amountRequest->setPlaceholderText(tr("Importo") + "*");
    descriptionRequest->setPlaceholderText(tr("Descrizione") + "*");
    noteRequest->setPlaceholderText(tr("Note"));
    helpButton->setIcon(qm);
    helpButton->setIconSize(QSize(30,30));

    amountHelpLayout->addWidget(amountRequest);
    amountHelpLayout->addWidget(helpButton, 0, Qt::AlignRight);
    addCommonEntryLayout->addWidget(amountMandatory);
    addCommonEntryLayout->addLayout(amountHelpLayout);
    addCommonEntryLayout->addWidget(descriptionMandatory);
    addCommonEntryLayout->addWidget(descriptionRequest);
    addCommonEntryLayout->addWidget(noteRequest);
    addCommonEntryLayout->addWidget(dateRequest);
    addCommonEntryLayout->addWidget(sendButton, 0, Qt::AlignRight);

    addCommonEntryFrame->show();
    addCommonEntryFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addCommonEntryFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addCommonEntryFrame->height()/2)));


    connect(helpButton, &QPushButton::clicked, [=](){
        QWhatsThis* wt;
        wt->showText(addCommonEntryFrame->mapToGlobal(QPoint(addCommonEntryFrame->rect().right() + 160, addCommonEntryFrame->rect().top())), tr("L'importo corrisponde a una restituzione uguale per tutti della stessa somma di denaro."));
        wt->enterWhatsThisMode();
    });

    connect(sendButton, &QPushButton::clicked, [=](){
        amountMandatory->setVisible(false);
        descriptionMandatory->setVisible(false);

        bool ok = true;
        if(amountRequest->text().isEmpty()){
           amountMandatory->setVisible(true);
           ok = false;
        }
        if(descriptionRequest->text().isEmpty()){
           descriptionMandatory->setVisible(true);
           ok = false;
        }
        if(ok){
            emit sendAddCommonExpense(commonFund, amountRequest->text().toDouble(), descriptionRequest->text(), getUsersInCommonFund(), {}, {}, noteRequest->text(), dateRequest->dateTime().toSecsSinceEpoch());
            addCommonEntryFrame->close();
            list->refresh(commonFund.getMovements());
            setBalance(commonFund.getBalance());
        }
    });
}

void CommonFundView::showRecap(){
    QFrame* recapFrame = new QFrame();
    QGridLayout* recapLayout = new QGridLayout(recapFrame);
    int i = 0, j = 1;
    auto parts = commonFund.getPartecipations();
    for(olist<const Partecipation>::iterator cit = parts.begin(); cit != parts.end(); cit++, i++){
        QLabel* name = new QLabel(QString::fromStdString(cit->getUser().getName()));
        recapLayout->addWidget(name, 0, i+1);
    }
    i = 1;
    auto movs = commonFund.getMovements();
    for(olist<DeepPtr<AbstractGroupMovement>>::const_iterator citm = movs.begin(); citm != movs.end(); citm++, i++){
        QLabel* mvtName = new QLabel(QString::fromStdString((*citm)->getDescription()));
        recapLayout->addWidget(mvtName, i, 0);
        for(std::map<User, double>::const_iterator citu = (*citm)->getUserCreditChange().begin(); citu != (*citm)->getUserCreditChange().end(); citu++, j++){
            QLabel* amount = new QLabel(QString::number(citu->second));
            recapLayout->addWidget(amount, i, j);
        }
        j = 1;
    }
    j = 1;
    recapLayout->addWidget(new QLabel(tr("Totale")), i, 0);
    for(auto k  = parts.begin(); k != parts.end(); k++, j++)
        recapLayout->addWidget(new QLabel(QString::number(k->getCredit())), i, j);
    recapFrame->show();
    recapFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - recapFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - recapFrame->height()/2)));

}
