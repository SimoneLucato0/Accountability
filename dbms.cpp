#include "dbms.h"

DBMS::DBMS(std::string fn) : filename(fn) {}

std::string DBMS::getFile() const { return filename; }

void DBMS::save(const Model *m) { save(m, filename); }
