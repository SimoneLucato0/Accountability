#ifndef ABSTRACTACCOUNT_H
#define ABSTRACTACCOUNT_H
#include "accountinterface.h"
#include "olist.h"
#include "user.h"
#include <ctime>
#include <string>

class AbstractAccount : public virtual AccountInterface {
  std::string name;
  const double init_balance;
  double balance;
  const std::time_t creation_time;
  User founder;

protected:
  double changeBalance(double delta);
  AbstractAccount(const User &f, std::string n, double b, std::time_t ct);

public:
  virtual ~AbstractAccount() = default;

  std::string getName() const override;
  double getInitBalance() const override;
  double getBalance() const override;
  std::time_t getCreationTime() const override;
  const User &getFounder() const override;
  virtual std::time_t getLastActivity() const = 0;

  bool operator<(const AbstractAccount &o) const;
};

#endif
