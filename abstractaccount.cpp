#include "abstractaccount.h"

double AbstractAccount::changeBalance(double delta) {
  return (balance += delta);
}

AbstractAccount::AbstractAccount(const User &f, std::string n, double b,
                                 std::time_t ct)
    : name(n), init_balance(b), balance(b), creation_time(ct), founder(f) {}

std::string AbstractAccount::getName() const { return name; }

double AbstractAccount::getInitBalance() const { return init_balance; }

double AbstractAccount::getBalance() const { return balance; }

std::time_t AbstractAccount::getCreationTime() const { return creation_time; }

const User &AbstractAccount::getFounder() const { return founder; }

bool AbstractAccount::operator<(const AbstractAccount &o) const {
  return name < o.name;
}