#include "Inscription.h"

Inscription::Inscription(QWidget* parent) : QWidget(parent), nameError(new QErrLabel(tr("È necessario inserire il nome"))), nameRequest(new QLineEdit()),
                                                             surnameError(new QErrLabel(tr("È necessario inserire il cognome"))), surnameRequest(new QLineEdit()),
                                                             usernameError(new QErrLabel(tr("È necessario inserire lo username"))), usernameRequest(new QLineEdit()),
                                                             passwordError(new QErrLabel(tr("È necessario inserire la password"))), passwordRequest(new QLineEdit()),
                                                             inscriptionFrame(new QFrame()){
    QVBoxLayout* inscriptionLayout = new QVBoxLayout(inscriptionFrame);

    QVBoxLayout* descriptionLayout = new QVBoxLayout();
    QVBoxLayout* nameLayout = new QVBoxLayout();
    QVBoxLayout* surnameLayout = new QVBoxLayout();
    QVBoxLayout* usernameLayout = new QVBoxLayout();
    QVBoxLayout* passwordLayout = new QVBoxLayout();
    QVBoxLayout* buttonsLayout = new QVBoxLayout();

    QLabel* description = new QLabel(tr("Inserisci i tuoi dati per registrarti"));
    QPushButton* sendButton = new QPushButton(tr("Iscriviti"));

    description->setFont(QFont("Helvetica", 12));
    nameRequest->setFont(QFont("Helvetica", 11));
    nameRequest->setMaximumSize(350, 30);
    nameRequest->setPlaceholderText(tr("Nome"));
    surnameRequest->setFont(QFont("Helvetica", 11));
    surnameRequest->setMaximumSize(350, 30);
    surnameRequest->setPlaceholderText(tr("Cognome"));
    usernameRequest->setFont(QFont("Helvetica", 11));
    usernameRequest->setMaximumSize(350, 30);
    usernameRequest->setPlaceholderText(tr("Username"));
    passwordRequest->setEchoMode(QLineEdit::Password);
    passwordRequest->setFont(QFont("Helvetica", 11));
    passwordRequest->setMaximumSize(350, 30);
    passwordRequest->setPlaceholderText(tr("Password"));
    sendButton->setCursor(QCursor(Qt::PointingHandCursor));
    sendButton->setFont(QFont("Helvetica", 12));
    sendButton->setFixedSize(150, 50);
    sendButton->setStyleSheet("QPushButton{background-color: rgba(6, 84, 49, 0.9); border-radius: 10px; color: white;}");

    descriptionLayout->addWidget(description);
    nameLayout->addWidget(nameError);
    nameLayout->addWidget(nameRequest);
    surnameLayout->addWidget(surnameError);
    surnameLayout->addWidget(surnameRequest);
    usernameLayout->addWidget(usernameError);
    usernameLayout->addWidget(usernameRequest);
    passwordLayout->addWidget(passwordError);
    passwordLayout->addWidget(passwordRequest);
    buttonsLayout->addWidget(sendButton, 0, Qt::AlignRight);

    inscriptionLayout->addLayout(descriptionLayout);
    inscriptionLayout->addLayout(nameLayout);
    inscriptionLayout->addLayout(surnameLayout);
    inscriptionLayout->addLayout(usernameLayout);
    inscriptionLayout->addLayout(passwordLayout);
    inscriptionLayout->addLayout(buttonsLayout);
    inscriptionLayout->setSizeConstraint(QLayout::SetMinimumSize);

    inscriptionFrame->move(mapToGlobal(QPoint(parentWidget()->rect().center().x() - inscriptionFrame->width()/4, parentWidget()->rect().center().y() - inscriptionFrame->height()/4)));
    inscriptionFrame->show();

    connect(sendButton, &QPushButton::clicked, this, &Inscription::sendInscription);

    setMaximumSize(400, 400);
    inscriptionFrame->setWindowTitle(tr("Iscrizione"));
}

void Inscription::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Return)
        QMetaObject::invokeMethod(this, "sendInscription");
}

void Inscription::showUserAlreadyExisting(){
    inscriptionFrame->show();
    usernameError->setText(tr("Questo username esiste già"));
    usernameError->setVisible(true);
}

void Inscription::sendInscription(){
    nameError->setVisible(false);
    surnameError->setVisible(false);
    usernameError->setText(tr("È necessario inserire lo username"));
    usernameError->setVisible(false);
    passwordError->setVisible(false);

    if(nameRequest->text().isEmpty())
        nameError->setVisible(true);
    if(surnameRequest->text().isEmpty())
        surnameError->setVisible(true);
    if(usernameRequest->text().isEmpty())
        usernameError->setVisible(true);
    if(passwordRequest->text().isEmpty())
        passwordError->setVisible(true);

    if(!nameError->isVisible() && !surnameError->isVisible() && !usernameError->isVisible() && !passwordError->isVisible()){
        inscriptionFrame->close();
        emit sendInscriptionInfo(nameRequest->text(), surnameRequest->text(), usernameRequest->text(), passwordRequest->text());
    }
}
