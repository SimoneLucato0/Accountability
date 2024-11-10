#ifndef USERMOVEMENT_H
#define USERMOVEMENT_H
#include "abstractmovement.h"
#include "register.h"
#include "serializable.h"
#include <ctime>
#include <string>

class UserMovement : public AbstractMovement, public virtual Serializable {
  Register reg;

public:
  UserMovement(Register &r, double a, std::string d, std::string n = "",
               std::time_t t = std::time(nullptr),
               std::time_t it = std::time(nullptr));

  void accept(DBMS::Visitor *v) const override;

  const Register &getRegister() const;
};

#endif
