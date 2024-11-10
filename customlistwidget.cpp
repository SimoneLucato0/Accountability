#include "customlistwidget.h"

template <>
CustomListWidget::Box<const Register>::Box(const Register& r, QWidget* parent) : ItemBox(parent), item(r){
    setName(QString::fromStdString(r.getName()));
    setDate(QString::fromStdString("Ultima attività: " + DateToString(r.getLastActivity())));
    setAmount(r.getBalance());
}

template <>
CustomListWidget::Box<const Group>::Box(const Group& g, QWidget* parent) : ItemBox(parent), item(g){
    setName(QString::fromStdString(g.getName()));
    setDate(QString::fromStdString("Ultima attività: " + DateToString(g.getLastActivity())));
}

template <>
CustomListWidget::Box<const CommonFund>::Box(const CommonFund &cf, QWidget *parent) : ItemBox(parent), item(cf){
    setName(QString::fromStdString(cf.getName()));
    setDate(QString::fromStdString("Ultima attività: " + DateToString(cf.getLastActivity())));
    setAmount(cf.getBalance());
}

template <>
CustomListWidget::Box<UserMovement>::Box(const UserMovement&m, QWidget *parent) : ItemBox(parent), item(m){
    setAmount(m.getAmount());
    setName(QString::fromStdString(m.getDescription()));
    setDate(QString::fromStdString(DateToString(m.getTime())));
}

template <>
CustomListWidget::Box<DeepPtr<AbstractGroupMovement>>::Box(const DeepPtr<AbstractGroupMovement>&m, QWidget *parent) : ItemBox(parent), item(m){
    setAmount(m->calculateBalanceChange());
    setName(QString::fromStdString(m->getDescription()));
    setDate(QString::fromStdString(DateToString(m->getTime())));
}

template <class T>
const T& CustomListWidget::Box<T>::getItem() const{
    return item;
}

template <class T>
T& CustomListWidget::Box<T>::getItem(){
    return item;
}

template <class T, class U>
CustomListWidget::CustomListWidget(const olist<T>& s, U*, QWidget *parent) : QListWidget(parent){
    setCursor(QCursor(Qt::PointingHandCursor));
    setSelectionMode(QAbstractItemView::NoSelection);
    setSpacing(1);
    setStyleSheet("QListWidget::item:hover {background-color: rgba(67, 166, 40, 0.1)}");
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    refresh<T,U>(s);
}

template <class T, class U>
void CustomListWidget::refresh(const olist<T> &s){
    clear();
    for(typename olist<T>::const_iterator cit = s.begin(); cit != s.end(); ++cit){
        QListWidgetItem* i = new QListWidgetItem(this);
        Box<U>* box = new Box<U>(*cit, this);
        i->setSizeHint(box->minimumSize());
        addItem(i);
        setItemWidget(i, box);
    }
}

template <>
void CustomListWidget::refresh<const Subscription, const Group>(const olist<const Subscription>& s){
    clear();
    for(typename olist<const Subscription>::const_iterator cit = s.begin(); cit != s.end(); ++cit){
        QListWidgetItem* i = new QListWidgetItem(this);
        Box<const Group>* box = new Box<const Group>(cit->getGroup(), this);
        i->setSizeHint(box->minimumSize());
        addItem(i);
        setItemWidget(i, box);
    }
}

template <>
void CustomListWidget::refresh<const Partecipation, const CommonFund>(const olist<const Partecipation>& s){
    clear();
    for(typename olist<const Partecipation>::const_iterator cit = s.begin(); cit != s.end(); ++cit){
        QListWidgetItem* i = new QListWidgetItem(this);
        Box<const CommonFund>* box = new Box<const CommonFund>(cit->getCommonFund(), this);
        i->setSizeHint(box->minimumSize());
        addItem(i);
        setItemWidget(i, box);
    }
}

template <>
void CustomListWidget::refresh<UserMovement, UserMovement>(const olist<UserMovement>& s){
    clear();
    if(s.empty())
        return;
    typename olist<UserMovement>::const_iterator cit = s.end();
    do{
        --cit;
        QListWidgetItem* i = new QListWidgetItem(this);
        Box<UserMovement>* box = new Box<UserMovement>(*cit, this);
        i->setSizeHint(box->minimumSize());
        addItem(i);
        setItemWidget(i, box);
    }
    while(cit != s.begin());
}

template <>
void CustomListWidget::refresh<DeepPtr<AbstractGroupMovement>, DeepPtr<AbstractGroupMovement>>(const olist<DeepPtr<AbstractGroupMovement>>& s){
    clear();
    if(s.empty())
        return;
    typename olist<DeepPtr<AbstractGroupMovement>>::const_iterator cit = s.end();
    do{
        --cit;
        QListWidgetItem* i = new QListWidgetItem(this);
        Box<DeepPtr<AbstractGroupMovement>>* box = new Box<DeepPtr<AbstractGroupMovement>>(*cit, this);
        i->setSizeHint(box->minimumSize());
        addItem(i);
        setItemWidget(i, box);
    }
    while(cit != s.begin());
}

template
CustomListWidget::CustomListWidget<const Register, const Register>(const olist<const Register>& s, const Register*, QWidget* parent);

template
CustomListWidget::CustomListWidget<const Subscription, const Group>(const olist<const Subscription>& s, const Group*, QWidget* parent);

template
CustomListWidget::CustomListWidget<const CommonFund,const CommonFund>(const olist<const CommonFund>&s, const CommonFund*, QWidget* parent);

template
CustomListWidget::CustomListWidget<UserMovement, UserMovement>(const olist<UserMovement>& s, UserMovement*, QWidget* parent);

template
CustomListWidget::CustomListWidget<DeepPtr<AbstractGroupMovement>, DeepPtr<AbstractGroupMovement>>(const olist<DeepPtr<AbstractGroupMovement>>& s, DeepPtr<AbstractGroupMovement>*, QWidget* parent);

template
const Register& CustomListWidget::Box<const Register>::getItem();

template
const Group& CustomListWidget::Box<const Group>::getItem();

template
const CommonFund& CustomListWidget::Box<const CommonFund>::getItem();
