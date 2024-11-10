#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"
#include "View.h"

#include "user.h"
#include "register.h"
#include "usermovement.h"
#include "group.h"
#include "commonfund.h"
#include "fundraise.h"
#include "commonexpense.h"

class View;

class Controller : public QObject{
    Q_OBJECT
private:
    Model* m;
    View* v;
public:
    explicit Controller(QObject* parent = nullptr);
    void setModel(Model* model);
    void setView(View* view);
     olist<const User> getUserList() const;
    static olist<const User> getUserDifference(const olist<const User>& all, const olist<const User>& part);
public slots:
    void addCommonFund(Group& g, User& u, const QString& name, double = 0, olist<QString> users = olist<QString>());
    void addCommonExpense(CommonFund& cf, const User& u, double amount, const QString& description, olist<User> users,
                          const std::map<QString, double>& personalExpense = std::map<QString, double>(),
                          const std::map<QString, double>& personalShares = std::map<QString, double>(), const QString& note = "", time_t ts = std::time_t(nullptr));
    void addFundRaise(CommonFund& cf, const User& u, const QString& description, const std::map<QString, double>& contributions = std::map<QString, double>(), const QString& note = "", time_t ts = std::time_t(nullptr));
    void addRegister(const QString& name, User& u, double balance = 0, std::time_t time = std::time_t(nullptr)) const;
    void addGroup(const QString& name, User& u, const QString& description = "", const olist<QString>& userList = olist<QString>());
    void addUserMovement(Register& r, double amount, const QString& description, const QString& note = "", time_t ts = std::time_t(nullptr));
    void addUserToGroup(Group& g, olist<QString> users);
    void addUserToCommonFund(CommonFund& cf, olist<QString> users);
    void logIn(const QString& user, const QString& password) const;
    void createUser(const QString& name, const QString& surname, const QString& username, const QString& password) const;
};

#endif // CONTROLLER_H
