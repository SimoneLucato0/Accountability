#include "register.h"

#include "model.h"
#include "usermovement.h"

Register::Data::Data(User &o, std::string n, double b, std::time_t ct)
    : AbstractAccount(o, n, b, ct), owner(o) {
  owner.getModel()->ownRegister(this);
}

double Register::Data::changeBalance(double delta) {
  return AbstractAccount::changeBalance(delta);
}

std::time_t Register::Data::getLastActivity() const {
  return movements.empty() ? getCreationTime() : (--movements.end())->getTime();
}
const User &Register::Data::getOwner() const { return owner; }

const olist<UserMovement> &Register::Data::getMovements() const {
  return movements;
}

Register::Register(Data *in) : internal(in) {}

Register::Register() : internal(nullptr) {}

Register::Register(const User &o, std::string n)
    : internal(o.getRegisterByName(n).internal) {}

Register::Register(User &o, std::string n, double b, std::time_t ct)
    : internal(o && !Register(o, n) ? new Data(o, n, b, ct) : nullptr) {}

void Register::addMovement(const UserMovement &mv) {
  internal->changeBalance(mv.calculateBalanceChange());
  internal->movements.insert(mv);
}

std::string Register::getName() const { return internal->getName(); }

double Register::getInitBalance() const { return internal->getInitBalance(); }

double Register::getBalance() const { return internal->getBalance(); }

std::time_t Register::getCreationTime() const {
  return internal->getCreationTime();
}

const User &Register::getFounder() const { return internal->getFounder(); }

std::time_t Register::getLastActivity() const {
  return internal->getLastActivity();
}

void Register::accept(DBMS::Visitor *v) const { v->visitRegister(this); }

const User &Register::getOwner() const { return internal->owner; }

const olist<UserMovement> &Register::getMovements() const {
  return internal->movements;
}

bool Register::operator<(const Register &o) const {
  return *internal < *o.internal;
}

Register::operator bool() const { return internal; }