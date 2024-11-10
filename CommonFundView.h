#ifndef COMMONFUNDVIEW_H
#define COMMONFUNDVIEW_H

#include <QCheckBox>
#include <QDateTimeEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QWidget>

#include <QMessageBox>
#include <QWhatsThis>

#include "float.h"

#include "commonfund.h"
#include "commonexpense.h"
#include "fundraise.h"
#include "partecipation.h"
#include "InnerPage.h"
#include "QErrLabel.h"
#include "UserInput.h"
#include "UserFilterList.h"


class CommonFundView : public InnerPage{
    Q_OBJECT
private:
    CommonFund commonFund;
    olist<const User> userDifference;
public:
    CommonFundView(const CommonFund& cf, QWidget* parent = nullptr);
    olist<User> getUsersInCommonFund() const;
    void setUserDifference(olist<const User> d);
public slots:
    void showAddUser();
    void showAddFundRaise();
    void showAddCommonExpense();
    void showAddCommonEntry();
    void showRecap();
signals:
    void showGroupView();
    void sendAddUsers(CommonFund& cf, olist<QString> users);
    void sendAddFundRaise(CommonFund& cf, const QString& description, std::map<QString, double> contributions, const QString& note = "", time_t ts = std::time_t(nullptr));
    void sendAddCommonExpense(CommonFund& cf, double amount, const QString& description, olist<User> users,
                              std::map<QString, double> personalExpense = std::map<QString, double>(),
                              std::map<QString, double> personalShares = std::map<QString, double>(), const QString& note = "", time_t ts = std::time_t(nullptr));
    void userDifferenceRequest(const olist<const User>& part);
};

#endif // COMMONFUNDVIEW_H
