#include "Login.h"

QSize Login::minimumSizeHint() const{
    return QSize(qApp->screens()[0]->size().width()/4, qApp->screens()[0]->size().height()/3);
}

Login::Login(QWidget* parent) : QWidget(parent){
    QGridLayout* loginLayout = new QGridLayout(this);

    QVBoxLayout* formLayout = new QVBoxLayout();
    QVBoxLayout* userLayout = new QVBoxLayout();
    QVBoxLayout* passwordLayout = new QVBoxLayout();

    QLabel* descriptionText = new QLabel(tr("Inserisci le credenziali per proseguire con l'accesso"));
    userError = new QErrLabel(tr("È necessario inserire lo username"));
    userRequest = new QLineEdit();
    passwordError = new QErrLabel(tr("È necessario inserire la password"));
    passwordRequest = new QLineEdit();
    QPushButtonAR* inscriptionButton = new QPushButtonAR(tr("Crea un nuovo account"));
    QPushButtonAR* sendButton = new QPushButtonAR(tr("Accedi"));

    QFont f("Helvetica", 12);
    f.setUnderline(true);

    descriptionText->setFont(QFont("Helvetica", 14, 57));
    descriptionText->setStyleSheet("QLabel{color: rgba(6, 84, 49, 0.9);}");
    QSizePolicy user_rs = userError->sizePolicy();
    user_rs.setRetainSizeWhenHidden(true);
    userError->setSizePolicy(user_rs);
    userRequest->setFont(QFont("Helvetica", 12));
    userRequest->setPlaceholderText(tr("Username"));
    QSizePolicy password_rs = passwordError->sizePolicy();
    password_rs.setRetainSizeWhenHidden(true);
    passwordError->setSizePolicy(password_rs);
    passwordRequest->setEchoMode(QLineEdit::Password);
    passwordRequest->setFont(QFont("Helvetica", 12));
    passwordRequest->setPlaceholderText(tr("Password"));
    inscriptionButton->setCursor(QCursor(Qt::PointingHandCursor));
    inscriptionButton->setFont(f);
    inscriptionButton->setMaximumSize(500, 75);
    inscriptionButton->setStyleSheet("QPushButton{background-color: transparent; border-style: outset; color: rgba(6, 84, 49, 0.9);}");
    sendButton->setCursor(QCursor(Qt::PointingHandCursor));
    sendButton->setFont(QFont("Helvetica", 12));
    sendButton->setMaximumSize(150, 50);
    sendButton->setStyleSheet("QPushButton{background-color: rgba(6, 84, 49, 0.9); border-radius: 10px; color: white;} "
                              "QPushButton:hover{background-color: rgba(6, 70, 41, 0.9); border-radius: 10px; color: white;}"
                              "QPushButton:focus { border: none; outline: none; }");

    userLayout->addWidget(userError);
    userLayout->addWidget(userRequest);
    userLayout->setSpacing(2);
    userLayout->setContentsMargins(0,0,0,0);
    passwordLayout->addWidget(passwordError);
    passwordLayout->addWidget(passwordRequest);
    passwordLayout->setSpacing(2);
    passwordLayout->setContentsMargins(0,0,0,0);
    formLayout->addLayout(userLayout);
    formLayout->addLayout(passwordLayout);
    userLayout->setSizeConstraint(QLayout::SetMinimumSize);
    passwordLayout->setSizeConstraint(QLayout::SetMinimumSize);
    formLayout->setSizeConstraint(QLayout::SetMinimumSize);

    loginLayout->addWidget(descriptionText, 0, 0, 1, -1);
    loginLayout->addLayout(formLayout, 1, 0, 1, -1);
    loginLayout->addWidget(inscriptionButton, 3, 0, 1, 2);
    loginLayout->addWidget(sendButton, 3, 2, 1, 1);
    loginLayout->setSpacing(5);
    loginLayout->setSizeConstraint(QLayout::SetMinimumSize);

    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    setMinimumSize(qApp->screens()[0]->size().width()/4, qApp->screens()[0]->size().height()/3);
    setLayout(loginLayout);

    connect(inscriptionButton, &QPushButton::clicked, [this](){emit showInscriptionBox();});
    connect(sendButton, &QPushButton::clicked, this, &Login::sendLogin);

}

void Login::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Return)
        QMetaObject::invokeMethod(this, "sendLogin");
}

void Login::sendLogin(){
    userError->setVisible(false);
    passwordError->setVisible(false);
    bool ok = true;
    if (userRequest->text().isEmpty()){
        userError->setText(tr("È necessario inserire lo username"));
        userError->setVisible(true);
        ok = false;
    }
    if (passwordRequest->text().isEmpty()){
        passwordError->setText(tr("È necessario inserire la password"));
        passwordError->setVisible(true);
        ok = false;
    }
    if(ok)
        emit sendLoginInfo(userRequest->text(), passwordRequest->text());
}

void Login::showUserNotExisting(){
    userError->setText(tr("Le credenziali inserite non corrispondono a nessun utente. Riprova"));
    userError->setVisible(true);
}

void Login::showIncorrectPassword(){
    passwordError->setText(tr("La password inserita non è corretta"));
    passwordError->setVisible(true);
}
