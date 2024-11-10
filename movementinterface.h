#ifndef MOVEMENTINTERFACE_H
#define MOVEMENTINTERFACE_H
#include <ctime>
#include <string>

class User;

class MovementInterface {
public:
  virtual ~MovementInterface() = default;

  virtual double getAmount() const = 0;
  virtual std::string getDescription() const = 0;
  virtual std::string getNote() const = 0;
  virtual std::time_t getTime() const = 0;
  virtual std::time_t getInsertionTime() const = 0;
  virtual User getInsertedBy() const = 0;
  virtual double calculateBalanceChange() const = 0;
};

#endif
