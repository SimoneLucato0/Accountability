#include "subscription.h"

#include "model.h"

Subscription::Subscription() : user(), group(), sub_time() {}

Subscription::Subscription(const User &u, const Group &g)
    : user(), group(), sub_time() {
  *this = g.getSubscriptionByUser(u);
}

Subscription::Subscription(User &u, Group &g, std::time_t st)
    : user(u), group(g), sub_time(st) {
  if (user.getModel() == group.getModel() && !Subscription(u, g)) {
    u.getModel()->ownSubscription(*this);
  }
}

void Subscription::accept(DBMS::Visitor *v) const {
  v->visitSubscription(this);
}

const User &Subscription::getUser() const { return user; }

const Group &Subscription::getGroup() const { return group; }

std::time_t Subscription::getSubTime() const { return sub_time; }

bool Subscription::operator<(const Subscription &o) const {
  return group < o.group || (!(o.group < group) && user < o.user);
}

Subscription::operator bool() const { return user && group; }