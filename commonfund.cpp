#include "commonfund.h"

#include "abstractgroupmovement.h"
#include "group.h"
#include "model.h"
#include "partecipation.h"
#include "subscription.h"

CommonFund::Data::Data(const Group &o, const User &f, std::string n, double b,
                       std::time_t ct)
    : AbstractAccount(f, n, b, ct), owner(o) {
  owner.getModel()->ownCommonFund(this);
}

std::time_t CommonFund::Data::getLastActivity() const {
  return movements.empty() ? getCreationTime()
                           : (--movements.end())->get()->getTime();
}

double CommonFund::Data::changeBalance(double delta) {
  return AbstractAccount::changeBalance(delta);
}

const Group &CommonFund::Data::getOwner() const { return owner; }

const olist<DeepPtr<AbstractGroupMovement>> &
CommonFund::Data::getMovements() const {
  return movements;
}

olist<const Partecipation> CommonFund::Data::getPartecipations() const {
  return owner.getModel()->getPartecipationsByCommonFund(
      CommonFund(owner, getName()));
}

Partecipation CommonFund::Data::getPartecipationByUser(const User &u) const {
  auto partecipations = getPartecipations();
  for (auto cit = partecipations.begin(); cit != partecipations.end(); ++cit) {
    if (cit->getUser() == u)
      return *cit;
  }
  return Partecipation();
}

CommonFund::CommonFund(Data *in)
    : owner(in->owner), name(in->getName()), internal(in) {}

CommonFund::CommonFund() : owner(), name(), internal(nullptr) {}

CommonFund::CommonFund(const Group &o, std::string n)
    : owner(o), name(n), internal(o.getCommonFundByName(n).internal) {}

CommonFund::CommonFund(Group &o, User &f, std::string n, double b,
                       std::time_t ct)
    : owner(o), name(n),
      internal(o && f && o.getModel() == f.getModel() && Subscription(f, o) &&
                       !CommonFund(o, n)
                   ? new CommonFund::Data(o, f, n, b, ct)
                   : nullptr) {
  if (internal) {
    Partecipation(f, *this, 0.0);
  }
}

void CommonFund::ownMovement(const DeepPtr<AbstractGroupMovement> &mv) {
  if (internal) {
    internal->movements.insert(mv);
    internal->changeBalance(mv->calculateBalanceChange());
    const std::map<User, double> &ucg = mv->getUserCreditChange();
    for (auto cit = ucg.begin(); cit != ucg.end(); ++cit) {
      getPartecipationByUser(cit->first).changeCredit(cit->second);
    }
  }
}

std::string CommonFund::getName() const { return name; }

double CommonFund::getInitBalance() const { return internal->getInitBalance(); }

double CommonFund::getBalance() const { return internal->getBalance(); }

std::time_t CommonFund::getCreationTime() const {
  return internal->getCreationTime();
}

const User &CommonFund::getFounder() const { return internal->getFounder(); };

std::time_t CommonFund::getLastActivity() const {
  return internal->getLastActivity();
}

const Group &CommonFund::getOwner() const { return owner; }

const olist<DeepPtr<AbstractGroupMovement>> &
CommonFund::getMovements() const {
  return internal->getMovements();
}

olist<const Partecipation> CommonFund::getPartecipations() const {
  return internal->getPartecipations();
}

Partecipation CommonFund::getPartecipationByUser(const User &u) const {
  if (internal)
    return internal->getPartecipationByUser(u);
  return Partecipation();
}

void CommonFund::accept(DBMS::Visitor *v) const { v->visitCommonFund(this); }

bool CommonFund::operator<(const CommonFund &o) const { return name < o.name; }

bool CommonFund::operator==(const CommonFund &o) const {
  return owner == o.owner && name == o.name;
}

CommonFund::operator bool() const { return internal; }