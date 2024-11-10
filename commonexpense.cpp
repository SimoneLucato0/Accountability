#include "commonexpense.h"

#include "commonfund.h"
#include "group.h"
#include "partecipation.h"
#include "user.h"

CommonExpense::CommonExpense(CommonFund &cf, double a, const User &u,
                             std::string d, const olist<User> &iu,
                             const std::map<User, double> &pe,
                             const std::map<User, double> &pp, std::string n,
                             std::time_t t, std::time_t it)
    : AbstractGroupMovement(cf, calculateUserCreditChange(cf, a, iu, pp, pe), a,
                            u, d, n, t, it),
      involved_users(iu), personal_expenses(pe), personal_payments(pp) {
  if (involved_users.empty()) {
    auto parts = cf.getPartecipations();
    for (auto cit = parts.begin(); cit != parts.end(); ++cit) {
      involved_users.insert(cit->getUser());
    }
  }
  bool ok = true;
  for (auto cit = involved_users.begin(); cit != involved_users.end() && ok;
       ++cit) {
    if (!Partecipation(*cit, cf)) {
      ok = false;
    }
  }
  for (auto cit = personal_expenses.begin();
       cit != personal_expenses.end() && ok; ++cit) {
    if (!Partecipation(cit->first, cf)) {
      ok = false;
    }
  }
  for (auto cit = personal_payments.begin();
       cit != personal_payments.end() && ok; ++cit) {
    if (!Partecipation(cit->first, cf)) {
      ok = false;
    }
  }
  if (ok)
    getOwnedBy(cf);
  else
    setInvalid();
}

std::map<User, double> CommonExpense::calculateUserCreditChange(
    const CommonFund &cf, double amount, const olist<User> &iu,
    const std::map<User, double> &pp, const std::map<User, double> &pe) {
  std::map<User, double> ret;

  double commonCost = amount + calculateTotal(pe);
  if (!iu.empty()) {
    for (auto cit = iu.begin(); cit != iu.end(); ++cit) {
      ret.insert({*cit, commonCost / iu.size()});
    }
  } else {
    auto parts = cf.getPartecipations();
    for (auto cit = parts.begin(); cit != parts.end(); ++cit) {
      ret.insert({cit->getUser(), commonCost / parts.size()});
    }
  }

  for (auto cit = pe.begin(); cit != pe.end(); ++cit) {
    try {
      ret.at(cit->first) -= cit->second;
    } catch (const std::out_of_range &e) {
      ret[cit->first] = -cit->second;
    }
  }

  for (auto cit = pp.begin(); cit != pp.end(); ++cit) {
    try {
      ret.at(cit->first) += cit->second;
    } catch (const std::out_of_range &e) {
      ret[cit->first] = cit->second;
    }
  }
  return ret;
}

std::map<User, double> CommonExpense::calculateUserCreditChange() const {
  return calculateUserCreditChange(getCommonFund(), getAmount(),
                                   getInvolvedUsers(), personal_payments,
                                   personal_expenses);
}

double CommonExpense::calculateBalanceChange() const {
  return getAmount() + calculateTotal(personal_payments);
}

CommonExpense *CommonExpense::clone() const { return new CommonExpense(*this); }

void CommonExpense::accept(DBMS::Visitor *v) const {
  v->visitCommonExpense(this);
}

const olist<User> &CommonExpense::getInvolvedUsers() const {
  return involved_users;
}

const std::map<User, double> &CommonExpense::getPersonalExpenses() const {
  return personal_expenses;
}

const std::map<User, double> &CommonExpense::getPersonalPayments() const {
  return personal_payments;
}
