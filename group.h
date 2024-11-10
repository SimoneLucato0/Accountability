#ifndef GROUP_H
#define GROUP_H
#include "olist.h"
#include "serializable.h"
#include "user.h"
#include <ctime>
#include <string>

class Model;
class Subscription;

class Group : public virtual Serializable {
  friend class Model;
  friend class CommonFund;

private:
  struct Data {
    Model *model;
    std::string name;
    std::string description;
    User founder;
    std::time_t creation_time;

    Data(Model *m, std::string n, std::string d, const User &f, std::time_t ct);

    std::string getName() const;
    std::string getDescription() const;
    std::time_t getCreationTime() const;
    olist<const CommonFund> getCommonFunds() const;
    CommonFund getCommonFundByName(std::string n) const;
    olist<const Subscription> getSubscriptions() const;
    Subscription getSubscriptionByUser(const User &u) const;
    const User &getFounder() const;
    std::time_t getLastActivity() const;
  };

  Model *model;
  std::string name;
  Data *internal;

  explicit Group(Data *in);

public:
  Group();
  Group(Model *m, std::string n);
  Group(Model *m, std::string n, std::string d, User &f,
        std::time_t ct = std::time(nullptr));

  std::string getName() const;
  std::string getDescription() const;
  std::time_t getCreationTime() const;
  olist<const CommonFund> getCommonFunds() const;
  CommonFund getCommonFundByName(std::string n) const;
  olist<const Subscription> getSubscriptions() const;
  Subscription getSubscriptionByUser(const User &u) const;
  const User &getFounder() const;
  std::time_t getLastActivity() const;

  void accept(DBMS::Visitor *v) const override;

  Model *getModel() const;
  bool operator<(const Group &o) const;
  bool operator==(const Group &o) const;
  operator bool() const;
};

#endif
