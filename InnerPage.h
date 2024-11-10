#ifndef INNERPAGE_H
#define INNERPAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QObject>
#include <QWidget>

#include "olist.h"
#include "customlistwidget.h"
#include "ItemBox.h"
#include "QPushButtonAR.h"


class InnerPage : public QWidget{
    Q_OBJECT
protected:
    QPushButtonAR* const backButton;
    QLabel* const name;
    QLabel* const balance;
    QPushButton* const addButtonL;
    QHBoxLayout* const buttonLayout;
    CustomListWidget* const list;

    void setBalance(const double& b);
public:
    explicit InnerPage(CustomListWidget* l, QWidget* parent = nullptr);
};

#endif // INNERPAGE_H
