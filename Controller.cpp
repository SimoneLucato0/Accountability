#include "Controller.h"

Controller::Controller(QObject* parent) : QObject(parent){}

void Controller::setModel(Model* model){m = model; }

void Controller::setView(View *view){v = view; }

 olist<const User> Controller::getUserList() const{
    return m->getUsers();
}

olist<const User> Controller::getUserDifference(const olist<const User> &all, const olist<const User> &part){
    olist<const User> aux;
    for(olist<const User>::const_iterator cit = all.begin(); cit != all.end(); ++cit){
        if(!part.contains(*cit))
            aux.insert(*cit);
    }
    return aux;
}

void Controller::addCommonFund(Group& g, User& u, const QString& name, double balance, olist<QString> users){
    CommonFund f(g, u, name.toStdString(), balance);
    for(auto i : users){
        User u = m->getUserByUsername(i.toStdString());
        Partecipation(u, f, 0);
    }
}

void Controller::addCommonExpense(CommonFund& cf, const User& u, double amount, const QString &description, olist<User> users, const std::map<QString, double> &personalExpense, const std::map<QString, double> &personalShares, const QString &note, time_t ts){
    std::map<User, double> pe = std::map<User, double>();
    std::map<User, double> pp = std::map<User, double>();
    for(auto i : personalExpense)
        pe.insert(std::pair<User, double>(m->getUserByUsername(i.first.toStdString()), i.second));
    for (auto i : personalShares)
        pp.insert(std::pair<User, double>(m->getUserByUsername(i.first.toStdString()), i.second));

    CommonExpense ce(cf, amount, u, description.toStdString(), users, pe, pp, note.toStdString(), ts);
}

void Controller::addFundRaise(CommonFund &cf, const User &u, const QString &description, const std::map<QString, double> &contributions, const QString &note, time_t ts){
    std::map<User, double> c = std::map<User, double>();
    for(auto i : contributions)
        c.insert(std::pair<User, double>(m->getUserByUsername(i.first.toStdString()), i.second));
    FundRaise f(cf, u, description.toStdString(), c, note.toStdString(), ts);
}

void Controller::addRegister(const QString& name, User& u, double balance, std::time_t time) const{
    Register r(u, name.toStdString(), balance, time);
}

void Controller::addGroup(const QString &name, User& u, const QString &description, const olist<QString> &userList){
    Group g(m, name.toStdString(), description.toStdString(), u);
    for(olist<QString>::const_iterator cit = userList.begin(); cit != userList.end(); ++cit){
        User u(m->getUserByUsername(cit->toStdString()));
        Subscription s(u, g, std::time_t(nullptr));
    }
}

void Controller::addUserMovement(Register& r, double amount, const QString &description, const QString &note, time_t ts){
    UserMovement(r, amount, description.toStdString(), note.toStdString(), ts);
}

void Controller::addUserToCommonFund(CommonFund &cf, olist<QString> users){
    for(auto i : users){
        User u = m->getUserByUsername(i.toStdString());
        Partecipation(u, cf, 0);
    }
}

void Controller::addUserToGroup(Group& g, olist<QString> users){
    for(auto i : users){
        User u = m->getUserByUsername(i.toStdString());
        Subscription(u, g, std::time(nullptr));
    }
}

void Controller::logIn(const QString& user, const QString& password) const{
    User u(m, user.toStdString());
    if(u)
        u.checkPw(password.toStdString()) ? v->showHomePage(u) : v->showIncorrectPassword();
    else
        v->showUserNotExisting();
}

void Controller::createUser(const QString &name, const QString &surname, const QString &username, const QString &password) const{
    User u(m, username.toStdString(), name.toStdString(), surname.toStdString(), password.toStdString());
    u ? v->showHomePage(u) : v->showUserAlreadyExisting();
}
