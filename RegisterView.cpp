#include "RegisterView.h"

RegisterView::RegisterView(const Register &r, QWidget *parent) : InnerPage(new CustomListWidget(r.getMovements()), parent), reg(r){
    name->setText(QString::fromStdString(reg.getName()));
    setBalance(reg.getBalance());
    addButtonL->setText(tr("Aggiungi movimento"));

    connect(backButton, &QPushButtonAR::clicked, [this](){
        hide();
        emit showHomePage();
    });
    connect(addButtonL, &QPushButtonAR::clicked, this, &RegisterView::showAddMovement);
}

void RegisterView::showAddMovement(){
    QFrame* addMovementFrame = new QFrame();
    QVBoxLayout* addMovementLayout = new QVBoxLayout(addMovementFrame);
    QHBoxLayout* amountHelpLayout = new QHBoxLayout();
    QErrLabel* amountError = new QErrLabel(tr("È necessario inserire l'importo"));
    QLineEdit* amountRequest = new QLineEdit();
    QDoubleValidator* validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2);
    QErrLabel* descriptionError = new QErrLabel(tr("È necessario inserire la descrizione del movimento"));
    QLineEdit* descriptionRequest = new QLineEdit();
    QLineEdit* noteRequest = new QLineEdit();
    QDateTimeEdit* dateRequest = new QDateTimeEdit(QDateTime::currentDateTime());
    QPixmap qm(":/images/imgs/information.png");
    QPushButtonAR* helpButton = new QPushButtonAR();
    QPushButton* sendButton = new QPushButton(tr("Invia"));

    amountRequest->setPlaceholderText(tr("Importo") + "*");
    amountRequest->setValidator(validator);
    descriptionRequest->setPlaceholderText(tr("Descrizione") + "*");
    noteRequest->setPlaceholderText(tr("Note"));
    helpButton->setIcon(qm);
    helpButton->setIconSize(QSize(30,30));

    amountHelpLayout->addWidget(amountRequest);
    amountHelpLayout->addWidget(helpButton, 0, Qt::AlignRight);
    addMovementLayout->addWidget(amountError);
    addMovementLayout->addLayout(amountHelpLayout);
    addMovementLayout->addWidget(descriptionError);
    addMovementLayout->addWidget(descriptionRequest);
    addMovementLayout->addWidget(noteRequest);
    addMovementLayout->addWidget(dateRequest);
    addMovementLayout->addWidget(sendButton, 0, Qt::AlignRight);
    addMovementLayout->setSizeConstraint(QLayout::SetMinimumSize);

    addMovementFrame->show();
    addMovementFrame->move(mapToGlobal(QPoint(parentWidget()->rect().left() + parentWidget()->width()/2 - addMovementFrame->width()/2, parentWidget()->rect().top() + parentWidget()->height()/2 - 150 - addMovementFrame->height()/2)));


    connect(helpButton, &QPushButton::clicked, [=](){
        QWhatsThis* wt;
        wt->showText(addMovementFrame->mapToGlobal(QPoint(addMovementFrame->rect().right() + 160, addMovementFrame->rect().top())), tr("Se è una spesa inserisci il segno meno davanti."));
        wt->enterWhatsThisMode();
    });

    connect(sendButton, &QPushButton::clicked, [=](){
        amountError->setVisible(false);
        descriptionError->setVisible(false);
        if (amountRequest->text().isEmpty())
            amountError->setVisible(true);
        else if (!descriptionRequest->text().isEmpty()){
            emit sendAddMovement(reg, amountRequest->text().toDouble(), descriptionRequest->text(), noteRequest->text(), dateRequest->dateTime().toSecsSinceEpoch());
            addMovementFrame->close();
            list->refresh(reg.getMovements());
            setBalance(reg.getBalance());
        }
        if (descriptionRequest->text().isEmpty())
            descriptionError->setVisible(true);
    });
}

