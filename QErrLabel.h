#ifndef QERRLABEL_H
#define QERRLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class QErrLabel : public QLabel{
    Q_OBJECT
public:
    QErrLabel(const QString& text = nullptr, QWidget* parent = nullptr);
};

#endif // QERRLABEL_H
