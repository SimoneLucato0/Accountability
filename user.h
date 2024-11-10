#ifndef USER_H
#define USER_H
#include "olist.h"
#include "serializable.h"
#include <ctime>
#include <string>

class Model;
class Partecipation;
class Register;
class Subscription;

class User : public virtual Serializable {
  friend class Model;
  friend class Partecipation;
  friend class Register;

private:
  struct Data {
    Model *model;
    std::string username;
    std::string name;
    std::string surname;
    std::size_t pw_hash;

    Data(Model *m, std::string un, std::string n, std::string sn,
         std::size_t hash);

    std::string getUsername() const;
    std::string getName() const;
    std::string getSurname() const;
    olist<const Register> getRegisters() const;
    Register getRegisterByName(std::string n) const;
    bool checkPw(std::string pw) const;
    olist<const Subscription> getSubscriptions() const;
    olist<const Partecipation> getPartecipations() const;
  };

  static const std::hash<std::string> hasher;
  Model *model;
  std::string username;
  Data *internal;

  explicit User(Data *in);

public:
  User();
  User(Model *m, std::string un);
  User(Model *m, std::string un, std::string n, std::string sn, std::string pw);
  User(Model *m, std::string un, std::string n, std::string sn,
       std::size_t hash);

  std::string getUsername() const;
  std::string getName() const;
  std::string getSurname() const;
  olist<const Register> getRegisters() const;
  Register getRegisterByName(std::string n) const;
  bool checkPw(std::string pw) const;
  olist<const Subscription> getSubscriptions() const;
  olist<const Partecipation> getPartecipations() const;

  void accept(DBMS::Visitor *v) const override;

  Model *getModel() const;
  bool operator<(const User &o) const;
  bool operator==(const User &o) const;
  operator bool() const;
};

#endif
