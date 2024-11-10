#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <QResizeEvent>
#include <QBoxLayout>
#include <QLabel>
#include <QObject>
#include <QWidget>

class ItemBox : public QWidget{
    Q_OBJECT
    QLabel* name;
    QLabel* date;
    QLabel* amount;

    QFrame* itemFrame;
protected:
    void resizeEvent(QResizeEvent *event);

    void setName(const QString& n);
    void setDate(const QString& d);
    void setAmount(const double& a);
public:
    explicit ItemBox(QWidget* parent = nullptr);
};

#endif // ITEMBOX_H
