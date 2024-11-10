#ifndef QPUSHBUTTONAR_H
#define QPUSHBUTTONAR_H

#include <QObject>
#include <QPushButton>
#include <QPaintEvent>
#include <QStyleOptionButton>
#include <QStylePainter>
#include <QWidget>

class QPushButtonAR : public QPushButton{
    Q_OBJECT
private:
    int minSize;
    int padding;

    void paintEvent(QPaintEvent* e) override;
public:
    QPushButtonAR(const QString& text = "", QWidget* parent = nullptr);
};

#endif // QPUSHBUTTONAR_H
