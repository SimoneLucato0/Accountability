#ifndef JSONDBMS_H
#define JSONDBMS_H
#include "dbms.h"
#include "olist.h"
#include <QJsonArray>
#include <QJsonObject>
#include <list>
#include <string>

class AbstractGroupMovement;
class AbstractMovement;

class JsonDBMS : public DBMS {
  enum mov_t { unknown, user_mov, fund_raise, common_expense };

  static std::string time_to_string(const time_t &t);
  static time_t string_to_time(const std::string &s);
  static std::string hash_to_string(const size_t &t);
  static size_t string_to_hash(const std::string &s);

  static void loadUsers(Model *m, const QJsonArray &uArr);
  static void loadRegisters(User &u, const QJsonArray &regArr);
  static void loadUserMovements(Register &r, const QJsonArray &movArr);
  static void loadGroups(Model *m, const QJsonArray &gArr);
  static void loadSubscriptions(Group &g, const QJsonArray &subArr);
  static void loadCommonFunds(Group &g, const QJsonArray &cfsArr);
  static void loadPartecipations(CommonFund &cf, const QJsonArray &partsArr);
  static void loadGroupMovements(CommonFund &cf, const QJsonArray &movArr);

public:
  class JsonVisitor : public DBMS::Visitor {
    static const std::string visitorVersion;
    std::list<QJsonObject> stack;

  public:
    JsonVisitor();
    void visitModel(const Model *m) override;
    void visitUser(const User *u, std::size_t pw_hash) override;
    void visitGroup(const Group *g) override;
    void visitSubscription(const Subscription *s) override;
    void visitRegister(const Register *r) override;
    void visitCommonFund(const CommonFund *cf) override;
    void visitPartecipation(const Partecipation *p) override;
    void visitAbstractMovement(const AbstractMovement *mv);
    void visitUserMovement(const UserMovement *um) override;
    void visitAbstractGroupMovement(const AbstractGroupMovement *mv);
    void visitCommonExpense(const CommonExpense *ce) override;
    void visitFundRaise(const FundRaise *fr) override;
    const QJsonObject &getJson() const;
  };
  JsonDBMS(std::string filename);

  void load(Model *m) override;
  void save(const Model *m, std::string f) override;
};

#endif
