#ifndef USERINPUT_H
#define USERINPUT_H

#include <QBoxLayout>
#include <QDoubleValidator>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QWidget>

#include "olist.h"
#include <exception>
#include "float.h"

#include "partecipation.h"

class UserInput : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;

    olist<const Partecipation> u;
public:
    explicit UserInput(olist<const Partecipation> us, QWidget* parent = nullptr);
    UserInput(const UserInput& u, QWidget* parent = nullptr);
    void clear();
    bool isEmpty() const;
    std::map<QString, QString> getResults() const;
    olist<const Partecipation> getPartecipations() const;
    void setLayout(olist<const Partecipation> users);
};

#endif // USERINPUT_H
