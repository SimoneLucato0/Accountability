#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H
#include "dbms.h"
#include "group.h"
#include "serializable.h"
#include "user.h"
#include <ctime>

class Subscription : public virtual Serializable {
  User user;
  Group group;
  std::time_t sub_time;

public:
  Subscription();
  Subscription(const User &u, const Group &g);
  Subscription(User &u, Group &g, std::time_t st);

  void accept(DBMS::Visitor *v) const override;

  const User &getUser() const;
  const Group &getGroup() const;
  std::time_t getSubTime() const;
  bool operator<(const Subscription &o) const;
  operator bool() const;
};

#endif
