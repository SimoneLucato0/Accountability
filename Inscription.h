#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QScreen>
#include <QVBoxLayout>
#include <QWidget>

#include "QErrLabel.h"

class Inscription : public QWidget{
    Q_OBJECT
private:
    QErrLabel* nameError;
    QLineEdit* nameRequest;
    QErrLabel* surnameError;
    QLineEdit* surnameRequest;
    QErrLabel* usernameError;
    QLineEdit* usernameRequest;
    QErrLabel* passwordError;
    QLineEdit* passwordRequest;

    QFrame* inscriptionFrame;
public:
    explicit Inscription(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* e) override;
    void showUserAlreadyExisting();
public slots:
    void sendInscription();
signals:
    void sendInscriptionInfo(const QString& name, const QString& surname, const QString& user, const QString& password);
};

#endif // INSCRIPTION_H
