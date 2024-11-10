#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include "dbms.h"

class Serializable {
public:
  virtual ~Serializable() = default;
  virtual void accept(DBMS::Visitor *) const = 0;
};

#endif