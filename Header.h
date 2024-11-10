#ifndef HEADER_H
#define HEADER_H

#include <QBoxLayout>
#include <QFrame>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QWidget>

#include <QAction>

#include "QPushButtonAR.h"

class Header : public QWidget{
    Q_OBJECT
private:
    QPushButtonAR* homeButton;
    QPushButtonAR* exitButton;
public:
    explicit Header(QWidget* parent = nullptr);
    void showHomeButton();
public slots:
    void showQuitConfirm();
signals:
    void closeAll();
    void showHomePage();
};

#endif // HEADER_H
