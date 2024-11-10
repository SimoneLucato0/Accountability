#include "model.h"

#include "group.h"
#include "jsondbms.h"
#include "subscription.h"
#include "user.h"

Model::Model(DBMS *d)
    : dbms(d), users(), groups(), registers(), commonfunds(), partecipations(),
      subscriptions() {
  dbms->load(this);
}

Model::~Model() {
  dbms->save(this);
  delete dbms;
  for (auto it = users.begin(); it != users.end(); ++it) {
    delete *it;
  }
  for (auto it = groups.begin(); it != groups.end(); ++it) {
    delete *it;
  }
  for (auto uit = registers.begin(); uit != registers.end(); ++uit) {
    auto regs = uit->second;
    for (auto rit = regs.begin(); rit != regs.end(); ++rit)
      delete *rit;
  }
  for (auto git = commonfunds.begin(); git != commonfunds.end(); ++git) {
    auto cfs = git->second;
    for (auto rit = cfs.begin(); rit != cfs.end(); ++rit)
      delete *rit;
  }
  for (auto it = partecipations.begin(); it != partecipations.end(); ++it) {
    delete *it;
  }
}

void Model::accept(DBMS::Visitor *v) const { v->visitModel(this); }

void Model::ownUser(User::Data *u) { users.insert(u); }

void Model::ownGroup(Group::Data *g) { groups.insert(g); }

void Model::ownRegister(Register::Data *r) {
  registers[r->getOwner()].insert(r);
}

void Model::ownCommonFund(CommonFund::Data *r) {
  commonfunds[r->getOwner()].insert(r);
}

void Model::ownPartecipation(Partecipation::Data *p) {
  partecipations.insert(p);
}

void Model::ownSubscription(const Subscription &s) { subscriptions.insert(s); }

void Model::save() const { dbms->save(this); }

void Model::save(std::string file) const { dbms->save(this, file); }

olist<const User> Model::getUsers() const {
  olist<const User> ret;
  for (auto cit = users.begin(); cit != users.end(); ++cit) {
    ret.insert(User(*cit));
  }
  return ret;
}

User Model::getUserByUsername(std::string un) const {
  for (auto cit = users.begin(); cit != users.end(); ++cit) {
    if ((*cit)->getUsername() == un) {
      return User(*cit);
    }
  }
  return User();
}

olist<const Group> Model::getGroups() const {
  olist<const Group> ret;
  for (auto cit = groups.begin(); cit != groups.end(); ++cit) {
    ret.insert(Group(*cit));
  }
  return ret;
}

Group Model::getGroupByName(std::string n) const {
  for (auto cit = groups.begin(); cit != groups.end(); ++cit) {
    if ((*cit)->getName() == n) {
      return Group(*cit);
    }
  }
  return Group();
}

olist<const Register> Model::getRegistersByUser(const User &u) const {
  auto uit = registers.find(u);
  olist<const Register> ret;
  if (uit != registers.end()) {
    auto regs = uit->second;
    for (auto rit = regs.begin(); rit != regs.end(); ++rit) {
      ret.insert(Register(*rit));
    }
  }
  return ret;
}

olist<const CommonFund> Model::getCommonFundsByGroup(const Group &g) const {
  auto git = commonfunds.find(g);
  olist<const CommonFund> ret;
  if (git != commonfunds.end()) {
    auto cfs = git->second;
    for (auto cfit = cfs.begin(); cfit != cfs.end(); ++cfit) {
      ret.insert(CommonFund(*cfit));
    }
  }
  return ret;
}

olist<const Partecipation> Model::getPartecipationsByUser(const User &u) const {
  olist<const Partecipation> ret;
  for (auto cit = partecipations.begin(); cit != partecipations.end(); ++cit) {
    if ((*cit)->getUser() == u) {
      ret.insert(Partecipation(*cit));
    }
  }
  return ret;
}

olist<const Partecipation>
Model::getPartecipationsByCommonFund(const CommonFund &cf) const {
  olist<const Partecipation> ret;
  for (auto cit = partecipations.begin(); cit != partecipations.end(); ++cit) {
    if ((*cit)->getCommonFund() == cf) {
      ret.insert(Partecipation(*cit));
    }
  }
  return ret;
}

olist<const Subscription> Model::getSubscriptionsByUser(const User &u) const {
  olist<const Subscription> ret;
  for (auto cit = subscriptions.begin(); cit != subscriptions.end(); ++cit) {
    if (cit->getUser() == u) {
      ret.insert(Subscription(*cit));
    }
  }
  return ret;
}

olist<const Subscription> Model::getSubscriptionsByGroup(const Group &g) const {
  olist<const Subscription> ret;
  for (auto cit = subscriptions.begin(); cit != subscriptions.end(); ++cit) {
    if (cit->getGroup() == g) {
      ret.insert(Subscription(*cit));
    }
  }
  return ret;
}