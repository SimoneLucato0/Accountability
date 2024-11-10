#include "UserFilterList.h"

UserFilterList::UserFilterList(const olist<const User>& users, QWidget *parent) : QWidget(parent){
    QVBoxLayout* userListLayout = new QVBoxLayout(this);
    QLineEdit* insertName = new QLineEdit();
    list = new QListView();
    proxy = new QSortFilterProxyModel();
    model = new QStandardItemModel();

    setUsers(users);

    list->setModel(proxy);
    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    insertName->setPlaceholderText("Filtra");

    userListLayout->addWidget(insertName);
    userListLayout->addWidget(list);
    userListLayout->setContentsMargins(0,0,0,0);
    userListLayout->setSpacing(5);

    connect(insertName, &QLineEdit::textChanged, [=](const QString& update){proxy->setFilterWildcard(update);});
}

olist<QString> UserFilterList::getSelectedUsers() const{
    olist<QString> aux;
    for(int i = 0; i < model->rowCount(); ++i){
        if (model->item(i)->checkState() == Qt::Checked)
            aux.insert(QString(model->item(i, 0)->data(Qt::DisplayRole).toString()));
    }
    return aux;
}

void UserFilterList::setUsers(const olist<const User>& users){
    int i = 0;
    for (olist<const User>::const_iterator cit = users.begin(); cit != users.end(); ++cit){
        QStandardItem* item = new QStandardItem(QString::fromStdString(cit->getUsername()));

        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->setItem(i, 0, item);
        ++i;
    }
}
