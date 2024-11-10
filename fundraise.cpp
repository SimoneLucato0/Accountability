#include "fundraise.h"

#include "partecipation.h"

FundRaise::FundRaise(CommonFund &cf, const User &u, std::string d,
                     std::map<User, double> c, std::string n, std::time_t t,
                     std::time_t it)
    : AbstractGroupMovement(cf, c, AbstractGroupMovement::calculateTotal(c), u,
                            d, n, t, it),
      collected(c) {
  bool ok = true;
  for (auto cit = collected.begin(); cit != collected.end() && ok; ++cit) {
    if (!Partecipation(cit->first, cf)) {
      ok = false;
    }
  }
  if (ok)
    getOwnedBy(cf);
  else
    setInvalid();
}

std::map<User, double> FundRaise::calculateUserCreditChange() const {
  return collected;
}

FundRaise *FundRaise::clone() const { return new FundRaise(*this); }

void FundRaise::accept(DBMS::Visitor *v) const { v->visitFundRaise(this); }

const std::map<User, double> &FundRaise::getCollected() const {
  return collected;
}
