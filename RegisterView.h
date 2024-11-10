#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QBoxLayout>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QWhatsThis>

#include <float.h>

#include "QErrLabel.h"
#include "InnerPage.h"
#include "abstractmovement.h"
#include "usermovement.h"
#include "register.h"
#include "olist.h"

class RegisterView : public InnerPage{
    Q_OBJECT
private:
    Register reg;
public:
    explicit RegisterView(const Register& a, QWidget* parent = nullptr);
public slots:
    void showAddMovement();
signals:
    void showHomePage();
    void showDeleteConfirm();
    void sendAddMovement(Register& r, double amount, const QString& description, const QString& note, time_t timestamp);
};

#endif // RegisterVIEW_H
