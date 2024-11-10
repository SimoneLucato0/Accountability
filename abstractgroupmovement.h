#ifndef ABSTRACTGROUPMOVEMENT_H
#define ABSTRACTGROUPMOVEMENT_H
#include "abstractmovement.h"
#include "commonfund.h"
#include <ctime>
#include <map>
#include <string>

class User;

class AbstractGroupMovement : public AbstractMovement,
                              public virtual MovementInterface,
                              public virtual Serializable {
  CommonFund commonfund;
  std::map<User, double> userCreditChange;

protected:
  AbstractGroupMovement(CommonFund &cf, const std::map<User, double> &ucg,
                        double a, const User &u, std::string d,
                        std::string n = "", std::time_t t = std::time(nullptr),
                        std::time_t it = std::time(nullptr));

  static double calculateTotal(const std::map<User, double> &m);
  virtual std::map<User, double> calculateUserCreditChange() const = 0;
  void getOwnedBy(CommonFund &cf);

public:
  const std::map<User, double> &getUserCreditChange() const;
  const CommonFund &getCommonFund() const;
  virtual AbstractGroupMovement *clone() const = 0;
};

#endif
