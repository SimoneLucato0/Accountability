#include "abstractmovement.h"

AbstractMovement::AbstractMovement(double a, const User &u, std::string d,
                                   std::string n, std::time_t t, std::time_t it)
    : amount(a), description(d), note(n), time(t), insertion_time(it),
      inserted_by(u), valid(true) {}

void AbstractMovement::setInvalid() { valid = false; }

double AbstractMovement::getAmount() const { return amount; }

std::string AbstractMovement::getDescription() const { return description; }

std::string AbstractMovement::getNote() const { return note; }

std::time_t AbstractMovement::getTime() const { return time; }

std::time_t AbstractMovement::getInsertionTime() const {
  return insertion_time;
}

User AbstractMovement::getInsertedBy() const { return inserted_by; }

double AbstractMovement::calculateBalanceChange() const { return amount; }

bool AbstractMovement::operator<(const AbstractMovement &o) const {
  return getTime() < o.getTime();
}

AbstractMovement::operator bool() const { return valid; }
