#ifndef FUNDRAISE_H
#define FUNDRAISE_H
#include "abstractgroupmovement.h"
#include <ctime>
#include <map>
#include <string>

class CommonFund;
class User;

class FundRaise : public AbstractGroupMovement {
  std::map<User, double> collected;

protected:
  std::map<User, double> calculateUserCreditChange() const override;

public:
  FundRaise(CommonFund &cf, const User &u, std::string d,
            std::map<User, double> c, std::string n = "",
            std::time_t t = std::time(nullptr),
            std::time_t it = std::time(nullptr));

  FundRaise *clone() const override;

  void accept(DBMS::Visitor *v) const override;

  const std::map<User, double> &getCollected() const;
};

#endif
