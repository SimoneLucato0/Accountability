#include "jsondbms.h"

#include "abstractgroupmovement.h"
#include "abstractmovement.h"
#include "commonexpense.h"
#include "commonfund.h"
#include "fundraise.h"
#include "group.h"
#include "model.h"
#include "partecipation.h"
#include "register.h"
#include "subscription.h"
#include "deep_ptr.h"
#include "user.h"
#include "usermovement.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <iomanip>
#include <sstream>

std::string JsonDBMS::time_to_string(const time_t &t) {
  std::tm tmb = *std::localtime(&t);
  std::ostringstream os;
  os << (tmb.tm_isdst ? "1 " : "0 ") << std::put_time(&tmb, "%F %T");
  return os.str();
}

time_t JsonDBMS::string_to_time(const std::string &s) {
  std::istringstream is(s);
  int isdst;
  std::tm t;
  is >> isdst >> std::get_time(&t, "%Y-%m-%d %T");
  t.tm_isdst = isdst;
  return mktime(&t);
}

std::string JsonDBMS::hash_to_string(const size_t &t) {
  std::ostringstream os;
  os << t;
  return os.str();
}

size_t JsonDBMS::string_to_hash(const std::string &s) {
  std::istringstream is(s);
  size_t t;
  is >> t;
  return t;
}

void JsonDBMS::loadUsers(Model *m, const QJsonArray &uArr) {
  for (auto cit = uArr.begin(); cit != uArr.end(); ++cit) {
    QJsonObject uObj = cit->toObject();

    if (!uObj.isEmpty()) {
      if (uObj["username"].isString() && uObj["name"].isString() &&
          uObj["surname"].isString() && uObj["pw_hash"].isString()) {
        User u(m, uObj["username"].toString().toStdString(),
               uObj["name"].toString().toStdString(),
               uObj["surname"].toString().toStdString(),
               string_to_hash(uObj["pw_hash"].toString().toStdString()));

        if (uObj["registers"].isArray()) {
          QJsonArray regArr = uObj["registers"].toArray();
          loadRegisters(u, regArr);
        }
      }
    }
  }
}

void JsonDBMS::loadRegisters(User &u, const QJsonArray &regArr) {
  for (auto cit = regArr.begin(); cit != regArr.end(); ++cit) {
    QJsonObject regObj = cit->toObject();

    if (!regObj.isEmpty()) {
      if (regObj["name"].isString() && regObj["init_balance"].isDouble() &&
          regObj["creation_time"].isString()) {
        Register r(
            u, regObj["name"].toString().toStdString(),
            regObj["init_balance"].toDouble(),
            string_to_time(regObj["creation_time"].toString().toStdString()));

        if (regObj["movements"].isArray()) {
          QJsonArray movArr = regObj["movements"].toArray();
          loadUserMovements(r, movArr);
        }
      }
    }
  }
}

void JsonDBMS::loadUserMovements(Register &r, const QJsonArray &movArr) {
  for (auto cit = movArr.begin(); cit != movArr.end(); ++cit) {
    QJsonObject mov = cit->toObject();

    if (!mov.isEmpty()) {
      if (mov["type"].toInt() == mov_t::user_mov && mov["amount"].isDouble() &&
          mov["description"].isString() && mov["note"].isString() &&
          mov["time"].isString() && mov["insertion_time"].isString()) {
        UserMovement(
            r, mov["amount"].toDouble(),
            mov["description"].toString().toStdString(),
            mov["note"].toString().toStdString(),
            string_to_time(mov["time"].toString().toStdString()),
            string_to_time(mov["insertion_time"].toString().toStdString()));
      }
    }
  }
}

void JsonDBMS::loadGroups(Model *m, const QJsonArray &gArr) {
  for (auto cit = gArr.begin(); cit != gArr.end(); ++cit) {
    QJsonObject gObj = cit->toObject();

    if (!gObj.isEmpty()) {
      if (gObj["name"].isString() && gObj["description"].isString() &&
          gObj["founder"].isString() && gObj["time"].isString()) {
        User u(m, gObj["founder"].toString().toStdString());
        Group g(m, gObj["name"].toString().toStdString(),
                gObj["description"].toString().toStdString(), u,
                string_to_time(gObj["time"].toString().toStdString()));

        if (gObj["subscriptions"].isArray()) {
          loadSubscriptions(g, gObj["subscriptions"].toArray());
        }

        if (gObj["commonfunds"].isArray()) {
          loadCommonFunds(g, gObj["commonfunds"].toArray());
        }
      }
    }
  }
}

void JsonDBMS::loadSubscriptions(Group &g, const QJsonArray &subArr) {
  for (auto cit = subArr.begin(); cit != subArr.end(); ++cit) {
    QJsonObject subObj = cit->toObject();

    if (!subObj.isEmpty()) {
      if (subObj["user"].isString() && subObj["time"].isString()) {
        User u(g.getModel(), subObj["user"].toString().toStdString());
        Subscription(u, g,
                     string_to_time(subObj["time"].toString().toStdString()));
      }
    }
  }
}

void JsonDBMS::loadCommonFunds(Group &g, const QJsonArray &cfsArr) {
  for (auto cit = cfsArr.begin(); cit != cfsArr.end(); ++cit) {
    QJsonObject cfObj = cit->toObject();

    if (!cfObj.isEmpty()) {
      if (cfObj["founder"].isString() && cfObj["name"].isString() &&
          cfObj["init_balance"].isDouble() &&
          cfObj["creation_time"].isString()) {
        User u(g.getModel(), cfObj["founder"].toString().toStdString());
        CommonFund cf(
            g, u, cfObj["name"].toString().toStdString(),
            cfObj["init_balance"].toDouble(),
            string_to_time(cfObj["creation_time"].toString().toStdString()));

        if (cfObj["partecipations"].isArray()) {
          loadPartecipations(cf, cfObj["partecipations"].toArray());
        }

        if (cfObj["movements"].isArray()) {
          loadGroupMovements(cf, cfObj["movements"].toArray());
        }
      }
    }
  }
}

void JsonDBMS::loadPartecipations(CommonFund &cf, const QJsonArray &partsArr) {
  for (auto cit = partsArr.begin(); cit != partsArr.end(); ++cit) {
    QJsonObject parObj = cit->toObject();

    if (!parObj.isEmpty()) {
      if (parObj["user"].isString() && parObj["init_credit"].isDouble()) {
        User u(cf.getOwner().getModel(),
               parObj["user"].toString().toStdString());
        Partecipation(u, cf, parObj["init_credit"].toDouble());
      }
    }
  }
}

void JsonDBMS::loadGroupMovements(CommonFund &cf, const QJsonArray &movArr) {
  for (auto mit = movArr.begin(); mit != movArr.end(); ++mit) {
    QJsonObject movObj = mit->toObject();

    if (!movObj.isEmpty()) {
      if (movObj["amount"].isDouble() && movObj["inserted_by"].isString() &&
          movObj["description"].isString() && movObj["note"].isString() &&
          movObj["time"].isString() && movObj["insertion_time"].isString()) {

        int type = movObj["type"].toInt();
        Model *model = cf.getOwner().getModel();
        switch (type) {
        case mov_t::fund_raise:

          if (movObj["collected"].isObject()) {

            std::map<User, double> collected;
            QJsonObject colObj = movObj["collected"].toObject();
            for (auto it = colObj.begin(); it != colObj.end(); ++it) {
              if (it.value().isDouble())
                collected.insert({User(model, it.key().toStdString()),
                                  it.value().toDouble()});
            }

            FundRaise(
                cf, User(model, movObj["inserted_by"].toString().toStdString()),
                movObj["description"].toString().toStdString(), collected,
                movObj["note"].toString().toStdString(),
                string_to_time(movObj["time"].toString().toStdString()),
                string_to_time(
                    movObj["insertion_time"].toString().toStdString()));
          }
          break;

        case mov_t::common_expense:

          if (movObj["involved_users"].isArray() &&
              movObj["personal_expenses"].isObject() &&
              movObj["personal_payments"].isObject()) {

            olist<User> involved_users;
            QJsonArray iuArr = movObj["involved_users"].toArray();
            for (auto iuit = iuArr.begin(); iuit != iuArr.end(); ++iuit) {
              involved_users.insert(
                  User(model, iuit->toString().toStdString()));
            }

            std::map<User, double> personal_expenses;
            QJsonObject peObj = movObj["personal_expenses"].toObject();
            for (auto peit = peObj.begin(); peit != peObj.end(); ++peit) {
              if (peit.value().isDouble())
                personal_expenses.insert({User(model, peit.key().toStdString()),
                                          peit.value().toDouble()});
            }

            std::map<User, double> personal_payments;
            QJsonObject ppObj = movObj["personal_payments"].toObject();
            for (auto ppit = ppObj.begin(); ppit != ppObj.end(); ++ppit) {
              if (ppit.value().isDouble())
                personal_payments.insert({User(model, ppit.key().toStdString()),
                                          ppit.value().toDouble()});
            }

            CommonExpense(
                cf, movObj["amount"].toDouble(),
                User(model, movObj["inserted_by"].toString().toStdString()),
                movObj["description"].toString().toStdString(), involved_users,
                personal_expenses, personal_payments,
                movObj["note"].toString().toStdString(),
                string_to_time(movObj["time"].toString().toStdString()),
                string_to_time(
                    movObj["insertion_time"].toString().toStdString()));
          }
          break;
        }
      }
    }
  }
}

JsonDBMS::JsonVisitor::JsonVisitor() : stack() {}

void JsonDBMS::JsonVisitor::visitModel(const Model *m) {

  QJsonArray usersArr;
  auto users = m->getUsers();
  for (auto uit = users.begin(); uit != users.end(); ++uit) {
    if (*uit) {
      uit->accept(this);
      usersArr.append(stack.back());
      stack.pop_back();
    }
  }

  QJsonArray groupsArr;
  auto groups = m->getGroups();
  for (auto git = groups.begin(); git != groups.end(); ++git) {
    if (*git) {
      git->accept(this);
      groupsArr.append(stack.back());
      stack.pop_back();
    }
  }

  QJsonObject modelObj({{"users", usersArr}, {"groups", groupsArr}});
  stack.push_back(modelObj);
}

void JsonDBMS::JsonVisitor::visitUser(const User *u, std::size_t pw_hash) {
  QJsonObject userObj;
  userObj["username"] = u->getUsername().c_str();
  userObj["name"] = u->getName().c_str();
  userObj["surname"] = u->getSurname().c_str();
  userObj["pw_hash"] = hash_to_string(pw_hash).c_str();

  // QJsonArray subsArr;
  // const olist<Subscription> &subs = u->getSubscriptions();
  // for (auto sit = subs.begin(); sit != subs.end(); ++sit) {
  //   sit->accept(this);
  //   subsArr.append(stack.back());
  //   stack.pop_back();
  // }
  // userObj["subscriptions"] = subsArr;

  // QJsonArray partsArr;
  // const olist<Partecipation> &parts = u->getPartecipations();
  // for (auto pit = parts.begin(); pit != parts.end(); ++pit) {
  //   pit->accept(this);
  //   partsArr.append(stack.back());
  //   stack.pop_back();
  // }
  // userObj["partecipations"] = partsArr;

  QJsonArray regsArr;
  auto regs = u->getRegisters();
  for (auto rit = regs.begin(); rit != regs.end(); ++rit) {
    if (*rit) {
      rit->accept(this);
      regsArr.append(stack.back());
      stack.pop_back();
    }
  }
  userObj["registers"] = regsArr;
  stack.push_back(userObj);
}

void JsonDBMS::JsonVisitor::visitGroup(const Group *g) {
  QJsonObject groupObj;
  groupObj["name"] = g->getName().c_str();
  groupObj["description"] = g->getDescription().c_str();
  groupObj["founder"] = g->getFounder().getUsername().c_str();
  groupObj["time"] = time_to_string(g->getCreationTime()).c_str();

  QJsonArray cfsArr;
  auto cfs = g->getCommonFunds();
  for (auto cfit = cfs.begin(); cfit != cfs.end(); ++cfit) {
    if (*cfit) {
      cfit->accept(this);
      cfsArr.append(stack.back());
      stack.pop_back();
    }
  }
  groupObj["commonfunds"] = cfsArr;

  QJsonArray subsArr;
  auto subs = g->getSubscriptions();
  for (auto sit = subs.begin(); sit != subs.end(); ++sit) {
    if (*sit) {
      sit->accept(this);
      subsArr.append(stack.back());
      stack.pop_back();
    }
  }
  groupObj["subscriptions"] = subsArr;
  stack.push_back(groupObj);
}

void JsonDBMS::JsonVisitor::visitSubscription(const Subscription *s) {
  QJsonObject subObj;
  subObj["user"] = s->getUser().getUsername().c_str();
  subObj["time"] = time_to_string(s->getSubTime()).c_str();
  stack.push_back(subObj);
}

void JsonDBMS::JsonVisitor::visitRegister(const Register *r) {
  QJsonObject regObj;
  regObj["name"] = r->getName().c_str();
  regObj["init_balance"] = r->getInitBalance();
  regObj["creation_time"] = time_to_string(r->getCreationTime()).c_str();

  QJsonArray movsArr;
  const olist<UserMovement> &movs = r->getMovements();
  for (auto mit = movs.begin(); mit != movs.end(); ++mit) {
    if (*mit) {
      mit->accept(this);
      movsArr.append(stack.back());
      stack.pop_back();
    }
  }
  regObj["movements"] = movsArr;
  stack.push_back(regObj);
}

void JsonDBMS::JsonVisitor::visitCommonFund(const CommonFund *cf) {
  QJsonObject cfObj;
  cfObj["name"] = cf->getName().c_str();
  cfObj["owner"] = cf->getOwner().getName().c_str();
  cfObj["founder"] = cf->getFounder().getUsername().c_str();
  cfObj["init_balance"] = cf->getInitBalance();
  cfObj["creation_time"] = time_to_string(cf->getCreationTime()).c_str();

  QJsonArray movsArr;
  const olist<DeepPtr<AbstractGroupMovement>> &movs = cf->getMovements();
  for (auto mit = movs.begin(); mit != movs.end(); ++mit) {
    if (*mit) {
      mit->get()->accept(this);
      movsArr.append(stack.back());
      stack.pop_back();
    }
  }
  cfObj["movements"] = movsArr;

  QJsonArray partsArr;
  auto parts = cf->getPartecipations();
  for (auto pit = parts.begin(); pit != parts.end(); ++pit) {
    if (*pit) {
      pit->accept(this);
      partsArr.append(stack.back());
      stack.pop_back();
    }
  }
  cfObj["partecipations"] = partsArr;
  stack.push_back(cfObj);
}

void JsonDBMS::JsonVisitor::visitPartecipation(const Partecipation *p) {
  QJsonObject partObj;
  partObj["user"] = p->getUser().getUsername().c_str();
  partObj["init_credit"] = p->getInitCredit();
  stack.push_back(partObj);
}

void JsonDBMS::JsonVisitor::visitAbstractMovement(const AbstractMovement *am) {
  QJsonObject amObj;
  amObj["type"] = mov_t::unknown;
  amObj["amount"] = am->getAmount();
  amObj["description"] = am->getDescription().c_str();
  amObj["note"] = am->getNote().c_str();
  amObj["time"] = time_to_string(am->getTime()).c_str();
  amObj["insertion_time"] = time_to_string(am->getInsertionTime()).c_str();
  amObj["inserted_by"] = am->getInsertedBy().getUsername().c_str();
  stack.push_back(amObj);
}

void JsonDBMS::JsonVisitor::visitUserMovement(const UserMovement *um) {
  visitAbstractMovement(um);
  QJsonObject umObj(getJson());
  stack.pop_back();
  umObj["type"] = user_mov;
  stack.push_back(umObj);
}

void JsonDBMS::JsonVisitor::visitAbstractGroupMovement(
    const AbstractGroupMovement *agm) {
  visitAbstractMovement(agm);
  QJsonObject agmObj(getJson());
  stack.pop_back();

  QJsonObject ucgObj;
  const std::map<User, double> &ucg = agm->getUserCreditChange();
  for (auto ucgit = ucg.begin(); ucgit != ucg.end(); ++ucgit) {
    ucgObj[ucgit->first.getUsername().c_str()] = ucgit->second;
  }
  agmObj["user_credit_change"] = ucgObj;
  stack.push_back(agmObj);
}

void JsonDBMS::JsonVisitor::visitCommonExpense(const CommonExpense *ce) {
  visitAbstractGroupMovement(ce);
  QJsonObject ceObj(getJson());
  stack.pop_back();
  ceObj["type"] = mov_t::common_expense;

  QJsonArray iuArr;
  const olist<User> &iu = ce->getInvolvedUsers();
  for (auto iuit = iu.begin(); iuit != iu.end(); ++iuit) {
    iuArr.append(iuit->getUsername().c_str());
  }
  ceObj["involved_users"] = iuArr;

  QJsonObject peObj;
  const std::map<User, double> &pe = ce->getPersonalExpenses();
  for (auto peit = pe.begin(); peit != pe.end(); ++peit) {
    peObj[peit->first.getUsername().c_str()] = peit->second;
  }
  ceObj["personal_expenses"] = peObj;

  QJsonObject ppObj;
  const std::map<User, double> &pp = ce->getPersonalPayments();
  for (auto ppit = pp.begin(); ppit != pp.end(); ++ppit) {
    ppObj[ppit->first.getUsername().c_str()] = ppit->second;
  }
  ceObj["personal_payments"] = ppObj;
  stack.push_back(ceObj);
}

void JsonDBMS::JsonVisitor::visitFundRaise(const FundRaise *fr) {
  visitAbstractGroupMovement(fr);
  QJsonObject frObj(getJson());
  stack.pop_back();
  frObj["type"] = mov_t::fund_raise;

  QJsonObject coObj;
  const std::map<User, double> &co = fr->getCollected();
  for (auto coit = co.begin(); coit != co.end(); ++coit) {
    coObj[coit->first.getUsername().c_str()] = coit->second;
  }
  frObj["collected"] = coObj;
  stack.push_back(frObj);
}

const QJsonObject &JsonDBMS::JsonVisitor::getJson() const {
  return stack.back();
}

JsonDBMS::JsonDBMS(std::string filename)
    : DBMS(filename.substr(filename.find_last_of(".") + 1) == "json"
               ? filename
               : filename.append(".json")) {}

void JsonDBMS::load(Model *m) {
  if (QFile::exists(filename.c_str())) {
    QFile file(filename.c_str());
    if (file.open(QIODevice::ReadOnly)) {
      QString str = file.readAll();
      file.close();
      QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
      if (doc.isObject()) {
        QJsonObject mObj = doc.object();
        if (mObj["users"].isArray() && mObj["groups"].isArray()) {
          QJsonArray uArr = mObj["users"].toArray();
          loadUsers(m, uArr);
          QJsonArray gArr = mObj["groups"].toArray();
          loadGroups(m, gArr);
        }
      }
    }
  }
}

void JsonDBMS::save(const Model *m, std::string f) {
  if (m) {
    JsonVisitor *v = new JsonVisitor();
    m->accept(v);
    QJsonDocument saveDoc(v->getJson());
    delete v;

    QFile saveFile(f.c_str());
    if (saveFile.open(QIODevice::WriteOnly)) {
      saveFile.write(saveDoc.toJson());
    }
  }
}
