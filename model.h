#ifndef MODEL_H
#define MODEL_H
#include "commonfund.h"
#include "group.h"
#include "olist.h"
#include "partecipation.h"
#include "register.h"
#include "serializable.h"
#include "user.h"
#include <ctime>
#include <map>
#include <string>

class DBMS;

class Model : public virtual Serializable {
  friend class User;
  friend class Group;
  friend class Register;
  friend class CommonFund;
  friend class Partecipation;
  friend class Subscription;

private:
  DBMS *dbms;
  olist<User::Data *> users;
  olist<Group::Data *> groups;
  std::map<User, olist<Register::Data *>> registers;
  std::map<Group, olist<CommonFund::Data *>> commonfunds;
  olist<Partecipation::Data *> partecipations;
  olist<Subscription> subscriptions;
  void ownUser(User::Data *u);
  void ownGroup(Group::Data *g);
  void ownRegister(Register::Data *r);
  void ownCommonFund(CommonFund::Data *cf);
  void ownPartecipation(Partecipation::Data *p);
  void ownSubscription(const Subscription &s);

public:
  Model(DBMS *d);
  ~Model();

  void accept(DBMS::Visitor *v) const override;

  void save() const;
  void save(std::string file) const;

  olist<const User> getUsers() const;
  User getUserByUsername(std::string un) const;
  olist<const Group> getGroups() const;
  Group getGroupByName(std::string n) const;
  olist<const Register> getRegistersByUser(const User &u) const;
  olist<const CommonFund> getCommonFundsByGroup(const Group &g) const;
  olist<const Partecipation> getPartecipationsByUser(const User &u) const;
  olist<const Partecipation>
  getPartecipationsByCommonFund(const CommonFund &u) const;
  olist<const Subscription> getSubscriptionsByUser(const User &u) const;
  olist<const Subscription> getSubscriptionsByGroup(const Group &g) const;
};

#endif
