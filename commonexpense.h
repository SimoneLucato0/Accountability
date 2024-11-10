#ifndef COMMONEXPENSE_H
#define COMMONEXPENSE_H
#include "abstractgroupmovement.h"
#include <ctime>
#include <map>
#include "olist.h"
#include <string>

class CommonFund;
class User;

class CommonExpense : public AbstractGroupMovement {
  olist<User> involved_users;
  std::map<User, double> personal_expenses;
  std::map<User, double> personal_payments;

  static std::map<User, double> calculateUserCreditChange(
      const CommonFund &cf, double amount, const olist<User> &ip,
      const std::map<User, double> &pp, const std::map<User, double> &pe);

protected:
  std::map<User, double> calculateUserCreditChange() const;

public:
  CommonExpense(CommonFund &cf, double a, const User &u, std::string d,
                const olist<User> &iu = {},
                const std::map<User, double> &pe = {},
                const std::map<User, double> &pp = {}, std::string n = "",
                std::time_t t = std::time(nullptr),
                std::time_t it = std::time(nullptr));

  double calculateBalanceChange() const override;
  CommonExpense *clone() const override;

  void accept(DBMS::Visitor *v) const override;

  const olist<User> &getInvolvedUsers() const;
  const std::map<User, double> &getPersonalExpenses() const;
  const std::map<User, double> &getPersonalPayments() const;
};

#endif
