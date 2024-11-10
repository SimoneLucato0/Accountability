#include "UserInput.h"

UserInput::UserInput(olist<const Partecipation> us, QWidget *parent) : QWidget(parent), u(us){
    mainLayout = new QVBoxLayout(this);
    setLayout(u);
    setContentsMargins(0,0,0,0);
}

UserInput::UserInput(const UserInput &us, QWidget* parent) : QWidget(parent), u(us.getPartecipations()){
    mainLayout = new QVBoxLayout(this);
    setLayout(us.getPartecipations());
    setContentsMargins(0,0,0,0);
}

void UserInput::clear(){
    for(int i = 0; i < mainLayout->count(); ++i){
        QHBoxLayout* box = static_cast<QHBoxLayout*>(mainLayout->itemAt(i));
        QLineEdit* amount = static_cast<QLineEdit*>(box->itemAt(1)->widget());
        amount->clear();
    }
}

bool UserInput::isEmpty() const{
    bool empty = true;
    for(int i = 0; i < mainLayout->count() && empty; ++i){
        QHBoxLayout* box = static_cast<QHBoxLayout*>(mainLayout->itemAt(i));
        QLineEdit* amount = static_cast<QLineEdit*>(box->itemAt(1)->widget());
        if(!amount->text().isEmpty())
            empty = false;
    }
    return empty;
}

std::map<QString, QString> UserInput::getResults() const{
    std::map<QString, QString> aux = std::map<QString, QString>();
    for(int i = 0; i < mainLayout->count(); ++i){
        QHBoxLayout* box = static_cast<QHBoxLayout*>(mainLayout->itemAt(i));
        QLabel* name = static_cast<QLabel*>(box->itemAt(0)->widget());
        QLineEdit* amount = static_cast<QLineEdit*>(box->itemAt(1)->widget());
        aux.insert(std::pair<QString, QString>(name->text(), amount->text().isEmpty() ? 0 : amount->text()));
    }
    return aux;
}

olist<const Partecipation> UserInput::getPartecipations() const{
    return u;
}

void UserInput::setLayout(olist<const Partecipation> users){
    for(auto i : users){
        QHBoxLayout* singleLayout = new QHBoxLayout();
        QLabel* name = new QLabel(QString::fromStdString(i.getUser().getUsername()));
        QLineEdit* amount = new QLineEdit();
        QDoubleValidator* validator = new QDoubleValidator(0, DBL_MAX, 2);
        amount->setPlaceholderText("Importo");
        amount->setValidator(validator);
        singleLayout->addWidget(name);
        singleLayout->addWidget(amount);
        mainLayout->addLayout(singleLayout);
    }
}
