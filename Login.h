#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QScreen>
#include <QWidget>

#include <QResizeEvent>

#include "QErrLabel.h"
#include "QPushButtonAR.h"

class Login : public QWidget{
    Q_OBJECT
private:
    QErrLabel* userError;
    QLineEdit* userRequest;
    QErrLabel* passwordError;
    QLineEdit* passwordRequest;

    QErrLabel* userNotExistingError;
    QErrLabel* incorrectPasswordError;
public:
    virtual QSize minimumSizeHint() const override;

    Login(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* e) override;
public slots:
    void sendLogin();
    void showUserNotExisting();
    void showIncorrectPassword();
signals:
    void showInscriptionBox();
    void sendLoginInfo(const QString& email, const QString& password);
};

#endif // LOGIN_H
