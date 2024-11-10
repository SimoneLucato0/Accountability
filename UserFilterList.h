#ifndef USERFILTERLIST_H
#define USERFILTERLIST_H

#include <QLineEdit>
#include <QListView>
#include <QObject>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "olist.h"
#include "user.h"

class UserFilterList : public QWidget{
    Q_OBJECT
private:
    QStandardItemModel* model;
    QSortFilterProxyModel* proxy;
    QListView* list;
public:
    UserFilterList(const olist<const User>& users, QWidget* parent = nullptr);
    olist<QString> getSelectedUsers() const;
    void setUsers(const olist<const User>& users);
};

#endif // USERFILTERLIST_H
