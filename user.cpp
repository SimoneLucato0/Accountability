#include "user.h"

#include "model.h"
#include "partecipation.h"
#include "register.h"
#include "subscription.h"
#include "usermovement.h"

const std::hash<std::string> User::hasher = std::hash<std::string>();

User::Data::Data(Model *m, std::string un, std::string n, std::string sn,
                 std::size_t hash)
    : model(m), username(un), name(n), surname(sn), pw_hash(hash) {
  model->ownUser(this);
};

User::User(Data *in) : model(in->model), username(in->username), internal(in) {}

std::string User::Data::getUsername() const { return username; }

std::string User::Data::getName() const { return name; }

std::string User::Data::getSurname() const { return surname; }

olist<const Register> User::Data::getRegisters() const {
  return model->getRegistersByUser(User(model, username));
}

Register User::Data::getRegisterByName(std::string n) const {
  olist<const Register> registers = getRegisters();
  for (auto cit = registers.begin(); cit != registers.end(); ++cit) {
    if (cit->getName() == n)
      return *cit;
  }
  return Register();
}

bool User::Data::checkPw(std::string pw) const {
  return static_cast<int>(hasher(pw)) == static_cast<int>(pw_hash);
}

olist<const Subscription> User::Data::getSubscriptions() const {
  return model->getSubscriptionsByUser(User(model, username));
}

olist<const Partecipation> User::Data::getPartecipations() const {
  return model->getPartecipationsByUser(User(model, username));
}

User::User() : model(nullptr), username(), internal(nullptr) {}

User::User(Model *m, std::string un)
    : model(m), username(un), internal(m->getUserByUsername(un).internal) {}

User::User(Model *m, std::string un, std::string n, std::string sn,
           std::size_t hash)
    : model(m), username(un),
      internal(m && !User(m, un) ? new Data(m, un, n, sn, hash) : nullptr) {}

User::User(Model *m, std::string un, std::string n, std::string sn,
           std::string pw)
    : model(m), username(un),
      internal(model && !User(m, un) ? new Data(m, un, n, sn, hasher(pw))
                                     : nullptr) {
}

std::string User::getUsername() const { return username; }

std::string User::getName() const { return internal->getName(); }

std::string User::getSurname() const { return internal->getSurname(); }

olist<const Register> User::getRegisters() const {
  return internal->getRegisters();
}

Register User::getRegisterByName(std::string n) const {
  if (internal)
    internal->getRegisterByName(n);
  return Register();
}

bool User::checkPw(std::string pw) const {
  return internal && internal->checkPw(pw);
}

olist<const Subscription> User::getSubscriptions() const {
  return internal->getSubscriptions();
}

olist<const Partecipation> User::getPartecipations() const {
  return internal->getPartecipations();
}

void User::accept(DBMS::Visitor *v) const {
  v->visitUser(this, internal->pw_hash);
}

Model *User::getModel() const { return model; }

bool User::operator<(const User &o) const { return username < o.username; }

bool User::operator==(const User &o) const {
  return model == o.model && username == o.username;
}

User::operator bool() const { return internal; }
