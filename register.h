#ifndef REGISTER_H
#define REGISTER_H
#include "abstractaccount.h"
#include "olist.h"
#include "serializable.h"
#include "user.h"
#include <ctime>

class UserMovement;

class Register : public virtual AccountInterface, public virtual Serializable {
  friend class Model;
  friend class UserMovement;

  struct Data : public AbstractAccount {
    User owner;
    olist<UserMovement> movements;
    Data(User &o, std::string n, double b, std::time_t ct);
    double changeBalance(double delta);
    time_t getLastActivity() const override;
    const User &getOwner() const;
    const olist<UserMovement> &getMovements() const;
  };
  Data *internal;

  explicit Register(Data *in);

  void addMovement(const UserMovement &mv);

public:
  Register();
  Register(const User &o, std::string n);
  Register(User &o, std::string n, double b,
           std::time_t ct = std::time(nullptr));

  std::string getName() const override;
  double getInitBalance() const override;
  double getBalance() const override;
  std::time_t getCreationTime() const override;
  const User &getFounder() const override;
  std::time_t getLastActivity() const override;

  void accept(DBMS::Visitor *v) const override;

  const User &getOwner() const;
  const olist<UserMovement> &getMovements() const;
  bool operator<(const Register &o) const;
  operator bool() const;
};

#endif
