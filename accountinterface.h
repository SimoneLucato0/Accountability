#ifndef ACCOUNTINTERFACE_H
#define ACCOUNTINTERFACE_H
#include <ctime>
#include "olist.h"
#include <string>

class User;

class AccountInterface {
public:
  virtual std::string getName() const = 0;
  virtual double getInitBalance() const = 0;
  virtual double getBalance() const = 0;
  virtual std::time_t getCreationTime() const = 0;
  virtual const User &getFounder() const = 0;
  virtual std::time_t getLastActivity() const = 0;
};

#endif