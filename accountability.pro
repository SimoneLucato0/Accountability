QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CommonFundView.cpp \
    Controller.cpp \
    DateToString.cpp \
    GroupView.cpp \
    Header.cpp \
    HomePage.cpp \
    InnerPage.cpp \
    Inscription.cpp \
    ItemBox.cpp \
    Login.cpp \
    QErrLabel.cpp \
    QPushButtonAR.cpp \
    RegisterView.cpp \
    UserFilterList.cpp \
    UserInput.cpp \
    View.cpp \
    abstractaccount.cpp \
    abstractgroupmovement.cpp \
    abstractmovement.cpp \
    commonexpense.cpp \
    commonfund.cpp \
    customlistwidget.cpp \
    dbms.cpp \
    fundraise.cpp \
    group.cpp \
    jsondbms.cpp \
    main.cpp \
    model.cpp \
    partecipation.cpp \
    register.cpp \
    subscription.cpp \
    user.cpp \
    usermovement.cpp

HEADERS += \
    CommonFundView.h \
    Controller.h \
    DateToString.h \
    GroupView.h \
    Header.h \
    HomePage.h \
    InnerPage.h \
    Inscription.h \
    ItemBox.h \
    Login.h \
    QErrLabel.h \
    QPushButtonAR.h \
    RegisterView.h \
    UserFilterList.h \
    UserInput.h \
    View.h \
    abstractaccount.h \
    abstractgroupmovement.h \
    abstractmovement.h \
    accountinterface.h \
    commonexpense.h \
    commonfund.h \
    customlistwidget.h \
    dbms.h \
    deep_ptr.h \
    fundraise.h \
    group.h \
    jsondbms.h \
    model.h \
    movementinterface.h \
    olist.h \
    partecipation.h \
    register.h \
    serializable.h \
    subscription.h \
    user.h \
    usermovement.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
