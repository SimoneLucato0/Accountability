#include "QErrLabel.h"

QErrLabel::QErrLabel(const QString &text, QWidget *parent) : QLabel(text, parent){
    setFont(QFont("Helvetica", 9));
    setStyleSheet("QLabel{color: red}");
    setVisible(false);
}
