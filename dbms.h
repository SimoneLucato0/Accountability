#ifndef DBMS_H
#define DBMS_H
#include "olist.h"
#include <string>

class Model;
class User;
class Group;
class Subscription;
class Register;
class CommonFund;
class Partecipation;
class UserMovement;
class CommonExpense;
class FundRaise;

class DBMS {
protected:
  std::string filename;

public:
  class Visitor {
  public:
    virtual ~Visitor() = default;
    virtual void visitModel(const Model *m) = 0;
    virtual void visitUser(const User *u, std::size_t pw_hash) = 0;
    virtual void visitGroup(const Group *g) = 0;
    virtual void visitSubscription(const Subscription *g) = 0;
    virtual void visitRegister(const Register *r) = 0;
    virtual void visitCommonFund(const CommonFund *cf) = 0;
    virtual void visitPartecipation(const Partecipation *cf) = 0;
    virtual void visitUserMovement(const UserMovement *um) = 0;
    virtual void visitCommonExpense(const CommonExpense *ce) = 0;
    virtual void visitFundRaise(const FundRaise *fr) = 0;
  };
  DBMS(std::string fn);
  virtual ~DBMS() = default;

  std::string getFile() const;
  virtual void load(Model *m) = 0;
  void save(const Model *m);
  virtual void save(const Model *m, std::string f) = 0;
};

#endif
