#include "abstractgroupmovement.h"

#include "commonfund.h"
#include "deep_ptr.h"

AbstractGroupMovement::AbstractGroupMovement(CommonFund &cf,
                                             const std::map<User, double> &ucg,
                                             double a, const User &u,
                                             std::string d, std::string n,
                                             std::time_t t, std::time_t it)
    : AbstractMovement(a, u, d, n, t, it), commonfund(cf),
      userCreditChange(ucg) {}

double AbstractGroupMovement::calculateTotal(const std::map<User, double> &m) {
  double sum = 0;
  for (auto cit = m.begin(); cit != m.end(); ++cit) {
    sum += (*cit).second;
  }
  return sum;
}

void AbstractGroupMovement::getOwnedBy(CommonFund &cf) {
  cf.ownMovement(DeepPtr<AbstractGroupMovement>(this->clone()));
}

const std::map<User, double> &
AbstractGroupMovement::getUserCreditChange() const {
  return userCreditChange;
}

const CommonFund &AbstractGroupMovement::getCommonFund() const {
  return commonfund;
}