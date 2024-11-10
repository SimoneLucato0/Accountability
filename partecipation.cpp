#include "partecipation.h"

#include "model.h"

Partecipation::Data::Data(User &u, CommonFund &cf, double c)
    : user(u), commonfund(cf), init_credit(c), credit(c) {
  user.getModel()->ownPartecipation(this);
}

const User &Partecipation::Data::getUser() const { return user; }

const CommonFund &Partecipation::Data::getCommonFund() const {
  return commonfund;
}

double Partecipation::Data::getCredit() const { return credit; }

double Partecipation::Data::getInitCredit() const { return init_credit; }

Partecipation::Partecipation(Data *in)
    : user(in->getUser()), commonfund(in->getCommonFund()), internal(in) {}

Partecipation::Partecipation() : user(), commonfund(), internal(nullptr) {}

Partecipation::Partecipation(const User &u, const CommonFund &cf)
    : user(u), commonfund(cf), internal(cf.getPartecipationByUser(u).internal) {
}

Partecipation::Partecipation(User &u, CommonFund &cf, double c)
    : user(u), commonfund(cf),
      internal(u.getModel() == cf.getOwner().getModel() && u && cf &&
                       !Partecipation(u, cf)
                   ? new Data(u, cf, c)
                   : nullptr) {}

double Partecipation::changeCredit(double d) const {
  return internal->credit += d;
}

void Partecipation::accept(DBMS::Visitor *v) const {
  v->visitPartecipation(this);
}

const User &Partecipation::getUser() const { return user; }

const CommonFund &Partecipation::getCommonFund() const { return commonfund; }

double Partecipation::getCredit() const { return internal->getCredit(); }

double Partecipation::getInitCredit() const {
  return internal->getInitCredit();
}

bool Partecipation::operator<(const Partecipation &o) const {
  return commonfund < o.commonfund ||
         (!(o.commonfund < commonfund) && user < o.user);
}

Partecipation::operator bool() const { return internal; }