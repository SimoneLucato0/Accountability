#ifndef COMMONFUND_H
#define COMMONFUND_H
#include "abstractaccount.h"
#include "group.h"
#include "olist.h"
#include "serializable.h"
#include "deep_ptr.h"
#include <ctime>
#include <string>

class Partecipation;
class AbstractGroupMovement;

class CommonFund : public virtual AccountInterface,
                   public virtual Serializable {
  friend class Model;
  friend class Group;
  friend class AbstractGroupMovement;
  friend class Partecipation;

private:
  struct Data : public AbstractAccount {
    Group owner;
    olist<DeepPtr<AbstractGroupMovement>> movements;

    Data(const Group &o, const User &f, std::string n, double b,
         std::time_t ct);

    std::time_t getLastActivity() const override;
    double changeBalance(double delta);
    const Group &getOwner() const;
    const olist<DeepPtr<AbstractGroupMovement>> &getMovements() const;
    olist<const Partecipation> getPartecipations() const;
    Partecipation getPartecipationByUser(const User &u) const;
  };

  Group owner;
  std::string name;
  Data *internal;

  explicit CommonFund(Data *in);

  void ownMovement(const DeepPtr<AbstractGroupMovement> &mv);

public:
  CommonFund();
  CommonFund(const Group &o, std::string n);
  CommonFund(Group &o, User &f, std::string n, double b,
             std::time_t ct = std::time(nullptr));

  std::string getName() const override;
  double getInitBalance() const override;
  double getBalance() const override;
  std::time_t getCreationTime() const override;
  const User &getFounder() const override;
  std::time_t getLastActivity() const override;

  const Group &getOwner() const;
  const olist<DeepPtr<AbstractGroupMovement>> &getMovements() const;
  olist<const Partecipation> getPartecipations() const;
  Partecipation getPartecipationByUser(const User &u) const;

  void accept(DBMS::Visitor *v) const override;

  bool operator<(const CommonFund &o) const;
  bool operator==(const CommonFund &o) const;
  operator bool() const;
};

#endif
