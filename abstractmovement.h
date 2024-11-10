#ifndef ABSTRACTMOVEMENT_H
#define ABSTRACTMOVEMENT_H
#include "movementinterface.h"
#include "user.h"
#include <ctime>
#include <string>

class AbstractMovement : public virtual MovementInterface {
  double amount;
  std::string description;
  std::string note;
  std::time_t time;
  const std::time_t insertion_time;
  const User inserted_by;
  bool valid;

protected:
  AbstractMovement(double a, const User &u, std::string d, std::string n = "",
                   std::time_t t = std::time(nullptr),
                   std::time_t it = std::time(nullptr));

  void setInvalid();

public:
  virtual ~AbstractMovement() = default;
  double getAmount() const override;
  std::string getDescription() const override;
  std::string getNote() const override;
  std::time_t getTime() const override;
  std::time_t getInsertionTime() const override;
  User getInsertedBy() const override;
  double calculateBalanceChange() const override;

  bool operator<(const AbstractMovement &o) const;
  operator bool() const;
};

#endif
