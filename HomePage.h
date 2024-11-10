#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QScrollBar>
#include <QWidget>

#include <QAction>

#include <float.h>

#include "customlistwidget.h"
#include "QErrLabel.h"
#include "QPushButtonAR.h"
#include "UserFilterList.h"
#include "user.h"
#include "subscription.h"

class HomePage : public QWidget{
    Q_OBJECT
private:
    CustomListWidget* registerList;
    CustomListWidget* groupList;
    UserFilterList* users;

    User user;
    olist<const User> allUserList;
public:
    explicit HomePage(User& u, olist<const User> allUsers, QWidget* parent = nullptr);
    void resetLists();
    void setUserList(const olist<const User>& u);
public slots:
    void showAddRegister();
    void showAddGroup();
signals:
    void sendAddRegisterInfo(const QString& name, User& u, double balance = 0, std::time_t time = std::time_t(nullptr));
    void sendAddGroupInfo(const QString& name, User& u,const QString& description = "", const olist<QString> users = olist<QString>());
    void showRegister(const Register& r);
    void showGroup(const Group& g);
    void userListRequest();
};

#endif // HOMEPAGE_H
