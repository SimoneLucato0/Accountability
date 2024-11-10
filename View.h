#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QObject>
#include <QScreen>
#include <QWidget>

#include <QResizeEvent>

#include "RegisterView.h"
#include "CommonFundView.h"
#include "GroupView.h"
#include "Header.h"
#include "Login.h"
#include "Inscription.h"
#include "HomePage.h"

#include "Controller.h"
#include "user.h"
#include "usermovement.h"

class Controller;

class View : public QWidget{
    Q_OBJECT
private:
    Header* h;
    Login* l;
    Inscription* i;
    HomePage* hp;
    RegisterView* r;
    GroupView* g;
    CommonFundView* cf;

    Controller* c;
    User currentUser;
    QVBoxLayout* mainLayout;
protected:
    void resizeEvent(QResizeEvent *event) override;
public:
    explicit View(QWidget* parent = nullptr);
    void hideAll();
    void keyPressEvent(QKeyEvent* e) override;
    void showHomePage(User& u);
    void setController(Controller* c);
    void showIncorrectPassword();
    void showUserNotExisting();
    void showUserAlreadyExisting();
public slots:
    void returnToHomePage();
    void showInscriptionBox();
    void showRegisterView(const Register& reg);
    void showGroupView(const Group &gr);
    void showCommonFundView(const CommonFund& commonFund);
signals:
    void sendInscriptionInfo(const QString& name, const QString& surname, const QString& username, const QString& password);
    void sendAddRegisterInfo(const QString& name, const QString& amount = "", const QString& description = "", const QString& note = "");
    void sendAddGroupInfo(const QString& name, const QString& description = "", const olist<QString> users = olist<QString>());
};

#endif // VIEW_H
