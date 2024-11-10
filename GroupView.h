#ifndef GROUPVIEW_H
#define GROUPVIEW_H

#include <QDateTimeEdit>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QWidget>

#include "commonfund.h"
#include "group.h"
#include "subscription.h"
#include "InnerPage.h"
#include "QErrLabel.h"
#include "UserFilterList.h"

#include <float.h>

class GroupView : public InnerPage{
    Q_OBJECT
private:
    User currentUser;
    Group group;
    UserFilterList* users;
    olist<const User> userDifference;
public:
    explicit GroupView(const Group& g, const User& user, QWidget* parent = nullptr);
    olist<const User> getUsers() const;
    void resetList();
    void setUserDifference(const olist<const User>& d);
public slots:
    void showAddCommonFund();
    void showAddUser();
signals:
    void showHomePage();
    void showDeleteConfirm();
    void showCommonFund(const CommonFund& cf);
    void sendAddCommonFund(Group& g, const QString& name, double = 0, olist<QString> users = olist<QString>());
    void sendAddUsers(Group& g, olist<QString> users);
    void userDifferenceRequest(const olist<const User>& part);
};

#endif // GROUPVIEW_H
