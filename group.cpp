#include "group.h"

#include "commonfund.h"
#include "model.h"
#include "subscription.h"

Group::Data::Data(Model *m, std::string n, std::string d, const User &f,
                  std::time_t ct)
    : model(m), name(n), description(d), founder(f), creation_time(ct) {
  model->ownGroup(this);
}

std::string Group::Data::getName() const { return name; }

std::string Group::Data::getDescription() const { return description; }

std::time_t Group::Data::getCreationTime() const { return creation_time; }

olist<const CommonFund> Group::Data::getCommonFunds() const {
  return model->getCommonFundsByGroup(Group(model, name));
}

CommonFund Group::Data::getCommonFundByName(std::string n) const {
  auto commonfunds = getCommonFunds();
  for (auto it = commonfunds.begin(); it != commonfunds.end(); ++it) {
    if (it->getName() == n)
      return CommonFund(*it);
  }
  return CommonFund();
}

olist<const Subscription> Group::Data::getSubscriptions() const {
  return model->getSubscriptionsByGroup(Group(model, name));
}

Subscription Group::Data::getSubscriptionByUser(const User &u) const {
  auto subscriptions = getSubscriptions();
  for (auto cit = subscriptions.begin(); cit != subscriptions.end(); ++cit) {
    if (cit->getUser() == u)
      return *cit;
  }
  return Subscription();
}

const User &Group::Data::getFounder() const { return founder; }

std::time_t Group::Data::getLastActivity() const {
  std::time_t last = creation_time;
  auto commonfunds = getCommonFunds();
  for (auto cit = commonfunds.begin(); cit != commonfunds.end(); ++cit) {
    std::time_t t = cit->getLastActivity();
    if (t > last)
      last = t;
  }
  return last;
}

Group::Group(Data *in) : model(in->model), name(in->name), internal(in) {}

Group::Group() : model(nullptr), name(), internal(nullptr) {}

Group::Group(Model *m, std::string n)
    : model(m), name(n), internal(m->getGroupByName(n).internal) {}

Group::Group(Model *m, std::string n, std::string d, User &f, std::time_t ct)
    : model(m), name(n), internal(f.getModel() == m && m && f && !Group(m, n)
                                      ? new Data(m, n, d, f, ct)
                                      : nullptr) {
  if (internal) {
    Subscription(f, *this, ct);
  }
}

std::string Group::getName() const { return name; }

std::string Group::getDescription() const { return internal->getDescription(); }

std::time_t Group::getCreationTime() const {
  return internal->getCreationTime();
}

olist<const CommonFund> Group::getCommonFunds() const {
  return internal->getCommonFunds();
}

CommonFund Group::getCommonFundByName(std::string n) const {
  if (internal)
    return internal->getCommonFundByName(n);
  return CommonFund();
}

olist<const Subscription> Group::getSubscriptions() const {
  return internal->getSubscriptions();
}

Subscription Group::getSubscriptionByUser(const User &u) const {
  if (internal)
    return internal->getSubscriptionByUser(u);
  return Subscription();
}

const User &Group::getFounder() const { return internal->getFounder(); }

std::time_t Group::getLastActivity() const {
  if (internal)
    return internal->getLastActivity();
  return 0;
}

void Group::accept(DBMS::Visitor *v) const { v->visitGroup(this); }

Model *Group::getModel() const { return model; }

bool Group::operator<(const Group &o) const { return name < o.name; }

bool Group::operator==(const Group &o) const {
  return model == o.model && name == o.name;
}

Group::operator bool() const { return internal; }
