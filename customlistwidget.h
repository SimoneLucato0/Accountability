#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QCursor>
#include <QListWidget>
#include <QWidget>

#include "abstractgroupmovement.h"
#include "commonfund.h"
#include "group.h"
#include "partecipation.h"
#include "register.h"
#include "subscription.h"
#include "usermovement.h"
#include "DateToString.h"
#include "ItemBox.h"


class CustomListWidget : public QListWidget{
public:
    template <class T>
    class Box : public ItemBox{
    private:
        T item;
    public:
        explicit Box(const T& t, QWidget* parent = nullptr);
        const T& getItem() const;
        T& getItem();
    };
    template <class T, class U = T>
    explicit CustomListWidget(const olist<T>& s = olist<T>(), U* = nullptr, QWidget* parent = nullptr);
    template <class T, class U = T>
    void refresh(const olist<T>& s);
};


#endif // CUSTOMLISTWIDGET_H
