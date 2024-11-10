#include "View.h"

void View::resizeEvent(QResizeEvent *event){
    if(l)
        l->setGeometry(event->size().width()/4, event->size().height()/3, event->size().width()/2, event->size().height()/2);
    else
        QWidget::resizeEvent(event);
}

View::View(QWidget* parent) : QWidget(parent), h(nullptr), l(nullptr), hp(nullptr), r(nullptr), g(nullptr), cf(nullptr), currentUser(){
    QSize s = qApp->screens()[0]->size();
    mainLayout = new QVBoxLayout(this);

    h = new Header(this);
    l = new Login(this);


    connect(h, &Header::closeAll, this, &View::close);
    connect(l, &Login::showInscriptionBox, this, &View::showInscriptionBox);

    mainLayout->addWidget(h, 0);
    mainLayout->addWidget(l, 1, Qt::AlignCenter);
    mainLayout->setSpacing(0);

    QSize hs = h->size();
    h->resize(hs.width(), hs.height()/2);

    setMinimumSize(s.width()/2, 2*s.height()/3);
    setContentsMargins(0,0,0,0);
    setFocusPolicy(Qt::StrongFocus);
    setWindowTitle("Login");
}

void View::setController(Controller *controller){
    c = controller;
    connect(h, &Header::closeAll, [](){});
    connect(l, &Login::sendLoginInfo, c, &Controller::logIn);
}

void View::showUserNotExisting(){
    l->showUserNotExisting();
}

void View::showUserAlreadyExisting(){
    i->showUserAlreadyExisting();
}

void View::showIncorrectPassword(){
    l->showIncorrectPassword();
}

void View::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape)
        QMetaObject::invokeMethod(h, "showQuitConfirm");
    if(l && e->key() == Qt::Key_Return)
        QMetaObject::invokeMethod(l, "sendLogin");
}

void View::showHomePage(User &u){
    currentUser = u;
    delete l;
    l = nullptr;
    olist<const User> uig;
    uig.insert(u);
    hp = new HomePage(u, c->getUserDifference(c->getUserList(), uig), this);
    mainLayout->addWidget(hp);

    h->showHomeButton();
    connect(h, &Header::showHomePage, [this](){
        hideAll();
        hp->show();
    });

    connect(hp, &HomePage::sendAddRegisterInfo, c, &Controller::addRegister);
    connect(hp, &HomePage::sendAddGroupInfo, c, &Controller::addGroup);
    connect(hp, &HomePage::showRegister, this, &View::showRegisterView);
    connect(hp, &HomePage::showGroup, this, &View::showGroupView);
    connect(hp, &HomePage::userListRequest, [this](){hp->setUserList(c->getUserList());});

    setWindowTitle("Home Page");
}

void View::hideAll(){
    if (r && r->isVisible())
        r->hide();
    else if (g && g->isVisible())
        g->hide();
    else if (cf && cf->isVisible())
        cf->hide();
}

void View::showInscriptionBox(){
    i = new Inscription(this);

    connect(i, &Inscription::sendInscriptionInfo, c, &Controller::createUser);
}

void View::showRegisterView(const Register &reg){
    r = new RegisterView(reg, this);
    mainLayout->addWidget(r);
    hp->hide();

    connect(r, &RegisterView::showHomePage, this, &View::returnToHomePage);
    connect(r, &RegisterView::sendAddMovement, c, &Controller::addUserMovement);

    setWindowTitle(tr(reg.getName().c_str()));
}

void View::showGroupView(const Group& gr){
    g = new GroupView(gr, currentUser, this);
    mainLayout->addWidget(g);
    hp->hide();

    connect(g, &GroupView::showHomePage, this, &View::returnToHomePage);
    connect(g, &GroupView::showCommonFund, this, &View::showCommonFundView);
    connect(g, &GroupView::sendAddCommonFund,
            [this](Group& g, const QString& name, double balance, olist<QString> users)
            {c->addCommonFund(g, currentUser, name, balance, users);});
   connect(g, &GroupView::sendAddUsers, c, &Controller::addUserToGroup);
   connect(g, &GroupView::userDifferenceRequest, [this](const olist<const User>& part){g->setUserDifference(c->getUserDifference(c->getUserList(), part));});

   setWindowTitle(tr(gr.getName().c_str()));
}

void View::showCommonFundView(const CommonFund& commonFund){
    cf = new CommonFundView(commonFund, this);
    mainLayout->addWidget(cf);
    g->hide();

    connect(cf, &CommonFundView::showGroupView, [this](){
        g->show();
        g->resetList();
    });
    connect(cf, &CommonFundView::sendAddCommonExpense, [this]
            (CommonFund& cf, double amount, const QString& description, olist<User> users,
            std::map<QString, double> personalExpense,
            std::map<QString, double> personalShares, const QString& note, time_t ts)
            {c->addCommonExpense(cf, currentUser, amount, description, users, personalExpense, personalShares, note, ts);});
    connect(cf, &CommonFundView::sendAddFundRaise,
            [this](CommonFund& cf, const QString& description, std::map<QString, double> contributions, const QString& note, time_t ts)
            {c->addFundRaise(cf, currentUser, description, contributions, note, ts);});
    connect(cf, &CommonFundView::sendAddUsers, c, &Controller::addUserToCommonFund);
    connect(cf, &CommonFundView::userDifferenceRequest, [this](olist<const User> part){cf->setUserDifference(c->getUserDifference(g->getUsers(), part));});

    setWindowTitle(tr(commonFund.getName().c_str()));
}

void View::returnToHomePage(){
    hp->show();
    hp->resetLists();
}







