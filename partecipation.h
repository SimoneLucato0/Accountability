#ifndef PARTECIPATION_H
#define PARTECIPATION_H
#include "commonfund.h"
#include "serializable.h"
#include "user.h"

class Partecipation : public virtual Serializable {
  friend class Model;
  friend class CommonFund;

  struct Data {
    User user;
    CommonFund commonfund;
    const double init_credit;
    double credit;
    Data(User &u, CommonFund &cf, double c);

    const User &getUser() const;
    const CommonFund &getCommonFund() const;
    double getCredit() const;
    double getInitCredit() const;
  };
  User user;
  CommonFund commonfund;
  Data *internal;

  explicit Partecipation(Data *in);

  double changeCredit(double d) const;

public:
  Partecipation();
  Partecipation(const User &u, const CommonFund &cf);
  Partecipation(User &u, CommonFund &cf, double c);

  void accept(DBMS::Visitor *v) const override;

  const User &getUser() const;
  const CommonFund &getCommonFund() const;
  double getCredit() const;
  double getInitCredit() const;
  bool operator<(const Partecipation &o) const;
  operator bool() const;
};

#endif
