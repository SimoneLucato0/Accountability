#include "usermovement.h"

UserMovement::UserMovement(Register &r, double a, std::string d, std::string n,
                           std::time_t t, std::time_t it)
    : AbstractMovement(a, r.getOwner(), d, n, t, it), reg(r) {
  r.addMovement(*this);
}

const Register &UserMovement::getRegister() const { return reg; }

void UserMovement::accept(DBMS::Visitor *v) const {
  v->visitUserMovement(this);
}
