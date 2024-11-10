#include "QPushButtonAR.h"

void QPushButtonAR::paintEvent(QPaintEvent *e){
    QWidget::paintEvent(e);
    QStylePainter painter(this);

    QStyleOptionButton opt;
    initStyleOption(&opt);

    QRect r = opt.rect;

    int h = r.height();
    int w = r.width();
    int iconSize = qMax(qMin(h, w) - 2 * padding, minSize);

    opt.iconSize = QSize(iconSize, iconSize);

    painter.drawControl(QStyle::CE_PushButton, opt);
}

QPushButtonAR::QPushButtonAR(const QString &text, QWidget *parent) : QPushButton(text, parent), minSize(8), padding(4){
    setCursor(QCursor(Qt::PointingHandCursor));
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    setStyleSheet("QPushButton{background: transparent; border-style: outset;}"
                  "QPushButton:focus { border: none; outline: none; }");
}
